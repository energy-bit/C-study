#include <iostream>
#include <string>
using namespace std;

//  菱形继承 菱形继承是多继承的一种特殊情况。
//菱形继承的问题：从下面的对象成员模型构造，可以看出菱形继承有数据冗余和二义性的问题。

/*
class A
{
public :
	int m_a = 1;
};
class B:public A
{

public:
	int m_b = 2;
};
class C :public A
{
public:
	int m_c = 3;
};
class D :public B,public C
{
public:
	int m_d = 4;
}; 
void main()
{
	D d;
	d.m_d = 40;
	d.m_c = 30;
	d.m_b = 20;
	//d.m_a = 10;//  二义性
	// 不能够访问  因为B 和C分别继承了A的m_a  
	//但是D 继承了B和C的m_a 所以D不能够分辨m_a到底是谁的
	d.B::m_a = 100;
	d.C::m_a = 200;
	// 这样的话 就造成了m_a 有两个空间  一个B的100  一个C的200

	//那要继承A的m_a 怎末做  如下
}

//////////////////////////////////////////////////////////////////////////////////
class A
{
public:
	int m_a = 1;
};
class B :virtual public A
{
public:
	int m_b = 2;
};
class C :virtual public A
{
public:
	int m_c = 3;
};
class D :public B, public C
{
public:
	int m_d = 4;
};
void main()
{
	D d;
	d.m_d = 40;
	d.m_c = 30;
	d.m_b = 20;
	d.m_a = 100;//  让B C虚拟继承 A virtual 
}
*/
