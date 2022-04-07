

# 父子进程gdb调试  

基本的gdb调试： 编译程序时带-g选项  然后使用gdb a.out 开始调试  

存在fork函数创建子进程时，需要设置跟踪  


* set follow-fork-mode parent (默认)  设置父进程调试路径
* set follow-fork-mode child  设置子进程调试路径

* gdb test.out  
* b 行号  
* set follow-fork-mode child
* n或s(单步)
