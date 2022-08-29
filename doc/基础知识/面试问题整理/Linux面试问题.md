# Linux面试问题 

* [grep工具](#grep工具)  
* [静态库与动态库的制作](#静态库与动态库的制作)  




<p id="grep工具"></p>      	
		
## grep工具  

[grep基本用法](https://baijiahao.baidu.com/s?id=1731545089327205615&wfr=spider&for=pc)  

[grep](https://www.cnblogs.com/HOsystem/p/16217517.html)


<p id="静态库与动态库的制作"></p>      	
		
## 静态库与动态库的制作  


* 静态库 gcc -c hello.c -o hello.o       ar cr libmyhello.a hello.o     gcc -o main main.c -L . -l myhello


* 动态库 gcc -shared -fPIC hello.c -o libmyhello.so          gcc -o main main.c -L . -l myhello
    *  -L ：表示要链接的库所在的目录
    *  -l (L的小写)：表示需要链接库的名称，注意不是库文件名称，比如库文件为 libmyhello.a，那么库名称为myhello
    *  -fPIC： 表示编译为位置独立的代码，不用此选项的话编译后的代码是位置相关的所以动态载入时事通过代码拷贝的方式来满足不同进程的需要，而不能达到真正代码共享的目的  

[静态库与动态库的制作](https://baijiahao.baidu.com/s?id=1731545089327205615&wfr=spider&for=pc](https://blog.csdn.net/chongbin007/article/details/123962714)  
