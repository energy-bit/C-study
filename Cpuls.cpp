#include<iostream>
//#include<bitset>
#include<vector>
#include<map>
using namespace std;

int Add(int a, int b)
{
	return a + b;
}

void main()
{
	Add(10, 20) = 100;  //const 
}
/*
void main()
{
	//10 = 1;  //右值
	int a = 10;
	&a;
	const int c = 100;
	//c = a;
	cout << &c << endl;
	int &&d = c;
}
//C++11对右值进行了严格的区分：
//C语言中的纯右值，比如：a + b, 100
//将亡值。比如：表达式的中间结果、函数按照值的方式进行返回。
/*
int Add(int a, int b)
{
	return a + b;
}
void main()
{
	const int &a = 10;
	int &&b = 20;  //右值引用  
	int &&res = Add(10, 20);
}
/*
void main()
{
	//左值 右值 引用
	int a = 10;
	int &b = a;
	int *ptr = &a;
	int* &q = ptr;
	int ar[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int(&br)[10] = ar;   //[] > &
	const int &x = 10;
}
//此关于左值与右值的区分不是很好区分，一般认为：
//      1. 普通类型的变量，因为有名字，可以取地址，都认为是左值。
//      2. const修饰的常量，不可修改，只读类型的，理论应该按照右值对待，但因为其可以取地址(如果只是
//         const类型常量的定义，编译器不给其开辟空间，如果对该常量取地址时，编译器才为其开辟空间)，
//          C++11认为其是左值。
//     3. 如果表达式的运行结果是一个临时变量或者对象，认为是右值。
//     4. 如果表达式运行结果或单个变量是一个引用则认为是左值
/*
class Test
{
public:
	//Test() = default;
	Test(int d) : m_data(d)
	{}
	Test(const Test &t) = delete;//  C++11不允许默认拷贝构造
	Test& operator=(const Test&) = delete;
protected:
	//C++98
	//Test(const Test &t);
	//Test& operator=(const Test&);
private:
	int m_data;
};
void main()
{
	Test t(1);
	Test t1 = t;
	Test t2(0);
	t2 = t;
}
/*
    typeid只能查看类型不能用其结果类定义类型
    dynamic_cast只能应用于含有虚函数的继承体系中
template<class T1, class T2>
T1 Add(const T1& left, const T2& right)
{
	auto res = left + right;
	//cout<<typeid(res).name()<<endl;
	decltype(res) value;//decltype关键字具有将res类型提取出来并且用于定义新变量的能力
	return res;
}
void main()
{
	Add(10, 'A');
}
/*

     auto使用的前提是：必须要对auto声明的类型进行初始化，否则编译器无法推导出auto的实际类型。但有
时候可能需要根据表达式运行完成之后结果的类型进行推导，因为编译期间，代码不会运行，此时auto也就
无能为力。
auto fun(auto a = 10)//  不能推导参数的类型 也不能推导返回值的类型
{
	cout << a << endl;
}
void main()
{
	//auto a = 10;//  可以推导变量的类型
}
/*
typedef map<int, string> ismap_type;  
void main()
{
	map<string, string> ssmap;
	map<string, string>::iterator it = ssmap.begin();
	cout << typeid(it).name() << endl;// 只能打印出it的类型
	auto it1 = ssmap.begin();//  auto自动推导
	cout << typeid(it1).name() << endl;
	ismap_type ismap;
}
/*
template<class Type>
class seqlist
{
public:
	seqlist(int sz = 10)
	{
		capacity = sz;
		base = new Type[capacity];
		size = 0;
	}
	seqlist(initializer_list<Type> l)
	{
		capacity = l.size();
		size = 0;
		base = new Type[capacity];
		for (auto &e : l)
			base[size++] = e;
	}
private:
	Type *base;
	size_t capacity;
	size_t size;
};
void main()
{
	seqlist<int> sq = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
}
/*
void main()
{
	int *ptr = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};// 动态数组，在C++98中不支持
}
/*
void main()
{
	vector<int> iv{ 1, 2, 3, 4, 5, 6 };//C++98就不可以
}
/*
void main()
{
	int ar[] = { 1, 2, 3, 4, 5 };//在C++98中，标准允许使用花括号{}对数组元素进行统一的列表初始值设定。
}
*/