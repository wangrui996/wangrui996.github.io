

# GBN与SR协议


# GBN协议   

* 假设分组头部包含 k bit序列号  则共有2^k序列号可用  
* 窗口尺寸为N，最多允许N个分组为确认  

![image](https://user-images.githubusercontent.com/58176267/160112562-0f3bec93-e4e9-4fdb-a5ce-c9f99bdae223.png)  

绿色部分：已经发送并被确认的分组  

**滑窗中最小的那个序列号，定义为send_base**

黄色部分：已经发送，还未确认的分组

蓝色部分：滑窗内可用的序列号 

nextseqnum: 滑窗内可用的序列号最小的那个  所以接下来如果要用就用这个  

白色部分： 当前不可使用的序列号(滑窗还没覆盖到)  

### GBN 发送方


**GBN采用累积确认的机制**

* ACK(n) : 确认到序列号n(包含n)的分组均已被正确接收  即序列号为 n， n-1， n-2....的分组都已经被正确接收了 
    * 可能收到重复的ACK  由于信道可能存在丢包等，可能会收到重复的ACK，可以解决
* 为空中的分组设置**计时器(timer)**  
* 超时(timeout)时间 ：超时是发生在某个分组上的(序列号)，假设对应的是N，则重传序列号大于等于n，但未收到ACK的所有分组


#### GBN发送方扩展(包含了变量)的FSM  

* 初始时 base(上图中的send_base) = 1   nextseqnum = 1 （nextseqnum表示滑窗内新发送分组时可用的起始序列号）


![image](https://user-images.githubusercontent.com/58176267/160113849-a53ef0a9-9ea9-4dee-9bf0-9b7f580b331e.png)







