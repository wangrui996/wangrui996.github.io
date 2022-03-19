# 每日一题  

## 0482. 密钥格式化
[leecode链接](https://leetcode-cn.com/problems/license-key-formatting/)
```cpp
class Solution {
public:
    string licenseKeyFormatting(string s, int k) {    
        string ss, ans;
        //将原字符串替换为没有'-'且都为大写字母的字符串
        for(char c : s)
        {
            if(c == '-')
                continue;
            if(c <= 'z' && c >= 'a')
                c += 'A' - 'a';
            ss += c;       
        }
        //计算第一部分有多少个字符串 
        int first = ss.size() % k;
        //
        if(first != 0)
        {
            ans += ss.substr(0, first);
            ans += '-';
        }
        //处理ss中剩余的部分，每k个一组取出来作为子串拼接到ans后，并添加一个'-'
        for(int i = first; i < ss.size(); i+=k)
        {
            ans += ss.substr(i, k);
            ans += '-';
        }
    //如果只有first部分，那么ans最后一个字符为'-'，如果有后面的部分，最后一个字符也为'-',因此最后只取前n-1个字符
        return ans.substr(0, ans.size() - 1);
    }
};
```

### 





### 0414.第三大的数  
[leecode链接](https://leetcode-cn.com/problems/third-maximum-number/)

#### 方法1：set集合  
题目要求了重复的元素只算一次，想法是同时维护一个保存有三个元素的有序序列，标准库的set集合能自动排序，且能够去除重复元素，符合我们的要求，每次向set集合插入一个元素，如果元素个数大于3，就把最小的删除掉,最后根据集合的大小决定返回第三大的数还是最大的数    

时间复杂度:O(n)
空间复杂度:O(1)
```cpp
class Solution {
public:
    int thirdMax(vector<int>& nums){ 
        int n = nums.size();
        set<int> s;
        for(int i = 0; i < n; i++)
        {
            s.insert(nums[i]);
            if(s.size() > 3)
            {
                s.erase(*s.begin());
            }
        }
        if(s.size() == 3)
            return *s.begin();
        else
            return *s.rbegin();
    }
};
```


#### 方法2：设置3个观察变量分别记录最大，次大，第三大的数字 


在一个序列中找最大和第二大的数的经典思路是，用两个变量分别代表最大和次大的数，遍历数组根据数组元素与这两个变量的比较结果决定是否修改两个变量。  

注意点：注意题目中是否将重复元素算上，即1,2,2在该题中是无第三大的值的  

这里也是一样的思路：设置变量first，second，third分别代表最大，第二大和第三大的数字，遍历nums数组
初始值设置：题目说了数组元素的范围是[-2^31, 2^31-1],这三个变量的初始值应该是一个足够小的数，至少要比数组可能的最小值还要小
1.若nums[i] > first, 则  

    third = second;
    second = first;
    first = nums[i];

2.若  second < nums[i] < first  (因为不算重复元素，因此次大的值不光要大于second，还要小于first，排除等于first的情况),则  

    thrid = second；
    second = nums[i];

3.若 third < nums[i] < second;则  

    third = nums[i];
遍历完成后，根据third的值是否为"无穷小"判断返回third还是first。

```cpp
class Solution {
public:
    int thirdMax(vector<int>& nums){ 
        const long long INF = LONG_MIN;
        long first = INF, second = INF, third = INF;
        for(int i = 0; i < nums.size(); i++)
        {
            if(nums[i] > first)
            {
                third = second;
                second = first;
                first = nums[i];
            }
            else if(nums[i] > second && nums[i] < first)
            {
                third = second;
                second = nums[i];              
            }
            else if(nums[i] > third && nums[i] < second)
            {
                third = nums[i];
            }
        }
        if(third != INF)
            return third;
        else
            return first;
    }
};
```


### 0434.字符串中的单词数
[leecode链接](https://leetcode-cn.com/problems/number-of-segments-in-a-string/)

#### 方法1  
每遇到一个空格，检查前面字符是否为空格，如果满足s[i] == ' ' && s[i-1] != ' ', 则单词数量加1，这种方式是把每个单词和单词后紧挨着的空格视为一组，但是要注意，第一个字符应该跳过防止越界(思考一下第一个字符是什么并不影响结果)，看题目给的例子，最后一个单词后面可能没有空格，因此我们在字符串尾添加一个空格再遍历检查  

```cpp
class Solution {
public:
    int countSegments(string s) {
        int space_count = 0;
        s += ' ';
        for(int i = 0; i < s.size(); i++)
        {
            if(i == 0)continue;
            if(s[i] == ' ' && s[i-1] != ' ')    
                space_count++;
        }     
        return space_count;
    }
};
```  

#### 方法2  
把每个单词和它前面的空格看作一组，这样就是每检查到一个非空格字符后，检查它前面的字符，若前面为空格，单词数就加1。与上面的情况相反，不需要对字符串尾部的单词做特殊考虑(因为即使是最后一个单词，它前面也应该有一个空格)，但是需要考第一个单词，如果字符串第一个字符不是空格，那它就算一个单词，不然会漏掉这种情况，导致"hello world!"明明两个单词却认为是一个。  


```cpp
class Solution {
public:
    int countSegments(string s) {
        int space_count = 0;
        for(int i = 0; i < s.size(); i++)
        {
            if(i == 0 && s[i] != ' ')
            {
                space_count++;
                continue;
            }    
            if(s[i] != ' ' && s[i-1] == ' ')
                space_count++;
        }     
        return space_count;
    }
};
```
或者下面更简洁的写法：  
这个写法i == 0如果成立，(i == 0 || s[i-1] == ' ')结果就为1了，不会导致后面s[i-1]越界  
```cpp
class Solution {
public:
    int countSegments(string s) {
        int space_count = 0;
        for(int i = 0; i < s.size(); i++)
        {
            if(s[i] != ' ' && (i == 0 || s[i-1] == ' ')) 
                space_count++;
        }     
        return space_count;
    }
};
```

### 0187.重复的DNA序列
[leecode链接](https://leetcode-cn.com/problems/repeated-dna-sequences/)  

注意：先记录一个今天刷本题时遇到的一个问题，使用C++的size()函数导致异常访问越界！  
我在for循环中直接将size()函数返回值与有符号整型做运算后，再与有符号整型做了比较运算。  
在C++Primer中明确建议了不要混用有符号数与无符号数，否则可能发生意想不到的后果！  

之前在遍历容器时，有时会写成下面这样
    for(int i = 0; i < v.size(); i++)  
有时会写成下面这样  
    int n = v.size();
    for(int i = 0; i < n; i++)  
好像一直都是可以的，但是今天写这个题的时候写成了下面这样  
    for(int i = 0; i < s.size() - L + 1;  i++)  
这里L = 10，当字符串长度小于10的时候，循环不应该进入，但这里却进入了，导致数组越界。其实就是没有遵循上面说的原则，s.size() - L + 1的结果是一个无符号数，运算是负数的时候就变成了一个很大的正数导致这里一定能进入循环。所以正确的写法应该是
    int n = s.size(); //这里n就是一个有符号数
    for(int i = 0; i < n - L + 1;  i++) //有符号数间做比较，没有问题


### 方法1 滑动窗口 + 哈希表 

这个题目要求目标子串长度10,重复子序列判断可以用哈希表unmap判断
    1.遍历每个字符,使滑动窗口记录以该字符开头的连续10个字符子串，记为sub(std::string::substr(i, L))
    2.将该子串在哈希表中记录次数+1；unmap[sub]++;
    3.判断子串出现的次数，次数正好为2的就放入数组，其余不足，或大于2次的跳过(大于2次的前面已经放入过了)

时间复杂度：O(nL) //子串长度为常数l时，遍历n个字符，每个字符构造长度为L = 10的字符串，时间复杂度nL
空间复杂度：O(nL)

```cpp
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        const int L = 10;
        vector<string> ans;
        unordered_map<string, int> unmap;
        int n = s.size();
        for(int i = 0; i < n - L + 1;  i++)
        {
            string sub = s.substr(i, L);
            unmap[sub]++;
            if(unmap[sub] == 2)
                ans.push_back(sub);
        }
        return ans;
    }
};
```  

### 方法2　　



### 0441.排列硬币
[leecode链接](https://leetcode-cn.com/problems/arranging-coins/)　　

### 方法1 数学法　　
假设n个元素刚好为k行，则(1+k)*k/2  = n; k  = (-1 + sqrt(1 + 8 * n)) / 2;
注意这里n范围是1 <= n <= 2^31 - 1, 8 * n可能会溢出，所以需要用long转一下
```cpp
class Solution {
public:
    int arrangeCoins(int n) {
        int ans;
        long ln = n;
        ans = (-1 + sqrt(1 + 8 * ln)) / 2;
        return ans;
    }
};
```

或者直接简洁点
```cpp
class Solution {
public:
    int arrangeCoins(int n) {
        return (int)(-1 + sqrt(1 + (long long) 8 * n)) / 2;
    }
};
```

### 方法2 二分法  
练习下二分法  
```cpp
class Solution {
public:
    int arrangeCoins(int n) {
        //练习二分法,第1行到第mid行的元素个数和为sum = (1 + mid) * mid / 2; 
        //通过比较sum与n决定区间怎么变化
        int left = 1, right = n;
        int mid;
        while(left <= right)
        {
            mid = left + (right - left) / 2;
            long sum = (long long)(1 + mid) * mid / 2;
            if(sum > n) //意思是假设有mid行，这样算出来总元素个数就超过n了，因此一定少于mid行
                right = mid - 1;
            else if(sum < n)//假设有mid行算出来总元素个数还不够n，因此一定多于mid行
                left = mid + 1;
            else if(sum == n)//mid行，算出来总元素个数正好为n，那就是正好有mid行，直接返回mid
                return mid;
        }
        //最后left > right,最后一次比较的时候，如果sum>n,right=mid-1.left就对应mid处，此时说明实际上第mid行没填满(因为按照填满算超出总元素个数了)，应该返回right(left-1或mid-1)
        //如果sum<n,left=mid+1,right对应mid处，此时说明第mid行都填满了，但加起来还不够n，第left行肯定有元素但肯定没有填满，因此返回right
        return right;
    }
};
```




### 0412.Fizz Buzz 2021/10/13
[leecode链接](https://leetcode-cn.com/problems/fizz-buzz/)  

简单题，，注意数值转字符串方法 std::to_string(value)

```cpp
class Solution {
public:
    vector<string> fizzBuzz(int n) 
    {
        vector<string> ans;
        for(int i = 1; i < n + 1; ++i)
        {
            string s;
            if(i % 3 == 0)
                s += "Fizz";
            if(i % 5 == 0)
                s += "Buzz";
            if(i % 3 != 0 && i % 5 != 0)
                s += to_string(i);
            ans.push_back(s);
        }
        return ans;
    }
};
```
或  

```cpp
class Solution {
public:
    vector<string> fizzBuzz(int n) 
    {
        vector<string> ans;
        for(int i = 1; i < n + 1; ++i)
        {
            string s;
            if(i % 3 == 0)
                s += "Fizz";
            if(i % 5 == 0)
                s += "Buzz";
            if(s.empty())
                s += to_string(i);
            ans.push_back(s);
        }
        return ans;
    }
};
```  


### 0852.山脉数组的峰顶索引 2021/10/14
[leecode链接](https://leetcode-cn.com/problems/peak-index-in-a-mountain-array/)  
[剑指offerII069](https://leetcode-cn.com/problems/B1IidL/)  

二分法

```cpp
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int n = arr.size();
        int left = 1, right = n - 2;
        while(left <= right)
        {
            int mid = left + (right - left) / 2;
            if(arr[mid] > arr[mid-1] && arr[mid] > arr[mid+1])
                return mid;
            else if(arr[mid] > arr[mid-1] && arr[mid] < arr[mid+1])
                left = mid + 1;
            else if(arr[mid] < arr[mid-1] && arr[mid] > arr[mid+1])
                right = mid - 1;
        }
        return left;
    }
};
```  

### 240. 搜索二维矩阵 II 2021/10/25
[leecode链接](https://leetcode-cn.com/problems/fizz-buzz/https://leetcode-cn.com/problems/search-a-2d-matrix-ii/)  

### 思路分析  
1.由二分的想法很容易想到实现O(mlongn)时间复杂度的做法，就是遍历每一行，然后对每一行进行二分求解；  
2.能不能实现O(n)的时间复杂度？刚才的做法只利用了每一行是排序好的这一特点，但是每一列也是排列好的，能不能利用上？




