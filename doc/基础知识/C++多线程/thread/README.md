
## thread  


[thread官方说明-cplusplus]https://www.cplusplus.com/reference/thread/thread/?kw=thread


## 定义、加入线程

线程入口可以是函数、类、lambda表达式

[构造函数说明及四种初始化方式示例](https://www.runoob.com/w3cnote/cpp-std-thread.html)
1.构造函数  

    (1)默认构造函数     thread() noexcept;
    (2)初始化构造函数	template <class Fn, class... Args>
                                explicit thread (Fn&& fn, Args&&... args);
    (3)拷贝构造函数     thread (const thread&) = delete;
    (4) move构造函数    thread (thread&& x) noexcept;

(1)默认构造函数创建一个空的std::thread对象  
(2)初始化构造函数，创建一个std::thread对象，可被joinable，所创建的新线程会调用fn函数，该函数的参数由args给出  
(3)拷贝构造函数被禁用  
(4)move构造函数

注意：可被 joinable 的 std::thread 对象必须在他们销毁之前被主线程 join 或者将其设置为detached.


2.std::thread::join()  
加入线程  
该函数在线程执行完成后返回  

join函数被线程对象调用，等线程内容执行完以后，join()函数才能返回  

在什么线程环境下调用了这个函数？  
由于join()必须要等线程方法执行完毕后才能返回，因此会阻塞调用线程，如果一个线程对象在一个线程环境A调用了这个函数，那么这个线程环境A就会被阻塞，直到这个线程对象在构造时传入的方法执行完毕后，才能继续执行。  

利用ORB_SLAM单目初始化中，因为不知道初始化时是平面还是非平面，开两个线程计算F和H矩阵


## 互斥锁 mutex  
互斥类
互斥量就是个类对象，可以理解为一把锁，多个线程同一时间只有一个线程能加锁或解锁    

### 初始化  

### lock与unlock  
两者要成对使用，对应，否则会出错




## 多线程数据共享问题  

只读数据是安全的  
同一个地址的数据有读有写，如果不做处理，容易冲突崩溃  

例如下面的代码，有一个全局区的数组，创建了两个线程，分别对其进行写入和读取操作  
这是程序运行时的输出，每次结果都不同  
很明显可以看出，会出现同一行中有两个线程的操作，就是说某个线程中操作还没完成就开始执行了另外一个线程导致冲突(因为我们最后输出的是换行符号，如果执行完那就换行了)
在操作同一块内存时没有加锁导致非常不稳定  
```shell
主线程 id = 24588
正在放入数据： 0
正在读出数据： 0
正在放入数据： 1
正在放入数据： 正在读出数据： 12

正在放入数据： 3
正在读出数据： 1
正在放入数据： 4
正在放入数据： 正在读出数据： 1
正在读出数据： 5
1
正在放入数据： 正在读出数据： 5
6
正在放入数据： 正在读出数据： 6
7
正在放入数据： 8
```

```cpp
#include <iostream>

#include <vector>
#include <thread>

using namespace std;

//全局变量，可由所有线程共享  
vector<int> v;
void inputData()
{
	cout << "子线程 id = " << this_thread::get_id() << endl;
	for (int i = 0; i < 1000; i++)
	{
		cout << "正在放入数据： " << i << endl;
		v.push_back(i);
	}
}

void outputData()
{
	cout << "子线程 id = " << this_thread::get_id() << endl;
	for (int i = 0; i < 1000; i++)
	{
		if(v.empty())
        {
            cout << "正在读出数据： " << i << endl;
		    v.pop_back();
        }
	}
}


//主线程从main函数入口开始执行
int main()
{
	cout << "主线程 id = " << this_thread::get_id() << endl;

	thread putThread(inputData);
	thread outThread(outputData);
	
	putThread.join();
	outThread.join();
	
	cout << "子线程执行完毕，继续执行主线程： " << endl;
	return 0;
}
```









