<p id="使用read和write实现cp命令"></p>

# 使用read和write实现cp命令 


## read

终端查看read函数  
```shell
man 2 read
```

read函数：从一个文件描述符读数据，保存在缓冲区


**函数原型**
```c
ssize_t read(int fd, void *buf, size_t count);
```

### 参数  

* fd ： 文件描述符  
* buf ：缓冲区
* count ：**缓冲区大小**

返回值 ： ssize_t  一个有符号的size_t  
* 成功 ：返回实际读到的字节数(**已经到达文件末尾会读到0个字符，返回值是0**)  
* 失败 ：返回-1.并设置errno  

**注意** 注意read函数返回值为0说明读到了文件末尾  

## write

终端查看write函数  
```shell
man 2 write
```

write函数 ：打开或创建一个文件/设备  


**函数原型**
```c
ssize_t write(int fd, const void *buf, size_t count);
```

### 参数  

* fd ： 文件描述符  
* buf ：缓冲区  注意参数中是个const，避免向fd写数据时误修改缓冲区内容
* count ：**实际要写出的数据大小**，缓冲区大小是可能大于要写出的数据的

返回值 ：  
* 成功 ：实际写入的字节数  
* 失败 ：返回-1.并设置errno 



## 实现cp函数  

```c
#include <unistd>
int main(int argc, char** argv)
{
	char buf[1024];

	int n = 0;

	int fd1 = open(argv[1], O_RDONLY); //读源文件

	//要写入的目标文件，如果文件不存在先创建,如果已经存在就截断为0  注意要创建的话就要指定权限
	int fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0664);  

	//缓冲区大小有限，但我们不知道源文件内容有多大因此需要while循环
	whlie( (n = read(rd1, buf, 1024)) != 0) {
		write(fd2, buf, n);
	}
	//!对应open要注意close
	close(fd1);
	close(fd2); 

	return 0;
}
```







### open函数 demo  

#### 1.打开一个已有文件

```c
#include <unistd.h>  //包含了open的两个函数原型  
#include <fcntl.h>   //file control  O_RDONLY等定义  
#include <stdio.h>


int main(int argc, char** argv) 
{
	int fd;
	fd = open("./txt/text.txt", O_RDONLY);
	printf("fd = %d\n", fd);
	
	close(fd);
	
	return 0;
}
```
输出
```shell
wr@wr:~/linux系统编程/open$ gcc open.c -o open
wr@wr:~/linux系统编程/open$ ls
open  open.c  txt
wr@wr:~/linux系统编程/open$ ./open 
fd = 3
```

#### 2.创建一个文件   需指定权限  

```c
#include <unistd.h>  //包含了open的两个函数原型  
#include <fcntl.h>   //file control  O_RDONLY等定义  
#include <stdio.h>


int main(int argc, char** argv) 
{
	int fd;
	//创建一个文件并以只读方式打开
	//权限是 rw-r--r-- 用户，同组用户和其他组权限分别为 可读写-只读-只读  
	fd = open("./txt/text2.txt", O_RDONLY | O_CREAT, 0664); 
	printf("fd = %d\n", fd);
	
	close(fd);
	
	return 0;
}
```
执行  
```shell
wr@wr:~/linux系统编程/open$ gcc open.c -o open
wr@wr:~/linux系统编程/open$ ./open 
fd = 3
```  

查看文件  
```shell
wr@wr:~/linux系统编程/open/txt$ ls -l
总用量 4
-rw-r--r-- 1 wr wr  0 3月  18 15:04 text2.txt
-rw-r--r-- 1 wr wr 36 3月  18 14:50 text.txt
```

#### 3.以追加方式打开文件  

该方式打开一个已有内容的文件后，再向里写不会清空原有内容  


#### 4.O_TRUNC 截断文件  把文件长度截断为0，相当于清零  

```c
#include <unistd.h>  //包含了open的两个函数原型  
#include <fcntl.h>   //file control  O_RDONLY等定义  
#include <stdio.h>

int main(int argc, char** argv) 
{
	int fd;
	//如果./txt/text.txt存在，以只读方式打开并将其清空    如果不存在，创建，并且权限为644
	fd = open("./txt/text.txt", O_RDONLY | O_CREAT | O_TRUNC, 0644); 
	printf("fd = %d\n", fd);
	
	close(fd);
	
	return 0;
}
```

执行
```shell
wr@wr:~/linux系统编程/open$ gcc open.c -o open
wr@wr:~/linux系统编程/open$ ./open 
fd = 3
```

