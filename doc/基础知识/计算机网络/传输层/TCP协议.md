

# TCP 协议概述 

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

### ACKs

* 希望接收到的下一个字节的序列号 
* 累计确认： 该序列号之前的所有字节均已被正确接收到 (GBN也是采用累积确认)  

**接收方如何处理乱序到达的Segment？**   

* TCP规范中没有规定，由TCP的实现者做出决策
    * GBN接收到乱序的会直接丢掉
    * SR会缓存起来  

下图演示了简单的TCP数据传输过程（假设连接在之前就已经建立了）  

* hostA发送的数据为一个字符C(1个字节)  段的序列号为42， 期望收到的下一个字节的序列号是79 

* hostB回传字符C，返回的段的序列号是79，ACK是43(刚才段的序列号42，已经接收到，现在期望接收的下一字节序列号就是43，刚才一个字符C占一个字节)，ACK为43也说明43之前的已经接收  

* hostA收到以后再发一个确认，序列号43，ACK80，不带任何数据，表示下一个期望接收的是80

![image](https://user-images.githubusercontent.com/58176267/160272941-df480678-0603-485b-b591-1dc2eccbaba6.png)



# TCP 可靠数据传输  


![image](https://user-images.githubusercontent.com/58176267/160273003-1428e312-1575-4978-ab50-7f624a5a8a6c.png)



## TCP RTT 和超时  

**如何设置定时器的超时时间？**  

* 大于RTT
    * 但是RTT是变化的  
* 过短
    * 不必要的重传(可能只是延迟)
* 过长
    * 对段丢失反应慢 

**如何估计RTT？**  

* SampleRTT：测量从段发出去到收到ACK的时间
    * 忽略重传 
* SampleRTT变化 
    * 测量多个SampleRTT，求平均值，形成RTT的估计值EstimatedRTT

 * **指数加权移动平均** ：用新测得RTT,更新   EstimatedRTT = (1-a) * EstimatedRTT + a * SampleRTT

### 定时器超时时间设置  

* EstimatedRTT + “安全边界”
* EstimatedRTT变化大————>较大的边界  

* 测量RTT的变化值 ： SampleRTT与EstimatedRTT的差值    

![image](https://user-images.githubusercontent.com/58176267/160273397-0f5c5ddc-79dd-478a-adf9-9ea4f23c9f90.png)

* 定时器超时时间设置  

![image](https://user-images.githubusercontent.com/58176267/160273410-f408f271-4241-4913-8680-e9a5a461a728.png)



## TCP发送方事件  

* **1.从应用层收到数据**
    * 创建Segment
    * 序列号是Segment第一个字节的编号
    * 开启定时器
    * 设置超时时间 TimeOutInterval

* **2.超时**
    * 重传引起超时的Segment （注意，这里只重传引起超时的那一个segment 与SR类似 ，GBN是重传多个）  
    * **这里的重传，因为只有一个定时器，所以重传的是具有最小序列号的没有被确认的segment？**
    * 重启定时器

* **3.收到ACK**
    * 如果确认此前未确认的Segment
        * 更新sendbase (滑动窗口向右移动) 
        * 如果窗口中还有未被确认的分组，重启启动定时器 (TCP中只使用一个定时器)  
       
       
## TCP重传示例 

![image](https://user-images.githubusercontent.com/58176267/160273804-97b4f744-4532-4518-9d69-a8e49fb55d80.png)


![image](https://user-images.githubusercontent.com/58176267/160273873-46697bb5-863c-4e5a-b959-ce2224963d46.png)


## TCP 接收方事件与动作 / ACK的生成  

* 1.到达了一个按序的段(期望的序列号和接收到段的序列号相同)， 且在这个段之前的所有数据已经被ACK————接收方延迟ACK，等待最多500ms看是否还有下一个段，如果没有下一个段来，就发送ACK
* 2.接收到按序的段，且刚才已经有一个段在等待ACK确认(上面的情况)————立即发送累积确认ACK，确认之前和当前收到的按序到达的段

* 3.接收到一个乱序的段（会检测到空隙，比如期望的序列号是100，来的是200），立即发送重复ACK，指示自己所期望收到的段的序列号(还是发ACK100)  
 
* 4.接收到部分会全部能够填补空隙的段， 发送ACK （前提是？）


![image](https://user-images.githubusercontent.com/58176267/160273966-3ee9ba3d-33cf-416b-bcff-2d42e1c43204.png)




## TCP 快速重传机制  

核心：通过重复ACK检测分组丢失  

原理：由于流水线机制，发送方会连续发送过个分组，如果某个分组丢失，接收方收到乱序的分组，会发送之前没收到的那个序列号的ACK  

* 因此如果发送方收到对同一数据的3个ACK，则假定数据之后的段已经丢失  
    * **快速重传** ： 在定时器超时之前进行重传   

**注意  这里为什么是3次， 因为收到重复的ACK，本身是无法判断因为乱序还是丢失  

* 比如接受方期望的100收到了300，发送ACK100，后面又收到200，还是发送ACK100，因此收到2次重复的ACK，也很有可能是因为乱序到达
* 3次重复的ACK，则很可能不是因为乱序导致的了  也就是三次重复ACK，相对比乱序导致，丢失的可能性更大  


![image](https://user-images.githubusercontent.com/58176267/160274443-72d5568a-3f68-4a87-8398-80da62b18ba5.png)


### 快速重传算法  

![image](https://user-images.githubusercontent.com/58176267/160274663-e3e1343f-1209-4237-84b2-49d40d69c558.png)

       
       
       
       
  



















