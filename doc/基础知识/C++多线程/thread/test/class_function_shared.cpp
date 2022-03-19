/*


	使用类的成员函数作为线程入口

*/

#include <iostream>

#include <vector>
#include <thread>

#include <mutex>

using namespace std;

//全局变量，可由所有线程共享  
vector<int> v;

mutex Mutex;

class dealData
{

public:

	dealData(){}

	void inputData()
	{
		//cout << "子线程 id = " << this_thread::get_id() << endl;
		for (int i = 0; i < 1000; i++)
		{
			Mutex.lock();
			cout << "正在放入数据： " << i << endl;
			v.push_back(i);
			Mutex.unlock();
		}
	}

	void outputData()
	{
		//cout << "子线程 id = " << this_thread::get_id() << endl;
		while (1)
		{
			if (!v.empty())
			{
				Mutex.lock();
				cout << "正在读出数据： " << v.back() << endl;
				v.pop_back();
				Mutex.unlock();
			}
		}
	}

private:	
	vector<int> v;
	mutex Mutex;
};


//主线程从main函数入口开始执行
int main()
{
	cout << "主线程 id = " << this_thread::get_id() << endl;
	dealData data;

	thread putThread(&dealData::inputData, ref(data));
	thread outThread(&dealData::outputData, ref(data));
	
	putThread.join();
	outThread.join();
	
	cout << "子线程执行完毕，继续执行主线程： " << endl;
	return 0;
}
