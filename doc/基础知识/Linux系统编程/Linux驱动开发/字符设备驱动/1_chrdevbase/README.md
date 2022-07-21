#


*  在模块的入口函数，需要注册字符设备   在模块的出口函数，需要注销字符设备  


## 字符设备的注册与注销  

* 在 fs.h 中定义如下  

```c
static inline int register_chrdev(unsigned int major, const char *name,
const struct file_operations *fops)
static inline void unregister_chrdev(unsigned int major, const char *name)
```

* register_chrdev 函数用于注册字符设备，此函数一共有三个参数，这三个参数的含义如下：
    * major：主设备号，Linux 下每个设备都有一个设备号，设备号分为主设备号和次设备号两部分，关于设备号后面会详细讲解。
        * 使用该函数注册的缺点就是，使用该主设备号后，会把它对应的所有次设备号都用了，比如可能只用一个次设备号的情景就可以了
        * 因此在新的Linux设备驱动编写时，已经不再使用该函数  直接指定主次设备号，也可以直接通过内核申请，这里还需要自己指定，需要先查看下哪个设备号没被使用（主要是主设备号）  
    * name：设备名字，指向一串字符串。  
    * fops：结构体 file_operations 类型指针，指向设备的操作函数集合变量。  

* unregister_chrdev 函数用户注销字符设备，此函数有两个参数，这两个参数含义如下：
    * major：要注销的设备对应的主设备号。
    * name：要注销的设备对应的设备名。


* **Linux下，使用 cat /proc/devices  查看当前设备下的所有设备  找一个没用的主设备号**  
 

* 定义一个struct file_operations类型结构体并实现其中部分函数  




## 设备号  

* Linux下每个设备都有一个设备号，分主设备号和次设备号   需要保证某个设备的设备号是唯一的
* Linux提供了一个 dev_t 数据类型表示设备号    定义在 /include/linux/types.h  

```c
typedef __u32 __kernel_dev_t;  （typedef unsigned int __u32;）
typedef __kernel_fd_set		fd_set;
typedef __kernel_dev_t		dev_t;
```

* 设备号使用dev_t类型  本质是unsigned int  手册 40.3.1  
* 高12位 为主设备号(0-4095)  低20位 为次设备号  

* 在 include/linux/kdev_t.h 中定义了几个操作设备号的宏  

```c
#define MINORBITS	20     
#define MINORMASK	((1U << MINORBITS) - 1)

#define MAJOR(dev)	((unsigned int) ((dev) >> MINORBITS))
#define MINOR(dev)	((unsigned int) ((dev) & MINORMASK))
#define MKDEV(ma,mi)	(((ma) << MINORBITS) | (mi))
```

* 宏 MINORBITS 表示次设备号位数,一共是 20 位
* 宏 MINORMASK 表示次设备号掩码
* 宏 MAJOR 用于从 dev_t 中获取主设备号,将 dev_t 右移 20 位即可
* 宏 MINOR 用于从 dev_t 中获取次设备号,取 dev_t 的低 20 位的值即可
* 宏 MKDEV 用于将给定的主设备号和次设备号的值组合成 dev_t 类型的设备号  


## 编写测试应用程序  

```cpp
```


* 挂载驱动文件，发现 /dev 下没注册时那个名字的设备  
* 这里先手动创建设备节点文件   mknod /dev/chrdevbase c 200 0
    * c 字符设备
    * 200 主设备
    * 0 次设备号 自己给一个


## 驱动程序 xxx_read 和 xxx_write

* 在驱动程序中，缓冲区对应的是内核缓冲区，当用户程序调用read读设备数据时，最终会调用驱动的xxx_read， 在该函数中，将内核数据拷贝给用户，需要借助 copy_to_user 函数
    * 不能直接将内核缓冲区指针赋值给传入的用户缓冲区指针buf   


* 对于xxx_write同理

### copy_to_user 与 copy_from_user 函数

* 头文件 #include <linux/uaccess.h>

* copy_to_user

```c
unsigned long copy_to_user (void __user * to, const void * from, unsigned long n);  
```

* 参数  
   * to 目标地址，这个地址是用户空间的地址
   * from 源地址，这个地址是内核空间的地址
   * n 将要拷贝的数据的字节数

* 返回值
    * 0 数据拷贝成功
    * 失败，返回没有拷贝成功的数据字节数



* copy_from_user

```c
unsigned long copy_from_user (void * to, const void __user * from, unsigned long n);
```

* 参数  
   * to 目标地址，这个地址是内核空间的地址
   * from 源地址，这个地址是用户空间的地址
   * n 将要拷贝的数据的字节数
   
* 返回值
    * 0 数据拷贝成功
    * 失败，返回没有拷贝成功的数据字节数








