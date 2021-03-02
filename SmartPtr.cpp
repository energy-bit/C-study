#include<iostream>
#include<vld.h>
#include<string>
#include<memory>
#include<thread>
#include<mutex>
using namespace std;
//#include<boost/smart_ptr.hpp>//   如果不提供shared_array 就用一个删除器
//using namespace boost;
struct listNode
{
	int data;
	std::weak_ptr<listNode> prev;
	std::weak_ptr<listNode> next;
	listNode()
	{
		cout << "listNode::listNode()" << endl;
	}
	~listNode()
	{
		cout << "listNode::~listNode()" << endl;
	}
};
//定制删除器  函数
void Del(listNode *pn)
{
	cout << "Del pn" << endl;
	delete[]pn;
}
void DelMalloc(int *pn)
{
	cout << "DelMalloc pn" << endl;
	delete[]pn;
}
void main()
{
	listNode *pa = new listNode[5];
	shared_ptr<listNode> spa(pa, Del);       //delete _px;  不在调用析构方法 而是去调用Del函数去释放
	int *ptr = (int*)malloc(sizeof(int)* 10);
	shared_ptr<int> spa1(ptr, DelMalloc);
}
/////////////////////////////////////////////////////////////////////////
/*
struct listNode
{
	int data;
	//shared_ptr<listNode> prev;
	//shared_ptr<listNode> next;
	weak_ptr<listNode> prev;
	weak_ptr<listNode> next;
	~listNode()
	{
		cout << "listNode::~listNode()" << endl;
	}
};
void main()
{
	shared_ptr<listNode> node1(new listNode);//   保存节点的地址
	shared_ptr<listNode> node2(new listNode);
	cout << "node1 use_count = " << node1.use_count() << endl;
	cout << "node2 use_count = " << node2.use_count() << endl;
	node1->next = node2;
	node2->prev = node1;
	cout << "node1 use_count = " << node1.use_count() << endl;
	cout << "node2 use_count = " << node2.use_count() << endl;
}
//shared_ptr的循环引用//1. node1和node2两个智能指针对象指向两个节点，引用计数变成1，我们不需要手动delete
//2. node1的_next指向node2，node2的_prev指向node1，引用计数变成2
//3. node1和node2析构，引用计数减到1，但是_next还指向下一个节点。但是_prev还指向上一个节点
//4. 也就是说_next析构了，node2就释放了
//5. 也就是说_prev析构了，node1就释放了
//6. 但是_next属于node的成员，node1释放了，_next才会析构，而node1由_prev管理，_prev属于node2成员，所以这就叫循环引用，谁也不会释放

//解决方案：在引用计数的场景下，把节点中的_prev和_next改成weak_ptr就可以了
// 原理就是，node1->_next = node2;和node2->_prev = node1;时weak_ptr的_next和_prev不会增加node1和node2的引用计数
/////////////////////////////////////////////////////////////////////////
/*
template<class T>
class Shared_Ptr
{
public:
	Shared_Ptr(T *_P = 0) : _Ptr(_P), _UseCount((size_t*)new int(1)), _Mutex(new mutex)
	{}
	Shared_Ptr(const Shared_Ptr<T> &_Y)
		: _Ptr(_Y._Ptr), _UseCount(_Y._UseCount), _Mutex(_Y._Mutex)
	{
		Increment();
	}
	Shared_Ptr<T>& operator=(const Shared_Ptr<T> &_Y)
	{
		if (this != &_Y)
		{
			//释放资源
			Decrement();
			_Ptr = _Y._Ptr;
			_UseCount = _Y._UseCount;
			Increment();
		}
		return *this;
	}
	~Shared_Ptr()
	{
		Decrement();
	}
public:
	T& operator*()const
	{
		return *_Ptr;
	}
	T* operator->()const
	{
		return _Ptr;
	}
	void reset(T *_P = 0)
	{
		if (_Ptr != _P)
			Decrement();
		_Ptr = _P;
		_UseCount = (size_t*)new int(1);
	}
public:
	size_t use_count()const
	{
		return *_UseCount;
	}
	bool unique()const
	{
		return (use_count() == 1);
	}
public:
	void Increment()
	{
		_Mutex->lock();
		++*_UseCount;   //临界区  就是同一个时刻只能一个线程在这里工作
		_Mutex->unlock();
	}
	void Decrement()
	{
		bool delete_flag = false;
		_Mutex->lock();
		if (--*_UseCount == 0)
		{
			delete _Ptr;
			delete _UseCount;
			delete_flag = true;//   当_UseCount为0的时候 将elete_flag置为真
		}
		_Mutex->unlock();
		if (delete_flag) // 如果为真的话  也就要释放-Mutex
			delete _Mutex;
	}
private:
	T *_Ptr;
	size_t *_UseCount;
	mutex *_Mutex;
};
class Date
{
public:
	Date() : year(0), month(0), day(0)
	{}
public:
	int year;
	int month;
	int day;
};
mutex mt;
void SharePtrFunc(Shared_Ptr<Date>& sp, size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		Shared_Ptr<Date> copy(sp);
		mt.lock();//   不加锁 就不安全 
		copy->year++;
		copy->month++;
		copy->day++;
		mt.unlock();
	}
}
void main()
{
	Shared_Ptr<Date> sp(new Date);
	const size_t n = 10000000;
	thread t1(SharePtrFunc, sp, n);
	thread t2(SharePtrFunc, sp, n);
	t1.join();
	t2.join();
	cout << sp->year << endl;
	cout << sp->month << endl;
	cout << sp->day << endl;
}
/////////////////////////////////////////////////////////////////////////

//shared_ptr的线程安全问题//  1. 智能指针对象中引用计数是多个智能指针对象共享的，两个线程中智能指针的引用计数同时++或--
//这个操作不是原子的，引用计数原来是1，++了两次，可能还是2.这样引用计数就错乱了
//会导致资源未释放或者程序崩溃的问题 所以只能指针中引用计数++、--是需要加锁的
//也就是说引用计数的操作是线程安全的。
//  2. 智能指针管理的对象存放在堆上，两个线程中同时去访问，会导致线程安全问题/*
void thread_fun(Shared_Ptr<int> &sp, int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << "use_count = " << sp.use_count() << endl;
		Shared_Ptr<int> copy(sp);//  如果不加锁的话 多线程 就有可能两者同时运行到这里  但是计数之加只一次 最后释放空间时发生错误
		cout << "use_count = " << sp.use_count() << endl;//  有可能有三个对象 但是引用计数只有2  释放空间时就发生错误了  这就是考虑线程安全的原因
	}
	cout << "use_count = " << sp.use_count() << endl;
}
void main()
{
	int n = 2;
	int *p = new int(100);
	Shared_Ptr<int> sp(p);
	thread th1(thread_fun, sp, n);
	thread th2(thread_fun, sp, n);
	cout << "sp use_count =" << sp.use_count() << endl;
	th1.join();
	th2.join();
}
/////////////////////////////////////////////////////////////////////////
/*
void main()
{
	int *p = new int(100);
	int *q = new int(200);
	int *x = new int(1);
	Shared_Ptr<int> sp(p);
	cout << "*sp = " << *sp << endl;
	cout << "use_count = " << sp.use_count() << endl;
	Shared_Ptr<int> sp1 = sp;
	cout << "use_count = " << sp.use_count() << endl;
	{
		Shared_Ptr<int> sp2 = sp1;
		cout << "use_count = " << sp.use_count() << endl;
	}
	cout << "use_count = " << sp.use_count() << endl;
	Shared_Ptr<int> sp2(q);
	Shared_Ptr<int> sp3(sp2);
	sp2 = sp1;
	sp3.reset(x);
}
*/