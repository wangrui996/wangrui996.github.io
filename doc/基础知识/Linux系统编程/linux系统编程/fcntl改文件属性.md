

# fcntl改文件属性  

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

## 总结——位图

![image](https://user-images.githubusercontent.com/58176267/159938076-a1779cf7-fb59-42cd-bcdf-d0ff7cc30dcd.png)



