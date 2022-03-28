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

## 使用opencv4.5.5编译vins-fusion-gpu 

* 1.需要修改里面的一些函数接口，由于不想一个一个文件去看，干脆就根据编译时的报错，再去查opencv官网修改，基本都是些小改动不过蛮琐碎的  
* 2.修改里面需要cv_bridge和opencv的地方，设置好版本  
* 如果上面opencv4.5.5和使用opencv4.5.5编译的cv_bridge没问题的话，这里编译vins应该没大问题
* 自己在运行时报错：
```shell
rosrun vins vins_node /home/wr/vins/src/VINS-Fusion-gpu/config/px4_gazebo_sitl/px4_sitl_stereo_imu_config.yaml
/home/wr/vins/devel/lib/vins/vins_node: error while loading shared libraries: libopencv_imgcodecs.so.3.2: cannot open shared object file: No such file or directory
```
它找不到libopencv_imgcodecs.so.3.2库文件是肯定的因为我移动了他们的位置u不在系统搜索路径下了，但是我一直纳闷为什么编译时指定了opencv4.5.5并且最重要的cv_bridge也是用了opencv4.5.5编译的，那么编译时必然链接的是opencv4.5.5的库，但这里运行时为什么还会去找opencv3.2的库；  

**其实如果它报找不到opencv4.5.5的库文件我就知道怎么解决了，因为opencv4.5.5被我安装在了/usr/local/opencv455下面，不在运行时系统搜索动态库的路径下，而之前的opencv3.4.1是安在了/usr/local下，他的库文件直接在/usr/local/lib下当然能找到；解决这个问题有多种方式，我选择了在环境变量下修改加入下面的语句;**

```shell
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/opencv455/lib
```
**问题是它报错找不到opencv3.2的库文件，让我以为编译时使用了opencv3.4的库，但实际上不是的, 这个问题之前也遇到过，可能是ros melodic和ubuntu18.04自带的ros就是3.2版本的，找不到4.5.5版本的库文件的情况下又找了默认的opecnv3.2的库文件？**  

**总之一定要分清楚是编译链接阶段的错误还是运行时的错误，运行时报错找不到某个库，而这个库又能找到的话，那基本就是因为不在系统搜索路径下的原因**  




 
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




# 源码安装mavros
[源码安装mavros](https://blog.csdn.net/weixin_44917390/article/details/106320411)


# ROS工作空间的注意事项  









