# 排序算法总结  


[排序算法超详细总结](https://leetcode.cn/circle/discuss/eBo9UB/#%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F)  

[菜鸟教程10大排序](https://www.runoob.com/w3cnote/heap-sort.html)

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


### 自顶向下 非原地  

```cpp
#include <vector>  
#include <iostream>

using namespace std;  

void merge(vector<int>& nums, vector<int>& temp, int leftPos, int leftEnd, int rightEnd) {
    int rightPos = leftEnd + 1;
    int leftIndex = leftPos, rightIndex = rightPos;
    int tmpIndex = leftPos;

    while(leftIndex <= leftEnd || rightIndex <= rightEnd) {
        while(leftIndex <= leftEnd && rightIndex <= rightEnd) {
            if(nums[leftIndex] <= nums[rightIndex]) {
                temp[tmpIndex++] = nums[leftIndex++];
            } else {
                temp[tmpIndex++] = nums[rightIndex++];
            }
        }
        while(leftIndex <= leftEnd) {
            temp[tmpIndex++] = nums[leftIndex++];
        }
        while(rightIndex <= rightEnd) {
            temp[tmpIndex++] = nums[rightIndex++];
        }
    }
    
    // 将数据拷贝回原数组  
    for(int i = leftPos; i <= rightEnd; ++i) {
        nums[i] = temp[i];
    }
    return;
}

void mergeSort(vector<int>& nums, vector<int>& temp, int start, int end) {
    // 要排序区间小于等于1个元素，直接返回 已经是有序的了  
    if(start >= end)
        return;
    int mid = start + (end - start) / 2;
    mergeSort(nums, temp, start, mid);
    mergeSort(nums, temp, mid + 1, end);
    merge(nums, temp, start, mid, end);
}


int main()  
{  
    vector<int> nums = {4,6,2,1,7,9,5,8,3};
    //vector<int> nums = {1,2,3,4,5,6,7,8,9};
    //vector<int> nums = {9,8,7,6,5,4,3,2,1};
    vector<int> temp(nums.size());
    
    mergeSort(nums, temp, 0, nums.size() - 1);
    for(int temp : nums) {
        cout << temp << " ";
    }
    cout << endl;
}  
```

### 自低向上 非原地  

* 递归方法是先拆成两组，对每一组各自调用排序函数排序后合并，这样不断递归下去，最终对单个数排序后(单个数不用排，递归终止条件)，先是一一合并，然后两两合并，一直到两组合并后结束  
* 非递归方法就是直接先一一合并，然后两两合并，最后两组合并
* 由于最开始单个元素不需要合并，因此定义一个变量 gap，记录每次合并时，区间左右两边各有多少元素，初始化为1，表示第一次是两两一组合并，之后每次gap *= 2;  那gap到什么为止呢？**注意：gap的含义是要合并的大区间中，左右两侧各几个元素，但是如果数组元素总个数n，不是2的次幂，会出现左右子区间数量不同的情况，因此不能让 gap <= n / 2， 而是 gap < n**
    * 例如，4,3,5,6,3,5 这个数组， gap为1时 排序后是 3,4,5,6,3,5  gap *= 2 变成4  此时仍需要对 3,4,5,6 和 3,5两个子区间合并 但是 如果按照gap <= n / 2，此时不满足，就不会继续合并了 而按照 gap < n 满足条件并合并后 数组为 3,3,4,5,5,6  gap *= 2后变为8 不再满足  

* **综上，这里的gap最好按这样理解：gap是要合并的大区间中，左侧子区间的元素个数，这样，当gap等于n时，表示要合并的区间左侧子区间有n个元素，表明要对一个数组合并，是没必要的，也就是可以直接结束了，而当gap小于n时，比如gap等于n - 1，表示要合并的大区间，左侧范围是[0, n - 2]共n个元素，右侧区间是下标n - 1这一个元素，比如数组元素n = 3，gap = 2时仍要合并，而不是截止到gap = 3 / 2 = 1**

* 每一轮合并时可能要对好多个区间合并，起始位置i肯定是从0开始，合并完之后，i应该加上gap * 2，移动到下一组位置继续合并两个子区间，当i移动到整个数组的末尾(新的要合并的区间只有一个元素)或者越界，就不再合并    
    * 比如 4,6,2,1,7,9,5,8,3   gap = 1 时， 内层循环i从0开始，合并完4,6  i += 2 * gap 变成2 新的要合并的区间起始位置变成了2...


* 因此，外层可以用while循环或者for循环控制，gap从1开始每次扩大2倍，直到其大于等于n()


```cpp
#include <vector>  
#include <iostream>

using namespace std;  

void merge(vector<int>& nums, vector<int>& temp, int leftPos, int leftEnd, int rightEnd) {
    
    // 主要针对最后一组可能不能保证合并大区间左右两侧都正好为gap个数据
    // 如果要合并区间，只有左子区间，不需要合并直接返回
    // 也可以在mergeSort函数内循环中，leftBorder < end 改为 leftBorder < end - gap 一样的，都是为了使得，如果最后几个元素不够gap个就不需要排序了
    if(leftPos >= nums.size() || leftEnd >= nums.size())return;
    // 如果要合并区间，左右子区间都存在，此时左子区间一定有gap个数据，但是右子区间不一定够；
    // 比如 最后三个元素是 5,4,2  需要合并5,4和2 如果只按排序算法中计算的结果，此时rightEnd已经越界  
    // 这里多加个判断，帕西算法计算左右子区间边界时不需要额外考
    // 当然也可以直接在调用merge的地方，最后一个参数传入 min(leftBorder + 2 * gap - 1, nums.size() - 1)
    if(rightEnd >= nums.size())rightEnd = nums.size() - 1; 
    
    int rightPos = leftEnd + 1;
    int leftIndex = leftPos, rightIndex = rightPos;
    int tmpIndex = leftPos;

    while(leftIndex <= leftEnd || rightIndex <= rightEnd) {
        while(leftIndex <= leftEnd && rightIndex <= rightEnd) {
            if(nums[leftIndex] <= nums[rightIndex]) {
                temp[tmpIndex++] = nums[leftIndex++];
            } else {
                temp[tmpIndex++] = nums[rightIndex++];
            }
        }
        while(leftIndex <= leftEnd) {
            temp[tmpIndex++] = nums[leftIndex++];
        }
        while(rightIndex <= rightEnd) {
            temp[tmpIndex++] = nums[rightIndex++];
        }
    }
    
    // 将数据拷贝回原数组  
    for(int i = leftPos; i <= rightEnd; ++i) {
        nums[i] = temp[i];
    }
    return;
}

void mergeSort(vector<int>& nums, vector<int>& temp, int start, int end) {
    // 要排序区间小于等于1个元素，直接返回 已经是有序的了  
    if(start >= end)
        return;
    
    int gap = 1;
    for(; gap < nums.size(); gap *= 2) {
        for(int leftBorder = 0; leftBorder < end; leftBorder += 2 * gap) {
            // leftBorder：要合并区间的左边界，每一轮都是从0开始，每次加上2倍gap  
            // 左子区间元素个数为 gap 因此左子区间结束位置为 leftBorder + gap - 1;
            // 右子区间起始位置leftBorder + gap，结束位置是 leftBorder + 2 * gap - 1;
            //cout << "left:" << leftBorder << endl;
            merge(nums, temp, leftBorder, leftBorder + gap - 1, leftBorder + 2 * gap - 1);
        }
    }
}


int main()  
{  
    vector<int> nums = {4,6,2,1,7,9,5,8,3};
    //vector<int> nums = {1,2,3,4,5,6,7,8,9};
    //vector<int> nums = {9,8,7,6,5,4,3,2,1};
    //vector<int> nums = {4,3,2,1,5};
    vector<int> temp(nums.size());
    
    mergeSort(nums, temp, 0, nums.size() - 1);
    for(int temp : nums) {
        cout << temp << " ";
    }
    cout << endl;
}  
```


## quickSort 快排


### 递归快排

* partition 分区方法 是核心，执行该算法后，主轴左侧元素都小于等于主轴元素，主轴右侧元素都大于等于主轴元素  
* 注意：不管采用什么方法选择了基准数，我们都会把基准数放在要排序区间的最左端；
* 设置两个哨兵left和right初始化分别在要排序数组的左右两端，先移动右哨兵，找到第一个小于基准数的位置(注意基准数在最左端，因此先移动右哨兵，原因看后面)；然后移动左哨兵，找到第一个大于基准数的元素，之后交换左右哨兵位置的元素;  这样，在循环过程中，左哨兵left以及其左侧元素均小于等于基准数，右哨兵及其右侧元素，均大于等于基准数  
* 当某次移动过程中，不管移动左还是右哨兵时发现左右哨兵相遇了，说明：此时查找完毕，具体看下：
    * 如果右哨兵在向左移动过程中停下来，要么是找到了小于基准数的位置，要么是到了左哨兵left的位置
    * 如果左哨兵向右移动过程停下来，要么是找到了大于基准数的位置，要么是到了右哨兵的right的位置
    * 因此，左右哨兵的移动过程中除了设置与基准数比较的条件外还要设置left和right的比较，另外整个大循环也是由left < right控制 
    * 当右哨兵，左哨兵查找完毕，直接交换他们对应位置元素，不会有问题，即使此时left == right  
    * 当发现left == right，循环会结束，此时，交换哨兵位置元素与基准数即可，因为该位置元素小于基准数，下面看下为什么
        * 假设是右哨兵right向左移动过程(寻找小于基准数的过程)，移动到了left位置，此时该位置元素小于基准数(因为left位置在上次交换后还没动，一定是小于基准数的)  
        * 假设是左哨兵left向右移动过程中(寻找大于基准数的过程)，移动到了right的位置，此时，由于左哨兵移动前右哨兵已经移动了！所以相遇位置一定是右哨兵找到的那个小于基准数的位置！ 这就是为什么升序排序，基准数在左端时，我们每次都是先移动右哨兵的原因。

* 注意：代码中，左右哨兵分别从排序区间的左右边界开始  

* 稳定性：不稳定  
    * 例如 7 2 4 4 8 9   第一次排序后，4 2 4 7 8 9 第一个4是原数组下标为3的那个4，进一步排序后，会发现，最终两个4的相对关系被破坏  
    
* 复杂度：如果每次都选排序区间左侧值作为基准数，假设原数组基本有序(不管升序还是降序),原本希望的O(logn)的复杂度变为O(n)，总的时间复杂度退化成O(n^2)  

* 改进：基准数选择为，左右边界，和中间元素的中位数   

```cpp
#include <vector>  
#include <iostream>
#include <algorithm，，，，，，，，

using namespace std;  

void quickSort(vector<int>& nums, int start, int end) {
    // 要排序区间小于等于1个元素，直接返回 已经是有序的了
    if(start >= end)return;
    
    int leftIndex = start, rightIndex = end;
    int pivot = nums[start];
    while(leftIndex < rightIndex) {
        while(leftIndex < rightIndex && nums[rightIndex] >= pivot)rightIndex--;
        while(leftIndex < rightIndex && nums[leftIndex] <= pivot)leftIndex++;
        swap(nums[leftIndex], nums[rightIndex]);
    }
    swap(nums[start], nums[leftIndex]);
   
    quickSort(nums, start, leftIndex - 1);
    quickSort(nums, leftIndex + 1, end);
   
}


int main()  
{  
    vector<int> nums = {4,6,2,1,7,9,5,8,3};
    //vector<int> nums = {1,2,3,4,5,6,7,8,9};
    //vector<int> nums = {9,8,7,6,5,4,3,2,1};
    //vector<int> nums = {4,3,2,1,5};
    
    quickSort(nums, 0, nums.size() - 1);
    for(int temp : nums) {
        cout << temp << " ";
    }
    cout << endl;
}  
```

### 非递归快排  

```cpp
#include <vector>  
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;  

int partition(vector<int>& nums, int start, int end) {
    if(start >= end)return start;
    
    int leftIndex = start, rightIndex = end;
    int pivot = nums[start];
    while(leftIndex < rightIndex) {
        while(leftIndex < rightIndex && nums[rightIndex] >= pivot)rightIndex--;
        while(leftIndex < rightIndex && nums[leftIndex] <= pivot)leftIndex++;
        swap(nums[leftIndex], nums[rightIndex]);
    }
    swap(nums[start], nums[leftIndex]);
    return leftIndex;
}


void quickSort(vector<int>& nums, int start, int end) {
    if(start >= end)return;
    stack<int> stk;
    stk.push(end);
    stk.push(start);
    while(!stk.empty()) {
        int left = stk.top();
        stk.pop();
        int right = stk.top();
        stk.pop();
        int pivotIndex = partition(nums, left, end);
        // 注意先判断下左右子区间是否最少含有一个数据，再入栈
        if(left <= pivotIndex - 1) {
            stk.push(pivotIndex - 1);
            stk.push(left);
        }
        if(right >= pivotIndex + 1) {
            stk.push(right);
            stk.push(pivotIndex + 1);
        }
    }
}

int main()  
{  
    vector<int> nums = {4,6,2,1,7,9,5,8,3,3,0};
    //vector<int> nums = {1,2,3,4,5,6,7,8,9};
    //vector<int> nums = {9,8,7,6,5,4,3,2,1};
    //vector<int> nums = {4,3,2,1,5};
    
    quickSort(nums, 0, nums.size() - 1);
    for(int temp : nums) {
        cout << temp << " ";
    }
    cout << endl;
}  
```


### 双轴快排  

[双轴快排图解](https://www.cnblogs.com/bigsai/p/13930945.html)  

* pivot1 和 pivot2 两个主轴，**同时要保证 pivot1 <= pivot2** ,一般选择初始化 pivot1 = nums[start]  pivot2 = nums[end] 
* 算法步骤：
    * 设要排序区间为 [start, end]   
    * 设置三个循环不变量 lower， k， upper    lower用于推进pivot1    upper用于推进pivot2  
        * 任意时刻：
        * 区间 [start, lower] 元素均小于等于 nums[start]    lower初始化为 start即可
        * 区间 [upper, end] 元素均大于等于   nums[end]      upper初始化为end
        * 区间 (lower, k)  元素均 大于nums[start], 且小于nums[end] 
        * 区间 [k, upper) 内元素为待比较元素  初始化k = start + 1 
    * 遍历k 
        * 如果  nums[k] <= nums[start] 需要将其放在左侧区间，根据循环不变量的定义，可以先将lower加1，然后交换nums[k]与nums[lower], 最后将k增加1 此时仍然满足上面定义  
        * 如果  nums[k] > nums[start] && nums[k] < nums[end] 也就是在中间区间，直接将 k++ 即可  
        * 如果  nums[k] >= nums[end]， nums[k]应该处于最右侧区间，由于此时 nums[upper]元素一定大于等于nums[end]，因此，可以先将upper减1，然后交换 nums[k]与nums[upper]，注意，交换后，不能将k++，因为交换过来的元素原先处于未判断区间  

* 另外注意，在将此代码做leedcode912排序时，有一个测试用例数据量为50000，且是升序排好的，超时，也发生了退化  可以改进，用随机数  假设要排序的区间为[start, end],选择一个下标在该区间的方法： int i = rand() % (end - start + 1) + start  

        
```cpp
#include <vector>  
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;  

void quickSort(vector<int>& nums, int start, int end) {
    if(start >= end)
        return;
    
    if(nums[start] > nums[end])
        swap(nums[start], nums[end]);
    
    int lower = start;
    int k = start + 1;
    int upper = end;
    
    while(k < upper) {
        if(nums[k] <= nums[start]) {  // 在左侧区间情况
            swap(nums[k++], nums[++lower]);
        } else if(nums[k] > nums[start] && nums[k] < nums[end]) { // 在中间的情况
            k++;
        } else if(nums[k] >= nums[end]) {  // 右侧的情况
            swap(nums[k], nums[--upper]);
        }   
    }
    swap(nums[start], nums[lower]);
    swap(nums[end], nums[upper]);
    quickSort(nums, start, lower - 1);
    quickSort(nums, lower + 1, upper - 1);
    quickSort(nums, upper + 1, end);
}


int main()  
{  
    vector<int> nums = {4,6,2,1,7,9,5,8,3,3,0,32,43,5,6,7,3,2,3,4};
    //vector<int> nums = {1,2,3,4,5,6,7,8,9};
    //vector<int> nums = {9,8,7,6,5,4,3,2,1};
    //vector<int> nums = {4,3,2,1,5};
    
    quickSort(nums, 0, nums.size() - 1);
    for(int temp : nums) {
        cout << temp << " ";
    }
    cout << endl;
}  
```

## heapSort 堆排序  

* 完全二叉树：假设根节点从0开始(用数组表示时与数组下标统一)，某个节点下标为i，则其左孩子下标为 2i + 1  右孩子下标为 2i + 1  其父节点下标为 (i - 1) / 2;  

```cpp
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        if(nums.size() <= 1)
            return nums;
        // 构建大顶堆  (升序排列) 
        heapify(nums);
        // 构造升序序列， 逐次将第一个元素与后面已经排序好的元素的前一个元素交换位置，然后重新对被交换过去的元素执行siftDown操作  
        // 由于堆顶每次都是nums[0], 因此这里用 i 记录未排序序列中最后一个元素的下标，也就是从后往前，依次需要交换到堆顶的元素下标
        for(int i = nums.size() - 1; i > 0; --i) { // 循环到1结束即可，后面所有元素都排序好，第一个元素也是有序的，这里大于0还是大于等于0都无所谓  
            // 交换堆顶和当前未排序序列的最后一个元素
            swap(nums[0], nums[i]);
            siftDown(nums, 0, i - 1); // 执行完swap后，当前未排序序列范围是[0, i - 1]; 因此执行siftDown时，超出此范围的不管
        }

        return nums;
    }

private:
    // 构建大顶堆  本质上是从下至上对所有的非叶子节点执行siftDown操作 
    void heapify(vector<int>& nums) {
        int n = nums.size();
        // 最后一个节点下标为n - 1 则其父节点，也就是最后一个非叶子节点下标为 (n - 1 - 1) / 2;
        // 最后一个非叶子节点前面的所有节点，肯定都有孩子节点，因此都需要执行siftDown操作  
        for(int i = (n - 2) / 2; i >= 0; --i) {
            siftDown(nums, i, n - 1);
        }
    }
    // index 表示要siftDown的节点，endIndex表示只对索引为[0, endIndex]的节点有效 无论是index还是其孩子
    void siftDown(vector<int>& nums, int index, int endIndex) {
        int maxChildIndex = index * 2 + 1; // 要siftDown的节点的最大的那个孩子的索引, 先初始化为左孩子索引
        while(maxChildIndex <= endIndex) {  // 左孩子在该范围内才进行比较
            // 判断有没有右孩子，有的话选出那个较大的孩子节点来  
            if(maxChildIndex + 1 <= endIndex && nums[maxChildIndex + 1] > nums[maxChildIndex]) {
                maxChildIndex++;
            }
            // 父节点与较大的孩子比较
            if(nums[index] > nums[maxChildIndex]) { // 父节点大于两个孩子节点，该节点的位置已经调整完毕 直接返回
                return;
            } else {
                swap(nums[index], nums[maxChildIndex]);
                // 注意：对索引为index的节点执行siftDown，如果该节点发生了交换，那需要继续跟随它往下走，一直沉到无法再沉为止 
                index = maxChildIndex;
                maxChildIndex = index * 2 + 1;
            }
        }
    }

};
```

## countSort 计数排序  

* 


