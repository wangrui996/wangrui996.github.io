


# ACM模式  



##  输入输出  


[C++基本的IO流](https://www.songbingjia.com/nginx/show-211503.html)  





## 小数点  

**头文件**  

#include <iomanip>

* 保留三位有效数字  如x = 10.0 / 3.0  输出的是3.33  如果x = 9.0 / 3.0 则输出3.00 

```cpp
cout << showpoint << setprecision(3) << x << endl;
```

*　这种情况，x = 9.0 / 3.0则输出3  

```cpp
cout << setprecision(3) << x << endl;
```


## 字符串处理  

### 案例1 输入一个未知长度的带空格的字符串  

 
#### 使用 getline(cin,char*) ————常用于不知道长度 

* 因为cin会阻塞，当字符串长度未知时，不能用cin使用while循环一直cin >> str ,  这样做会导致程序一直阻塞在这 


```cpp
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    string str;
    getline(cin, str);
    int wordCount = 0;
    float length = 0;
    
    for(char ch : str) {
        if(ch != ' ') {
            length++;
        } else {
            wordCount++;
        }
    }
    
    cout << showpoint << setprecision(3) <<length / (wordCount + 1) << endl;
    
    return 0;
}
```


####


####  例题  

* 将输入字符串中  元音字母替换为对应的大写字母  辅音字母替换为小写

```cpp
#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
    string str;
    getline(cin, str);
    unordered_map<char, char> map = {
        {'a', 'A'},
        {'e', 'E'},
        {'i', 'I'},
        {'o', 'O'},
        {'u', 'U'},
    };
    if(str.empty()) return 0;
    for(char& ch : str) {
        if(map.count(ch)) {
            ch = map[ch];
        } else if(ch >= 'A' && ch <= 'Z' && !map.count((ch - 'A' + 'a')) ) {
            ch = ch - 'A' + 'a';
        }
    }
    
    cout << str << endl;
    
    return 0;
}
```





#include <iostream>

using namespace std;

int calculateSum(const int& n) 
{
    int res = 0;
    int remain = n;
    if(remain == 1) 
        return 0;
    if(remain == 2)
        return 1;
    while(remain >= 3) {
        int count = remain / 3;
        res += count;
        remain = remain % 3 + count;
    }
    if(remain == 2) 
        res += 1;
    return res;
}

int main(int argc, char** argv)
{
    int n;
    while(cin >> n) {
        if(n == 0) 
            break;
        cout << calculateSum(n) << endl;
    }

    return 0;
}



## 头文件篇  

* ACM模式下 C++万能头文件 #include<bits/stdc++.h>  牛客网支持   




## #include<algorithm>  

* max  min   

* sort


## limits.h  

* INT_MAX   INT_MIN  




## 大顶堆  小顶堆  


```cpp
//升序队列  小顶堆
priority_queue <int,vector<int>,greater<int> > que;   
//降序队列
priority_queue <int,vector<int>,less<int> > que;
//对于基础类型 默认是大顶堆
priority_queue<int> a; 
//等同于 priority_queue<int, vector<int>, less<int> > a;
```

```cpp
#include <iostream>
#include <queue>
using namespace std;

//方法1
struct tmp1 //运算符重载<
{
    int x;
    tmp1(int a) {x = a;}
    bool operator<(const tmp1& a) const
    {
        return x < a.x; //大顶堆
    }
};
//方法2
struct tmp2 //重写仿函数
{
    bool operator() (tmp1 a, tmp1 b) 
    {
        return a.x < b.x; //大顶堆
    }
};
```


```cpp
#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>     // std::greater
 
using namespace std;
 
int main()
{
	int myints[] = { 10,60,50,20 };
 
	priority_queue<int> first;//默认构造大顶堆，基础容器为vector，相当于priority_queue<int, vector<int>, less<int> > 
	priority_queue<int> second(myints, myints + 4);
	cout << second.top() << endl;//此时输出最大元素60
	priority_queue<int, vector<int>, greater<int> >
		third(myints, myints + 4);//构造小顶堆
	cout << third.top() << endl;//输出最小元素10
 
	return 0;
}
```

```cpp
#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
 
using namespace std;
 
class mycomparison
{
	bool reverse;//reverse为ture时构造小顶堆，为false时构造大顶堆
public:
	mycomparison(const bool& revparam = false)
	{
		reverse = revparam;
	}
	bool operator() (const int& lhs, const int&rhs) const
	{
		if (reverse) return (lhs > rhs); //小顶堆
		else return (lhs < rhs); //大顶堆
	}
};
 
int main()
{
	typedef priority_queue<int, vector<int>, mycomparison> mypq_type;
	mypq_type fourth(myints, myints + 4);       // 大顶堆
        cout << fourth.top() << endl; //输出最大元素60
        //mypq_type fifth(myints, myints + 4, mycomparison(true));   // 小顶堆
        //cout << fifth.top() << endl;    //输出最小元素10
 
	return 0;
}
```



## 自定义比较  

### 对于vector  

* int型变量 升序

```cpp
bool cmp(const int &a, const int &b){
	return a < b;
}
sort(vec.begin(), vec.end(), cmp);
```

```cpp
sort(vec.begin(), vec.end(), greater<int>()); // 升序
sort(vec.begin(), vec.end(), less<int>()); // 降序
```


* 实现不限制vector中元素类型的自定义比较函数

```cpp
bool cmp(const pair<int, int> &a, const pair<int, int> &b){
	return a.second < b.second;
}
sort(vec.begin(), vec.end(), cmp);
```


### 对于优先级队列  

```cpp
class Cmp{
public:
	bool operator()(int a, int b){
		return a < b;
	}
}
priority_queue<int, vector<int>, Cmp> pri_que;

```




## 数组、哈希表、哈希集合相互转换  








