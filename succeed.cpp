#include <iostream>
#include <string>
using namespace std;


/*
//�̳��뾲̬��Ա
//���ඨ����static��̬��Ա���������̳���ϵ����ֻ��һ�������ĳ�Ա���������������ٸ����࣬��ֻ��һ��static��Աʵ�� ������class Test{public:	Test()	{		count++;	}public:	int GetCount()const	{		return count;	}	//int GetCount()const	//{	//	return GetOBJCount();	//}private:	static int count;//  ��ľ�̬��Ա�����������ʼ��};int Test::count = 0;class D1 :public Test{public:	//int GetCount()const	//{	//	return GetOBJCount();	//}};class D2 :public Test{public:	//int GetCount()const	//{	//	return GetOBJCount();	//}};class D3 :public Test{public:	//int GetCount()const	//{	//	return GetOBJCount();	//}};class D4 :public Test{public:	//int GetCount()const	//{	//	return GetOBJCount();	//}};void main(){	D1 d1;	cout << d1.GetCount() << endl;	D2 d2;	cout << d2.GetCount() << endl;	D3 d3;	cout << d3.GetCount() << endl;	D4 d4;	cout << d4.GetCount() << endl;}


//��Ԫ��ϵ���ܼ̳У�Ҳ����˵������Ԫ���ܷ�������˽�кͱ�����Ա  ����
class Student;
class Person;
void Display(const Person& p, const Student& s);
class Person
{
public:
	friend void Display(const Person& p, const Student& s);
protected:
	string _name = "cb"; // ����
};
class Student : public Person
{

protected:
	int _stuNum = 418; // ѧ��
};
void Display(const Person& p, const Student& s)
{
	cout << p._name << endl;
	cout << s._stuNum << endl;// ֮���Բ��ܷ��ʾ�����Ϊ������Ǹ������Ԫ���� ���಻�ܷ���
	// Ҫ��ĩ���ܷ���  ��ֻ���γ��Լ�����Ԫ����  ���������ڼ�һ��friend void Display(const Person& p, const Student& s);
	//  �൱�ڰְֵ����Ѳ������Ƕ��ӵ�����  ����Ҫ����ֻ���Լ��������������γ���Ԫ����
}
void main()
{
	Person p;
	Student s;
	Display(p, s);
}
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
	//��Ԫ��ϵ���ܼ̳У�Ҳ����˵������Ԫ���ܷ�������˽�кͱ�����Ա
}

//   ��̳�
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
//  ��̳�
//class D:public Base1,Base2,Base3  //�����ֻ���м̳�Base1  ˽�м̳�2��3

//class D :public Base1, public Base2, public Base3
class D :public Base1, public Base3, public Base2  //�����������˳���������˳���й�
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



//1. ������Ĺ��캯��������û���Ĺ��캯����ʼ���������һ���ֳ�Ա���������û��Ĭ�ϵĹ��캯
//����������������๹�캯���ĳ�ʼ���б�׶���ʾ����
//2. ������Ŀ������캯��������û���Ŀ���������ɻ���Ŀ�����ʼ����
//3. �������operator = ����Ҫ���û����operator = ��ɻ���ĸ��ơ�
//4. ������������������ڱ�������ɺ��Զ����û��������������������Ա����Ϊ�������ܱ�֤������
//�����������������Ա����������Ա��˳��
//5. ����������ʼ���ȵ��û��๹���ٵ������๹�졣
//6. ������������������ȵ��������������ٵ����������
class Base
{
public:
	Base()
	{
		cout << "Base::Base()" << endl;
	}
	Base(const Base &b)//  ��������
	{
		cout << "Base::Base(const Base &)" << endl;
		m_b = b.m_b;
	}
	Base operator=(const Base &b)//��ֵ���
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
// ����          ����
class D :public Base  //  �̳�
{
public:
	D() :m_b(0)  // ����ø���Ĺ��췽�� ����������๹�췽����һ�� Base��int b):m_b(b) �Ͳ��ܳɹ��� ��Ϊ����Ҫ����һ���вε�  �����ڲ����б��Ϊ D():m_b(0),Base(0)
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
	D d1 = d;//  ���õ��Ǹ���Ŀ������췽��  ˵���������������Ŀ������쵱������Ҫ����������Ǹ������
	D d2;
	d2 = d1;
}

//�̳��е�������
//1. �ڼ̳���ϵ�л���������඼�ж�����������
//2 ����͸�������ͬ����Ա�������Ա�����θ����ͬ����Ա��ֱ�ӷ��ʣ�������������أ�Ҳ���ض��塣
//���������Ա�����У�����ʹ�� ����::�����Ա ��ʾ���ʣ�
//3. ��Ҫע���������ǳ�Ա���������أ�ֻ��Ҫ��������ͬ�͹������ء�
//4. ע����ʵ�����ڼ̳���ϵ������ò�Ҫ����ͬ���ĳ�Ա��
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
// ����          ����
class D :public Base  //  �̳�
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
	//d.fun(0);//  ���������û��fun()�������ǿ��Ե�  ������������fun()����  �Ͳ�������
	//������Ϊ����һ�����˺͸���ͬ������ �Ͳ��ܷ��ʸ������������صķ����� ���ǰ������������ͬ������
	//Ҳ����˵�����ͬ�������������ͬ���������ص���  ����һ������͸���ķ�����ͬ��  ��ֻ�ܹ��������౾��ķ���

	//���һ��Ҫ����ֻ����ȷ��֪������  �������� ���з���
	d.Base::fun(0);
}


class Base
{
public:
	void fun()
	{
		cout << "Base::fun()" << endl;
	}
};
// ����          ����
class D :public Base  //  �̳�
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
	pb->fun();//  ֻ�ܷ��������и������е�fun����
	//d.fun();  //  ֻ�ܷ��������Լ���fun����
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
	string _name = "peter"; // ����
	int _age = 18; // ����
};class Teacher : public Person
{
protected:
	int _stuid; // ѧ��
};
void main(){	Teacher tcher;  //��������һ�� _name  _age  _stuid ��Ա	Person per;  //  _name  _age ��Ա	//  ��Ϊtcher �а�����per�����г�Ա   ��������Ϳ��Ը����ำֵ  �����಻���Ը����ำֵ 	//�������ǽ�����Ϳ��Ը����ำֵ�����������  �������Ƭ}


class Base
{
public:
	void fun()
	{
		cout << "Base::fun()" << endl;
	}
};
// ����          ����
class D :public Base  //  �̳�
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
	d.fun();//  ������Է��ʸ������Ϣ
}
*/