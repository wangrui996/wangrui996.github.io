
# readme  




# 

给一个数组nums 和 k  问有没有满足以下两个条件的连续子数组 

* 元素个数为2 
* 子数组和为k的倍数  

（用空间换时间？）



# C++问题

## 1. 递归和迭代的区别

## 2.虚函数的，多态的优缺点  

## 3.内存(字节)对齐，原因，规则    （原因：为了提高cpu访问内存的效率）  规则：    注意什么

[内存对齐](https://leetcode.cn/circle/discuss/qhqXQm/)

* **对齐值** ：n 
* 通过 预编译指令 #pragma pack(N) 指定 N为1 2 4 8 16  
* 如果不指定，编译器默认使用成员变量中占用空间最大的类型对应的字节数 
* 由以上得到**对齐值** 
* 成员对齐：
	* 首个成员的偏移offset为0  
	* 其他成员，假设其类型对应字节数为k 则该成员在内存中相对首地址的偏移(相对于结构体的首地址)为 min(n, k)的整数倍
* 整体的对齐
	* 整体对齐后的字节数应该是对齐值n的整数倍，不够的话在后面填补空位(也就是对结束地址有要求，不一定是最后一个成员结束位置作为整个结构的结束位置)

```cpp
#include <iostream>
#pragma pack(4)     
using namespace std;
typedef struct{     
    int a;     
    char b;      
    
}test;
int main() {
    cout << sizeof(test);  
}
```
* 上面例子输出为8，分析下为什么  



## 4.内联函数和宏函数的区别

## 5.各种排序算法,原理，时间复杂度(平均和最坏)，适用场景

## 6.

建议：纯软件的项目：用到设计模式等等、 力扣上设计模式相关？ 比如代码量大的  


（问道项目中用到了哪些设计模式：  回答： 状态模式   实际上还有单例模式自己竟然没说）





# 手撕代码  


## 1.任务调度  



![image](https://user-images.githubusercontent.com/58176267/161364940-869cde05-650f-49cb-bb2c-ad54858732a9.png)


## 两数之和的绝对值最小  

![image](https://user-images.githubusercontent.com/58176267/161364957-92b31d5d-5f0f-4b6a-a3ef-4419e1487dfd.png)

先排序  假设排序后  -5 -4 -2 -1 0 1 5 6 7 

* 如果都是非负数，最小的两个数之和即为结果
* 如果都是非正数，选最大的两个数之和就是结果  
* 如果有正有负 因为只能选择两个数，这两个数要么都是正数，要么都是负数，要么一个是正数一个是负数
    * 因此，计算非负数中最小的两个和记为 a1     计算非正数中两个最大的数之和取绝对值 记为 a2   然后再去找一正一负的情况中绝对值最小的数，记a3  三者选最小值即可 
    * 对于a3的计算   遍历排序后的数组中所有负数，寻找一个整数并计算两者之和的绝对值 
        * 遇到一个负数，在所有正数中，与它的绝对值最接近的那个，两者之和的绝对值才最小  如上面例子中，-5对应的应该是5  -4对应5  -2对应1 -1对应1 
        * 所以遇到一个负数，取绝对值，然后在有序数组中查找与它最接近的正数  二分即可  

```cpp
int binaryFind(vector<int>& v, int start, int target) {
	int left = start, right = v.size() - 1;


	while (left <= right) {
		int mid = left + (right - left) / 2;

		if (v[mid] == target)
			return v[mid];
		else if (v[mid] > target)
			right = mid - 1;
		else if (v[mid] < target)
			left = mid + 1;
	}

	return (v[left] - target) < (target - v[right]) ? v[left] : v[right];

}

int getMinAbs(vector<int>& nums) {
	if (nums.size() < 2) {
		return -1;
	}

	sort(nums.begin(), nums.end());

	if (nums[0] >= 0)
		return (nums[0] + nums[1]);
	if (nums[nums.size() - 1] <= 0)
		return -(nums[nums.size() - 1] + nums[nums.size() - 2]);

	int a1 = INT_MAX, a2 = INT_MAX, a3 = INT_MAX;
	int index = 0;
	while (index < nums.size() && nums[index] < 0)
		index++;
	if (nums[index] == 0) {
		if (index - 1 >= 0)
			a1 = abs(nums[index] + nums[index - 1]);
	}
	else {
		if (index - 2 >= 0)
			a1 = abs(nums[index - 1] + nums[index - 2]);
	}
	if (index + 1 < nums.size())
		a2 = nums[index] + nums[index + 1];
	
	for (int i = 0; i < index; ++i) {

		int tmp = -nums[i];
		int sum = abs(nums[i] + binaryFind(nums, index, tmp));

		a3 = sum < a3 ? sum : a3;
	}

	return min(a1, min(a2, a3));

}

int main()
{
	vector<int> nums{ 0, 5, -4, -4, -2, -3, -1, 6, 78, 7 };
	cout << getMinAbs(nums) << endl;
	return 0;
}
```

##  盒子问题

[力扣链接](https://leetcode.cn/circle/discuss/VDRNkZ/)

M个相同盒子，N个不同的球，每个盒子至少放k个球，请问最多有多少种放法？（不能使用排列组合）
输入是m,n,k，输出是总的放法

## 