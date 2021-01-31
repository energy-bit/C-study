#include <iostream>
using namespace std;
// 纯虚函数
//抽象类
class A  // 比如动物
{
public :
	//  作用  就是起到了一个接口作用
	virtual void Eat() = 0;//  等于0 就构成了纯虚函数  这个类也就叫抽象类
	virtual void sleep() = 0;
	virtual void Foot() = 0;
};
void main()
{
	A a;
	// 抽象类  就不能实例化它   
	//比如动物  具体神魔是动物 是一个抽象的概念就不能用具体的去实例化它
}

//////////////////////////////////////////////////////////////////////
//  重载  覆盖  隐藏的区别
// 重载
/*
class Base
{
public :
	void fun()       //两个fun函数构成了重载  		               
	{                       //1  是因为在同一个类中               
	}                       //2   函数名相同
	void fun(int a, int b)  //3   参数不同
	{
	}
};
/////////////////////////////////////////////////////////////////////////
//  覆盖
// 覆盖指的是子类函数覆盖父类函数
// 1  分别位于子类和父类中
// 2  函数名字相同
// 3  参数相同
// 4  父类中必须要有virtual 关键字  说起来覆盖就是多态的形式
class Base
{
public:
	virtual void fun()        		               
	{                                    
	}                      
};
class D :public Base
{
public :
	void fun()
	{

	}
};
void main()
{

}
*/