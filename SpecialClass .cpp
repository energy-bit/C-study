#include<iostream>
#include<vld.h>
#include<string>
#include<memory>
#include<thread>
#include<mutex>
using namespace std;
mutex mt;
//懒汉模式
//   神魔时候用  就神魔时候构造
class Test
{
public:
	static Test* CreateInstance()
	{
		if (_instance == nullptr)   //双检机制  既能加锁兼顾线程安全又能兼顾效率
		{
			mt.lock();
			if (_instance == nullptr)
			{
				_instance = new Test;
			}
			mt.unlock();
		}

		return _instance;
	}
protected:
	Test()
	{
		cout << "Test::Test()" << endl;
	}
private:
	static Test *_instance;
};
Test* Test::_instance = nullptr;
void thread_fun()
{
	for (int i = 0; i < 10; ++i)
	{
		Test *pt = Test::CreateInstance();
		printf("pt = %p\n", pt);
	}
}
void main()
{
	thread t1(thread_fun);
	thread t2(thread_fun);//  要考虑线程安全问题

	t1.join();
	t2.join();
}
/////////////////////////////////////////////////////////////////////////////
/*
//饿汉模式
//就是说不管你将来用不用，程序启动时就创建一个唯一的实例对象。
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		return &m_instance;
	}
private:
	// 构造函数私有
	Singleton(){};
	// C++98 防拷贝
	Singleton(Singleton const&);
	Singleton& operator=(Singleton const&);
private:
	static Singleton m_instance;//  必须是静态的  因为自身的对象不能用自身的类型去定义
};
Singleton Singleton::m_instance;  //如果使用的非常频繁非常多 这个效率就很高了
void main()
{
	//....
	//Singleton *p = Singleton::GetInstance();
	//Singleton *p1 = Singleton::GetInstance();// 也是可以构造出来的  单例模式 也就是构造的是同一个对象
	int a = 10; //饿汉模式  是先构造 然后才进入主函数
}
///////////////////////////////////////////////////////////////////////////////
/*
//如何只能创建一个对象(单例模式)
class Test
{
public:
	static Test* CreateInstance()
	{
		if (_instance == nullptr)//   为空 说明还没有对象 就给他new一个
		{
			_instance = new Test;
		}
		return _instance;
	}
protected:
	Test()
	{}
private:
	static Test *_instance;
};
Test* Test::_instance = nullptr;
void main()
{
	Test *pt = Test::CreateInstance();//   通过这样的方法去产生一个对象
	Test *pt1 = Test::CreateInstance();
	Test *pt2 = Test::CreateInstance();
	Test *pt3 = Test::CreateInstance();
	Test *pt4 = Test::CreateInstance();
	Test *pt5 = Test::CreateInstance(); //每个对象的地址都一样  说明是同一个对象 这样就是单例模式
}
/*
class Test
{
public:
	Test(int data = 0) : m_data(data)
	{}
private:
	int  m_data = 0;
};
void main()
{
	Test t1;                // 这是三个不同的对象  看起来值都一样  但是地址不同
	Test t2;               //如何只能创建一个对象(单例模式)  看上面
	Test t3 = t2;
	//}
	////////////////////////////////////////////////////////////////////////

	//设计一个类 不能被继承 加一个final
	class Base final
	{
	};
	class D : public Base
	{};
	void main()
	{
		D d;
	}
	///////////////////////////////////////////////////////////////////////////////
	//设计一个类 不能被赋值和拷贝
	/*
#include<boost/noncopyable.hpp>
	using namespace boost;
	class Test : noncopyable//   直接继承就不能够赋值 和拷贝 这是boost库里的方法
	{
	public:
		Test(int data = 0) : m_data(data)
		{}
	private:
		int  m_data = 0;
	};
	void main()
	{
		Test t(1);
		Test t1;
		Test t2;
		Test t3;
		//t3 = t;
		//Test t4 = t3;
	}

	// C++98中  不许拷贝 赋值的方法
	class Test
	{
	public:
		Test(int data = 0) : m_data(data)
		{}
	private:
		Test(const Test&);
		Test& operator=(const Test &t);
	private:
		int  m_data = 0;
	};
	void main()
	{
		Test t(1);
		Test t1;
		Test t2;
		Test t3;
		t3 = t;
	}
	/////////////////////////////////////////////////////////////////////////
	/*
	//只能在栈上创建对象  方法二
	class Test
	{
	public:
		Test(int data = 0) : m_data(data)
		{}
		Test(const Test &);
	private:
		void* operator new(size_t sz);
		void* operator new(size_t sz, int pos);//  定位new
	private:
		int  m_data = 0;
	};
	void main()
	{
		Test t;
		//Test *pt = new Test;   //new operator    operator new  堆上不行
	}
	/*
	//只能在栈上创建对象  方法一
	class Test
	{
	public:
		static Test& CreateInstance(int data = 0)
		{
			return Test(data);
		}
	private:
		Test(int data = 0) : m_data(data)
		{}
		Test(const Test &);
	private:
		int  m_data = 0;
	};
	void main()
	{
		Test &pt = Test::CreateInstance();
	}
	////////////////////////////////////////////////////////////////////////////////
/*
	//只能在堆上创建
	//实现方式
	//1. 将类的构造函数私有，拷贝构造声明成私有。防止别人调用拷贝在栈上生成对象
	//2. 提供一个静态的成员函数，在该静态成员函数中完成堆对象的创建
	class Test
	{
	public:
		static Test* CreateInstance(int data = 0)
		{
			return new Test(data);
		}
	private:
		Test(int data = 0) :m_data(data)
		{}
		Test(const Test &);
	private:
		int  m_data = 0;
	};
	void main()
	{
		Test *pt = Test::CreateInstance();
		//Test t = *pt;
	}
*/
