#include<iostream>
#include<vld.h>
#include<string>
#include<memory>
#include<thread>
#include<mutex>
using namespace std;
//#include<boost/smart_ptr.hpp>//   ������ṩshared_array ����һ��ɾ����
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
//����ɾ����  ����
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
	shared_ptr<listNode> spa(pa, Del);       //delete _px;  ���ڵ����������� ����ȥ����Del����ȥ�ͷ�
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
	shared_ptr<listNode> node1(new listNode);//   ����ڵ�ĵ�ַ
	shared_ptr<listNode> node2(new listNode);
	cout << "node1 use_count = " << node1.use_count() << endl;
	cout << "node2 use_count = " << node2.use_count() << endl;
	node1->next = node2;
	node2->prev = node1;
	cout << "node1 use_count = " << node1.use_count() << endl;
	cout << "node2 use_count = " << node2.use_count() << endl;
}
//shared_ptr��ѭ������//1. node1��node2��������ָ�����ָ�������ڵ㣬���ü������1�����ǲ���Ҫ�ֶ�delete
//2. node1��_nextָ��node2��node2��_prevָ��node1�����ü������2
//3. node1��node2���������ü�������1������_next��ָ����һ���ڵ㡣����_prev��ָ����һ���ڵ�
//4. Ҳ����˵_next�����ˣ�node2���ͷ���
//5. Ҳ����˵_prev�����ˣ�node1���ͷ���
//6. ����_next����node�ĳ�Ա��node1�ͷ��ˣ�_next�Ż���������node1��_prev����_prev����node2��Ա��������ͽ�ѭ�����ã�˭Ҳ�����ͷ�

//��������������ü����ĳ����£��ѽڵ��е�_prev��_next�ĳ�weak_ptr�Ϳ�����
// ԭ����ǣ�node1->_next = node2;��node2->_prev = node1;ʱweak_ptr��_next��_prev��������node1��node2�����ü���
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
			//�ͷ���Դ
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
		++*_UseCount;   //�ٽ���  ����ͬһ��ʱ��ֻ��һ���߳������﹤��
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
			delete_flag = true;//   ��_UseCountΪ0��ʱ�� ��elete_flag��Ϊ��
		}
		_Mutex->unlock();
		if (delete_flag) // ���Ϊ��Ļ�  Ҳ��Ҫ�ͷ�-Mutex
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
		mt.lock();//   ������ �Ͳ���ȫ 
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

//shared_ptr���̰߳�ȫ����//  1. ����ָ����������ü����Ƕ������ָ�������ģ������߳�������ָ������ü���ͬʱ++��--
//�����������ԭ�ӵģ����ü���ԭ����1��++�����Σ����ܻ���2.�������ü����ʹ�����
//�ᵼ����Դδ�ͷŻ��߳������������ ����ֻ��ָ�������ü���++��--����Ҫ������
//Ҳ����˵���ü����Ĳ������̰߳�ȫ�ġ�
//  2. ����ָ�����Ķ������ڶ��ϣ������߳���ͬʱȥ���ʣ��ᵼ���̰߳�ȫ����/*
void thread_fun(Shared_Ptr<int> &sp, int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << "use_count = " << sp.use_count() << endl;
		Shared_Ptr<int> copy(sp);//  ����������Ļ� ���߳� ���п�������ͬʱ���е�����  ���Ǽ���֮��ֻһ�� ����ͷſռ�ʱ��������
		cout << "use_count = " << sp.use_count() << endl;//  �п������������� �������ü���ֻ��2  �ͷſռ�ʱ�ͷ���������  ����ǿ����̰߳�ȫ��ԭ��
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