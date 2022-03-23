# README 


1. 安装支持gpu的opencv4.5.5

2. cv_bridge  

重新下载了cv_bridge(1.13.0)但是指定opencv4.5.5编译时报错，可能有接口发生了变化  
下载更高版本的cv_bridge发现可能是针对ros2的?

因此采取了先用opencv3.4.1编译然后修改配置文件的方式  

* 重新下载vison_opencv，我选择了是tags 1.13.0  

* 编译安装

cv_bridge 修改CMakeLists.txt  
```cmake
set(OpenCV_DIR "/usr/local/opencv455/lib/cmake/opencv4")
find_package(OpenCV 4.5.5 REQUIRED
  COMPONENTS
    opencv_core
    opencv_imgproc
    opencv_imgcodecs
  CONFIG
)
```  
注意这里为了区分之前的cv_bridge341 重新安装一个目录
```shell
cmake -D CMAKE_INSTALL_PREFIX=/usr/local/cv_bridge455 ..
make -j16
sudo make install
```
* 修改配置文件  

```shell
sudo gedit /usr/local/cv_bridge455/share/cv_bridge/cmake/cv_bridgeConfig.cmake
```
```html
#if(NOT "include;/usr/local/include;/usr/local/include/opencv " STREQUAL " ")
if(NOT "/usr/local/opencv455/include/opencv4 " STREQUAL " ")
  set(cv_bridge_INCLUDE_DIRS "")
  set(_include_dirs "/usr/local/opencv455/include/opencv4")

set(libraries "cv_bridge;/usr/local/opencv455/lib/libopencv_core.so.4.5.5;/usr/local/opencv455/lib/libopencv_imgproc.so.4.5.5;/usr/local/opencv455/lib/libopencv_imgcodecs.so.4.5.5")
```
```shell
sudo gedit cv_bridge-extras.cmake
``` 
```shell
set(OpenCV_VERSION 4.5.5)
set(OpenCV_VERSION_MAJOR 4)
set(OpenCV_VERSION_MINOR 5)
set(OpenCV_VERSION_PATCH 5)
set(OpenCV_SHARED ON)
set(OpenCV_CONFIG_PATH /usr/local/opencv455/lib/cmake/opencv4)
set(OpenCV_INSTALL_PATH /usr/local/opencv455/include/opencv4)
set(OpenCV_LIB_COMPONENTS opencv_calib3d;opencv_core;opencv_cudaarithm;opencv_cudabgsegm;opencv_cudacodec;opencv_cudafeatures2d;opencv_cudafilters;opencv_cudaimgproc;opencv_cudalegacy;opencv_cudaobjdetect;opencv_cudaoptflow;opencv_cudastereo;opencv_cudawarping;opencv_cudev;opencv_dnn;opencv_features2d;opencv_flann;opencv_highgui;opencv_imgcodecs;opencv_imgproc;opencv_ml;opencv_objdetect;opencv_photo;opencv_shape;opencv_stitching;opencv_superres;opencv_video;opencv_videoio;opencv_videostab;opencv_viz;opencv_aruco;opencv_bgsegm;opencv_bioinspired;opencv_ccalib;opencv_cvv;opencv_datasets;opencv_dnn_objdetect;opencv_dpm;opencv_face;opencv_freetype;opencv_fuzzy;opencv_hdf;opencv_hfs;opencv_img_hash;opencv_line_descriptor;opencv_optflow;opencv_phase_unwrapping;opencv_plot;opencv_reg;opencv_rgbd;opencv_saliency;opencv_sfm;opencv_stereo;opencv_structured_light;opencv_surface_matching;opencv_text;opencv_tracking;opencv_xfeatures2d;opencv_ximgproc;opencv_xobjdetect;opencv_xphoto)
set(OpenCV_USE_MANGLED_PATHS FALSE)
set(OpenCV_MODULES_SUFFIX )
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

