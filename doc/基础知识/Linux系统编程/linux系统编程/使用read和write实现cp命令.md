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
#include <unistd.h>  
#include <fcntl.h>   //file control  O_RDONLY等定义  

int main(int argc, char** argv)
{
	char buf[1024];

	int n = 0;

	int fd1 = open(argv[1], O_RDONLY); //读源文件

	//要写入的目标文件，如果文件不存在先创建,如果已经存在就截断为0  注意要创建的话就要指定权限
	int fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0664);

	//缓冲区大小有限，但我们不知道源文件内容有多大因此需要while循环
	while ((n = read(fd1, buf, 1024)) != 0) {
		write(fd2, buf, n);
	}
	//!对应open要注意close
	close(fd1);
	close(fd2); 

	return 0;
} 
```

## 错误检查  

基本上所有系统调用都要进行错误检查  

1 利用strerror函数  

函数原型
```c
char *strerror(int errnum);
```
```c
printf("xxx error : %s\n", strerror(errno))
```

2 利用perror()函数  

函数原型
```c
void perror(const char *s); //传入参数为出错时字符提示
```
它会与strerror结合  

```c
#include <unistd.h>  
#include <fcntl.h>   //file control  O_RDONLY等定义  
#include <stdio.h>  //其中包含了perror函数
#include <stdlib.h> //包含了exit函数

//#include <string.h>

int main(int argc, char** argv)
{
	char buf[1024];

	int n = 0;

	int fd1 = open(argv[1], O_RDONLY); //读源文件
	
	if(fd1 == -1) {
		perror("open argv1 error");
		exit(1);
	}

	//要写入的目标文件，如果文件不存在先创建,如果已经存在就截断为0  注意要创建的话就要指定权限
	int fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0664);
	
    if(fd2 == -1) {
		perror("open argv2 error");
		exit(1);
	}

	//缓冲区大小有限，但我们不知道源文件内容有多大因此需要while循环
	while ((n = read(fd1, buf, 1024)) != 0) {
		if(n < 0) {
			perror("read error");
			break;
		}
		write(fd2, buf, n);
	}
	//!对应open要注意close
	close(fd1);
	close(fd2); 

	return 0;
}
```




