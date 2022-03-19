# man命令  

## man man  命令

![image](https://user-images.githubusercontent.com/58176267/157900508-ec48a0a4-27ee-41ff-94c5-90d5781e159e.png)



重点是1可执行程序(shell命令), 2系统调用, 3 库调用(程序库中的函数如printf), 9内核例程  
其中5 文件格式和转换，定义了一些文件格式如 通过 man 5 passwd  查看如下，可以知道每一个冒号分隔符分割的字段的含义  

![image](https://user-images.githubusercontent.com/58176267/157900763-9680f33d-7bce-4a10-b349-1e45140dc852.png)


## man中文包安装  
```shell
sudo apt-get install manpages-zh  
sudo gedit /etc/manpath.config
将所有的/usr/share/man替换为/usr/share/man/zh_CN
```
