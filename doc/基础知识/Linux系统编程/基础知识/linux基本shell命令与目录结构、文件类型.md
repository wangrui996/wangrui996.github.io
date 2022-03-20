  

## Linux终端基本shell命令  

**终端**：一系列输入输出设备的集合  

### 终端常用命令  

* pwd：查看当前路径  
* cat：读一个文件的内容
* ls -l ：显示详细信息
* ls -a ：显示隐藏目录
* ls - d ： 显示目录
* ls -R ： 递归进入子目录并显示  
* cat + 文件名 查看文件内容    cat直接回车，会什么也不显示，当用户在终端输入指令后它会回显
* tac + 文件名 倒着显示文件内容  用途：Linux维护等查看文件日志，最新的内容在文件最后  
* more + 文件名  可以分屏显示该文件  空格翻页 回车换行  q退出(或crtl+c终止)  
* less + 文件名  分屏显示  q退出(crtl+c不管用?)
* head + 文件名  默认显示该文件前10行 可以指定参数  head -5 文件名  
* tail - 行数 文件名  显示后面多少行数  
* tree  把当前目录结构以树的方式显示  该命令在操作系统中没有附带，需要sudo apt-get install tree  



### 常用快捷键  

Crtl+a :移动到输入命令最前端  
Crtl+e :移动到输入命令末端  
Crtl+u :直接删除整行命令  

## 类Unix系统目录  

/bin：系统自带的可执行文件，里面有个date，可以用/date执行， 在命令行输入date也可以执行但这是通过shell命令解释器帮忙执行的  
/boot：开机的启动例程　　
/dev: linux系统中有一句话叫**所见皆文件**  
/etc:当前系统用户的配置信息  如passwd存放着用户信息（用户id等）  
/home: 用户主目录  
/lib:库文件  
/media:挂载磁盘相关  
/opt:
/proc:linux系统编程进程相关？  
/root:
/usr: unix software resource  用户安装的软件、第三方库  

## Linux系统文件类型  

* 普通文件： -
* 目录文件： d 
* 字符设备文件：c  
* 块设备文件： b   (block)
* 软连接： l  
* 管道文件：p  
* 套接字： s  
* 未知文件  
**可通过ls -l查看文件详细信息时，第一个字符就是**  
![image](https://user-images.githubusercontent.com/58176267/156586847-e8978bf1-408e-4d4d-8b32-8279feca5fc3.png)
![image](https://user-images.githubusercontent.com/58176267/156586959-c07a67ae-62d3-40c8-9d15-d6ea2683a0b4.png)


## 补充  

1.安装aptitude可以代替apt-get命令  
如 sudo aptitude install xxx

同时可以使用  
sudo aptitude show xxx  
查看xxx是否已经被安装






