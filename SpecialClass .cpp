#include<iostream>
#include<vld.h>
#include<string>
#include<memory>
#include<thread>
#include<mutex>
using namespace std;
mutex mt;
//����ģʽ
//   ��ħʱ����  ����ħʱ����
class Test
{
public:
	static Test* CreateInstance()
	{
		if (_instance == nullptr)   //˫�����  ���ܼ�������̰߳�ȫ���ܼ��Ч��
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
	thread t2(thread_fun);//  Ҫ�����̰߳�ȫ����

	t1.join();
	t2.join();
}
/////////////////////////////////////////////////////////////////////////////
/*
//����ģʽ
//����˵�����㽫���ò��ã���������ʱ�ʹ���һ��Ψһ��ʵ������
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		return &m_instance;
	}
private:
	// ���캯��˽��
	Singleton(){};
	// C++98 ������
	Singleton(Singleton const&);
	Singleton& operator=(Singleton const&);
private:
	static Singleton m_instance;//  �����Ǿ�̬��  ��Ϊ����Ķ����������������ȥ����
};
Singleton Singleton::m_instance;  //���ʹ�õķǳ�Ƶ���ǳ��� ���Ч�ʾͺܸ���
void main()
{
	//....
	//Singleton *p = Singleton::GetInstance();
	//Singleton *p1 = Singleton::GetInstance();// Ҳ�ǿ��Թ��������  ����ģʽ Ҳ���ǹ������ͬһ������
	int a = 10; //����ģʽ  ���ȹ��� Ȼ��Ž���������
}
///////////////////////////////////////////////////////////////////////////////
/*
//���ֻ�ܴ���һ������(����ģʽ)
class Test
{
public:
	static Test* CreateInstance()
	{
		if (_instance == nullptr)//   Ϊ�� ˵����û�ж��� �͸���newһ��
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
	Test *pt = Test::CreateInstance();//   ͨ�������ķ���ȥ����һ������
	Test *pt1 = Test::CreateInstance();
	Test *pt2 = Test::CreateInstance();
	Test *pt3 = Test::CreateInstance();
	Test *pt4 = Test::CreateInstance();
	Test *pt5 = Test::CreateInstance(); //ÿ������ĵ�ַ��һ��  ˵����ͬһ������ �������ǵ���ģʽ
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
	Test t1;                // ����������ͬ�Ķ���  ������ֵ��һ��  ���ǵ�ַ��ͬ
	Test t2;               //���ֻ�ܴ���һ������(����ģʽ)  ������
	Test t3 = t2;
	//}
	////////////////////////////////////////////////////////////////////////

	//���һ���� ���ܱ��̳� ��һ��final
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
	//���һ���� ���ܱ���ֵ�Ϳ���
	/*
#include<boost/noncopyable.hpp>
	using namespace boost;
	class Test : noncopyable//   ֱ�Ӽ̳оͲ��ܹ���ֵ �Ϳ��� ����boost����ķ���
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

	// C++98��  ������ ��ֵ�ķ���
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
	//ֻ����ջ�ϴ�������  ������
	class Test
	{
	public:
		Test(int data = 0) : m_data(data)
		{}
		Test(const Test &);
	private:
		void* operator new(size_t sz);
		void* operator new(size_t sz, int pos);//  ��λnew
	private:
		int  m_data = 0;
	};
	void main()
	{
		Test t;
		//Test *pt = new Test;   //new operator    operator new  ���ϲ���
	}
	/*
	//ֻ����ջ�ϴ�������  ����һ
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
	//ֻ���ڶ��ϴ���
	//ʵ�ַ�ʽ
	//1. ����Ĺ��캯��˽�У���������������˽�С���ֹ���˵��ÿ�����ջ�����ɶ���
	//2. �ṩһ����̬�ĳ�Ա�������ڸþ�̬��Ա��������ɶѶ���Ĵ���
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
