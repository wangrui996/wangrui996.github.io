# 字符设备驱动  

* **驱动就是获取外设或传感器数据，或控制外设** 所获取的数据交给应用程序  

* 用户程序想要访问内核资源，需要通过：**系统调用、异常(中断)和陷入(软中断)**    

* 每一个系统调用都有一个系统调用号  
    * 如 #define __NR_read 3   

![image](https://user-images.githubusercontent.com/58176267/173308097-ac1ee8bc-17d8-4770-a424-631cb82271cc.png)  

* 要有一个对应的文件结构体，使用open打开设备后，根据此结构体获取设备信息  

![image](https://user-images.githubusercontent.com/58176267/173309129-c052ce71-427d-4ca5-aa86-99d78fbc3c22.png)  



