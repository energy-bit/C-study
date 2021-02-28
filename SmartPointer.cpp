#include<iostream>
#include<vld.h>
#include<string>
#include<memory>
#include <boost/smart_ptr.hpp>

using namespace std;

//  模拟实现 shared_ptr  没有考虑线程安全问题
template<class T>
class Shared_Ptr
{
public:
	Shared_Ptr(T *_P = 0) : _Ptr(_P), _UseCount((size_t*)new int(1))
	{}
	Shared_Ptr(const Shared_Ptr<T> &_Y) : _Ptr(_Y._Ptr), _UseCount(_Y._UseCount)
	{
		Increment();
	}
	Shared_Ptr<T>& operator=(const Shared_Ptr<T> &_Y)
	{
		if (this != &_Y)
		{
			//释放资源
			Decrement();//  如果自身指向空间的话  要把自身的引用计数减小  然后赋值
			_Ptr = _Y._Ptr;  
			_UseCount = _Y._UseCount;
			Increment();//  最后指向赋值的空间 计数再加1
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
	void reset(T *_P = 0)//   重新设置
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
	bool unique()const//  判断是否唯一
	{
		return (use_count() == 1);
	}
public:
	void Increment()
	{
		++*_UseCount;
	}
	void Decrement()
	{
		if (--*_UseCount == 0)//   当计数为0的时候 要释放空间
		{
			delete _Ptr;
			delete _UseCount;
		}
	}
private:
	T *_Ptr;
	size_t *_UseCount;
};

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


	Shared_Ptr<int> sp2(q);
	Shared_Ptr<int> sp3(sp2);

	sp2 = sp1;

	sp3.reset(x);
}

//
/*
void main()
{
	int *p = new int(10);
	shared_ptr<int> sp;
	cout << "use_count = " << sp.use_count() << endl;
	sp.reset(p);
	cout << "*sp = " << *sp << endl;
	cout << "use_count = " << sp.use_count() << endl;
	weak_ptr<int> wp = sp;//   不影响 引用计数的增加   相当于是个shared_ptr的助手
	cout << "use_count = " << sp.use_count() << endl;
	shared_ptr<int> sp1;
	sp1 = sp;
	cout << "use_count = " << sp.use_count() << endl;
	weak_ptr<int> wp1 = wp; //弱指针：不能 * ->  观察手做监测
	//cout<<*wp<<endl;
	cout << "wp_use_count = " << wp.use_count() << endl;

}
//

/*
void main()
{
	int *p = new int(10);
	unique_ptr<int> sp(p);
	cout << "*sp = " << *sp << endl;
	unique_ptr<int> sp1;
	sp1 = sp;   //  拥有权是不能转移的   和boost中的scoped_ptr一样  不同名而已
	//   所以unique_ptr是不支持 拷贝构造 和赋值
}
//shared_ptr的原理：是通过引用计数的方式来实现多个shared_ptr对象之间共享资源。例如：老师晚
//上在下班之前都会通知，让最后走的学生记得把门锁下。
//   1. shared_ptr在其内部，给每个资源都维护了着一份计数，用来记录该份资源被几个对象共享。
//   2. 在对象被销毁时(也就是析构函数调用)，就说明自己不使用该资源了，对象的引用计数减一。
//   3. 如果引用计数是0，就说明自己是最后一个使用该资源的对象，必须释放该资源；
//   4. 如果不是0，就说明除了自己还有其他对象在使用该份资源，不能释放该资源，否则其他对象就成野指
针了。
/*
//C++11的
void main()
{
	int *p = new int(10);
	shared_ptr<int> sp;
	cout << "use_count = " << sp.use_count() << endl;
	sp.reset(p);
	cout << "*sp = " << *sp << endl;
	cout << "use_count = " << sp.use_count() << endl;
	shared_ptr<int> sp1 = sp;
	cout << "use_count = " << sp.use_count() << endl;
	if (sp.unique())//  判断是否唯一
		cout << "is unique." << endl;
	else
		cout << "is not unique." << endl;
}
/*
//  boost库里的
#include<boost/smart_ptr.hpp>
using namespace boost;
void main()
{
	int *p = new int(10);
	boost::shared_ptr<int> sp(p);
	cout << "*sp = " << *sp << endl;
	cout << "use_count = " << sp.use_count() << endl;
	boost::shared_ptr<int> sp1 = sp;
	cout << "use_count = " << sp.use_count() << endl;
	{
		boost::shared_ptr<int> spx = sp;
		cout << "use_count = " << sp.use_count() << endl;
	}
	cout << "use_count = " << sp.use_count() << endl;//   出来之后就会被析构 所以引用计数会减一个1
	boost::shared_ptr<int> sp2;
	sp2 = sp1;
	cout << "use_count = " << sp.use_count() << endl;
}

/*
namespace bit
{
	template<class T>
	class scoped_ptr
	{
		typedef scoped_ptr<T> this_type;
	public:
		explicit scoped_ptr(T * p = 0) : px(p)
		{}
		~scoped_ptr() // never throws
		{
			delete px;
		}
	public:
		void reset(T * p = 0) // never throws
		{
			this_type(p).swap(*this);  //this_type(p)  弄了个临时对象
		}
		void swap(scoped_ptr & b) // never throws
		{
			T * tmp = b.px;  //  运用临时空间 省掉delete 因为是临时对象所以在结束的时候会调用析构方法 再去释放
			b.px = px;       //  所以不会内存泄露
			px = tmp;
		}
	public:
		T & operator*() const
		{
			return *px;
		}
		T * operator->() const
		{
			return px;
		}
		T * get() const
		{
			return px;
		}
	private:
		scoped_ptr(scoped_ptr const &);
		scoped_ptr & operator=(scoped_ptr const &);
		void operator==(scoped_ptr const&) const;
		void operator!=(scoped_ptr const&) const;
	private:
		T * px;
	};
	template<class T>
	class scoped_array
	{
		typedef scoped_array<T> this_type;
	public:
		explicit scoped_array(T * p = 0) : px(p)
		{}
		~scoped_array() // never throws
		{
			delete[]px;
		}
	public:
		T & operator[](size_t i) const
		{
			return px[i];
		}
	private:
		T * px;
		scoped_array(scoped_array const &);
		scoped_array & operator=(scoped_array const &);
		void operator==(scoped_array const&) const;
		void operator!=(scoped_array const&) const;
	};
};
void main()
{
	int *p = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	bit::scoped_array<int> sp(p);
	for (int i = 0; i < 10; ++i)
		cout << sp[i] << " ";
	cout << endl;
}



/*
void main()
{
	int *p = new int(10);
	int *q = new int(20);
	bit::scoped_ptr<int> sp(p);  //不允许拥有权发生转移
	cout << "*sp = " << *sp << endl;
	sp.reset(q);// 重新设置
	cout << "*sp = " << *sp << endl;
}

/*
void main()
{
	int *p = new int(10);
	bit::scoped_ptr<int> sp(p);  //不允许拥有权发生转移
	cout << "*sp = " << *sp << endl;
	bit::scoped_ptr<string> sp1(new string("HelloBoost"));
	cout << sp1->size() << endl;
	//bit::scoped_ptr<int> sp2 = sp;
	//sp2 = sp;
}

/*
namespace bit
{
	template<class _Ty>
	class auto_ptr
	{
		typedef auto_ptr<_Ty> _Myt;
	public:
		explicit auto_ptr(_Ty *_Ptr = 0) : _Myptr(_Ptr)
		{}
		auto_ptr(_Myt& _Right) : _Myptr(_Right.release())
		{}
		_Myt& operator=(_Myt& _Right)
		{
			if (this != &_Right)
				reset(_Right.release());
			return (*this);
		}
		~auto_ptr()
		{
			delete _Myptr;
		}
	public:
		_Ty& operator*() const
		{
			return (*get());
		}
		_Ty *operator->() const
		{
			return (get());
		}
		_Ty *get() const
		{
			return (_Myptr);
		}
	public:
		_Ty *release()
		{
			_Ty *_Tmp = _Myptr;
			_Myptr = 0;
			return (_Tmp);
		}
		void reset(_Ty *_Ptr = 0)
		{
			if (_Ptr != _Myptr)// 判断是否是同一个空间
				delete _Myptr;
			_Myptr = _Ptr;
		}
	private:
		_Ty *_Myptr;
	};
};
void main()
{
	int *p = new int[10];//  不能够是数组空间
	bit::auto_ptr<int> ap(p);
}

/*
void main()
{
	int *p = new int(10);
	int *q = new int(100);
	bit::auto_ptr<int> ap(p);  //RAII
	cout << "*ap = " << *ap << endl;
	ap.reset(q);
	bit::auto_ptr<int> ap1;
	ap1 = ap;
}

/*
void main()
{
	int *p = new int(10);
	bit::auto_ptr<int> ap(p);  //RAII
	cout << "*ap = " << *ap << endl;
	bit::auto_ptr<string> ap1(new string("abc"));
	cout << ap1->size() << endl;
	bit::auto_ptr<int> ap2 = ap;
}
////VC 6.0
/*
namespace bit
{
	template<class _Ty>
	class auto_ptr
	{
	public:
		auto_ptr(_Ty *_P = 0) : _Owns(_P != 0), _Ptr(_P)
		{}
		auto_ptr(const auto_ptr<_Ty> &_Y) :_Owns(_Y._Owns), _Ptr(_Y.release())
		{}
		auto_ptr<_Ty>& operator=(const auto_ptr<_Ty> &_Y)
		{
			if (this != &_Y)
			{
				if (_Ptr != _Y._Ptr)
				{
					if (_Owns)
						delete _Ptr;
					_Owns = _Y._Owns;
				}
				else if (_Y._Owns)
					_Owns = true;
				_Ptr = _Y.release();
			}
			return *this;
		}
		~auto_ptr()
		{
			if (_Owns)
				delete _Ptr;
		}
	public:
		_Ty& operator*()const
		{
			return *get();
		}
		_Ty* operator->()const
		{
			return get();
		}
		_Ty* get()const
		{
			return _Ptr;
		}
	public:
		//const auto_ptr<_Ty> * const this
		_Ty* release()const
		{
			((auto_ptr<_Ty> * const)this)->_Owns = false;
			_Ty *_Tmp = _Ptr;
			((auto_ptr<_Ty> * const)this)->_Ptr = nullptr;
			return _Tmp;
		}
	private:
		bool _Owns;
		_Ty *_Ptr;
	};
};
void main()
{
	int *p = new int(10);
	bit::auto_ptr<int> ap(p);  //RAII
	cout << "*ap = " << *ap << endl;
	//ap.release();
	int *q = new int(20);
	bit::auto_ptr<int> ap1(q);
	ap1 = ap;
}
/*
void main()
{
	int *p = new int(10);
	bit::auto_ptr<int> ap(p);  //RAII
	cout << "*ap = " << *ap << endl;
	bit::auto_ptr<int> ap1 = ap; //拥有权的转移问题 -->
	cout << "*ap1 = " << *ap1 << endl;
	//cout<<"*ap = "<<*ap<<endl;   //不想让其能够访问
	int *q = new int(20);
	bit::auto_ptr<int> ap2(q);
	ap2 = ap1;  //赋值
	cout << "*ap2 = " << *ap2 << endl;
}
/*
void main()
{
	int *p = new int(10);
	bit::auto_ptr<int> ap(p);  //RAII  
	cout << "*p = " << *p << endl;
	cout << "*ap = " << *ap << endl;//  不能访问   必须重载*号
	bit::auto_ptr<string> ap1(new string("Hello"));
	cout << ap1->size() << endl;
}
*/