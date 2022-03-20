<h1 align="center">leedcode笔记之二分法</h1>

<p id="easy"></p>

## Easy

[easy](doc/leedcode题解/二分法/easy/README.md)


<p id="medium"></p>


##  Medium 

[medium](doc/leedcode题解/二分法/medium/README.md)


<p id="hard"></p>

## Hard

[hard](doc/leedcode题解/二分法/hard/README.md)   



## 二分法  

可以先看一下这个题解，讲解了二分法的基本思路和注意事项，尤其要思考关于区间的选择，循环终止条件，对比较结果中三种情况的处理
[leedcode题解]（https://leetcode-cn.com/problems/binary-search/solution/er-fen-cha-zhao-xiang-jie-by-labuladong/)

## 查找有序数组中目标元素(目标元素无重复)
    * [leedcode.0704.二分查找]()* 

该题提示了数组中元素是不重复的,如果有序数组中有重复的,我们想要返回目标值的左侧边界或者右侧边界,上题中的做法就不能满足了,例如nums = [0,1,1,2,3],target为1时,返回的是2，怎样可以查找一个目标元素的左边界或右边界呢？  

## 查找有序数组目标元素的左边界(目标元素可能重复也可能不重复)

### 使用左闭右闭区间  
假设元素个数为n，我个人喜欢使用左闭右闭的区间，此时区间的[left, right]初始值为[0, n-1]   
这里以一个例演示下整个代码运行的过程，元素个数n=16，初始时left=0，right=15，终止条件是left>right,但与上面代码不同的是，等于情况的处理，由于是 查找左边界，又因为是右闭区间，所以调整right=mid-1;
先看代码  
```cpp
class Solution {
public:
    int search_left(vector<int>& nums, int target) { 
        //定义初始查找区间  左闭右闭
        int left = 0, right = nums.size() - 1;
        while(left <= right)
        {
            int mid = left + (right - left) / 2;            
            if(target == nums[mid])
               right = mid - 1;
            else if(target < nums[mid])
               right = mid - 1;
            else if(target > nums[mid])
               left = mid + 1; 
            }
        }
        if(left>=nums.size()) return -1;
        return nums[left] == target ? left : -1;
    }
};
```
<p align="center"><img src="https://user-images.githubusercontent.com/58176267/135704231-723d1a41-434d-4997-b916-8a45e06e3776.png"></p>   

多推敲几次上面的流程就会发现，在 不断二分的过程中，如果能找到target，那么在后面缩小区间的过程中，nums[right]一定对应了target，直到最后left==right时锁定了左边界，接下来由于nums[mid]
==target, right=mid-1,while循环结束时，left对应的就是target的左边界。如果一直没找到target，最后也是left>right，只不过nums[left]不等于target  
进一步想，实际上此时left对应就是数组中比target小的元素个数，因为最后left的取值分三大类：
   *  1.能找到target的时候，left就是target的左边界，值位于[0, n-1]；**既表示target左边界索引，也代表比target小的元素个数为left**
   *  2.找不到target，数组中所有元素都比target大，循环结束后left=0，right=-1；**表示比target小的元素个数为0**
   *  3.找不到target，数组中所有元素都比target小，循环结束后left=n，right=n-1；**表示比target小的元素个数为n**
**可以看到，最后循环结束后如果是情况3，left是可能越界的(left==nums.size()),因此需要先判断是越界，之后按照nums[left]是否等于target决定返回left还是-1 **   


### 使用左闭右开区间  
用来理解区间的选择对代码哪些部分有影响  
```cpp
class Solution {
public:
    int search_left(vector<int>& nums, int target) { 
        //定义初始查找区间  左闭右开
        int left = 0, right = nums.size(); //注意这里是nums.size()
        while(left < right)  //注意这里是小于时，区间才有意义(才有元素)
        {
            int mid = left + (right - left) / 2;            
            if(target == nums[mid])
               right = mid;
            else if(target < nums[mid])
               right = mid;
            else if(target > nums[mid])
               left = mid + 1; 
            }
        }
        if(left>=nums.size()) return -1;
        return nums[left] == target ? left : -1;
    }
};
```  

**两种方式，可以看出只要区间左侧是闭合的，最后都是可以根据left进行判断的，两种方式本质上相同，最关键的是不漏掉元素就可以**   


## 查找有序数组目标元素的右边界(目标元素可能重复也可能不重复)

### 使用左闭右闭区间  

```cpp
class Solution {
public:
    int search_left(vector<int>& nums, int target) { 
        //定义初始查找区间  左闭右闭
        int left = 0, right = nums.size() - 1;
        while(left <= right)
        {
            int mid = left + (right - left) / 2;            
            if(target == nums[mid])
               left = mid + 1;
            else if(target < nums[mid])
               right = mid - 1;
            else if(target > nums[mid])
               left = mid + 1; 
            }
        }
        if(right < 0) return -1;
        return nums[right] == target ? right : -1;
    }
};
```  
保证如果能找到target时，左边界nums[left]一直保持为target,最后循环结束前一步，left=right, nums[left] = nums[right] = target, 之后left = mid + 1；循环结束时，nums[right]对应的是target  
结果还是分三类：
   *  1.能找到target的时候，right就是target的右边界，值位于[0, n-1]；**既表示target右边界索引，也代表比target大的元素个数为right**
   *  2.找不到target，数组中所有元素都比target大，循环结束后left=0，right=-1；**表示比target大的元素个数为n-0=n**
   *  3.找不到target，数组中所有元素都比target小，循环结束后left=n，right=n-1；**表示比target小的元素个数为n-n=0**