查看文件属性及内容  

```shell
wr@wr:~/linux系统编程/open/txt$ ll
总用量 8
drwxr-xr-x 2 wr wr 4096 3月  18 15:04 ./
drwxr-xr-x 3 wr wr 4096 3月  18 15:13 ../
-rw-r--r-- 1 wr wr    0 3月  18 15:04 text2.txt
-rw-r--r-- 1 wr wr    0 3月  18 15:13 text.txt
wr@wr:~/linux系统编程/open/txt$ cat text.txt
wr@wr:~/linux系统编程/open/txt$ 
```  


#### 5 创建文件权限问题  

文件权限 = mode & ~umask   （umask为022，取反(按照位取反)后为 755），777 & 755 按位与后结果为755

* 执行umask查看权限掩码   如下图，umask为022 则权限应该是 755（rwxr-xr-x）
```shell
wr@wr:~/linux系统编程/open$ umask
0022
```  

```c
#include <unistd.h>  //包含了open的两个函数原型  
#include <fcntl.h>   //file control  O_RDONLY等定义  
#include <stdio.h>

int main(int argc, char** argv) 
{
	int fd;
	//如果/txt/text_new.txt存在，以只读方式打开并将其清空    如果不存在，创建，并且权限为777
	fd = open("./txt/text_new.txt", O_RDONLY | O_CREAT | O_TRUNC, 0777); 
	printf("fd = %d\n", fd);
	
	close(fd);
	
	return 0;
}
```
text_new.txt本来不存在，按照下面代码执行后 权限是755  也就是不是按照我们设定的mode = 777 而是 mode & ~umask  755

```shell
-rwxr-xr-x 1 wr wr    0 3月  18 15:25 text_new.txt*
```

### open常见错误  

#### 6 打开不存在的文件  

```c
#include <unistd.h>  //包含了open的两个函数原型  
#include <fcntl.h>   //file control  O_RDONLY等定义  
#include <stdio.h>
#include <errno.h>

int main(int argc, char** argv) 
{
	int fd;
	
	fd = open("./txt/text111111.txt", O_RDONLY); 
	//根据open手册，如果打开失败，返回值为-1，且会设置一个errno，这个errno可看作操作系统的一个全局变量 #include <errno.h>
	printf("fd = %d\n, errno=%d\n", fd, errno);
	
	close(fd);
	
	return 0;
}
```


编译运行  

```shell
wr@wr:~/linux系统编程/open$ ./open 
fd = -1
, errno=2
```

终端输入 man strerror  
有个函数原型
```shell
#include <string.h>
char *strerror(int errnum);
```
根据输入的参数errnum，可以查看其i对应的解释  


```c
#include <unistd.h>  //包含了open的两个函数原型  
#include <fcntl.h>   //file control  O_RDONLY等定义  
#include <stdio.h>
#include <errno.h>   //使用errno变量
#include <string.h>  //使用strerror函数

int main(int argc, char** argv) 
{
	int fd;
	
	fd = open("./txt/text111111.txt", O_RDONLY); 
	printf("fd = %d\n, errno=%d:%s\n", fd, errno, strerror(errno));
	
	close(fd);
	
	return 0;
}
```

```shell
wr@wr:~/linux系统编程/open$ ./open 
fd = -1
, errno=2:No such file or directory
```

#### 7 以写方式打开只读文件  (打开文件没有对应权限)  

先将text2.txt权限修改为只读  

```c
#include <unistd.h>  //包含了open的两个函数原型  
#include <fcntl.h>   //file control  O_RDONLY等定义  
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv) 
{
	int fd;
	
	fd = open("./txt/text2.txt", O_WRONLY); 
	printf("fd = %d\n, errno=%d:%s\n", fd, errno, strerror(errno));
	
	close(fd);
	
	return 0;
}
```
```shell
wr@wr:~/linux系统编程/open$ ./open 
fd = -1
, errno=13:Permission denied
```
#### 8 以只写方式打开目录  一般open是打开一个文件  

```c
#include <unistd.h>  //包含了open的两个函数原型  
#include <fcntl.h>   //file control  O_RDONLY等定义  
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv) 
{
	int fd;
	
	fd = open("./txt/", O_WRONLY); 
	printf("fd = %d\n, errno=%d:%s\n", fd, errno, strerror(errno));
	
	close(fd);
	
	return 0;
}
```

```shell
wr@wr:~/linux系统编程/open$ ./open 
fd = -1
, errno=21:Is a directory
```

