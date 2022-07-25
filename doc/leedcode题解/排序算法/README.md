# 排序算法总结  


[排序算法超详细总结](https://leetcode.cn/circle/discuss/eBo9UB/#%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F)  

[10大排序算法总结](https://www.runoob.com/w3cnote/ten-sorting-algorithm.html)  


 
## 1.bubbleSort  

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



## 2.selectSort


* 单元选择 每次遍历找到最小的元素并记录其下标，然后和遍历的起始位置元素交换  

* 稳定性： 存在跨越交换。找到本轮次最小值之后，将其与本轮起始数字交换，此时若中间有与起始元素同值的元素，将打破稳定性。
    * 例如 2 4 4 3 5   第二轮会交换nums[3]与nums[1] 交换后，4的顺序被打破  

* 时间复杂度：两层for循环，第1轮比较 n - 1 次(n = arr.length)，最后一轮比较1次。总比较次数为 n*(n - 1) / 2n∗(n−1)/2 次，时间复杂度为 O(n^2)
双元选择优化版本也是 O(n^2)      冒泡排序和选择排序的比较次数均为 O(n^2)，但选择排序的交换次数是O(n)，而冒泡排序的平均交换次数仍然是二次的。

空间复杂度：算法中只有常数项变量，O(1)。

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


void selectSort(vector<int>& nums) {
    if(nums.size() < 2)
        return;
    
    for(int i = 0; i < nums.size() - 1; ++i) {
        int minIndex = i;
        for(int j = i + 1; j < nums.size(); ++j) {
            if(nums[j] < nums[minIndex])
                minIndex = j;
        }
        if(minIndex != i)  /// 微优化，在数组基本有序情况下节省不必要的交换带来的开销
            swap(nums[i], nums[minIndex]);
    }
    
    return;
}



int main()  
{  
    //vector<int> nums = {4,6,2,1,7,9,5,8,3};
    //vector<int> nums = {1,2,3,4,5,6,7,8,9};
    vector<int> nums = {9,8,7,6,5,4,3,2,1};
    selectSort(nums);
    for(int temp : nums) {
        cout << temp << " ";
    }
    cout << endl;
}  

```

* 双元选择 ： 每次除了选择最小的，再选择一个最大的 
* 注意：为了优化交换次数，一轮找下来有好几个if判断，要特别注意，当交换完minIndex和left后，要判断下maxIndex是不是left，是的话，接下来交换maxIndex和right元素前需要先修改下maxIndex，因为此时maxIndex元素已经被换到了原来minIndex的位置  

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

void selectSort(vector<int>& nums) {
    if(nums.size() < 2)
        return;
    // 双元选择，每次从子区间选择最大和最小的，因为左右边界在收缩 维护左右边界即可 
    int left = 0, right = nums.size() - 1;
    
    while(left <= right) {
        // 初始化最小，最大值下标都为left
        int minIndex = left, maxIndex = left;
        for(int i = left; i <= right; ++i) {
            if(nums[i] < nums[minIndex])minIndex = i;
            if(nums[i] > nums[maxIndex])maxIndex = i;
        }
        // 本轮[left, right]区间寻找，最小和最大值索引相等，说明这个区间所有元素都相等，否则但凡有任意两个互不相等，一定不会出现minIndex == maxIndex
        if(minIndex == maxIndex)break;
        // 如果最小值索引不是left，就交换两者，但是可能会有个问题是：
        // nums[left]如果正好是最大值，该步相当于交换了最大值和最小值，下一步将最大值交换到right位置就是把最小值又放到了最右侧
        if(minIndex != left)swap(nums[left], nums[minIndex]);
        // 所以在最后一步交换前，判断下如果 maxIndex 是 left的话，那它刚刚已经被交换到了minIndex的位置，因此需要修改maxIndex = minIndex
        if(maxIndex == left)maxIndex = minIndex;
        if(maxIndex != right)swap(nums[right], nums[maxIndex]);
        left++;
        right--;
    }
    
    return;
}

int main()  
{  
    vector<int> nums = {4,6,2,1,7,9,5,8,3};
    //vector<int> nums = {1,2,3,4,5,6,7,8,9};
    //vector<int> nums = {9,8,7,6,5,4,3,2,1};
    selectSort(nums);
    for(int temp : nums) {
        cout << temp << " ";
    }
    cout << endl;
}  
```


