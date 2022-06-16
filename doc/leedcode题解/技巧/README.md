


1.判断奇偶性  

根据 x & 1 等于0还是1来判断x是偶数还是奇数  

2.乘2的幂次方  

对于正数  通过左移一位，x <<= 1  将x扩大为原来两倍  同理通过右移一位，讲x缩小一倍  

3.vector的初始化

vector<vector<bool>> dp(n, vector<bool>(target + 1));


4.数组，集合，哈希表的相互转化  


## 关于左移右移  

* 对于int类型正数，超过INT_MAX / 2的正数如果左移1位会越界，最小的正整数1，右移1位等于0 
* 负数的左移右移也代表将其乘2或者除以2，但是需要注意下-1右移1位还是-1(防止死循环)，小于INT_MIN / 2的int型变量左移1位会越界 


# 类相关  

1.定义类的私有成员时  一般只定义  在构造函数初始化就行  

```cpp
private:
    vector<long long> count;    //可以
    vector<long long> count(5); //错误  
```


# 字符串相关  

* 截取子串  substr  
* 向字符串某个位置插入字符  insert      
    * s.insert(s.begin() + i + 1 , '.');  // 在i的后面插入一个逗点
* 删除字符串内的字符  erase
    * s.erase(s.begin() + i + 1);  // 删掉i后面那个字符

