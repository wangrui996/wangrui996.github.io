

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

       
       
# TCP流量控制  

![image](https://user-images.githubusercontent.com/58176267/160349849-4a61ac35-58a7-465b-b4b6-2259dd3390f6.png)

![image](https://user-images.githubusercontent.com/58176267/160350236-c1951c2d-808d-4170-a02d-6daa1762b4e9.png)


* 加入Receiver告知Sender RcvWindow = 0  
    * 如果发送方不发送，那么之后接收方有空闲，发送方也不会发————死锁
    * **发送方应该仍然发送一个较小的段，从而在让接收方发送ACK，此时带有新的RevWindows信息，避免死锁的现象**

       

# TCP连接管理  

TCP是面向连接的传输层协议  因此，在实际数据传输前，要建立连接，数据都传输完了，要拆除连接  

## 三次握手  

* 1.客户机发送TCP报文段至服务器，其中SYN位置1,
    * 携带的信息有  SYN位为1(表示要建立连接)、客户机选择的初始的序列号client_isn（初始序列号的选择机制有很多研究，比如随机选择？）
    * 不携带数据

* 2.服务器收到SYN报文段，如果自己可以连接连接，服务器分配缓存，并答复SYNACK报文段  
    * SYN标志位还是1
    * 选择自己的初始序列号并告知客户端server_isn
    * ACK client_isn + 1 (刚才客户端选择的序列号的基础上加1)

* 3.客户机收到 SYNACK 报文段，答复ACK报文段 
    * 该报文段中SYN为0
    * 序列号为client_isn + 1
    * ACK server_isn + 1
    * 可以包含数据    
    * 目的是为了告知服务器，自己收到了服务器同意建立连接的报文段 

### 为什么要用三次握手  



### TCP 三次握手  

* 可以看到，在第二次握手时，服务器就分配资源，假如第三次握手也就是客户机发送的ACK没有被服务器收到，服务器会保留所分配的资源一段时间，等它确认该连接不会再建立时，再释放资源 

![image](https://user-images.githubusercontent.com/58176267/160354165-861e20b1-ea7e-4687-bff8-c8266c4bfbdf.png)



### TCP 关闭连接   

连接的拆除，客户机和服务器都可以发起，大多数情况是客户机发起请求  

![image](https://user-images.githubusercontent.com/58176267/160355293-f26b6550-d1a9-4dd7-9008-60470b151851.png)


### TCP连接管理  

下图分别表好似客户机和服务器上TCP的生命周期，可以看出

* 客户端
    * 初始是TCP关闭状态
    * 应用层需要一个TCP连接时，TCP发送SYN报文段尝试连接，进入SYN_SENT状态,等待SYN ACK 
    * 收到SYN ACK后，发送ACK,进入ESTABLISHED状态，该状态下，可为上层应用传输数据
    * 当上层应用希望关闭连接时，TCP发送FIN报文段，进入FIN_WAIT_1状态
    * 当收到ACK时，进入FIN_WAIT_2状态
    * 当收到FIN报文段时，发送ACK，进入TIME_WAIT等待状态
    * 一般会等待30s，这个过程如果又收到FIN，会再次发送ACK； 等待完毕，关闭连接  
    
* 服务器端类似

![image](https://user-images.githubusercontent.com/58176267/160357273-f3e3226d-e2d7-4486-bb43-edf36e83a01d.png)



# TCP 拥塞控制

* 非正式定义 ： 太多发送主机发送了太多数据或者发送速度太快，以至于网络无法处理  
* 表现 
    * 分组丢失 (路由器缓存溢出)  路由器缓存是有限的，数据发送太多太快时，如果路由器缓存溢出，就会导致分组丢失
    * 分组延迟过大 （在路由器缓存中排队）  前面知识讲过分组延迟由四部分构成，这里主要指排队延迟

* 可靠数据传输解决了分组丢失问题，那里更多强调的是 针对端到端的连接，从个体利益的角度，采用确认，重传等机制保证数据传输  而拥塞控制更像是一个社会问题，从整体角度出发，不能使整个网路拥塞，瘫痪  

* 拥塞控制 vs 流量控制
    * 流量控制 指的是发送方不要发送太快，以至于接收方无法处理  
    * 拥塞控制 指的是在可靠数据传输基础上要做出部分牺牲，使整个网络工作好

## 拥塞的成因的代价  

1.场景一： **分组的时延大**  

* 两个发送方和两个接收方共用一个路由器，假定路由器缓存无限大
* 假定链路带宽为C
* 路由器缓存无限，不管A,B发送数据速度有多快，路由器都能缓存下来发送给接收方C,D  不会出现丢包，因此发送方没有重传  

下图中，横坐标表示A,B发送数据速率(假设两者一致)，纵坐标表示C,D主机接收到数据的速率

* **吞吐率——左图表示** 
    * 随着横坐标增大，小于C/2时(C为路由器出口的链路带宽)，线性增长   当横坐标达到C/2时，接收方接收数据速率就不再增长了，因为路由器出口链路带宽总共为C
    * 因此，发送方发送速率再快都可以，但是总的速率超过路由器链路带宽后，接收方接受数据的速率不再改变，也就是达到了最大的**吞吐率**；

* **时延————右图表示**
    * 当发送方发送速率逐渐增大时，时延也缓慢增长
    * 当发送方发送速率接近C/2时，时延快速增长，接近C/2时时延会无限大


![image](https://user-images.githubusercontent.com/58176267/160548430-37c81450-5d4b-4bf9-b6fc-b56df24100ea.png)


2.场景2  

拥塞的代价： 造成资源的浪费

![image](https://user-images.githubusercontent.com/58176267/160550439-4cfab85b-fe1f-4347-a7c1-30a843b9944d.png)


* 情况a ： 发送方发送速率不会超过R/2，因为发送方会查询路由器buffer，没空闲不会发，如果发送方发送速率超过了R/2，路由器buffer肯定会满，发送方也不会发
* 情况b ： 分组丢失会重发  b图，吞吐率降低   
* 情况c ： 分组丢失和定时器超时后都重发  吞吐率变得更低 

![image](https://user-images.githubusercontent.com/58176267/160550546-d91ecef3-dec1-4799-bfca-9f8527071800.png)


3.场景3  

在多条网络中，当分组在某个路由节点丢弃时(由于拥塞缓存满了),任何用于该分组的“上游”传输能力全部被**浪费**掉 （就是前面的资源白浪费了）

* 如果发送方发送速率不断上升时到一定程度时，接收方接收速率最终可能会接近于0，也就是很多向网络发送数据的，但是几乎没有数据被正确接收，也就是网络所有资源都被浪费掉了，网络瘫痪  

![image](https://user-images.githubusercontent.com/58176267/160551976-254593aa-bd4f-4d21-a78f-81fce3afacc0.png)


![image](https://user-images.githubusercontent.com/58176267/160552690-091e9b53-1fe2-475e-8442-154648a392fd.png)


## 拥塞控制原理  

### 拥塞控制方法  

![image](https://user-images.githubusercontent.com/58176267/160553825-2e284fd9-2527-4c59-b75f-e4536bbc05ab.png)


### 网络辅助拥塞控制案例 ATM   ABR

![image](https://user-images.githubusercontent.com/58176267/160554233-ed37b859-35a7-4f37-a415-9bd2536ae5be.png)  

![image](https://user-images.githubusercontent.com/58176267/160554932-0bc9a481-64e7-4b2e-a095-f220b107aa7d.png)  


## TCP 拥塞控制原理  