当出现情况2时，nums[right]越界  
**所以最后只要先判断right是否越界，再判断nums[right]是否等于target即可**


### 使用左闭右开区间  
用来理解区间的选择对代码哪些部分有影响  
```cpp
class Solution {
public:
    int search_left(vector<int>& nums, int target) { 
        //定义初始查找区间  左闭右开
        int left = 0, right = nums.size(); //注意这里是nums.size()
        while(left < right)  //注意这里是小于时，区间才有意义(才有元素)
        {
            int mid = left + (right - left) / 2;            
            if(target == nums[mid])
               right = mid + 1;
            else if(target < nums[mid])
               right = mid;
            else if(target > nums[mid])
               left = mid + 1; 
            }
        }
        if(right==0) return -1;
        return nums[right-1] == target ? right-1 : -1;
    }
};
``` 
结果还是分三类：终止循环时，left == right成立
   * 1.能找到target，left和right实际上位于target右边界的后一个位置，因此nums[left] == nums[right] == target; 
   * 2.找不到target，数组中所有元素都比target大，循环结束后，left == right == 0;
   * 3.找不到target，数组中所有元素都比target小，循环结束后，left == right == nums.size();  
所以可以看到最后left和right是位于我们希望与target比较的元素后一个位置的，因此要用nums[right-1]与target比较，且如果最后right == 0，一定是因为所有元素都比target大导致的，right = nums.size(),则需要比较nums[right-1]与target,如果相等说明右边界是nums.size()-1,不相等说明数组所有元素都比target小；




## 统一写法  
看一看出，如果使用左闭右开区间，寻找左边界和右边界时有细微区别，就我个人而言感觉还是使用全闭的区间好理解，而且可以统一写法  


   * 关于越界：寻找左边界时，当数组所有元素都小于target时，循环结束后left为n，越界；(当数组所有元素都小于target时right最后为-1也越界，不过我们是用nums[left]判断的所以不关心right的值)；寻找右边界时，使用nums[right]判断，当数组元素都大于target时，循环结束后right=-1，越界； 

统一模板：
 ```cpp
   int search(vector<int>& nums, int target) {
        //利用有序的特点先排查target是否在区间内
        if(target < nums[0] || target > nums[nums.size() - 1])
            return -1;
        //定义初始查找区间
        int left = 0, right = nums.size() - 1;
        while(left <= right)
        {
            int mid = left + (right - left) / 2;            
            if(target == nums[mid])
               return mid;
            else if(target < nums[mid])
               right = mid - 1;
            else if(target > nums[mid])
               left = mid + 1; 
            }
        }
        return -1;
    }

   int search_left(vector<int>& nums, int target) { 
        //利用有序的特点先排查target是否在区间内
        if(target < nums[0] || target > nums[nums.size() - 1])
            return -1;
        //定义初始查找区间  左闭右闭
        int left = 0, right = nums.size() - 1;
        while(left <= right)
        {
            int mid = left + (right - left) / 2;            
            if(target == nums[mid])
               right = mid - 1;
            else if(target < nums[mid])
               right = mid - 1;
            else if(target > nums[mid])
               left = mid + 1; 
            }
        }
        //检查left是否越界
        if(left>=nums.size()) return -1;
        return nums[left] == target ? left : -1;
    }


   int search_right(vector<int>& nums, int target) {
      //利用有序的特点先排查target是否在区间内
      if(target < nums[0] || target > nums[nums.size() - 1])
         return -1;
      //定义初始查找区间  左闭右闭
      int left = 0, right = nums.size() - 1;
      while(left <= right)
      {
         int mid = left + (right - left) / 2;            
         if(target == nums[mid])
            left = mid + 1;
         else if(target < nums[mid])
            right = mid - 1;
         else if(target > nums[mid])
            left = mid + 1; 
    
      }
      if(right < 0) return -1;
      return nums[right] == target ? right : -1;
}
```


    * [leedcode.0704.二分查找](https://leetcode-cn.com/problems/binary-search/) 
    * [leedcode.0034.在排序数组中查找元素的第一个和最后一个位置]()
    * [leedcode.0035.搜索插入位置](https://leetcode-cn.com/problems/search-insert-position/)  
    * [leedcode.0069.求x的平方根Sqrt(x)](https://leetcode-cn.com/problems/sqrtx/)
    * [leedcode.0367.有效的完全平方数](https://leetcode-cn.com/problems/valid-perfect-square/)
    * [leedcode.0441.排列硬币](https://leetcode-cn.com/problems/arranging-coins/)  
    * [leedcode.0074.搜索二维矩阵](https://leetcode-cn.com/problems/search-a-2d-matrix/)
    * [leedcode.0240.搜索二维矩阵 II](https://leetcode-cn.com/problems/search-a-2d-matrix-ii/)



## leedcode.0035.搜索插入位置 


### 
```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        if(nums[0] > target)return 0;
        if(nums[nums.size() - 1] < target)return nums.size();
        int left = 0, right = nums.size() - 1;
        int mid;
        while(left <= right)
        {   
            mid = left + (right - left) / 2;
            if(nums[mid] == target)
                return mid;
            else if(nums[mid] < target)
                left = mid + 1;
            else if(nums[mid] > target)
                right = mid - 1;
        }
        return left;
    }
};
```



