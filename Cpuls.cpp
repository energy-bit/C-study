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
	//10 = 1;  //��ֵ
	int a = 10;
	&a;
	const int c = 100;
	//c = a;
	cout << &c << endl;
	int &&d = c;
}
//C++11����ֵ�������ϸ�����֣�
//C�����еĴ���ֵ�����磺a + b, 100
//����ֵ�����磺���ʽ���м�������������ֵ�ķ�ʽ���з��ء�
/*
int Add(int a, int b)
{
	return a + b;
}
void main()
{
	const int &a = 10;
	int &&b = 20;  //��ֵ����  
	int &&res = Add(10, 20);
}
/*
void main()
{
	//��ֵ ��ֵ ����
	int a = 10;
	int &b = a;
	int *ptr = &a;
	int* &q = ptr;
	int ar[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int(&br)[10] = ar;   //[] > &
	const int &x = 10;
}
//�˹�����ֵ����ֵ�����ֲ��Ǻܺ����֣�һ����Ϊ��
//      1. ��ͨ���͵ı�������Ϊ�����֣�����ȡ��ַ������Ϊ����ֵ��
//      2. const���εĳ����������޸ģ�ֻ�����͵ģ�����Ӧ�ð�����ֵ�Դ�������Ϊ�����ȡ��ַ(���ֻ��
//         const���ͳ����Ķ��壬�����������俪�ٿռ䣬����Ըó���ȡ��ַʱ����������Ϊ�俪�ٿռ�)��
//          C++11��Ϊ������ֵ��
//     3. ������ʽ�����н����һ����ʱ�������߶�����Ϊ����ֵ��
//     4. ������ʽ���н���򵥸�������һ����������Ϊ����ֵ
/*
class Test
{
public:
	//Test() = default;
	Test(int d) : m_data(d)
	{}
	Test(const Test &t) = delete;//  C++11������Ĭ�Ͽ�������
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
    typeidֻ�ܲ鿴���Ͳ����������ඨ������
    dynamic_castֻ��Ӧ���ں����麯���ļ̳���ϵ��
template<class T1, class T2>
T1 Add(const T1& left, const T2& right)
{
	auto res = left + right;
	//cout<<typeid(res).name()<<endl;
	decltype(res) value;//decltype�ؼ��־��н�res������ȡ�����������ڶ����±���������
	return res;
}
void main()
{
	Add(10, 'A');
}
/*

     autoʹ�õ�ǰ���ǣ�����Ҫ��auto���������ͽ��г�ʼ��������������޷��Ƶ���auto��ʵ�����͡�����
ʱ�������Ҫ���ݱ��ʽ�������֮���������ͽ����Ƶ�����Ϊ�����ڼ䣬���벻�����У���ʱautoҲ��
����Ϊ����
auto fun(auto a = 10)//  �����Ƶ����������� Ҳ�����Ƶ�����ֵ������
{
	cout << a << endl;
}
void main()
{
	//auto a = 10;//  �����Ƶ�����������
}
/*
typedef map<int, string> ismap_type;  
void main()
{
	map<string, string> ssmap;
	map<string, string>::iterator it = ssmap.begin();
	cout << typeid(it).name() << endl;// ֻ�ܴ�ӡ��it������
	auto it1 = ssmap.begin();//  auto�Զ��Ƶ�
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
	int *ptr = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};// ��̬���飬��C++98�в�֧��
}
/*
void main()
{
	vector<int> iv{ 1, 2, 3, 4, 5, 6 };//C++98�Ͳ�����
}
/*
void main()
{
	int ar[] = { 1, 2, 3, 4, 5 };//��C++98�У���׼����ʹ�û�����{}������Ԫ�ؽ���ͳһ���б��ʼֵ�趨��
}
*/