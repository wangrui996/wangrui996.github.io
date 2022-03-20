# Email应用  

## Email应用的构成组件  

* 邮件客户端  
    * 读写Email消息 
    * 与服务器交互，收，发Email消息  
    * 典型的邮件客户端Outlook，Foxmail
    * Web客户端(使用Web Email时)   

* 邮件服务器/Mail Server  
    * 邮箱：存储发给该用户的Email  
    * 消息队列：存储等待发送的Email  
    
* **SMTP协议(Simple Mail Transfer Protocol)  简单邮件传输协议**  
    * 邮件服务器之间传递消息所使用的的协议  
    * 客户端：发送消息的服务器  
    * 服务器：接收消息的服务器  

## 存在邮件服务器的好处  

* 如果没有邮件服务器，我们的PC机或其它网络设备无法保证24小时接入网络，对方也是，因此无法保证对方发送的时候我们刚好可以接收，反过来也是  


## SMTP协议  

* 使用TCP进行Email消息的可靠传输
* 端口 25
* 传输的三个阶段  
    * 握手
    * 消息的传输  
    * 关闭
* 命令/响应的交互模式  (HTTP是请求响应模式)  
    * 命令(command) :ASCII文本  
    * 响应(response)：状态代码和语句  
   
* Email消息只能包含7位ASCII码(设计之处是不支持图片，音频等的)


## 实例  

![image](https://user-images.githubusercontent.com/58176267/156175812-9c30cf71-e971-46a4-891e-137021a8e728.png)


### SMTP交互实例  

![image](https://user-images.githubusercontent.com/58176267/156176698-bb60c69b-9f3c-4a7a-bd67-1ab4c5fd69be.png)

## SMTP协议  

* 使用持久性连接(每个TCP连接允许传输多个对象    在HTTP协议中 1.0版本使用非持久性连接，1.1就使用的是持久性连接) 
* 要求消息必须由7位ASCII码构成  
* SMTP服务器利用CRLF.CRL确定消息的结束（回车换行+.+回车换行）  

## SMTP与HTTP对比  

* HTTP：拉式(pull)——浏览器要到web server那拉回对象   SMTP：推式(push)——由发送方主动与接收方建立连接然后由发送方将消息推送到接收方  
* 都使用命令/响应交互模式  
* 命令和状态代码都是ASCII码  
* HTTP：每个对象封装在独立的响应消息中  SMTP：多个对象在由多个部分构成的消息中发送  
