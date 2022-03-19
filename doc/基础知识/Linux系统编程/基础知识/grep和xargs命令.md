# grep命令  

根据文件内容检索  

1. grep -r "内容" 路径   
-r 递归搜索

![image](https://user-images.githubusercontent.com/58176267/157048874-45e40acf-5d25-4100-ae6a-7672108e32a0.png)

2. grep -r "内容" 路径 -n  
 
-n 显示行号  

![image](https://user-images.githubusercontent.com/58176267/157049248-556b2218-d44d-4c13-bd17-313fdb3e255d.png)


2.ps命令  

监控后台进程的工作情况  

如果只输入ps，默认只显示可以和当前用户交互的进程  

3.ps aux  

显示所有运行的进程  

4.ps aux | grep xxx  
检索进程内容包含xxx的进程  

下图显示和内核相关的进程
![image](https://user-images.githubusercontent.com/58176267/157050847-8eb20dd7-bca1-4e64-9410-556e545c3908.png)

**注意** 如果使用ps配合grep命令搜索结果只有一条，说明没有搜索到包含xxx内容的进程；因为搜索结果中有一条是搜索命令本身，所以如果有其他进程包含内容xxx，则搜索结果最少有两条  





5.find … | xargs ls -l 对 find搜索的结果集进行操作  

通过上面管道的用法，**ps aux的结果是个结果集，可以交给管道|再接着进行操作(如再通过grep将结果集中内容包含xxx的找到)  
前面学的find命令的结果也是个结果集，可以配合 | 使用吗？ 答案是需要配合xargs使用，，将搜索到的结果集进行执行** 

等价于find … -exec ls -l {} \;   

6. xargs和exec区别  

两者差别：
xargs要借助管道 | 执行  
在于当结果集很大的时候，exec会将所有结果都直接执行    xargs 会对结果集进行分片映射再执行，效率高一点  
但 xargs 也有缺陷，xargs 默认用空格来分割结果集，当文件名有空格的时候，会因为文件名被切割
失效



7. touch命令创建名称带有空格的文件 

touch abc xyz
直接执行上面的命令会创建两个文件  但如果想创建一个abc空格xyz的文件呢？  

* 通过转义字符解决    
![image](https://user-images.githubusercontent.com/58176267/157053384-17e71c05-0127-460d-83fb-022e55b27da8.png)

* 文件名加单引号  
touch 'abc xyz'  

8.**问题**  
通过find 配合-exec参数执行，能找到文件名带空格的文件  
![image](https://user-images.githubusercontent.com/58176267/157056082-46f87ed5-7fd8-4a23-86b3-54b15f28c195.png)

但是find配合管道和xargs就出现下面情况  xargs 默认用空格来分割结果集，当文件名本身就有空格的时候，会因为文件名被分割而失效  
![image](https://user-images.githubusercontent.com/58176267/157056198-3ab21f99-d776-4a2c-a206-76f21b07051f.png)  

**解决方法**：  
不让xargs使用空格作为切分方式
-print0 指定切分符号位使用null  由于执行时也要用这个方式所以后面也要有这个参数  

![image](https://user-images.githubusercontent.com/58176267/157058364-f02a1c63-0417-41ea-b3d7-5abd6f7afcfc.png)


