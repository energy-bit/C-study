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

int Div(int a, int b)throw(int, char, double, Test) //异常规范 不能抛出异常只能抛出括号里的异常
{
	char ch = 'A';
	double d = 12.34;
	short s = 10;
	if (b == 0)
	{
		//throw Test();   //以类型抛出
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

	catch (int)//按类型捕获
	{
		cout << "What<int>?> Div Error By Zero." << endl;
	}
	catch (char)//按类型捕获
	{
		cout << "What<char>?> Div Error By Zero." << endl;
	}
	catch (double &d)
	{
		cout << "What<double>: " << d << endl;
	}
	catch (...)// 放在后边  前边的捕获不了的都在这
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
		lock_guard<mutex> lock(g_lock);  // 好处就是如果程序异常退出 他是个对象就会析构 从而解锁
		//unique_lock<mutex> lock(g_lock);//lock_guard的缺陷：太单一，用户没有办法对该锁进行控制，因此C++11又提供了unique_lock。
		//lock.   //会有很多方法   它是一个模板
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
//下面代码锁控制不好时，可能会造成死锁，最常见的比如在锁中间代码返回，或者在锁的范围内抛出异常
//因此：C++11采用RAII的方式对锁进行了封装，即lock_guard（守卫锁）和unique_lock（唯一锁）如上解决这个问题

/*
//一个线程对变量number进行加一100次，另外一个减一100次，每次操作加一或者减一之后，输出
//number的结果，要求number为0
int number = 0;
mutex g_lock;
int ThreadProc1()
{
	for (int i = 0; i < 1000; i++)
	{
		g_lock.lock();
		++number;// 一个++  一个--按道理说 一个加一个减  最后结果为0 程序正常运行 但是有可能最常见的比如在锁中间代码返回，或者在锁的范围内抛异常。造成死锁
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
		return;// 这样就会直接返回 就不会有解锁了 那么下面的就会造成接下来的无法在加锁 程序最后 join()会一直等待 无法结束  造成死锁
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


// 如说控制的是一个变量 则用原子操作就可以了
atomic_long sum = { 0 }; //自身会进行互斥操作  
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
//因为下面的加锁使效率不高
//因此C++11中引入了原子操作 即不可被中断的一个或一系列操作，C++11引入的原子操作类型，使得线程间数据的同步变得非常高效
////////////////////////////////////////////////////////////////////////////////////
/*

mutex mt;
unsigned long sum = 0;
void fun(size_t num)
{
	for (size_t i = 0; i < num; ++i)
	{
		//mt.lock();// 加了锁之后那就只能一个进行完 才能进行另一个 所以效率会低一点
		sum++;  //如果不加锁的话  就会造成t1 t2两个线程同时进行的时候 但是sum结果只加了一次
		//mt.unlock();
	}
}
//虽然加锁可以解决，但是加锁有一个缺陷就是：只要一个线程在对sum++时，其他线程就会被阻塞，会影响
//程序运行的效率，而且锁如果控制不好，还会锁死
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
//互斥量
mutex mt;
void thread_fun1(int n)
{
	mt.lock();//  锁 就比如公共厕所 来的人进去后都会关锁
	          //比如进入fun1 执行完解锁后 才能轮得到fun2 在进行关锁 执行 开锁   
	          //但是不能保证来的先进fun2还是fun1 但是只能一个进去执行完 开锁之后才能到另一个进去
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
		if (th_obj.joinable())//判断对象线程还是否有效
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
	std::thread t(ThreadFunc); //将这个线程交给obj 
	//t.detach();
	thread_obj obj(t);   //代理 t

	if (!DoSomething(0)) //>0 <0 =0
		return -1;
	//采用jion()方式结束线程时，jion()的调用位置非常关键。为了避免该问题，可以采用RAII的方式对线程对象进行封装
	//th.join(); //上面的意思就是把这个写到obj对象的析构函数里  对象什么时候析构 他就什么时候结束等待
	return 0;
}
///////////////////////////////////////////////////////////////////////
/*  
 // join() 误用2 
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
//串行执行
int main()
{
	std::thread t(ThreadFunc);
	t.join();
	if (!DoSomething())
		return -1;
	// t.join();//  不能放在这里 如果让一条语句直接返回就不会进行这一步 程序就会错误
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
/*
class Test
{
public:
	void fun()//  是类里面的成员  要做线程的函数的时候  一定要将对象的地址一并传出去
	{
		cout << "This is Test::fun()" << endl;
	}
};
void main()
{
	Test t;  // 下面这块一定要&
	thread th(&(Test::fun), &t);
	th.join();
	//th.join();  不能多次用 
}
//  知识点  如果是类成员函数作为线程参数时，必须将this作为线程函数参数

///////////////////////////////////////////////////////////////////////////////////
/*
void thread_fun1(int &a)// &接受  不会真正改变x的值 
{
	//线程参数为引用类型，在线程中修改后也不能修改外部实参，因为其实际引用的是线程栈中的拷贝，而不是外部实参
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
	int y = 10;//若要改变这里的值 用th2 的方式传递值 也可以用th3
	int z = 10;// 要变z的值  也可以引用传递 就是th3
	thread th1(thread_fun1, x);//这样传过去x  
	thread th2(thread_fun2, &y);
	thread th3(thread_fun3, ref(z));//ref  引用传递  但必须&接受

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
	thread th1 = move(th);//移动构造 将th  转移给th1 这样th就成了无效
	if (th.joinable())//  判断线程是否有效
	{
		cout << "th OK" << endl;
		th.join();
	}
	else
	{
		cout << "th error." << endl;
		th1.join();
	}
	if (th1.joinable())//   如果上一步已经调用 -》th1.join()则下面无效
	{
		cout << "th1 OK" << endl;
	    //th1.join();  
	}
	else
		cout << "th1 Error." << endl;
}
//有可以通过jionable()函数判断线程是否是有效的，如果是以下任意情况，则线程无效
// 1 采用无参构造函数构造的线程对象
// 2 线程对象的状态已经转移给其他线程对象
// 3 线程已经调用jion或者detach结束
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
	thread th(thread_fun);//1. 通过函数指针  提供一个函数地址
	thread th1([]{cout << "Hello Thread." << endl; });//  2 通过lambda表达式 
	thread_obj obj;//构造一个对象
	thread th2(obj);//函数对象 传过去要重载小（）
	cout << "th id = " << th.get_id() << endl;
	cout << "th1 id = " << th1.get_id() << endl;
	cout << "th2 id = " << th2.get_id() << endl;
	thread th3;
	th3 = thread(thread_fun1);  //无名的临时对象 相当于const --> 右值  移动构造

	//    thread类是防拷贝的，不允许拷贝构造以及赋值，但是可以移动构造和移动赋值，即将一个线程对象关
	//联线程的状态转移给其他线程对象，转移期间不意向线程的执行。
	th.join();
	th1.join();
	th2.join();
	th3.join();
}
//当创建一个线程对象后，并且给线程关联线程函数，该线程就被启动，与主线程一起运行。线程函数一
//般情况下可按照三种方式提供： 1.函数指针  2.lambda表达式   3.函数对象


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
	cout << "th id=" << th.get_id() <<endl;//获取id 号
	cout << "This is Main Thread" << endl;
	th.join();//  等待子线程 运行结束
	cout << "Main End." << endl;
}
*/