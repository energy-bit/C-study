#include <iostream>
#include <thread>
using namespace std;
#include<iostream>
#include<thread>
#include<mutex>
#include<atomic>
#include<windows.h>
#include<assert.h>
using namespace std;

class Test
{};

int Div(int a, int b)throw(int, char, double, Test) //�쳣�淶 �����׳��쳣ֻ���׳���������쳣
{
	char ch = 'A';
	double d = 12.34;
	short s = 10;
	if (b == 0)
	{
		//throw Test();   //�������׳�
		throw d;
	}
	return a / b;
}

void  main()
{
	int a = 10;
	int b = 0;

	int result = 0;
	try
	{
		result = Div(a, b);
		cout << "result = " << result << endl;
	}

	catch (int)//�����Ͳ���
	{
		cout << "What<int>?> Div Error By Zero." << endl;
	}
	catch (char)//�����Ͳ���
	{
		cout << "What<char>?> Div Error By Zero." << endl;
	}
	catch (double &d)
	{
		cout << "What<double>: " << d << endl;
	}
	catch (...)// ���ں��  ǰ�ߵĲ����˵Ķ�����
	{
		cout << "What<...>?> Div Error By Zero." << endl;
	}
}


/*
int Div(int a, int b)
{
	//assert(b != 0);
	if (b == 0)
	{
		cout << "Div Error By Zero." << endl;
		exit(1);
	}
	return a / b;
}
void  main()
{
	int a = 10;
	int b = 0;
	cout << Div(a, b) << endl;
}
/////////////////////////////////////////////////////////////////////////
/*
int number = 0;
mutex g_lock;
int ThreadProc1()
{
	for (int i = 0; i < 1000; i++)
	{
		lock_guard<mutex> lock(g_lock);  // �ô�������������쳣�˳� ���Ǹ�����ͻ����� �Ӷ�����
		//unique_lock<mutex> lock(g_lock);//lock_guard��ȱ�ݣ�̫��һ���û�û�а취�Ը������п��ƣ����C++11���ṩ��unique_lock��
		//lock.   //���кܶ෽��   ����һ��ģ��
		++number;
		cout << "thread 1 :" << number << endl;
	}
	return 0;
}
int ThreadProc2()
{
	for (int i = 0; i < 1000; i++)
	{
		lock_guard<mutex> lock(g_lock);
		--number;
		cout << "thread 2 :" << number << endl;
	}
	return 0;
}
int main()
{
	thread t1(ThreadProc1);
	thread t2(ThreadProc2);
	t1.join();
	t2.join();
	cout << "number:" << number << endl;
	return 0;
}
//������������Ʋ���ʱ�����ܻ��������������ı��������м���뷵�أ����������ķ�Χ���׳��쳣
//��ˣ�C++11����RAII�ķ�ʽ���������˷�װ����lock_guard������������unique_lock��Ψһ�������Ͻ���������

/*
//һ���̶߳Ա���number���м�һ100�Σ�����һ����һ100�Σ�ÿ�β�����һ���߼�һ֮�����
//number�Ľ����Ҫ��numberΪ0
int number = 0;
mutex g_lock;
int ThreadProc1()
{
	for (int i = 0; i < 1000; i++)
	{
		g_lock.lock();
		++number;// һ��++  һ��--������˵ һ����һ����  �����Ϊ0 ������������ �����п�������ı��������м���뷵�أ����������ķ�Χ�����쳣���������
		cout << "thread 1 :" << number << endl;
		g_lock.unlock();
	}
	return 0;
}
int ThreadProc2()
{
	for (int i = 0; i < 1000; i++)
	{
		g_lock.lock();
		--number;//--
		cout << "thread 2 :" << number << endl;
		g_lock.unlock();
	}
	return 0;
}
int main()
{
	thread t1(ThreadProc1);
	thread t2(ThreadProc2);
	t1.join();
	t2.join();
	cout << "number:" << number << endl;
	return 0;
}
/*
mutex mt;
void thread_fun1(int n)
{
	mt.lock();
	cout << "This is thread fun1. " << endl;
	Sleep(3000);
	if (n == 5)
		return;// �����ͻ�ֱ�ӷ��� �Ͳ����н����� ��ô����ľͻ���ɽ��������޷��ڼ��� ������� join()��һֱ�ȴ� �޷�����  �������
	cout << "thread fun1 wake up." << endl;
	mt.unlock();
}
void thread_fun2(int n)
{
	mt.lock();
	cout << "This is thread fun2." << endl;
	Sleep(1000);
	cout << "thread fun2 wake up." << endl;
	mt.unlock();
}
void main()
{
	int n = 5;
	thread th1(thread_fun1, n);
	thread th2(thread_fun2, n);
	th1.join();
	th2.join();
	cout << "Main Thread End." << endl;
}


// ��˵���Ƶ���һ������ ����ԭ�Ӳ����Ϳ�����
atomic_long sum = { 0 }; //�������л������  
void fun(size_t num)
{
	for (size_t i = 0; i < num; ++i)
	{
		sum++;
		
	}
}
int main()
{
	cout << "Before joining,sum = " << sum << std::endl;
	thread t1(fun, 10000000); //sum++
	thread t2(fun, 10000000); //sum++
	t1.join();
	t2.join();
	cout << "After joining,sum = " << sum << std::endl;
	return 0;
}
//��Ϊ����ļ���ʹЧ�ʲ���
//���C++11��������ԭ�Ӳ��� �����ɱ��жϵ�һ����һϵ�в�����C++11�����ԭ�Ӳ������ͣ�ʹ���̼߳����ݵ�ͬ����÷ǳ���Ч
////////////////////////////////////////////////////////////////////////////////////
/*

mutex mt;
unsigned long sum = 0;
void fun(size_t num)
{
	for (size_t i = 0; i < num; ++i)
	{
		//mt.lock();// ������֮���Ǿ�ֻ��һ�������� ���ܽ�����һ�� ����Ч�ʻ��һ��
		sum++;  //����������Ļ�  �ͻ����t1 t2�����߳�ͬʱ���е�ʱ�� ����sum���ֻ����һ��
		//mt.unlock();
	}
}
//��Ȼ�������Խ�������Ǽ�����һ��ȱ�ݾ��ǣ�ֻҪһ���߳��ڶ�sum++ʱ�������߳̾ͻᱻ��������Ӱ��
//�������е�Ч�ʣ�������������Ʋ��ã���������
int main()
{
	cout << "Before joining,sum = " << sum << std::endl;
	thread t1(fun, 10000000); //sum++
	thread t2(fun, 10000000); //sum++
	t1.join();
	t2.join();
	cout << "After joining,sum = " << sum << std::endl;
	return 0;
}
/////////////////////////////////////////////////////////////////////////
/*
//������
mutex mt;
void thread_fun1(int n)
{
	mt.lock();//  �� �ͱ��繫������ �����˽�ȥ�󶼻����
	          //�������fun1 ִ��������� �����ֵõ�fun2 �ڽ��й��� ִ�� ����   
	          //���ǲ��ܱ�֤�����Ƚ�fun2����fun1 ����ֻ��һ����ȥִ���� ����֮����ܵ���һ����ȥ
	cout << "This is thread fun1. " << endl;
	Sleep(3000);
	cout << "thread fun1 wake up." << endl;
	mt.unlock();
}
void thread_fun2(int n)
{
	mt.lock();
	cout << "This is thread fun2." << endl;
	Sleep(1000);
	cout << "thread fun2 wake up." << endl;
	mt.unlock();
}
void main()
{
	int n = 5;
	thread th1(thread_fun1, n);
	thread th2(thread_fun2, n);
	th1.join();
	th2.join();
	cout << "Main Thread End." << endl;
}

/*
void thread_fun1(int n)
{
	mt.lock();
	for (int i = 0; i < n; ++i)
	{
		cout << "This is thread fun1." << endl;
		Sleep(1000);
	}
	mt.unlock();
}
void thread_fun2(int n)
{
	mt.lock();
	for (int i = 0; i < n; ++i)
	{
		cout << "This is thread fun2." << endl;
		Sleep(1000);
	}
	mt.unlock();
}
void main()
{
	int n = 5;
	thread th1(thread_fun1, n);
	thread th2(thread_fun2, n);
	th1.join();
	th2.join();
	cout << "Main Thread End." << endl;
}
/////////////////////////////////////////////////////////
/*
class thread_obj
{
public:
	thread_obj(thread &th) : th_obj(th)
	{}
	~thread_obj()
	{
		if (th_obj.joinable())//�ж϶����̻߳��Ƿ���Ч
		{
			th_obj.join();
		}
	}
public:
	thread_obj(const thread_obj &) = delete;
	thread_obj& operator=(const thread_obj &) = delete;
private:
	thread  &th_obj;
};
void ThreadFunc()
{
	cout << "ThreadFunc()" << endl;
}
bool DoSomething(int x)
{
	if (x > 0)
		return true;
	return false;
}
int main()
{
	std::thread t(ThreadFunc); //������߳̽���obj 
	//t.detach();
	thread_obj obj(t);   //���� t

	if (!DoSomething(0)) //>0 <0 =0
		return -1;
	//����jion()��ʽ�����߳�ʱ��jion()�ĵ���λ�÷ǳ��ؼ���Ϊ�˱�������⣬���Բ���RAII�ķ�ʽ���̶߳�����з�װ
	//th.join(); //�������˼���ǰ����д��obj���������������  ����ʲôʱ������ ����ʲôʱ������ȴ�
	return 0;
}
///////////////////////////////////////////////////////////////////////
/*  
 // join() ����2 
void ThreadFunc() { cout << "ThreadFunc()" << endl; }
void Test1() { throw 1; }
void Test2()
{
	int* p = new int[10];
	std::thread t(ThreadFunc);
	try
	{
		Test1();
	}
	catch (...)
	{
		delete[] p;
		throw;
	}
	t.join();
}
void main()
{
	Test2();
}

/*
void ThreadFunc()
{
	cout << "ThreadFunc()" << endl;
}
bool DoSomething()
{
	return false;
}
//����ִ��
int main()
{
	std::thread t(ThreadFunc);
	t.join();
	if (!DoSomething())
		return -1;
	// t.join();//  ���ܷ������� �����һ�����ֱ�ӷ��ؾͲ��������һ�� ����ͻ����
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
/*
class Test
{
public:
	void fun()//  ��������ĳ�Ա  Ҫ���̵߳ĺ�����ʱ��  һ��Ҫ������ĵ�ַһ������ȥ
	{
		cout << "This is Test::fun()" << endl;
	}
};
void main()
{
	Test t;  // �������һ��Ҫ&
	thread th(&(Test::fun), &t);
	th.join();
	//th.join();  ���ܶ���� 
}
//  ֪ʶ��  ��������Ա������Ϊ�̲߳���ʱ�����뽫this��Ϊ�̺߳�������

///////////////////////////////////////////////////////////////////////////////////
/*
void thread_fun1(int &a)// &����  ���������ı�x��ֵ 
{
	//�̲߳���Ϊ�������ͣ����߳����޸ĺ�Ҳ�����޸��ⲿʵ�Σ���Ϊ��ʵ�����õ����߳�ջ�еĿ������������ⲿʵ��
	a += 10;
	cout << "In thread fun1 x = " << a << endl;
}
void thread_fun2(int *a)
{
	*a += 10;
	cout << "In thread fun2 y = " << *a << endl;
}
void thread_fun3(int &a)//
{
	a += 10;
	cout << "In thread fun1 z = " << a << endl;
}
void main()
{
	int x = 10; 
	int y = 10;//��Ҫ�ı������ֵ ��th2 �ķ�ʽ����ֵ Ҳ������th3
	int z = 10;// Ҫ��z��ֵ  Ҳ�������ô��� ����th3
	thread th1(thread_fun1, x);//��������ȥx  
	thread th2(thread_fun2, &y);
	thread th3(thread_fun3, ref(z));//ref  ���ô���  ������&����

	th1.join();
	th2.join();
	th3.join();
	cout << "In main x = " << x << endl;
	cout << "In main y = " << y << endl;
	cout << "In main z = " << z << endl;
}

/////////////////////////////////////////////////////////
/*
void thread_fun()
{
	cout << "This is Child Thread." << endl;
}
void main()
{
	thread th(thread_fun);
	thread th1 = move(th);//�ƶ����� ��th  ת�Ƹ�th1 ����th�ͳ�����Ч
	if (th.joinable())//  �ж��߳��Ƿ���Ч
	{
		cout << "th OK" << endl;
		th.join();
	}
	else
	{
		cout << "th error." << endl;
		th1.join();
	}
	if (th1.joinable())//   �����һ���Ѿ����� -��th1.join()��������Ч
	{
		cout << "th1 OK" << endl;
	    //th1.join();  
	}
	else
		cout << "th1 Error." << endl;
}
//�п���ͨ��jionable()�����ж��߳��Ƿ�����Ч�ģ����������������������߳���Ч
// 1 �����޲ι��캯��������̶߳���
// 2 �̶߳����״̬�Ѿ�ת�Ƹ������̶߳���
// 3 �߳��Ѿ�����jion����detach����
//////////////////////////////////////////////////////////////////////////
/*
void thread_fun()
{
	cout << "This is Child Thread." << endl;
}
struct thread_obj
{
	void operator()()
	{
		cout << "This is thread obj." << endl;
	}
};
void thread_fun1()
{
	cout << "This is thread fun1" << endl;
}
void main()
{
	thread th(thread_fun);//1. ͨ������ָ��  �ṩһ��������ַ
	thread th1([]{cout << "Hello Thread." << endl; });//  2 ͨ��lambda���ʽ 
	thread_obj obj;//����һ������
	thread th2(obj);//�������� ����ȥҪ����С����
	cout << "th id = " << th.get_id() << endl;
	cout << "th1 id = " << th1.get_id() << endl;
	cout << "th2 id = " << th2.get_id() << endl;
	thread th3;
	th3 = thread(thread_fun1);  //��������ʱ���� �൱��const --> ��ֵ  �ƶ�����

	//    thread���Ƿ������ģ��������������Լ���ֵ�����ǿ����ƶ�������ƶ���ֵ������һ���̶߳����
	//���̵߳�״̬ת�Ƹ������̶߳���ת���ڼ䲻�����̵߳�ִ�С�
	th.join();
	th1.join();
	th2.join();
	th3.join();
}
//������һ���̶߳���󣬲��Ҹ��̹߳����̺߳��������߳̾ͱ������������߳�һ�����С��̺߳���һ
//������¿ɰ������ַ�ʽ�ṩ�� 1.����ָ��  2.lambda���ʽ   3.��������


/////////////////////////////////////////////////////////////////////////////////////////////
/*
void thread_fun()
{
	cout << "This is Child Thread." << endl;
}
void main()
{
	thread th(thread_fun);
	cout << "th id = " << th.get_id() << endl;
	th.detach();
	cout << "This is Main Thread." << endl;
	//th.join();
	cout << "Main End." << endl;
}

/////////////////////////////////////////////////////////////////////
/*
void thread_fun()
{
	cout << "This is Child Thread " << endl;
}
void main()
{
	thread th(thread_fun);
	cout << "th id=" << th.get_id() <<endl;//��ȡid ��
	cout << "This is Main Thread" << endl;
	th.join();//  �ȴ����߳� ���н���
	cout << "Main End." << endl;
}
*/