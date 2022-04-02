
# readme  

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
