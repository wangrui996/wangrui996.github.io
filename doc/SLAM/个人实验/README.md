# README 


1. 安装支持gpu的opencv4.5.5

2. cv_bridge  

重新下载了cv_bridge(1.13.0)但是指定opencv4.5.5编译时报错，可能有接口发生了变化  
下载更高版本的cv_bridge发现可能是针对ros2的?

因此采取了先用opencv3.4.1编译然后修改配置文件的方式  

* 重新下载vison_opencv，我选择了是tags 1.13.0  


## 使用opencv4.5.5编译cv_bridge!  

编译前需要修改的地方
https://github.com/ros-perception/vision_opencv/issues/272


按上面修改完后，编译安装
 
注意这里为了区分之前的cv_bridge341 重新安装一个目录
```shell
cmake -D CMAKE_INSTALL_PREFIX=/usr/local/cv_bridge455 ..
make -j16
sudo make install
```






 
## cmake更换高版本 (这里没有用到，只做下记录)

使用cmake时发现其默认的最小版本是3.13 而cmake -version发现目前版本是3.10  

下载高版本源码编译安装 
https://gitlab.kitware.com/cmake/cmake

进入源码目录  
```shell
mkdir build  
cmake ..
make -j16
sudo make install
```

