#include<iostream>
//#include<memory>
#include<vld.h>
using namespace std;

//ӵ��Ȩ��ת������-->��������ָ��ĺ���
namespace bit
{
	template<class _Ty>
	class auto_ptr
	{
	public:
		auto_ptr(_Ty *_P = 0) :_Owns(_P != 0), _Ptr(_P)
		{}
		auto_ptr(const auto_ptr<_Ty> &_Y) : _Owns(_Y._Owns), _Ptr(_Y.release())//�ٿ��������ʱ��  �ֽ�ԭ����ӵ��Ȩ�ͷŵ���ap)
		{}                                                                     // ��˼���ǣ�ap���Ұѿռ��ӵ��Ȩ���ݸ���ap1)��  ��ô�ҾͲ��������ͷ���
		~auto_ptr()
		{
			if (_Owns)  //ӵ��ȨΪ���ʱ�� �ͷ�
				delete _Ptr;
		}
	public:
		//const auto_ptr<_Ty> *const this
		_Ty* release()const// �ͷ�ӵ��Ȩ
		{
			((auto_ptr<_Ty> *const)this)->_Owns = false;
			//_Owns = false;
			return _Ptr;
		}
		_Ty& operator*()const
		{
			return *get();
		}
		_Ty* operator->()const
		{
			return get();
		}
		_Ty* get()const
		{
			return _Ptr;
		}
	private:
		bool _Owns;  //ӵ��Ȩ
		_Ty  *_Ptr;  //�����ָ��
	};
};
void main()
{
	int *p = new int(10);
	bit::auto_ptr<int> ap(p);
	cout << "*ap = " << *ap << endl;

	bit::auto_ptr<int> ap1 = ap; //vc 6.0�� auto_ptr  ��������
	//bit::auto_ptr<int> ap1;
	//ap1 = ap; //vc auto_ptr
	cout << "*ap1 = " << *ap1 << endl;

	cout << "*ap = " << *ap << endl;    //����Ҫ  ź��˿�� ��˼�ǽ�ӵ��Ȩ�Ѿ���Ϊ���� ����ָ�뻹ָ��  ���Ի��ܷ���
}
//////////////////////////////////////////////////////////////////
/*
class Test
{
public:
	void fun()
	{
		cout << "This is Test::fun()" << endl;
	}
};
void main()
{
	int *p = new int(10);
	bit::auto_ptr<int> ap(p);
	cout << "*ap = " << *ap << endl;
	bit::auto_ptr<Test> ap1(new Test);
	ap1->fun();
}
////////////////////////////////////////////////////////////////////////////////////
/*
class Test
{
public:
	void fun()
	{
		cout << "This is Test::fun()" << endl;
	}
};
void main()
{
	int *p = new int(10); //��Ϊ�������  ��������ѿռ佻�����������ָ����  ��ô����Ͳ����� ���е��ͷž�����������
	auto_ptr<int> ap(p);  //���� ָ��   ������� �������
	cout << *ap << endl;
	Test *pt = new Test;
	auto_ptr<Test> ap1(pt); // * ->  ��������ָ��  ��ʵ�Ƕ��� ֻ���������ص�* �� ->
	ap1->fun();
}
/////////////////////////////////////////////////////////////////////////////////
/*
int Div(int a, int b)throw(int, char, double)  //�쳣�淶
{
	char ch = 'A';
	if (b == 0) // �����쳣
		throw b;
	return a / b;
}
void main()
{
	int *p = new int(10); //����һ���ռ�
	//auto_ptr<int> ap(p);  //����ָ��  �Զ�ָ��  ��������Ͳ��ᷢ���ڴ�й¶�� ���²���delete p;
	try
	{
		int result = Div(10, 0);
	}
	catch (int)
	{
		cout << "Error." << endl;
		return;
	}
	//........................��û������ָ��ǰ����쳣�ͻ�������ڴ��й¶
	delete p;
}
/////////////////////////////////////////////////////////////////////
/*
//   �Զ����쳣��   
//ջ���쳣����
template<typename T>
class pushOnFull
{
private:
	T _value;
public:
	pushOnFull(T i)
	{
		_value = i;
	}
	T value()
	{
		return _value;
	}
	void what()
	{
		cerr << "ջ����" << value() << "δѹ��ջ" << endl;
	}
};
//ջ���쳣����
template<typename T>
class popOnEmpty
{
public:
	void what()
	{
		cerr << "ջ�ѿգ��޷���ջ" << endl;
	}
};
template<typename T>
class Stack
{
private:
	int top;                                    //ջ��ָ�루�±꣩
	T *elements;                               //��̬��������ֵ
	int maxSize;                               //ջ������ɵ�Ԫ�ظ���
public:
	Stack(int sz = 20)                 //ջ�粻ָ����С����Ϊ20Ԫ��
	{
		maxSize = sz;
		elements = new T[maxSize];
		top = 0;
	}
	~Stack()
	{
		delete[] elements;
		elements = nullptr;
		maxSize = top = 0;
	}
	void Push(const T &data) throw(pushOnFull<T>)
	{
		if (IsFull())
			throw pushOnFull<T>(data);
		elements[top++] = data;
	}
	T Pop() throw(popOnEmpty<T>)
	{
		if (IsEmpty())
			throw popOnEmpty<T>();
		top--;
		return  elements[top];
	}
	T GetElem(int i)
	{
		return elements[i];
	} //����ָ��Ԫ��
	void MakeEmpty()
	{
		top = 0;
	}                  //���ջ
	bool IsEmpty() const
	{
		return top == 0;
	}          //��ջ��
	bool IsFull() const
	{
		return top == maxSize;
	}      //��ջ��
	void PrintStack()
	{
		for (int i = top - 1; i >= 0; --i)
			cout << elements[i] << endl;
	}
};
void main()
{
	Stack<int> st(8);
	try
	{
		for (int i = 1; i <= 8; ++i)
			st.Push(i);
		st.PrintStack();
		for (int i = 0; i < 9; ++i)
			cout << st.Pop() << "��ջ." << endl;
	}
	catch (pushOnFull<int> &e)
	{
		e.what();
	}
	catch (popOnEmpty<int> &e)
	{
		e.what();
	}
}
//////////////////////////////////////////////////////////////
//  ϵͳ�ṩ���쳣
/*
#define DefaultArraySize 5
template<typename elemType>
class Array
{
private:
	int        size;
	elemType * ia;
public:
	explicit Array(int sz = DefaultArraySize)
	{
		size = sz;
		ia = new elemType[size];
	}
	~Array()
	{
		delete[] ia;
	}
	elemType & operator[](int ix) const
	{
		//�±������[ ]����
		if (ix < 0 || ix >= size)  //�±�Խ��
		{
			//�����쳣�׳�,��ֹ����ֵԽ��
			string eObj = "out_of_range error in Array<elemType >::operator[]()";
			//throw out_of_range(eObj);
			throw range_error(eObj.c_str());
		}
		return  ia[ix];//����ԭ��[ ]������������ʽ
	}
};
void main()
{
	Array<int> ar(10);
	for (int i = 0; i < 10; ++i)
		ar[i] = i + 1;
	try
	{
		for (int i = 0; i <= 10; ++i)
			cout << ar[i] << " ";
		cout << endl;
	}
	catch (out_of_range &e)
	{
		cout << e.what() << endl;
	}
	catch (range_error &e)
	{
		cout << e.what() << endl;
	}

}
/*
void main()
{
	try
	{
		int *ptr = new int[536870910];  //new  һ�����bad_alloc���������쳣
		delete[]ptr;
	}
	catch (bad_alloc &e)
	{
		cout << e.what() << endl;
		//cout<<"bad alloc."<<endl;
	}
}
////////////////////////////////////////////////////////////////
/*
class Base
{};
class D : public Base
{};
class C : public Base
{};
int Div(int a, int b)throw(int, char, double)  //�쳣�淶
{
	char ch = 'A';
	D d;
	C c;//��Ϊ���̳��˸���  ���������׳�c ��catch(C &e)���� û�оͻᱻ����Base����
	if (b == 0) // �����쳣
		throw c;
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
	catch (int &x)
	{
		cout << "Div<int> Error By Zero." << endl;
	}
	catch (char &x)
	{
		cout << "Div<char> Error By Zero." << endl;
	}
	catch (D &e)
	{
		cout << "Div<D> Error By Zero." << endl;
	}
	catch (Base &e)
	{
		cout << "Div<Base> Error By Zero." << endl;
	}
	catch (...)
	{
		cout << "Div<...> Error By Zero." << endl;
	}
}
////////////////////////////////////////////////////////////////////////
/*
double Division(int a, int b)
{
	// ��b == 0ʱ�׳��쳣
	if (b == 0)
	{
		throw "Division by zero condition!";
	}
	return (double)a / (double)b;
}
void Func()
{
	// ������Կ������������0�����׳��쳣�����������arrayû�еõ��ͷš�
	// �������ﲶ���쳣�󲢲������쳣���쳣���ǽ������洦�����ﲶ������
	// �����׳�ȥ
	int* array = new int[10];
	try
	{
		int len, time;
		cin >> len >> time;
		cout << Division(len, time) << endl;
	}
	catch (...)
	{
		cout << "delete []" << array << endl;
		delete[] array;
		throw;   //�쳣�ٴ��׳�  �׳��Ļ���Division����쳣
	}
	// ...
	cout << "delete []" << array << endl;
	delete[] array;
}
int main()
{
	try
	{
		Func();
	}
	catch (const char* errmsg)//  ��������ַ���
	{
		cout << errmsg << endl;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////
/*
int Div(int a, int b)throw(int, char, double)  //�쳣�淶
{
	if (b == 0) // �����쳣
		throw b;
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
	catch (int &x)
	{
		cout << "Div Error By Zero." << endl;
	}
}
*/