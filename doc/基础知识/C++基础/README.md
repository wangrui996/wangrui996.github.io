<h1 align="center">C++基础</h1>


**C++基础知识**

- <font style="font-weight:bold; color:#4169E1;text-decoration:underline;" target="_blank">[基本语法](doc/基础知识/C++基础/基本语法/README.md)</font>  





## float与double类型数据  

* float是32位，double是64位
* float32位中，有1位符号位，8位指数位，23位尾数为
* double64位中，1位符号位，11位指数位，52位尾数位  
* 一般float型只能精确到小数到后六位即1e-6,将float型的数a的绝对值abs（a）与1e-6比较，如果abs（a）比1e-6还要小的话就可以认为a的值为零，因为小数六位以后是不精确的，是没有意义的  
* 比如数0.0000001虽然确实不等于零，但是第七位小数1是没有意义的就可以认为这个数等于0。
 

### 判断一个float或double类型数据是否等于0

* 判断一个单精度浮点数：if( abs(f) <= 1e-6 ) 满足即为0
* 要判断一个双精度浮点数：则是if( abs(f) <= 1e-15 ) 满足即为0
