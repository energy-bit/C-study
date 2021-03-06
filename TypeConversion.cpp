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
	set_new_handler(OutOfMemory); //����Ԥ���ڴ治������
	int *ptr = nullptr;
	try
	{
		ptr = new int[536870911]; //�ռ䲻��  malloc
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

	�ռ�������
	template<class T>
	class allocator
	{
	public:
		typedef T value_type;// ֵ
		typedef T* pointer;   // ָ������
		typedef T& reference;//  ��������
		typedef size_t size_type;// ��С
	public:
		����ռ�
		pointer allocate(size_type n, const void *hint = 0)
		{
			return _allocate(n, (pointer)0);
		}
		�ͷſռ�
		void deallocate(pointer p, size_type n)//  ��p��ָ��n���ռ��ͷŵ�
		{
			_deallocate(p);
		}
		�������
		void construct(pointer p, const T &value)// ��ָ��p��ָ�Ŀռ乹����� ��ֵ
		{
			_construct(p, value);
		}
		��������
		void destroy(pointer p)//  ��ָ��p��ָ�Ŀռ�Ķ�������
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
	D *ptmp = dynamic_cast<D*>(pb);  //������������ת��  �����̬ ���麯��

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
	D *ptmp = (D*)pb; //  ���з�������
	ptmp->show();
}
void main()
{
	//D d;
	Base d;//   �����������ǿתΪ�����ָ��   ����Ҳ��������  
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
	printf("%p, %p, %p\n", &c, static_cast<B*>(&c), reinterpret_cast<B*>(&c));// reinterpret_castֻ����ת������  ���ǲ���֤��ȫ��
}
/*
void main()
{
	const int a = 10;
	const int *p = &a;
	cout << "a = " << a << endl;
	int *q = reinterpret_cast<int*>(&a);//����ǣ�������� �� �ױ��Ե� reinterpret_cast������ת�� �������ⲻ����
	*q = 100;
	cout << "a = " << a << endl;
	volatile int b = 20; //�ױ���
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
	a = static_cast<double>(d); //��ʾת��
	//int *pi = static_cast<int*>(&ch);  
	int *pi = reinterpret_cast<int*>(&ch);  // reinterpret_cast�൱����ʾת��
}
/////////////////////////////////////////////////////////////////////////
/*
//const_cast ��������
//  1.����ȥ�������ĳ���
//  2.ȥ���ױ���
void main()
{
	const int a = 10;
	const int *p = &a;// int *p = &a;�ǲ��ܽ��ܵ�  �����const  ˵�����ܸ���
	cout << "a = " << a << endl;
	int *q = const_cast<int*>(&a);//  ����ȥ�������ĳ���
	*q = 100;
	cout << "a = " << a << endl;
	volatile int b = 20; //�ױ���
	int *pb = const_cast<int*>(&b);//  ȥ���ױ���
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
	a = static_cast<double>(d); //��ʾת��
	int *pi = static_cast<int*>(&ch);  //�����ǲ�������  ��Ϊ��������ʽת������ ���ǿ�����ʽת���Ĳſ�����static_cast
	int *pi = (int*)&ch;  
}
/////////////////////////////////////////////////////////////////////////////
/*
//��explicit  ���ܷ�����ʽת��
class Test
{
public:
	explicit Test(int data = 0) :m_data(data)  
	{}
	operator int() //ǿ������ת��
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
	//t=20;   //��explicit �ؼ��� ˵��������ʽת��
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
	int *p = (int*)0x0012ff7c;  //��ַ ���� -->16���ƽ��б�ʾ
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
	a = d; //��ʾת��
	int *pi = (int*)&ch;  //��ʾת��
}
*/