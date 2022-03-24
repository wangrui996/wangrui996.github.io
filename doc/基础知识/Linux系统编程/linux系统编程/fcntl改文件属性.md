

## fcntl函数————修改文件属性  

fcntl 用来改变一个**已经打开** 的文件的访问控制属性

重点掌握两个参数的使用， F_GETFL，F_SETFL  

获取文件状态： F_GETFL
设置文件状态： F_SETFL

int flags = fcntl(STDIN_FILENO, F_GETFL); //先获取信息

```c
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_TRY "try again\n"

int main(void)
{
    char buf[10];
    int flags, n;

    flags = fcntl(STDIN_FILENO, F_GETFL); //获取 stdin 信息
    if(flags == -1){
        perror("fcntl error");
        exit(1);
    }
    flags |= O_NONBLOCK; //位或  不改flag原来的属性，会添加上O_NONBLOCK 非阻塞状态
    int ret = fcntl(STDIN_FILENO, F_SETFL, flags);
    if(ret == -1){
        perror("fcntl error");
        exit(1);
    }

tryagain:
    n = read(STDIN_FILENO, buf, 10);
    if(n < 0){
    if(errno != EAGAIN){
        perror("read /dev/tty");
        exit(1);
    }
    sleep(3);
    write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
    goto tryagain;
   }
    write(STDOUT_FILENO, buf, n);

    return 0;
```

执行后发现，终端设备是非阻塞的（默认的stdin是阻塞的，终端没读到数据会一直阻塞）  

### fcntl总结——位图

![image](https://user-images.githubusercontent.com/58176267/159938076-a1779cf7-fb59-42cd-bcdf-d0ff7cc30dcd.png)


## lseek 函数  

**修改文件的读写指针位置**

函数原型  
```c
off_t lseek(int fd, off_t offset, int whence);
```

* 参数：
    * fd：文件描述符
    * offset： 偏移量（矢量, 默认单位为字节），将读写指针从 whence 指定位置向后偏移 offset 个单位
    * whence：起始偏移位置： SEEK_SET(文件起始位置)/SEEK_CUR(文件当前位置)/SEEK_END(文件末尾位置)

* 返回值：
    * 成功：**较文件起始位置向后的偏移量**
    * 失败：-1  并设置errno

* 应用场景：
    * 1. 文件的“读”、“写”使用同一偏移位置。 (比如先读了10个字节，再接着写，会接着写)
    * 2. 使用 lseek 获取文件大小   int size = lseek(fd, 0, SEEK_END) 修改读写指针到文末，返回值是当前读写指针较起始位置的偏移量，因此就是文件大小
    * 3. 使用 lseek 拓展文件大小：要想使文件大小真正拓展，必须引起 IO 操作。  int size = lseek(fd, 100, SEEK_END)   向后扩展100  但是文件没有进行IO操作，程序结束后文件大小不变  
        * 可以在执行完lseek函数后，写入一个'\0'字符 

* 使用 truncate 函数，直接拓展文件  int ret = truncate("slam.txt", 250)

### demo  

* 由于对于同一个文件来说write和read是使用同一偏移位置，在程序中先使用write向文件lseek.txt写入了一个字符串，写完退出后，**读写位置在末尾**，紧接着调用read函数从fd读一个字符，是读不到的;
* 因此使用lseek函数将文件fd读写指针移动到起始位置  ，从SEEK_SET(文件起始位置)开始偏移0，就是起始位置

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(void)
{
    int fd, n;
    char msg[] = "It's a test for lseek\n";
    char ch;

    fd = open("lseek.txt", O_RDWR|O_CREAT, 0644);
    if(fd < 0){
        perror("open lseek.txt error");
        exit(1);    
    }

    write(fd, msg, strlen(msg)); //使用 fd 对打开的文件进行写操作，问价读写位置位于文件结尾处。

    lseek(fd, 0, SEEK_SET); //修改文件读写指针位置，位于文件开头。 注释该行会怎样呢？ 屏幕上不会显示，因为read是从文末接着读的

    while((n = read(fd, &ch, 1))){
        if(n < 0){    //读普通文件，返回值为0不需要额外判断阻塞非阻塞  
            perror("read error");
            exit(1);
    }
    write(STDOUT_FILENO, &ch, n); //将文件内容按字节读出，写出到屏幕
    }

    close(fd);
    
    return 0;
```

## 传入传出参数  

### 传入参数

* 1. 指针作为函数参数
* 2. 通常有 const 关键字修饰
* 3. 指针指向有效区域， 在函数内部做读操作

### 传出参数  

* 1. 指针作为函数参数
* 2. 在函数调用之前，指针指向的空间可以无意义，但必须有效
* 3. 在函数内部，做写操作
* 4. 函数调用结束后，充当函数返回值  


### 传入传出参数：

* 1. 指针作为函数参数
* 2. 在函数调用之前，指针指向的空间有实际意义(不止有效，有意义才能读)
* 3. 在函数内部，先做读操作，后做写操作
* 4. 函数调用结束后，充当函数返回值


## 目录项和inode (对于文件)  

一个文件主要由两部分组成，dentry(目录项)和 inode

![image](https://user-images.githubusercontent.com/58176267/159956493-9001e9c6-173a-43c9-857a-7089787f62c6.png)


### dentry  目录项 (directory entry)

包含
* 文件名
* inode号

### inode

* inode 本质是结构体，存储文件的属性信息，如：权限、类型、大小、时间、用户、硬连接计数、盘块位置（根据它得到文件对应的磁盘位置，从而获取文件内容）…
    * 也叫做文件属性管理结构，大多数的 inode 都存储在磁盘上
    * 少量常用、近期使用的 inode 会被缓存到内存中
* 所谓的删除文件，就是删除 inode，但是数据其实还是在硬盘上，以后会覆盖掉


### 硬连接  

如果对一个文件创建一个硬连接，硬连接与它有相同的inode，操作系统根据inode对他们进行管理  **不同硬连接的区别在于，每个硬连接具有不同的目录项，但每个硬链接的目录项的inode是相同的**

**删除一个硬链接，实际上就是删除一个目录项，也就是硬连接计数减1，当目录项全删除后，也就是下图中硬连接为1的情况下再删除它时，就没有任何一个目录项引用这个文件的inode，引用值变为0,注意此时，并不会将磁盘中内容擦除, 这块空间只会被覆盖, 这也就是说把硬盘格式化，实际上并不会正常擦除它的内容，如果将磁盘建立每一个对应的inode，即可恢复数据，上图中绿色的部分就表示数据的恢复**  


![image](https://user-images.githubusercontent.com/58176267/159955526-d0ed475c-085b-4d45-bdb7-4d228b65f315.png)

