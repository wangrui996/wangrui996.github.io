# 排序算法总结  


[排序算法超详细总结](https://leetcode.cn/circle/discuss/eBo9UB/#%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F)  

[10大排序算法总结](https://www.runoob.com/w3cnote/ten-sorting-algorithm.html)  


 
## bubble sort  

* 更新边界 + 提前结束   优化  

* 更新边界：记录前一轮交换的最终位置，说明该位置之后的元素为已排序状态，下一轮的交换只需执行到该处。
* 提前结束：当某一轮比较均未发生交换，说明排序已完成，可设置一个布尔值记录一轮排序是否有发生交换，若无则提前退出循环结束程序。


* 时间复杂度   最好 有序数组情况下 O(n)   最坏和平均 O(n^2)  
* 空间复杂度   O(1)
* 稳定

```cpp
#include <vector>  
#include <iostream>

using namespace std;  
  
void swap(vector<int>& nums, int i, int j)
{
    if(i == j)return;
    nums[i] ^= nums[j];
    nums[j] ^= nums[i];
    nums[i] ^= nums[j];
    return;
}


void bubbleSort(vector<int>& nums) {
    if(nums.size() < 2)
        return;
    int lastIndex = nums.size() - 1;
    int swapIndex = 0;
    bool isSwapped = true;
    
    while(isSwapped) {
        // 每一轮循环开始前先将isSwapped置为false，之后循环比较过程中，如果发生了交换再置为true，这样一轮循环结束后，如果还是false，说明数组已经有序  
        // 注意lastIndex在这一轮循环中不应该改变，因此需要一个额外的变量记录更新某一轮中交换的最后一个位置
        isSwapped =false;
        for(int i = 0; i < lastIndex; ++i) {
            if(nums[i] > nums[i + 1]) {
                //swap(nums, i, i + 1); //使用自定义的swap函数
                swap(nums[i], nums[i + 1]);
                isSwapped = true;
                swapIndex = i + 1;
            }
        }
        lastIndex = swapIndex;
    }
    return;
}

int main()  
{  
    vector<int> nums = {4,6,2,1,7,9,5,8,3};
    //vector<int> nums = {1,2,3,4,5,6,7,8,9};
    //vector<int> nums = {9,8,7,6,5,4,3,2,1};
    bubbleSort(nums);
    for(int temp : nums) {
        cout << temp << " ";
    }
    cout << endl;
}  
```
