#include <iostream>
#include <string>
using namespace std;
/*
//继承与静态成员
//基类定义了static静态成员，则整个继承体系里面只有一个这样的成员。无论派生出多少个子类，都只有一个static成员实例 。如下
class Test
{
public:
	Test()
	{
		count++;
	}
public:
	int GetCount()const
	{
		return count;
	}
	//int GetCount()const
	//{
	//	return GetOBJCount();
	//}
private:
	static int count;//  类的静态成员必须在类外初始化
};
int Test::count = 0;
class D1 :public Test
{
public:
	//int GetCount()const
	//{
	//	return GetOBJCount();
	//}
};
class D2 :public Test
{
public:
	//int GetCount()const
	//{
	//	return GetOBJCount();
	//}
};
class D3 :public Test
{
public:
	//int GetCount()const
	//{
	//	return GetOBJCount();
	//}
};
class D4 :public Test
{
public:
	//int GetCount()const
	//{
	//	return GetOBJCount();
	//}
};
void main()
{
	D1 d1;
	cout << d1.GetCount() << endl;
	D2 d2;
	cout << d2.GetCount() << endl;
	D3 d3;
	cout << d3.GetCount() << endl;
	D4 d4;
	cout << d4.GetCount() << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//友元关系不能继承，也就是说基类友元不能访问子类私有和保护成员  如下
class Student;
class Person;
void Display(const Person& p, const Student& s);
class Person
{
public:
	friend void Display(const Person& p, const Student& s);
protected:
	string _name = "cb"; // 姓名
};
class Student : public Person
{

protected:
	int _stuNum = 418; // 学号
};
void Display(const Person& p, const Student& s)
{
	cout << p._name << endl;
	cout << s._stuNum << endl;// 之所以不能访问就是因为这仅仅是父类的友元函数 子类不能访问
	// 要怎末才能访问  就只能形成自己的友元函数  在子类中在加一句friend void Display(const Person& p, const Student& s);
	//  相当于爸爸的朋友不见得是儿子的朋友  儿子要操作只能自己在声明交朋友形成友元函数
}
void main()
{
	Person p;
	Student s;
	Display(p, s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Base1;
	ostream& operator<<(ostream &out, const Base1 &b);
class Base1
{
	friend ostream& operator<<(ostream &out, const Base1 &b);
public:
	Base1(int b = 0) :m_b(b)
	{
		cout << "Base1::Base1()" << endl;
	}
	~Base1()
	{
		cout << "Base1::~Base1()" << endl;
	}
private:
	int m_b = 0;
};
ostream& operator<<(ostream &out, const Base1 &b)
{
	out << b.m_b;
	return out;
}
class D :public Base1
{
public:
	D(int d = 0) :m_d(d)
	{

	}
private:
	int m_d = 0;

};
void main()
{
	Base1 b(100);
	cout <<"base"<< b << endl;
	D d;
	cout << "D=" << d << endl;
	//友元关系不能继承，也就是说基类友元不能访问子类私有和保护成员
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   多继承
class Base1
{
public:
	Base1()
	{
		cout << "Base1::Base1()" << endl;
	}
	~Base1()
	{
		cout << "Base1::~Base1()" << endl;
	}
};
class Base2
{
public:
	Base2()
	{
		cout << "Base2::Base2()" << endl;
	}
	~Base2()
	{
		cout << "Base2::~Base2()" << endl;
	}
};
class Base3
{
public:
	Base3()
	{
		cout << "Base3::Base3()" << endl;
	}
	~Base3()
	{
		cout << "Base3::~Base3()" << endl;
	}
};
//  多继承
//class D:public Base1,Base2,Base3  //这表明只共有继承Base1  私有继承2和3

//class D :public Base1, public Base2, public Base3
class D :public Base1, public Base3, public Base2  //构造和析构的顺序至于这个顺序有关
{
public:
	D()
	{
		cout << "D::D()" << endl;
	}
	~D()
	{
		cout << "D::~D()" << endl;
	}
};

void main()
{
	D d;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//1. 派生类的构造函数必须调用基类的构造函数初始化基类的那一部分成员。如果基类没有默认的构造函
//数，则必须在派生类构造函数的初始化列表阶段显示调用
//2. 派生类的拷贝构造函数必须调用基类的拷贝构造完成基类的拷贝初始化。
//3. 派生类的operator = 必须要调用基类的operator = 完成基类的复制。
//4. 派生类的析构函数会在被调用完成后自动调用基类的析构函数清理基类成员。因为这样才能保证派生类
//对象先清理派生类成员再清理基类成员的顺序。
//5. 派生类对象初始化先调用基类构造再调派生类构造。
//6. 派生类对象析构清理先调用派生类析构再调基类的析构
class Base
{
public:
	Base()
	{
		cout << "Base::Base()" << endl;
	}
	Base(const Base &b)//  拷贝构造
	{
		cout << "Base::Base(const Base &)" << endl;
		m_b = b.m_b;
	}
	Base operator=(const Base &b)//赋值语句
	{
		cout << "Base operator=(const Base &b)" << endl;
		m_b = b.m_b;
		return *this;
	}
public:
	void fun()
	{
		cout << "Base::fun()" << endl;
	}
	void fun(int a)
	{
		cout << "Base::fun(int a)" << endl;
	}
private:
	int m_b;
};
// 子类          父类
class D :public Base  //  继承
{
public:
	D() :m_b(0)  // 会调用父类的构造方法 但是如果父类构造方法给一个 Base（int b):m_b(b) 就不能成功了 因为父类要求是一个有参的  所以在参数列表改为 D():m_b(0),Base(0)
	{

	}

public:
	void fun()
	{
		cout << "Base::fun()" << endl;
	}
	void show()
	{
		cout << "D::shoe()" << endl;
	}
private:
	int m_b;
};
void main()
{
	D d;
	D d1 = d;//  调用的是父类的拷贝构造方法  说明我们在完成子类的拷贝构造当中首先要拷贝构造的是父类对象
	D d2;
	d2 = d1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//继承中的作用域
//1. 在继承体系中基类和派生类都有独立的作用域。
//2 子类和父类中有同名成员，子类成员将屏蔽父类对同名成员的直接访问，这种情况叫隐藏，也叫重定义。
//（在子类成员函数中，可以使用 基类::基类成员 显示访问）
//3. 需要注意的是如果是成员函数的隐藏，只需要函数名相同就构成隐藏。
//4. 注意在实际中在继承体系里面最好不要定义同名的成员。
class Base
{
public:
	void fun()
	{
		cout << "Base::fun()" << endl;
	}
	void fun(int a)
	{
		cout << "Base::fun(int a)" << endl;
	}
};
// 子类          父类
class D :public Base  //  继承
{
public:
	void fun()
	{
		cout << "Base::fun()" << endl;
	}
	void show()
	{
		cout << "D::shoe()" << endl;
	}
};
void main()
{
	D d;
	d.fun();
	//d.fun(0);//  如果子类中没有fun()方法就是可以的  但是子类有了fun()方法  就不能运行
	//这是因为子类一旦有了和父类同名方法 就不能访问父类其他的重载的方法了 我们把这种现象叫做同名隐藏
	//也就是说父类的同名方法被子类的同名方法隐藏掉了  所以一旦子类和父类的方法名同名  就只能够调用子类本身的方法

	//如果一定要访问只能明确告知编译器  可以如下 进行访问
	d.Base::fun(0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Base
{
public:
	void fun()
	{
		cout << "Base::fun()" << endl;
	}
};
// 子类          父类
class D :public Base  //  继承
{
public:
	void fun()
	{
		cout << "Base::fun()" << endl;
	}
	void show()
	{
		cout << "D::shoe()" << endl;
	}
};
void main()
{
	D d;
	Base *pb = &d;
	pb->fun();//  只能访问子类中父类所有的fun函数
	//d.fun();  //  只能访问子类自己的fun函数
}



class Person
{
public:
	void Print()
	{
		cout << "name" << _name << endl;
		cout << "age:" << _age << endl;
	}
protected:
	string _name = "peter"; // 姓名
	int _age = 18; // 年龄
};
class Teacher : public Person
{
protected:
	int _stuid; // 学号
};
void main()
{
	Teacher tcher;  //首先他有一个 _name  _age  _stuid 成员
	Person per;  //  _name  _age 成员
	//  因为tcher 中包含有per的所有成员   所以子类就可以给父类赋值  而父类不可以给子类赋值 
	//所以我们将子类就可以给父类赋值的这种现象叫  对象的切片
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Base
{
public:
	void fun()
	{
		cout << "Base::fun()" << endl;
	}
};
// 子类          父类
class D :public Base  //  继承
{
public:
	void show()
	{
		cout << "D::shoe()" << endl;
	}
};
void main()
{ 
	D d;
	d.show();
	d.fun();//  子类可以访问父类的信息
}
*/
