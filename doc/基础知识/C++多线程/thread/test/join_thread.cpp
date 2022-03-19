/*




*/

#include <iostream>


#include <thread>

using namespace std;


void pubData()
{
	cout << "子线程 id = " << this_thread::get_id() << endl;
	for (int i = 0; i < 100; i++)
	{
		cout << "正在执行子线程： " << i << endl;
	}
}

//主线程从main函数入口开始执行
int main()
{
	cout << "主线程 id = " << this_thread::get_id() << endl;

	//1.创建子线程，线程入口是pubData()函数
	thread pubDataThread(pubData);

	//2.加入子线程，join()会阻塞主线程并等待子线程执行完毕，子线程执行完毕则join()执行完毕主线程继续执行  
	pubDataThread.join();

	//3.detach() 分离  主线程不再与子线程汇合，不再等待子线程执行完才执行 !不建议使用
	//detach后，子线程和主线程失去关联，驻留在后台，由C++运行时库接管
	//这样的话，主线程如果先执行完毕，可能会出现程序结束子线程还在执行过程中，会被强行中断
	//一般在子线程结束与否与主线程关系不大时，在主线程结束时不关系子线程结不结束
	//pubDataThread.detach();
	
	//4.joinable() 判断是否可以成功使用join()或者detach()
	//返回true,证明可以调用join()或者detach()  
	//返回false,证明调用过join()或detach()，此时两者就不能再调用了
	if (pubDataThread.joinable())
	{
		cout << "可以调用join()或detach()" << endl;
		pubDataThread.join();
	}

	cout << "子线程执行完毕，继续执行主线程： " << endl;

	for (int i = 0; i < 100; i++)
	{
		cout << "正在执行主线程： " << i << endl;
	}

	return 0;
}