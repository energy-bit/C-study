#include<iostream>
#include<assert.h>
#include<vector>
using namespace std;


void OutOfMemory()
{
	cout << "Out Of Memory." << endl; //delete 
	exit(1);
}

void main()
{
	set_new_handler(OutOfMemory); //用于预防内存不足的情况
	int *ptr = nullptr;
	try
	{
		ptr = new int[536870911]; //空间不足  malloc
	}
	catch (bad_alloc &e)
	{
		cout << e.what() << endl;
		return;
	}

	cout << "new OK" << endl;
	delete[]ptr;
}

/*
namespace bit
{
	template<class T>
	T* _allocate(size_t size, T*)
	{
		T *tmp = (T*)::operator new(size * sizeof(T));
		if (tmp == 0)
		{
			cout << "out of memory." << endl;
			exit(1);
		}
		return tmp;
	}
	template<class T>
	void _deallocate(T *buffer)
	{
		::operator delete(buffer);
	}
	template<class T1, class T2>
	void _construct(T1 *p, const T2 &value)
	{
		new(p)T1(value);  //placement new
	}
	template<class T>
	void _destroy(T *ptr)
	{
		ptr->~T();
	}

	空间配置器
	template<class T>
	class allocator
	{
	public:
		typedef T value_type;// 值
		typedef T* pointer;   // 指针类型
		typedef T& reference;//  引用类型
		typedef size_t size_type;// 大小
	public:
		申请空间
		pointer allocate(size_type n, const void *hint = 0)
		{
			return _allocate(n, (pointer)0);
		}
		释放空间
		void deallocate(pointer p, size_type n)//  将p所指的n个空间释放掉
		{
			_deallocate(p);
		}
		构造对象
		void construct(pointer p, const T &value)// 在指针p所指的空间构造对象 赋值
		{
			_construct(p, value);
		}
		析构对象
		void destroy(pointer p)//  将指针p所指的空间的对象析构
		{
			_destroy(p);
		}
	};
};
void main()
{
	vector<int, bit::allocator<int> > iv;
	iv.push_back(1);
}
/*
void main()
{
	bit::allocator<int> alloc;
	int *ptr = alloc.allocate(10);
	for (int i = 0; i < 10; ++i)
		ptr[i] = i + 1;
	for (int i = 0; i < 10; ++i)
		cout << ptr[i] << " ";
	cout << endl;
	alloc.deallocate(ptr, 10);
}
///////////////////////////////////////////////////////////////////////////
/*
class Base
{
public:
	virtual void fun()
	{
		cout << "Base::fun()" << endl;
	}
};
class D : public Base
{
public:
	void show()
	{
		cout << "D::show()" << endl;
		m_x = 100;
	}
public:
	int m_x = 0;
};
void Active(Base *pb)
{
	D *ptmp = dynamic_cast<D*>(pb);  //父子类型向下转换  必须多态 加虚函数

	if (ptmp ==nullptr)
		cout << "dynamic_cast error." << endl;
	else
		ptmp->show();
}
void main()
{
	//D d;
	Base d;
	Active(&d);
}
/*
void Active(Base *pb)
{
	D *ptmp = (D*)pb; //  运行发生错误
	ptmp->show();
}
void main()
{
	//D d;
	Base d;//   父类对象哪怕强转为子类的指针   但是也不能运行  
	Active(&d);
}
///////////////////////////////////////////////////////////////////////
/*
class A
{
private:
	int m_a = 0;
};
class B
{
private:
	int m_b = 1;
};
class C : public A, public B
{
private:
	int m_c = 2;
};
void main()
{
	C c;
	printf("%p, %p, %p\n", &c, static_cast<B*>(&c), reinterpret_cast<B*>(&c));// reinterpret_cast只负责转换类型  但是不保证安全性
}
/*
void main()
{
	const int a = 10;
	const int *p = &a;
	cout << "a = " << a << endl;
	int *q = reinterpret_cast<int*>(&a);//凡是牵扯到常性 和 易变性的 reinterpret_cast不参与转换 所以在这不可以
	*q = 100;
	cout << "a = " << a << endl;
	volatile int b = 20; //易变性
	int *pb = const_cast<int*>(&b);
}
/*
void main()
{
	int a = 10;
	int b = 20;
	a = b;
	char ch = 'A';
	a = static_cast<int>(ch);
	double d = 12.34;
	a = static_cast<double>(d); //隐示转换
	//int *pi = static_cast<int*>(&ch);  
	int *pi = reinterpret_cast<int*>(&ch);  // reinterpret_cast相当于显示转换
}
/////////////////////////////////////////////////////////////////////////
/*
//const_cast 两个作用
//  1.用于去掉变量的常性
//  2.去掉易变性
void main()
{
	const int a = 10;
	const int *p = &a;// int *p = &a;是不能接受的  必须加const  说明不能更改
	cout << "a = " << a << endl;
	int *q = const_cast<int*>(&a);//  用于去掉变量的常性
	*q = 100;
	cout << "a = " << a << endl;
	volatile int b = 20; //易变性
	int *pb = const_cast<int*>(&b);//  去掉易变性
}
/////////////////////////////////////////////////////////////////////////
/*
void main()
{
	int a = 10;
	int b = 20;
	a = b;
	char ch = 'A';
	a = static_cast<int>(ch);
	double d = 12.34;
	a = static_cast<double>(d); //隐示转换
	int *pi = static_cast<int*>(&ch);  //这样是不允许的  因为他不是隐式转换类型 凡是可以隐式转换的才可以用static_cast
	int *pi = (int*)&ch;  
}
/////////////////////////////////////////////////////////////////////////////
/*
//有explicit  不能发生隐式转换
class Test
{
public:
	explicit Test(int data = 0) :m_data(data)  
	{}
	operator int() //强制类型转换
	{
		return m_data;
	}
private:
	int m_data;
	int m_data1 = 0;
	int m_data2 = 0;
};
void main()
{
	Test t(10);
	//t=20;   //有explicit 关键字 说明不能隐式转换
	t = (Test)20;
	int value = (int)t;
}
/*
int Max(int a, int b)
{
	return a > b ? a : b;
}
void main()
{
	int *p = (int*)0x0012ff7c;  //地址 整数 -->16进制进行表示
	Max(1, 2);
	Max('A', 'B');
	Max(12.34, 23.45);
}
/*
void main()
{
	int a = 10;
	int b = 20;
	a = b;
	char ch = 'A';
	a = ch;
	double d = 12.34;
	a = d; //隐示转换
	int *pi = (int*)&ch;  //显示转换
}
*/