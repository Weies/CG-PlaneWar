//#include<thread>
//#include<iostream>
//#include<mutex>
//#include<future>
//#include<condition_variable>
//#include"widget.h"
//using namespace std;
//int a = 0;
//mutex mu;
//void fun(int b)
//{
//	debug("thread1 start");
//	mu.lock();
//	Sleep(3000);
//	b = 3;
//	debug(b);
//	a = 4;
//	mu.unlock();
//}
//
//void fun2(int b)
//{
//	
//	debug("thread2 start");
//	mu.lock();
//	b = 300;
//	debug(b);
//	a = 400;
//	mu.unlock();
//}
//int main()
//{
//	//thread t([]() {//主线程结束该线程会被立刻终止
//	//	debug(" hello");
//	//	Sleep(3000);
//	//});
//	//t.detach();
//	//debug(t.hardware_concurrency());//硬件支持的最大线程
//	//debug(t.native_handle());
//
//	//创建异步线程，调用future.get可以阻塞主线程。
//	//调用get之前主线程一直执行，但是不会自动退出
//	int b = 5;
//	future<void> fu = async(fun, b);
//	future<void> fu1 = async(fun2, b);
//	debug(a);
//	//fu.get();
//	//fu1.get();
//	thread thrd;
//	
//	condition_variable cond;
//	
//	unique_lock<mutex> locker(mu);
//	cond.wait(locker);
//	cond.notify_one();
//	debug("enen");
//	debug(a);
//}