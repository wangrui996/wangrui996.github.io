

# TCP 协议  

![image](https://user-images.githubusercontent.com/58176267/160266608-3d1701f3-2f24-40c8-9731-5562660e4380.png)


## TCP段结构  

传输层处理的是一个一个的segment(段)

![image](https://user-images.githubusercontent.com/58176267/160266809-f4ceff17-d563-48b1-86e0-7d0143233b40.png)


* sequrence number 和 ack number  不是段的编号，而是利用数据的字节数来计数  

* UAPRSF
  * U：urgent data（一般不使用）
  * A: 标志位  指示ACK number子段是否有效 
  * P: push data now 将数据立即推送到上层(一般不使用)
  * 下面三个是与连接的建立，拆除等相关的标志位
  * R：RST 
  * S：SYN
  * F: FIN   

* Receive window 接收窗口大小                        
## TCP的序列号和ACK  

### 序列号  

* 序列号指的是segment中第一个字节的编号，而不是segment的编号  
    * 如有1KB数据，拆成了两个segment，第二个segment的序列号，不是2(假设从1开始)或1(从0开始)，而是501或者500    
* 建立TCP连接时，双方随机选择序列号  







