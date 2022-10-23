# Gazebo仿真飞行手册  



## 实验步骤  

* 1.启动px4仿真环境  

```shell
roslaunch px4 d435i_px4.launch
```

* 2.启动里程计  

```shell
cd /home/wr/px4_fsm/src/px4ctrl/scripts/simulation
bash vins.sh
```

* 3.检查里程计话题是否正常  

```shell
rostopic echo /vins_estimator_gpu/imu_propagate
```


* 3.启动控制状态机  

```shell
roslaunch px4ctrl ctrl_sim.launch
```

* 状态机处于Idle状态，等待地面站切换Offboard模式————解锁

* 飞机处于takeoff模式起飞，到预定高度切换到Hover模式，并不断调节油门————状态机可查看此时悬停油门

* 观察飞机稳定的话，即可启动规划模块  



* 4.启动测试用的规划模块  

```shell
rosrun tra_test tra_test_node
```

## 关键话题查看


* 里程计消息  

```shell
rostopic echo rostopic echo /vins_estimator_gpu/imu_propagate
```

* 控制消息

```shell
rostopic echo /mavros/setpoint_raw/attitude
```




