


1.判断奇偶性  

根据 x & 1 等于0还是1来判断x是偶数还是奇数  

2.乘2的幂次方  

对于正数  通过左移一位，x <<= 1  将x扩大为原来两倍  同理通过右移一位，讲x缩小一倍  

3.vector的初始化

vector<vector<bool>> dp(n, vector<bool>(target + 1));


4.数组，集合，哈希表的相互转化  





# 类相关  

1.定义类的私有成员时  一般只定义  在构造函数初始化就行  

```cpp
private:
    vector<long long> count;    //可以
    vector<long long> count(5); //错误  
```