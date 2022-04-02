

# exec函数族
 
execute缩写  

使进程执行某一程序。成功无返回值，失败返回 -1  

![image](https://user-images.githubusercontent.com/58176267/161289511-70291a76-f641-47b1-8dbb-56c95bfb010a.png)

![image](https://user-images.githubusercontent.com/58176267/161289683-f37c802e-9e3c-491b-9db9-9d8227fe4f3e.png)

上面的函数只需掌握下面两个    

## execlp函数与execl函数

#### execlp函数  

```c
int execlp(const char * file, const char * arg, ...);  //p是path缩写  借助 PATH 环境变量找寻待执行程序
```

该函数通常用来调用系统程序 如ls  data  cp cat等命令

参数1： 要加载的程序名   该函数需要配合PATH环境变量使用，当PATH中所有目录搜索后没有参数1则出错返回  
参数2： argv0
参 3： argv1
...： argvN
哨兵：NULL

返回值：只有当出错时才有返回值 (因此如果execlp执行成功一定不会返回到调用的位置，所以错误判断可以放在调用execlp后面 具体看下面的demo)

* 函数原型中...表示参数是可变的，可以根据file需要的参数来定  
* 因此在使用execlp函数时，需要用NULL表明参数的结束  

* 注意，参数中，第一个参数时arg0，类似执行可执行文件时的命令行参数 ./a.out x y  其中x是argv[1]  y是argv[2]   a.out是argv[0]  因此参数需要注意

### demo 

* 如果是父亲进程，执行print之前可以加个sleep，目的是防止父进程执行完，则父进程的父进程bash会回到前台  输出计算机名等字符串

![image](https://user-images.githubusercontent.com/58176267/161295383-3c36098a-fa5c-4c3a-bbdb-eb2f4f105a11.png)

* **bash就是通过这种方式，先创建一个子进程，然后让子进程执行我想要执行的可执行程序只不过用的可能是execl**  如输入./a.out   bash创建子进程，然后用exec让子进程执行a.out可执行程序，此时该进程的父进程就是bash  

#### execl函数  

```c
int execl(const char *path, const char *arg, ...);  //自己指定待执行程序路径
```

* 刚才execlp第一个参数是file因为它会PATH环境变量寻找叫这个名字的可执行程序  这里execl，第一个参数是path  因此假如执行当前目录下的a.out，第一个参数是./a.out（绝对路径也可以）  
* 第二个参数 a.out或者./a.out 
* 如果a.out需要命令行参数，后面依次加
* 该函数也可以执行系统可执行文件，路径知道就可以 如 execl("/bin/ls", "ls", "-l", NULL);


## 子进程执行exrc后的变化  

### 刚创建出来时  

![image](https://user-images.githubusercontent.com/58176267/161290229-49c6b6ab-06ec-450a-975c-b6ff78563e19.png)

### 子进程执行extc后  

假如exec指定了a.out，则子进程的代码段和数据段替换为a.out的，然后从a.out第一条语句开始执行  

* **注意**：**子进程的进程id并没有变化，但由于子进程调用exec后就去执行a.out（相当于执行另外一个程序），因此不能有返回值返回给调用者**

![image](https://user-images.githubusercontent.com/58176267/161290783-1954f124-37c1-4ca5-884a-3f0c964b384e.png)



# exec函数族特性  







