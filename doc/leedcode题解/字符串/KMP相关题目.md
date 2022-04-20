

# KMP相关题目  


[](https://www.nowcoder.com/practice/bb1615c381cc4237919d1aa448083bcc?tpId=117)  

```cpp
class Solution {
public:

    int kmp(string S, string T) {
        
        vector<int> next(S.size());
        getNext(next, S);
        int res = 0;
        int j = 0;
        for(int i = 0; i < T.size(); ++i) {
            while(j > 0 && T[i] != S[j]) {
                j = next[j - 1];
            }
            if(T[i] == S[j]) {
                j++;
            }
            if(j >= S.size()) {   //找到一个匹配的 位置是从文本串的i - S.size() + 1开始的
                // 如果让记录或返回文本串中匹配的子串的起始位置，就记录会返回 i - S.size() + 1;
                res++; 
                // 这里j = next[j - 1];是精髓  
                // 以示例 S = "ababab",  T = "abababab" 为例，在找到第一个匹配的子串时，下一次循环i = 6 即字符'a'
                // 如果在这里把 j置为0，i置为 i - S.size() + 1 那么下一次 匹配相当于从i = 1，j = 0即上一个匹配起始位置的下一个位置开始，这样肯定没问题，但是仍然有些暴力
                // 像这里处理，j = next[j - 1] 即 2  i 下一次等于6 相当于前缀"ab"已经匹配好了  
                // 因为进入到这里，说明此时，模式串已经和i前面的某个子串匹配成功了，i如果移动到1这个位置，j移动到0，是不能保证能和模式串的第一个字符匹配的
                // 但是让i移动不动，j等于next[j-1] = 2,i前面刚好已经匹配好子串的后缀("ab"), 是和j位置前面的前缀("ab")匹配成功的 
                // 也就是，还是利用已匹配的信息，i不需要移动到1这个位置，而是4这个位置，只不过i移动到4，j移动到0，相当于i不变，j移动到2这里  
                j = next[j - 1];            
            }            
        }
    
        return res;
          
    }
    
    void getNext(vector<int>& next, const string& s) {
        next[0] = 0;
        int j = 0;

        for(int i = 1; i < s.size(); ++i) {
            while(j > 0 && s[i] != s[j]) {
                j = next[j - 1];                
            }
            if(s[i] == s[j]) {
                j++;
            }
            next[i] = j;
        }
        return;
    }  
    
};
```
