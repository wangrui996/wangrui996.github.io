# find命令  

## 基本find命令

1.-type 按文件类型搜索  

find 路径 -type "l"  将输入路径下及其子目录(递归查找)下的**软链接**都找到  

**l用双引号和单引号都可，后面的命令也一样**

-type 按文件类型查找  
**补充知识点：** linux下区分文件类型并不是以后缀，而是通过ll命令查看文件详情中第一个字符来区分，具体如下：
* f 普通文件 (注意，这里-type后跟f表示搜索普通文件，普通文件包括纯文本文件、二进制文件、数据文件，通过ls -l查看第一个字符是‘-’)
* d 目录文件
* p 管道文件
* s 套接字
* c 字符设备文件
* b 块设备文件
* l 软连接文件

2.-name 按文件名搜索 

find 路径 -name "*.c"  
![image](https://user-images.githubusercontent.com/58176267/157042485-a1c2450f-b088-40b1-a75a-75b5b4a65ffc.png)


3. -maxdepth 按指定深度搜索  

find 路径 -maxdepth 1 -name "*.c"  

注意：-maxdepth参数应该作为find的第一个参数  
![image](https://user-images.githubusercontent.com/58176267/157042617-0c18ba3c-a64b-4db5-95b5-3a3c99cc9c0b.png)

4.-size 按文件大小搜索   文件大小单位：b、k、M、G  
注意：
两个-size都不能省
且单位区分大小写  
搜索大于1k小于500k的文件  
![image](https://user-images.githubusercontent.com/58176267/157043598-66da421e-3921-485e-bb89-c5dfaaf91fb3.png)

5. 按时间搜索  

-atime、-mtime、-ctime 天
-amin、-mmin、-cmin 分钟
a(Access) 最近访问时间  
m(Modify) 最近更改时间（更改文件属性）  
c(Change) 最近改动时间（更改文件内容）  
使用 stat+文件名   可以查看上面参数  

![image](https://user-images.githubusercontent.com/58176267/157045092-d122e097-28d8-4f9a-b7e8-48e10785a79b.png)

## find命令进阶  

1.将find 搜索的结果集执行某一指定命令

find 路径 -name "*tmp" -exec ls -l {} \;  

{}表示find搜索的结果集  
\表示转义字符

![image](https://user-images.githubusercontent.com/58176267/157046053-d81f7d69-227a-45c7-b28e-673ddff63a6a.png)

![image](https://user-images.githubusercontent.com/58176267/157046249-2698a781-6dfd-4a27-bf6a-9047d1f54b96.png)

2.-ok 以交互式的方式将find搜索的结果集执行某一指定命令   

![image](https://user-images.githubusercontent.com/58176267/157046843-508dae25-bb7d-41be-8a4b-630beb9a8042.png)


