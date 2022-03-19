
## C++笔记  
* [1基础](#1基础)
  * [输入输出流](#输入输出流)
  * [标准库对象string](#标准库对象string)
  * [引用](#引用)
  * [文件操作](#文件操作)
  * [类的静态成员](#类的静态成员)
  * [虚函数和纯虚函数](#虚函数和纯虚函数)
  * [内联函数与静态内联函数](#内联函数与静态内联函数)
  * [取整操作](#取整操作)
  * [decltype关键字](#decltype关键字)

* [2C++智能指针](#2C++智能指针) 


* [关于整型溢出的问题](#关于整型溢出的问题)


## 1基础

### return0、return1

### 输入输出流

#### std::cerr
std::cerr(console error)是ISO C++标准错误输出流，对应标准错误流，用于显示错误消息，与cout不同的是cerr无缓冲，即错误信息直接发送到显示器，不需要等待缓冲区或新的换行符才被显示，一般用于错误信息快速显示。

### 字符串  


#### std::string  

##### compare方法比较两个字符串





### 引用  


```cpp
#include <iostream>
using namespace std;

class Camera
{
public:
    




};


int main()
{

}
```


### 文件操作


### 类的静态成员 
C++类可以通过static声明静态成员函数或者静态成员变量  
#### 静态成员变量  
##### 初始化  
一般在类外执行main函数之前初始化，不能在类内初始化
静态成员变量归属于该类的所有对象，不依赖于某个对象而存在，也就是说，不能在定义某个对象时通过构造函数对其进行初始化(否则每次新创建一个对象都对该变量重新初始化，static成员变量不就没意义了吗)；  
如果类的某些属性在所有对象中都是一致的话，可以声明成static类型的，例如某个图像类，所有对象拥有共同的内参。  
```cpp
long unsigned int Frame::nNextId=0;
float Frame::cx, Frame::cy, Frame::fx, Frame::fy;
class Frame
{
   public:
       Frame(){}
       static long unsigned int nNextId; 
       static float fx;        
       static float fy;       
       static float cx;     
       static float cy;        
   private:
       cv::Mat mRcw; 
       cv::Mat mtcw; 
};
```
#### 访问性质  
静态成员遵循public，protected和private的访问准则，


### 静态成员函数  
静态成员函数主要用来访问静态成员变量  
普通成员函数和静态成员函数的区别  
(1)普通成员函数在被编译时都会有一个隐式的形参this，指向当前对象，可以访问类内的任意成员，必须要某个对象才能调用它  
静态成员函数没有this指针，所以静态成员函数不能使用和返回类的非静态成员，只能调用静态成员函数或使用静态成员变量，在使用时可以用某个对象调用也可以直接由类本身调用(使用类名加范围解析运算符::加静态成员名即可)


### 虚函数和纯虚函数
[虚函数和纯虚函数](https://www.huaweicloud.com/articles/994d149b0c54b0578c89805b87051688.html)  


### 内联函数与静态内联函数




### 取整操作  

(1)四舍五入 round()  
需包含头文件
    #include<cmath>




## 2C++智能指针  
### STL库
[std::shared_ptr官方文档](http://www.cplusplus.com/reference/memory/shared_ptr/)  
以下部分示例代码来自该官方文档  
#### 定义

#### get() 返回存储的指针  
```cpp
// shared_ptr::get example
#include <iostream>
#include <memory>

int main () {
  int* p = new int (10);
  std::shared_ptr<int> a (p);

  if (a.get()==p)
    std::cout << "a and p point to the same location\n";

  // three ways of accessing the same address:
  std::cout << *a.get() << "\n";
  std::cout << *a << "\n";
  std::cout << *p << "\n";

  return 0;
}
```
输出：  
```bash
a and p point to the same location
10
10
10
```  
#### get  
 
 
### for循环遍历方法  
 

 
 
 

[C++智能指针](https://www.cnblogs.com/tenosdoit/p/3456704.html)

### boost库  

## 关于整型溢出的问题  
 
    int n;
    cout << n * 10 << endl;
上面例子中，n * 10为int型，表示范围是[-2^31 ,2^31 - 1]; 当n * 10超出该范围时就会出错。下面这样输出就不会出错
 
    int n;
    cout << (long long) n * 10 << endl;




