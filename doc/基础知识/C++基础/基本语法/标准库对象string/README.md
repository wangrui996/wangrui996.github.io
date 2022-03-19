
## 标准库对象string  
本笔记部分来源于C++ Primer第五版

std::string为标准库的可变长字符序列，需要包含头文件string  


[关于string和stringstream](https://blog.csdn.net/shs1992shs/article/details/83051298)  

### 1.定义和初始化  

```cpp
string s1；           //默认构造函数初始化，s1为空字符串  
string s2 = s1;      //拷贝初始化
string s3(s1);       //与s2 = s1等价但属于直接初始化   
string s4("value");  //直接初始化(调用带参的构造函数)
string s5 = "value"; //拷贝初始化 相当于string s5 = string("value")
string s6(10, 'c');       
```

### 2.赋值 

```cpp
string s1;       
string s2("Hello");
s1 = s2;  //s2赋值给s1 
```


### 3.运算
string对象重载了关系运算符 ==  !=  比较两个字符串是否相等，区分大小写，相等的字符串长度相同，每个字符也相同  
此外还有关系运算符 < <= > >=  

加速运算符+支持两个字符串相加(串接)、字符串与字面值相加，可以使用+=在原字符串后拼接一个字符串或一个字符



但需要注意，C++中字符串字面值如"Hello"并不是一个string对象  

### 4.处理string对象中的字符  

#### 4.1 使用范围for语句遍历字符串

首先想要遍历一个string对象中每个字符，可以使用C++11提供的"range for"语句  
   
    for(变量 ：对象)
        操作
变量用于访问序列中元素，每次迭代，变量就会被初始化为对象中下一个元素值，该对象可以是标准库的其他容器，string是一个对象，也支持该操作  
另外，借助自动类型推导关键字auto，可以在元素类型未知时编译器推导变量的类型  
如： 

```cpp
string s = "Hello";
for(auto c : s)
    cout << c << endl;
```

#### 4.2 使用范围for语句改变字符串中的字符  
要改变其中的字符值需要用引用类型  
```cpp
string s = "Hello";
  for(auto &c : s)
    c = 'W';
```

#### 4.3 只访问string中部分字符  
使用下标运算符[]或迭代器  

下标运算符[]接收的是string::size_type类型的值，代表要访问字符的位置；返回值是该位置上字符的引用。下标从0开始 最后一个字符位置是 s.size() - 1  
这里索引如果用整型也可以但是会自动转换成string::size_type类型  
注意使用该方法要求下标大于等于0，小于s.size()，如果越界可能会引发异常(C++标准不要求标准库检查下标是否合法)，所以在使用时要确保那个位置上有字符。(直接使用无符号型的变量作为索引可以保证不小于0)  

### 4.string对象常用成员函数  
[cplusplus](https://www.cplusplus.com/reference/string/string/find/)


1.std::string::find  


2.std::string::substr  生成子串  
函数原型 
    string substr (size_t pos = 0, size_t len = npos) const;  
    返回一个新构造的string对象，其值初始化为此对象的子字符串的副本。  
子字符串是对象的从字符位置pos开始并跨越len个字符的部分（或直到字符串的结尾，以先到者为准）。  

pos:要复制子串的起始位置，若其等于字符串长度length，返回一个空字符串，如果大于字符串长度，会抛出异常(第一个字符位置为0)  
len:要包含在子串中的字符数，。string::npos 的值表示直到字符串末尾的所有字符。  

s.substr(0, 0)返回的是个空字符串
 

3.std::string::append  追加字符串  

[cplusplus](https://www.cplusplus.com/reference/string/string/append/)

**补充**：[C++字符串拼接效率对比](https://blog.csdn.net/mijichui2153/article/details/118154341)  
多次拼接时使用+运算符会产生较多的临时对象？


### 5.常用的标准库函数  

##### 1.std::to_string  数值转string
[官方说明](https://www.cplusplus.com/reference/string/to_string/?kw=to_string)

```cpp
// to_string example
#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string

int main ()
{
  std::string pi = "pi is " + std::to_string(3.1415926);
  std::string perfect = std::to_string(1+2+4+7+14) + " is a perfect number";
  std::cout << pi << '\n';
  std::cout << perfect << '\n';
  return 0;
}
```


### C++字符串和C字符串  

C++ string类提供了c_str()、data()和copy()这三个成员函数用于将C++字符串string转换为C字符串C_string  

    函数	功能
    c_str()	返回一个以‘/0’结尾的字符数组
    data()	以字符数组的形式返回字符串内容，但并不添加’/0’
    copy()	字符串的内容复制或写入既有的c_string或字符数组内





### 注意事项  

1.Sstring的size()函数返回的是一个string::size_type类型，是一个无符号数，因此不能将它与有符号数混用，比如做运算或者比较。  
    * 例1. 有符号数和无符号数做比较，两者都会转换成无符号数。s.size() < n;如果n是个负数，比较时会被转换为一个很大的负数(-1可能转换为2^32 - 1)；
    * 例2. 有符号数和无符号数作运算，结果   例如字符串长度为5，s.size() - 6,得到的并不是-1，而是2^32 - 1； 可见结果是“错误”的；另外这个数是个无符号数，之后如果再与有符号数比较，
