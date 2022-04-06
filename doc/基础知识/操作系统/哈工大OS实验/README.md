# README   

[哈工大操作系统实验手册](https://hoverwinter.gitbooks.io/hit-oslab-manual/content/)  

[哈工大操作系统实验GITHUB代码]https://github.com/wangrui996/HIT-OSLab

https://www.lanqiao.cn/courses/115


## 环境配置方面  

### 编译源码报错  
在安装gcc3.4后编译报错：fatal error: bits/libc-header-start.h: No such file or directory  原因是环境不完善，在64位机器上编译产生32位机器可执行文件，还需要一些依赖  

sudo apt-get install gcc-multilib  解决  

### 运行run脚本时报错  


**2.libSM.so.6: cannot open shared object file: No such file or directory** 

运行  
ldconfig -p |grep -i libsm.so.6  
输出  
libSM.so.6 (libc6,x86-64) => /usr/lib/x86_64-linux-gnu/libSM.so.6
说明系统有64位的libSM.so.6库，但是没有32位的，

sudo apt-get install libsm6:i386
再次查看：
sudo find /usr/lib -name libSM.so.6  
显示  
/usr/lib/i386-linux-gnu/libSM.so.6下有了32位的链接库

但是在sudo apt-get install libsm6:i386时提示找不到库文件，通过以下命令解决(ubunut 18.04)  
```xml
sudo dpkg --add-architecture i386
echo "deb http://old-releases.ubuntu.com/ubuntu/ bionic main restricted universe multiverse" |\
sudo tee -a /etc/apt/sources.list.d/ia32-libs-bionic.list
sudo apt-get update
sudo apt-get install libsm6:i386
```

**3.libX11.so.6: cannot open shared object file: No such file or directory**  

通过命令dpkg-query -S libX11.so.6
得到包名：
libx11-6:i386: /usr/lib/i386-linux-gnu/libX11.so.6.3.0
libx11-6:amd64: /usr/lib/x86_64-linux-gnu/libX11.so.6
libx11-6:amd64: /usr/lib/x86_64-linux-gnu/libX11.so.6.3.0
libx11-6:i386: /usr/lib/i386-linux-gnu/libX11.so.6

sudo apt-get install libx11-6:i386


**4。libXpm.so.4: cannot open shared object file: No such file or directory**  

sudo apt-get install libxpm4:i386

### 运行成功  


![image](https://user-images.githubusercontent.com/58176267/161963901-a5e031f7-9b0d-4d87-9414-a50fab70984a.png)










