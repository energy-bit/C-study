#include <iostream>
using namespace std;
class Base
{
public:
	 Base()
	{
		cout << "Base::Base()" << endl;
	}
	 ~Base()
	 {
		 cout << "Base::~Base()" << endl;
	 }
public:
	virtual Base* fun()  //  返回父类的地址
	{
		cout << "Base::fun()" << endl;
		return this;
	}
};
class D :public Base
{
public:
	D()
	{
		cout << "D::D()" << endl;
	}
	~D()  //  如果不加virtual 是无法调动子类的析构方法的
	{
		cout << "D::~D()" << endl;
	}
public:
	virtual D* fun()// 返回子类的地址
	{
		cout << "D::fun()" << endl;
		return this;
	}
private:
	int m_b = 0;
};
void main()
{
	Base*pb = new D;//  动态开辟  必须delete
	delete pb;//  调不动子类的析构方法  导致内存泄露
	//只要在弗雷德析构方法上 加上virtual  就会实现析构D 
	//  这也是唯一一个不同名的方法实现的多态
}

/////////////////////////////////////////////////////////////////////////////////////////
/*
//1. 协变(基类与派生类虚函数返回值类型不同)
//派生类重写基类虚函数时，与基类虚函数返回值类型不同。即基类虚函数返回基类对象的指针或者引用，
//派生类虚函数返回派生类对象的指针或者引用时，称为协变。
class Base
{
public:
	virtual Base* fun()  //  返回父类的地址
	{
		cout << "Base::fun()" << endl;
		return this;
	}
};
class D :public Base
{
public:
	virtual D* fun()// 返回子类的地址
	{
		cout << "D::fun()" << endl;
		return this;
	}
private:
	int m_b = 0;
};
void  main()
{
	D d;
	Base *pb = &d;
	pb->fun();
	//   这是唯一同名函数返回值类型不同还能形成的多态
	//  成之为协变
}
////////////////////////////////////////////////////////////////////////

class Base
{
public:
	 void fun(int a)
	{
		cout << "Base::fun()" << endl;
	}
	//virtual void fun(int a)
	//{
	//	cout << "Base::fun()" << endl;
	//}
private:
	int m_b = 0;
};
class D :public Base
{
public:
	void fun()
	{
		cout << "D::fun()" << endl;
	}
};
void main()
{
	cout << sizeof(Base) << endl;
	//  当不加virtual时 大小只有4个字节  加了之后变为8
	// 原因是底层多了一个_vfptr指针  多了四个字节  指的是虚函数 
} 

/////////////////////////////////////////////////////////////////////////

class Base
{
public:
	virtual void fun(int a)
	{
		cout << "Base::fun()" << endl;
	}
};
class D :public Base
{
public:
	void fun()
	{
		cout << "D::fun()" << endl;
	}
};
void  main()
{
	D d;
	Base *pb = &d;
	pb->fun(0);
	Base &rb = d;
	rb.fun(0);
	//  调的还是父类的fun函数  说明不能实现多态 
	//问题在于 父类fun函数有参数  那么子类就要重写才能被调用实现多态
	// 所以说多态不光是要给父类加一个虚 virtual 
	//有三个条件   
	//1 父类一定要虚  加virtual
	//2  子类要重写 要和父类的同名函数 参数类型 参数个数 返回值类型相同
	//3  在调动的时候必须通过父类的指针或引用
}
///////////////////////////////////////////////////////////////////////////

class A
{
public:
	virtual void Eat()
	{
		cout << "A::Eat()" << endl;
	}
	virtual void Sleep()
	{
		cout << "A::Sleep()" << endl;
	}
	virtual void Foot()
	{
		cout << "A::Foot()" << endl;
	}
};
class Person : public A
{
public:
	void Eat()
	{
		cout << "Person::Eat()" << endl;
	}
	void Sleep()
	{
		cout << "Person::Sleep()" << endl;
	}
	void Foot()
	{
		cout << "Person::Foot()" << endl;
	}
};
class Dog : public A
{
public:
	void Eat()
	{
		cout << "Dog::Eat()" << endl;
	}
	void Sleep()
	{
		cout << "Dog::Sleep()" << endl;
	}
	void Foot()
	{
		cout << "Dog::Foot()" << endl;
	}
};
class Pig : public A
{
public:
	void Eat()
	{
		cout << "Pig::Eat()" << endl;
	}
	void Sleep()
	{
		cout << "Pig::Sleep()" << endl;
	}
	void Foot()
	{
		cout << "Pig::Foot()" << endl;
	}
};
class Bug : public A
{
public:
	void Eat()
	{
		cout << "Bug::Eat()" << endl;
	}
	void Sleep()
	{
		cout << "Bug::Sleep()" << endl;
	}
	void Foot()
	{
		cout << "Bug::Foot()" << endl;
	}
};
//多态---用相同的接口实现不同的功能
void Active(A *pa)
{
	pa->Eat();
	pa->Foot();
	pa->Sleep();
}
void main()
{
	Person per;
	Dog    dog;
	Pig    pig;
	Bug    bug;
	Active(&per);   
	Active(&pig);
	Active(&dog);
	Active(&bug);
	//  比如A是动物 有很多功能  但是Person  Dog Pig Bug都是动物的一种
	//都有各自不同的功能  所以就要用一个相同的接口去实现这些不同类的功能 我们把这种就叫多态
}
///////////////////////////////////////////////////////////////////////////////////////////////////
class Base
{
public:
	virtual void fun()
	{
		cout << "Base::fun()" << endl;
	}
};
class D:public Base
{
public:
	void fun()
	{
		cout << "D::fun()" << endl;
	}
};
void main()
{
	D d;
	d.fun();
	Base *pb = &d;
	pb->fun();// 多态 在继承的角度 这行代码只能调用父类的fun()
	//函数但是因为在Base fun函数中加入了virtual 所以可以调用子类fun函数 形成多态
}
*/