# DNS记录和消息格式  

## DNS记录  

* 资源记录（RR， resource records） 
    *  RR format： 四元组 (name, value, type, ttl)    ttl是关于时间有效性的字段  
    *  不同的type，name和value的解释不同  
* Type = A
    * Name：主机域名
    * Value：主机IP地址  
* Type = NS   指出某个域的域名解析服务器是谁
    * Name：域(edu.cn)
    * Value：该域权威域名解析服务器的主机**域名**  
* Type = CNAME   别名服务  指出某一真是域名别名背后对应的真实域名  
    * Name：某一真实域名的别名  
        * www.ibm.com——servereast.backup2.ibm.com
    * Value：真实域名 
* Type = MX  用于邮件   
    * Value是与Name相对应的邮件服务器  
 
 
 ## DNS协议与消息格式  
 
 ### DNS协议
 
* 查询(query消息)和回复(reply消息) 
* 查询和回复消息格式相同  
 
 ### DNS消息格式  
 
 * 消息头部  
    * Identification：16位查询编号，回复使用相同的编号  
    * flags 标志位
        * 查询还是回复消息
        * 期望递归
        * 递归可用
        * 是否是一个权威回答  
 
### 遗留问题 

* 1.DNS使用的传输层协议是TCP还是UDP？  
* 还有哪些在应用层实现的但却是Internet的核心服务  


