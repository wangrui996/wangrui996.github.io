


# ACM模式  

[C++基本的IO流](https://www.songbingjia.com/nginx/show-211503.html)  


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
