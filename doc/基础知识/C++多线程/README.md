# C++ 多线程  


### 并发与并行  

并行：程序运行时的状态，同时运行(同个时间点)  

并发：指的是程序的结构，这个程序能够同时执行多个独立的任务就说这个程序是并发(或者说这个程序采用了支持并发的设计)  



实现并发的方式：  
1.通过多个进程实现并发(多进程)  
2.在单独的进程中，写代码创建除主线程之外的其他线程来实现并发:多线程  

多进程并发  
    例如：比如SLAM采集专门一个进程，处理数据一个进程  

多线程并发  
    1.一个进程中所有线程共享地址空间(共享内存)，全局变量，全局内存、全局引用都可以在线程之间传递，所以多线程开销远远小于多进程  







## 互斥量  

* 一般情况下，使用std::lock_guard 或者 std::unique_lock而不是直接用 std::mutex


```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx1;
std::mutex mtx2;

int x = 0;

void task1() {
    for(int i = 0; i < 10000000; ++i) {
        //std::lock_guard<std::mutex> lock1(mtx1);
        //std::lock_guard<std::mutex> lock2(mtx2);
        //析构时自动释放锁(本质是构造时上锁，析构时解锁)

        //
        std::unique_lock<std::mutex> lock3(mtx1);
        // std::unique_lock<std::mutex>允许对象析构前就释放锁
        // 它还记录了当前是上锁还是解锁的状态  
        lock3.unlock();

        x++;
        x--;
    }

}

```


## 原子量  



```cpp
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> x = 0;

void task1() {
    for(int i = 0; i < 10000000; ++i) {
        x++;
        x--;
    }
}

void task2() {
    for(int i = 0; i < 10000000; ++i) {
        x++;
        x--;
    }
}

int main() {
    std::thread t1(task1);
    std::thread t2(task2);

    t1.join();
    t2.join();

    return 0;
}
```



## 条件变量 和 信号量  


```cpp
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> x = 0;

void task1() {
    for(int i = 0; i < 10000000; ++i) {
        x++;
        x--;
    }
}

void task2() {
    for(int i = 0; i < 10000000; ++i) {
        x++;
        x--;
    }
}

int main() {
    std::thread t1(task1);
    std::thread t2(task2);

    t1.join();
    t2.join();

    return 0;
}
```