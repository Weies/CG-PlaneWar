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
//	//thread t([]() {//���߳̽������̻߳ᱻ������ֹ
//	//	debug(" hello");
//	//	Sleep(3000);
//	//});
//	//t.detach();
//	//debug(t.hardware_concurrency());//Ӳ��֧�ֵ�����߳�
//	//debug(t.native_handle());
//
//	//�����첽�̣߳�����future.get�����������̡߳�
//	//����get֮ǰ���߳�һֱִ�У����ǲ����Զ��˳�
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