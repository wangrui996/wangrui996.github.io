# 排序算法总结  


[排序算法超详细总结](https://leetcode.cn/circle/discuss/eBo9UB/#%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F)  

[10大排序算法总结](https://www.runoob.com/w3cnote/ten-sorting-algorithm.html)  


 
## 1.bubbleSort 冒泡排序  

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



## 2.selectSort 选择排序


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


### 3.insertSort 插入排序

* 对于未排序的数据，在已排序序列中从后向前扫描，找到相应位置并插入  
* 假如是升序排列，将某个要插入元素，依次与它前面的排序好的序列元素比较，如果要插入元素比它前面元素小，就交换
* 插入排序的每一轮向前插入都使得该元素在完成插入后，从第一个元素到该元素是排序状态


#### 基础插入排序  

* 时间复杂度：两层for循环，外层总轮次为n - 1轮(n = nums.size())，当原数组逆序时，移动次数为 n*(n - 1) / 2次，最坏时间复杂度为O(n^2)，平均时间复杂度同为 O(n^2); 当原数组已基本有序时，接近线性复杂度 O(n)。例如原数组已完全排序，则算法只需比较 n - 1 次。

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


void insertSort(vector<int>& nums) {
    if(nums.size() < 2)
        return;
    
    for(int i = 1; i < nums.size(); ++i) {   // n-1轮循环
        int insertValue = nums[i]; // 记录插入值  后面有可能会被覆盖  
        // 当前要插入元素为nums[i]，此时区间 [0, i - 1]内元素是已排序好的  现在要做的就是从这个区间找到nums[i]的插入位置
        int j = i - 1;
        for(; j >= 0; --j) {
            if(nums[j] > insertValue)  // 稳定排序 因为这里当nums[i]等于它前面某个位置的nums[j]时，就break了
                nums[j + 1] = nums[j];
            else 
                break;
        }
        // 现在，j + 1位置就是插入元素要插入的位置
        nums[j + 1] = insertValue;  // 假如没有发生交换 j会等于i-1 nums[j + 1]就是nums[i]也没错
    }
  
    return;
}



int main()  
{  
    vector<int> nums = {4,6,2,1,7,9,5,8,3};
    //vector<int> nums = {1,2,3,4,5,6,7,8,9};
    //vector<int> nums = {9,8,7,6,5,4,3,2,1};
    insertSort(nums);
    for(int temp : nums) {
        cout << temp << " ";
    }
    cout << endl;
}  
```

#### 二分查找优化  

* 可以知道，对于要插入元素nums[i], 它前面的 [0, i - 1]区间是已经排序好的，因此在寻找它的插入位置时，不需要依次和前面元素一一比较，可以二分查找模板，在区间[0, i - 1]中，寻找它应当的插入位置，这个在二分的题目中有个专门的题目  
* 随便举个例子，搞清楚 当插入元素nums[i] 分别 大于，等于和小于二分中点元素时应该怎样收缩边界即可  


* 时间复杂度： 二分插入总的查找(比较)次数虽为 O(nlogn)，但平均移动 (每轮移动一半的数字) 次数仍是 O(n^2)

* 空间复杂度：算法中只有常数项变量，O(1)。 

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


int binarySearch(const vector<int> &nums, int start, int end, int target) {
    int left = start, right = end;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] > target) {
            right = mid - 1;
        } else if(nums[mid] < target) {
            left = mid + 1;
        } else if(nums[mid] == target) {
            left = mid + 1;
        }
    }
    return left;
}

void insertSort(vector<int>& nums) {
    if(nums.size() < 2)
        return;
    
    for(int i = 1; i < nums.size(); ++i) {
        int insertValue = nums[i];
        int insertIndex = binarySearch(nums, 0, i - 1, insertValue);
        // 移动元素
        for(int j = i - 1; j >= insertIndex; --j) {
            nums[j + 1] = nums[j];
        }
        // 插入  
        nums[insertIndex] = insertValue;
    }  
    return;
}



int main()  
{  
    vector<int> nums = {4,6,2,1,7,9,5,8,3};
    //vector<int> nums = {1,2,3,4,5,6,7,8,9};
    //vector<int> nums = {9,8,7,6,5,4,3,2,1};
    insertSort(nums);
    for(int temp : nums) {
        cout << temp << " ";
    }
    cout << endl;
}  
```

## 4.shellSort 希尔排序  

* 对简单插入排序的一种优化  
* 希尔增量gap 初始化 gap = n / 2;  gap每次折半，直到 gap 为 1，继续一次简单插入排序后结束  
* **注意：希尔排序的gap，既表示：间隔gap的元素为一组，也表示总共有gap组**
* 例如下图   gap初始化为5，表示第一次需要对5组数据分别进行排序 
* 能快速写出代码的关键在于，先把简单插入排序写熟练！ 然后理解希尔排序的基本步骤和记住希尔增量的更新方式，注意分组排序时是对有gap间隔的元素排序  
    
![image](https://user-images.githubusercontent.com/58176267/181150282-75063a1e-e79f-4bf5-8ee9-dc1102b6aea8.png)

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

void shellSort(vector<int>& nums) {
    if(nums.size() < 2)
        return;
    int n = nums.size();
    // 希尔增量 增量初始化为 n / 2  之后每次折半，知道gap = 1，进行一次简单插入排序后结束  
    for(int gap = n / 2; gap > 0; gap /= 2) {
        // 在希尔增量为gap时，表示需要对gap组数据分别进行插入排序
        for(int start = 0; start < gap; ++start) {
            // 对于每一组要排序的，start就是起始元素下标 比如 8 9 1 7 2 3 5 4 6 0 
            // gap为5时，共有5组需要排序，5组的起始下标分别是0,1,2,3,4 
            // 对于其中一组，简单插入排序 比如第一轮中，对第一组 8 3 排序  或者第二组9 5排序
            // 也就是要从该组的第二个元素开始，遍历整个该组的元素
            for(int i = start + gap; i < n; i += gap) {
                int insertValue = nums[i];
                int j = i - gap;
                // 与该组前面已经排序好的数组依次比较，找到插入位置  
                for(; j >= 0; j -= gap) {
                    if(nums[j] > insertValue) {
                        nums[j + gap] = nums[j];
                    } else break;
                }
                nums[j + gap] = insertValue;
            }

        }
    }
    return;
}



int main()  
{  
    vector<int> nums = {4,6,2,1,7,9,5,8,3};
    //vector<int> nums = {1,2,3,4,5,6,7,8,9};
    //vector<int> nums = {9,8,7,6,5,4,3,2,1};
    shellSort(nums);
    for(int temp : nums) {
        cout << temp << " ";
    }
    cout << endl;
}  
```


## 5.mergeSort 归并排序  

* 






