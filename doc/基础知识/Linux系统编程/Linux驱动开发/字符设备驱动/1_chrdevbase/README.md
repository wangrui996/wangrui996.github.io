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
    * name：设备名字，指向一串字符串。
    * fops：结构体 file_operations 类型指针，指向设备的操作函数集合变量。


*unregister_chrdev 函数用户注销字符设备，此函数有两个参数，这两个参数含义如下：
    * major：要注销的设备对应的主设备号。
    * name：要注销的设备对应的设备名。


## 设备号  

* Linux下每个设备都有一个设备号，分主设备号和次设备号  
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





