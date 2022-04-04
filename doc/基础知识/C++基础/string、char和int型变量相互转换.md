

# string、char和int型变量相互转换


[C语言中字符数组和字符串详解](http://c.biancheng.net/view/1832.html)  
[C语言字符串指针](http://c.biancheng.net/view/2012.html)  

## 补充C字符串的基础知识

C语言中除了用字符数组表示字符串外，还可以直接用一个字符指针指向字符串

区别在于：在内存中的存储区域不一样，字符数组存储在全局数据区或栈区，第二种形式的字符串存储在常量区。全局数据区和栈区的字符串（也包括其他数据）有读取和写入的权限，而常量区的字符串（也包括其他数据）只有读取权限，没有写入权限。(来自C语言中文网)

字符数组在定义后可以读取和修改每个字符，而对于第二种形式的字符串，一旦被定义后就只能读取不能修改，任何对它的赋值都是错误的。(来自C语言中文网)  

比如下面的操作

```c
#include <stdio.h>
int main(){
    char *str = "Hello World!";
    str = "xxxxxxxx";  //正确 修改指针变量的指向
    str[3] = 'P';  //错误

    return 0;
}
```


## 1.string与char  

* 1.1 char * 或者char []转string类型时可以直接复制 

```cpp
const char * p1 = "ss122";
char p2[] = "sdad";
p2[0] = 'c';
string s1 = p1;
string s2;
s2 = p2;
cout << s1 << endl << s2 << endl;
return 0;
```  

* 1.2 string转char*或者char[]  

* 1.2.1 使用string内置的c_str()函数； 该方法会附加结束符\0，比较常用  

**注意**： 不能直接赋值如 char *p1 = s1.c_str() 因为string对象析构以后会导致左值char *或char[])成为空指针

```cpp
string s1 = "ss122";
	
char *p1;

strcpy(p1, s1.c_str());
```

* 1.2.2 用string内置的data()函数；该方法不附加结束符\0  


## 2.char与int  

* 2.1 char转int  

直接将char型变量减去字符'0'即可(减去0的ASCII码)  

* 2.2 int转char  

加'0'

## 3.string与int  

* 3.1 int转string     

使用std内置to_string函数或stringstream流

* 3.1.1 std内置的to_string函数  

```cpp
string str ;
int num=123;
str = to_string(num);
```

* 3.2.2 利用stringstream输出到string    或使用流的str()函数  

```cpp
int num = 123;
string str;
stringstream ss;
ss<<num;
ss>>str;
//借助string流的重载运算符  
cout<<str<<endl;
//使用字符串流的str()函数
cout<<ss.str()<<endl;
```

* 3.2  string转int

* 3.2.1 借助stringstream  或者stoi和atoi函数 

```cpp
int num;
string str = "123";
stringstream ss;
ss<<str;
ss>>num0;
```

* 3.2.2 使用atoi函数或者stoi函数  

头文件#include <cstring>  

atoi 的参数是 const char* ,因此对于一个字符串str，必须调用 c_str()的方法把这个string转换成 const char*类型；

stoi()的参数是const string*,不需要转化为 const char*；

```cpp

```