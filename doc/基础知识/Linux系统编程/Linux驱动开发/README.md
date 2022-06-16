# Linux驱动开发  

## 驱动开发基本概念  

* 外设有很多，对应的驱动有很多如led、键盘等，对上层应用而言，希望调用的都是些通用接口如open、read、write，每个外设如果都有不同接口让上层应用调用就太繁杂了  


![image](https://user-images.githubusercontent.com/58176267/173302901-494384fe-20f5-4b1d-bd13-bb11bdf8c9c4.png)  


## Linux驱动开发  

* Linux下驱动的开发不同于在MCU上的开发，直接操作寄存器不太现实，一般是根据Linux下的各种驱动框架进行开发，学习Linux驱动开发一般可以说是Linux下各种驱动框架的掌握  
* Linux下，驱动最终表现就是文件，/dev/xxx  那么对应的就有 open  write  read  close  
* 新的Linux内核支持设备树，一个.dts文件，该文件描述了板子的设备信息  

## Linux驱动分类  

* 一般区分方法：先判断是否是块设备或网络设备，不是的话就是字符设备

* 字符设备驱动  
    * 顺序的数据流     
* 块设备驱动  
    * 存储相关 EMMC   
* 网络设备驱动  

一个设备不一定只属于一个类型，如USB WIFI、SDIO WIFI属于网络设备驱动，但因为有USB和SDIO，因此也属于字符设备驱动  







