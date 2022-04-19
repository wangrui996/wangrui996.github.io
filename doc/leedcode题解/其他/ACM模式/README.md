


# ACM模式  

[C++基本的IO流](https://www.songbingjia.com/nginx/show-211503.html)  




## 字符串处理  

### 案例1 输入一个未知长度的带空格的字符串  

#### 错误  

* 因为cin会阻塞，当字符串长度未知时，这样么做会导致cout << c / count << endl;一直无法执行  

```cpp
#include <string> 
#include <iostream>
using namespace std;

int main() {
	
	float c = 0;
	int count = 0;
	string str;
	while (cin >> str) {
		count++;
		c += (float)str.size();
		cout << "str" << str << endl;
	}

	cout << c / count << endl;
	return 0;
}
```


#### 使用 getline(cin,char*) ————常用于不知道长度 

```cpp

```

#include <iostream>
#include <string>
#include<iomanip>

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
    
    cout << setprecision(3) <<length / (wordCount + 1) << endl;
    showpoint
    return 0;
}



####


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






* ACM模式下 C++万能头文件 #include<bits/stdc++.h>  牛客网支持  

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
