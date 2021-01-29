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
	virtual Base* fun()  //  ���ظ���ĵ�ַ
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
	~D()  //  �������virtual ���޷��������������������
	{
		cout << "D::~D()" << endl;
	}
public:
	virtual D* fun()// ��������ĵ�ַ
	{
		cout << "D::fun()" << endl;
		return this;
	}
private:
	int m_b = 0;
};
void main()
{
	Base*pb = new D;//  ��̬����  ����delete
	delete pb;//  �������������������  �����ڴ�й¶
	//ֻҪ�ڸ��׵����������� ����virtual  �ͻ�ʵ������D 
	//  ��Ҳ��Ψһһ����ͬ���ķ���ʵ�ֵĶ�̬
}

/////////////////////////////////////////////////////////////////////////////////////////
/*
//1. Э��(�������������麯������ֵ���Ͳ�ͬ)
//��������д�����麯��ʱ��������麯������ֵ���Ͳ�ͬ���������麯�����ػ�������ָ��������ã�
//�������麯����������������ָ���������ʱ����ΪЭ�䡣
class Base
{
public:
	virtual Base* fun()  //  ���ظ���ĵ�ַ
	{
		cout << "Base::fun()" << endl;
		return this;
	}
};
class D :public Base
{
public:
	virtual D* fun()// ��������ĵ�ַ
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
	//   ����Ψһͬ����������ֵ���Ͳ�ͬ�����γɵĶ�̬
	//  ��֮ΪЭ��
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
	//  ������virtualʱ ��Сֻ��4���ֽ�  ����֮���Ϊ8
	// ԭ���ǵײ����һ��_vfptrָ��  �����ĸ��ֽ�  ָ�����麯�� 
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
	//  ���Ļ��Ǹ����fun����  ˵������ʵ�ֶ�̬ 
	//�������� ����fun�����в���  ��ô�����Ҫ��д���ܱ�����ʵ�ֶ�̬
	// ����˵��̬������Ҫ�������һ���� virtual 
	//����������   
	//1 ����һ��Ҫ��  ��virtual
	//2  ����Ҫ��д Ҫ�͸����ͬ������ �������� �������� ����ֵ������ͬ
	//3  �ڵ�����ʱ�����ͨ�������ָ�������
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
//��̬---����ͬ�Ľӿ�ʵ�ֲ�ͬ�Ĺ���
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
	//  ����A�Ƕ��� �кܶ๦��  ����Person  Dog Pig Bug���Ƕ����һ��
	//���и��Բ�ͬ�Ĺ���  ���Ծ�Ҫ��һ����ͬ�Ľӿ�ȥʵ����Щ��ͬ��Ĺ��� ���ǰ����־ͽж�̬
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
	pb->fun();// ��̬ �ڼ̳еĽǶ� ���д���ֻ�ܵ��ø����fun()
	//����������Ϊ��Base fun�����м�����virtual ���Կ��Ե�������fun���� �γɶ�̬
}
*/