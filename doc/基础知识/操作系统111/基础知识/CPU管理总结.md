# CPU管理总结  


## 实现在屏幕上交替打印字母A和B

1.用户代码  
![image](https://user-images.githubusercontent.com/58176267/157414749-293d8cb3-3e6b-4655-a49b-7393633c9de0.png)  

![image](https://user-images.githubusercontent.com/58176267/157414630-131b52a2-f49c-4736-86b8-4cbc9b9ce1b9.png)  

用户代码的汇编代码如上，将中断调用号__NR_fork赋值给eax 并调用系统中断int 0x80  中断处理中创建子进程，然后会将子进程TSS中的eax置为0，接下来将物理寄存器eax赋值给res，如果子进程创建成功，并且父进程系统调用中经过阻塞后切换到了子进程(eax = TSS->eax)，此时物理寄存器eax为0，如果没有切换到子进程，是父进程系统调用结束后返回，此时res(eax)不为0，接下来因为函数体中是printf("A"),所以通过判断res是否为0  

* **因此如果res不为0，执行208，也就是父进程，等于0的话，子进程执行printf，就会打印A**  

* 前面讲过，切换到子进程，子进程一开始也是执行int 0x80后面的代码,在内核级代码实现的例子中，fork创建子进程，返回来以后，判断如果是子进程，那么会调用一个系统调用exec去执行cmd，exec中会修改子进程的eip为cmd的入口，exec调用结束后子进程会执行cmd   

**下面是int 0x80到底发生了什么**   

2. int 0x80就要进入内核，中断处理函数 调用system_call  而system_call调用sys_call_table就会知道是调用sys_fork

![image](https://user-images.githubusercontent.com/58176267/157417445-6c53fe86-fb20-4c29-81e5-9d5feb51cb06.png)

![image](https://user-images.githubusercontent.com/58176267/157417982-4740a42e-6b68-419e-b961-55fd047af127.png)

3.sys_fork调用copy_process 做出一套新的PCB，栈，其中申请PCB内存后一部分做了内核栈，然后将PCB中tss的eip、esp、eax等赋好值(PCB中除了tss，还有该进程的状态等)    

注意copy_process会使用一堆参数，这些参数都是从栈中取的，是父进程在执行int 0x80时将当时cpu各寄存器的时压入的栈，**其中的eip就是父进程调用int 0x80后的地址100**
copy_process还将eax设为了0  

![image](https://user-images.githubusercontent.com/58176267/157419233-0a629b6d-201c-4088-abf0-8854d509a5c1.png)


4.父进程执行完copy_process() {} 就要返回 ret到哪里？  

下面的图很清楚，按调用的顺序逆着回去就可，在回到system_call时，会进行调度 jne reschedule （打印A的进程刚才只是创建了并且具备了执行的条件，但父进程中必须经过调度后才会执行，所以需要在适当的地方进行schedule，这里的一个策略是父进程在iret也就是中断返回的时候进行了调度）

**注意：**

**看下本页起始处main函数及转换后的汇编代码**  

1.**在下图中如果父进程没有通过调度schedule函数，也就没有不会switch_to函数，不会切换到子进程，那么在父进程system_call执行iret时，寄存器eax的值不为0，返回以后执行eax赋值给res并和它做比较就不会跳转到printf函数执行**————物理寄存器eax的值并不是创建完子进程就等于0，创建子进程只是将子进程PCB中的TSS->eax置为0，只要经过调度切换到子进程后，物理寄存器eax的值才为0
2.如果时父进程通过调度schedule函数切换到了子进程，上节内容讲了copy_process中已经讲父进程的eip也给了子进程TSS->eip，同样CS，以及父进程的栈都赋值给了子进程TSS对应的寄存器，因此子进程从内核态回到用户态时也就是遇到iret时，会从栈中弹出eip，CS，EFLAGS，ESP等，这些与父进程是一致的，因此也是到100处执行，但接下来由于eax为0，就知道是子进程在执行了就会**跳到200处执行printf打印A** 
3.**父进程iret返回后，跳到208继续执行，会接着执行创建另一个子进程的代码**  
4.也就是父进程创建完一个打印A的进程，假设时间片没有用完，这个过程也没有阻塞，所以没有调度，因此父进程继续执行，又会创建一个打印B的进程  

```cpp
system_call:
 ...call sys_call_table(,%eax,4) 
 cmpl $0, state(current)
 jne reschedule
 iret  //到哪里
```
![image](https://user-images.githubusercontent.com/58176267/157423674-120c6822-70d7-4e94-8e71-41637f0fbf34.png)

5.父进程创建完两个进程后，就可以执行wait()了，进入阻塞态让出cpu   **wait()函数会执行一个系统调用 __NR_wait**  

**将自己这个进程的状态设置成阻塞态，再调用schedule();**  

![image](https://user-images.githubusercontent.com/58176267/157430843-d5e99c1f-a259-4fc3-a476-122c591ddffb.png)

6.schedule  
![image](https://user-images.githubusercontent.com/58176267/157431222-e43a5c71-ef8a-4fa8-bd29-0c50e7259658.png)

怎样切换到另外一个线程：将cpu中内容给当前进程current的PCB(里面的TSS)，然后将next进程的PCB(里面的TSS)赋值给CPU  

![image](https://user-images.githubusercontent.com/58176267/157431748-1bbc9128-7633-44c6-abe6-53cc1d345bda.png)

**这样已经可以不断打印A了，但是怎么让B线程执行？**  

**7.切换到打印B的线程————时钟中断**

因为schedule已经有了(包括调度(最简单的就从就绪态队列的队首取出一个next)和switch_to等)，那么需要的就是调用schedule函数，也就是要有个**调度点**来调用schedule  

打印的过程怎样在哪里插入这个**调度点**，因为schedule必须在内核态调用，所以必须进入内核，那么就要靠中断————**时钟中断**  

**时钟中断代码：**  

* 首先能够捕获时钟
* 初始化时钟中断
* 每到一个时钟中断，进入中断处理函数，将当前进程(current)的counter减1，一旦减成0，调用schedule();   **这个counter是时间片，每个进程的PCB中都有这样一个量**  
* A进程切换到B进程过程与前面一致

![image](https://user-images.githubusercontent.com/58176267/157433668-8f2736d9-8cff-49b8-9d78-0e44d5370bde.png)















