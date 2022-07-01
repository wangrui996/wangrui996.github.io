# 面试问题准备  


## 操作系统  

### linux与ucos等的区别与联系 

[UCOSii和Linux的区别和联系](https://blog.csdn.net/chen_geng/article/details/51556459)


## C语言  

# C语言字符串与字符数组  

[C语言字符串与字符数组](https://blog.csdn.net/annjeff/article/details/107727886)   

[C语言字符串与字符数组 及 字符串常用操作函数](https://www.jb51.net/article/229511.htm)  
 
## ASCII码  

* 'a'————>97   'A'————>65  

* 字符串 “\x21” 的字节数为1字节 16进制的21 对应ASCII码的'!'
* ”\test”字符串的字节 ： 5

* printf("%d\n",(int)strlen("\t\"\65\xff\n"));  输出结果为 5  
	* 转移字符后跟数字  数字会被当作八进制的ASCII码进行转义  
	* \xff：这是一个转义字符，\x表示后面的数是十六进制，ff是十六进制数。常规的ASCII码，最大值是为0x7f，后面的从0x80到0xff为扩展ASCII码，不是标准的ASCII码.这些字符是用来表示框线、音标和其它欧洲非英语系的字母。
	* **strlen求的是字符串的长度（不包含末尾的'\0'）**
 
![image](https://user-images.githubusercontent.com/58176267/176386754-8ec4c41b-4d61-427f-95d1-a3ad581abea9.png)


## switch case 执行顺序  

* **进到case之后就顺序往后执行，碰到break或者到switch末尾处就结束** 只要能顺序到达default(起始也就是defalut之前没有break)，就一定能执行它的语句  
* 下面代码执行 输出为13

```c
int main()
{
	int i = 10;

	switch (i) {
	case 9:i++;
	case 10:i++;
	case 11:i++;
	default:i++;
	}
	printf("result= %d\n", i);

	return 0;
}
```

## 二维数组赋值方式  

* 定义时赋值或者之后赋值  [二维数组赋值方式](https://blog.csdn.net/weixin_39084493/article/details/105125981)

## 指针数组与数组指针

[指针数组与二维指针数组](https://www.cnblogs.com/Chary/p/16098192.html)

### 指针数组

下面两种写法相同，表示p为一个指针数组，数组中有五个元素，每个元素是一个指针  

指针数组是一个数组，只是每个元素保存的都是指针，以下面代码中 p1 为例，在32位环境下它占用 4×5 = 20 个字节的内存（每一个int型指针4个字节，一共有5个，sizeof(p1) = 20）
```c
int *p1[5]; 
int *(p1[5]);
```

```c
char *arr[]={“Hello”,“World”}，存储了两个指针，第一个指针指向了字符串"Hello"，第二个指针指向了字符串"World"， sizeof(arr) = 8，因为在32位平台，指针类型大小占4个字节。指针数组最重要的用途是对多个字符串进行处理操作，因为字符指针比二维数组更快更有效
```



## 数组指针  

```c
int (*p2)[5];
```

数组指针是一个指针，它指向一个一维数组，每个数组5个元素，以上面的 p2 为例，它占用 4 个字节的内存

**区分方式： []的优先级高于*，因此如果是int * p1[5],表示p1是一个数组，数组元素类型是int*    int (* p2)[5] 这样就表示定义的p2是一个指针，它指向一个int型数组，数组中元素5个** 对该二维数组指针进行加法（减法）运算时，它前进（后退）的步长与它指向的数据类型有关，假如p2 指向的数据类型是int [5]，那么p+1就前进 4×5 = 20 个字节，即指向二维数组下一行起始位置; 二维数组的数组名如果参与运算，就会转换成与p2等价的二维数组指针  *(*(p2+1)+1) 表示第 1 行第 1 个元素的值  理解的话可以从定义上，p2是一个指向int[5]数组的指针，p2 + 1是指向二维数组第1行的int[5]数组的指针,解引用后是int[5]这个数组(首地址),再加上数组内偏移1,解引用后就表示第一行第一列数据  


## 指针函数与函数指针  

* 与指针数组和数组指针类似，核心在于：**括号的优先级大于* **

### 指针函数 

* 它的主体是一个函数  函数返回值类型为指针

```c
int * f() {
}
```

### 函数指针 

* 主体是一个指针，它指向一个函数，因此叫函数指针

* 一个函数在内存中是一段连续空间(虚拟内存)，函数名是起始地址
* void func (void) 这个函数的函数指针是 void(* p)(void) 函数指针的类型是 void( * )(void)
* char* func (int * a) 这个函数的函数指针是 char* (* p) (int * )
* typedef char* (* pfunc) (int * ) 新定义一个类型，可以指向形如char* func (int * a)这样的函数

```c
int (* f)(int x, int y);
```


**判断是指针函数还是函数指针就看那个f**

### 例子  

* **注意**  C++和C语言使用函数指针调用函数的语法不同，需要进一步查阅资料

```c
#include <stdio.h>
#include <stdlib.h>

int add(int x, int y) {
	return x + y;
}

int sub(int x, int y) {
	return x - y;
}

// 函数指针  
int (*f)(int x, int y);

int main(int argc, char** argv) 
{
	f = add; // f = &add;
	//printf("1+2= %d\n", f(1,2)); C++语言中是这种语法，直接用函数指针名调用函数 C语言中用下面的语法
	printf("1+2= %d\n", (*f)(1,2));
	
	f = sub; // f = &sub;
	//printf("1-2= %d\n", f(1,2));
	printf("1-2= %d\n", (*f)(1,2));
	
	system("pause");
	return 0;
}
```

```c
#include <stdio.h>
#include <stdlib.h>

int c;
int* add(int x, int y) {
	c = x + y;
	return &c;
}

int* sub(int x, int y) {
	c = x - y;
	return &c;
}

// 指针函数指针，指向指针函数的指针
int* (*f)(int x, int y)

int main(int argc, char** argv) 
{
	f = add; // f = &add;
	//printf("1+2= %d\n", *f(1,2));C++语言中是这种语法，直接用函数指针名调用函数 C语言中用下面的语法
	printf("1+2= %d\n", *(*f)(1,2));
	
	f = sub; // f = &sub;
	printf("1-2= %d\n", *(*f)(1,2));
	
	system("pause");
	return 0;
}
```

### 函数指针使用  

* 声明函数指针
	* 声明普通函数需要指定指针类型, 声明函数指针同样要提供**函数类型**，**函数类型是指返回值和参数列表（不包括函数名和参数名）**
```c
int fun1(int a, string b);
int fun2(int c, string d);
int fun3(int e, string f);
// 对应的函数指针  函数指针参数中也可以写处变量名，用什么都可以
int (*pf1) (int, string)
```

## 函数指针与回调函数  

* 某个函数func的参数是一个函数指针，在函数func内使用函数指针调用某个具体的函数B    在调用函数A时，传入一个函数地址(函数名B),就可以让函数A在执行时调用的是指定的函数B
* 为什么这么做呢？ 直接调用B不就行了？————任务简单时确实是这样，但是如果有很多这样的自定义函数B,C,D,E等，我们在每次调用它们之前，都会执行一段相同的代码M，执行它们之后，也都会执行一段相同的代码N, 面对这样的场景，首先我们肯定想要复用代码段M和N，那我们就将它们分别写进函数X, Y 好，这样假设我们依次需要执行B,C,D,E，那代码就是 X,B,Y,X,C,Y,X,D,Y,X,E,Y  如果我们修改下BCDE函数，即把代码段分别加入到它们的函数头和尾，这样调用BCDF即可，但是这部分代码太冗余
* 现在有了函数指针这个东西，既然BCDE四个函数的**函数类型**相同，只不过做的事可能有区别，那就定义一个它们的函数指针，然后写一个函数A，函数A的参数包含这个函数指针类型，假设函数指针被定义为 int (* pfunc) (int x, char y); 则执行BCDE就可以是这种形式 pfunc = B; A(pfunc);
* **尽管一个函数, 可以直接被另一个函数调用, 但是在这种情况下, 不能在A中直接调用B或CDE, 因为在写A函数时，并不知道哪个函数会被调用, 也不是可能被调用函数的函数名**,C++中，尽管可以用函数重载的方式，使函数实现不同功能，重载A是否够可以？ 简单情况下可以，但很多情况下，写这个函数的时候，并不知道可能需要做的动作，也就是说要执行的内容很可能要之后才能确定，没法提前确定;（这不很像多态嘛）
* linux操作系统中使用了函数指针，实际上也可以理解为是一种多态？ 在驱动开发中，很多也是在已有框架基础上，绑定自己的函数，然后在某些表中注册好

* **在函数A中调用BCDE函数的形式，叫做函数的回调，B,C,D,E就称为回调函数** 也就是，在一个函数中，通过函数指针的方式调用的函数，被调用的函数就叫做回调函数

### 给回调函数传递参数  

* 1.可以修改回调函数，和函数指针，它们参数类型一致即可 
* 注意，这里使用的是c++语法，函数指针调用函数的语法, 可以直接用函数指针名pf 而不用(* pf)
```cpp
//回调函数
void func1(int a) {
	cout << "a = " << a << endl;
}

void f(void(*pf)(int)) {
	cout << "调用回调函数之前的准备" << endl;
	// 调用回调函数 
	int x = 3;
	pf(x);
	cout << "调用回调函数之后的收尾工作" << endl;
}

void (*pfunc)(int);

int main() 
{
	f(func1);
	return 0;
}
```

* 2.给回调函数传递参数的方式：不修改回调函数,修改调用函数  

```cpp
//回调函数
void func1(int a) {
	cout << "a = " << a << endl;
}

void f(void(*pf)(int), int m) {
	cout << "调用回调函数之前的准备" << endl;
	// 调用回调函数 
	pf(m);
	cout << "调用回调函数之后的收尾工作" << endl;
}

void (*pfunc)(int);

int main() 
{
	f(func1, 3);
	return 0;
}
```


## memcpy  

[C标准库 memcpy](https://www.runoob.com/cprogramming/c-function-memcpy.html)





## linux  


### 软链接和硬链接  

* 硬链接与原文件共用inode  实际上是一个文件的别名  ln a b 创建a的硬链接b 
* 软链接又叫符号链接   ln -s a b 创建a的软链接b
[软链接和硬链接](https://www.cnblogs.com/xiaochaohuashengmi/archive/2011/10/05/2199534.html)

#### 查看软、硬链接  

* 使用 ls -l 查看文件信息  
	* 软链接文件的符号是s  
	* 权限后面第二列的数字就是硬链接计数，大于等于2说明它是一个硬链接文件
* 使用 ls -il  会在最前面增加一个文件的 inode number 硬链接文件会和其它文件拥有相同的inode number


### 查看进程id  

ps -aux ：查看所有进程信息，包括进程id，进程名，子进程id等
ps -aux | grep 执行文件名  可以查看指定进程的id  

### 查看cpu占有率 top指令  



### 查看内存使用 free 命令

显示系统内存的使用情况，包括物理内存、交换内存(swap)和内核缓冲区内存


## 全局变量和同名的局部变量  


* 在定义局部变量所在的范围内，以局部变量为准，否则就是全局变量  
* 例如下面例子上有个全局变量m, 函数中又定义了一个m，在函数中，m值为3，在主函数或其他函数中直接用m就是13  
* 如果把函数中m前面int去掉，那么m就是修改的全局变量  

```cpp
int m =13;
int fun(int x, int y){
    int m = 3; return(x*y - m);
}
```

## typedef  

* typedef 基本作用   
* typedef与函数指针  
* 根据下面链接内容  
```c
typedef int (* FUN) (); // 给类型起别名  这以后，FUN就代表  int () 函数指针类型  用它来定义一个变量，这个变量就是一个函数指针
FUN funPoint;  //funPoint是一个函数指针  如果没有上面的typedef  可以这么声明：int (* funPoint) (); 

funPoint = print; //使用函数指针  后面可以直接调用 funPoint(); （C语言中好像要加解引用符？ （*funPoint)(); ）

int print()
{
	//.....
}
```
[typedef](https://blog.csdn.net/weixin_42639919/article/details/81240779?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-0-81240779-blog-85251417.pc_relevant_aa2&spm=1001.2101.3001.4242.1&utm_relevant_index=3)



## sizeof 与 strlen  

* sizeof是操作符  strlen是string.h中的函数  
* sizeof操作对象可以是变量、类型名   strlen只针对字符串
* sizeof计算的是字节数   strlen求的是字符串的长度，不包含末尾的'\0' （但在sizeof中'\0'也算占一个字节）  

* 在32位机器上，分别对下面求sizeof,得到6  4  4

```c
    char str[] = "hello";
    char *p = str;
    int n = 10;
```
 
## linux bootloader过程  


## 中断处理的过程  


## 线程的几种锁  

[线程的几种锁](https://www.csdn.net/tags/OtDakgwsNjU0Ny1ibG9n.html)  


## 排序算法 

* 稳定的排序算法  


* 如果给出大量数据，用什么排序算法  



## 字节对齐的概念，原因，规则  


## map和set  



## 智能指针  

* 种类
	* auto
	* unique
	* shared
	* 
	* 作用： 
* 什么时候智能指针  
* **循环引用问题**  有什么解决方式  
* 




