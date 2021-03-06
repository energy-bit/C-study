#include<iostream>
#include<list>
#include<vector>
#include<set>
#include<deque>
#include<algorithm>
#include<numeric>
#include<functional>
using namespace std;
//find算法在查找时 与具体的数据结构无关 只要给出待查找数据集合的范围 find就可在该范围中查找，找
//到返回该元素在区间中的位置，否则返回end
void  main()
{
	vector<int> v1{ 4, 1, 8, 0, 5, 9, 3, 7, 2, 6 };
	list<int>   v2{ 4, 1, 8, 0, 5, 9, 3, 7, 2, 6 };
	deque<int>  v3{ 4, 1, 8, 0, 5, 9, 3, 7, 2, 6 };
	set<int>    v4{ 4, 1, 8, 0, 5, 9, 3, 7, 2, 6 };

	auto it1 = find(v1.begin(), v1.end(), 9);
	auto it2 = find(v2.begin(), v2.end(), 9);
	auto it3 = find(v3.begin(), v3.end(), 9);
	auto it4 = find(v4.begin(), v4.end(), 9);
}

/////////////////////////////////////////////////////////////////////////
/*
void  main()
{
	vector<int> v = { 1, 2, 3 };//  必须是排序的 升序才能用 next...
	sort(v.begin(), v.end());
	do
	{
		cout << v[0] << " " << v[1] << " " << v[2] << endl;
	} while (next_permutation(v.begin(), v.end()));//  后一个序列
	cout << "======================================" << endl;

	sort(v.begin(), v.end(), greater<int>()); //3 2 1  必须是降序的  才能用prev...
	do
	{
		cout << v[0] << " " << v[1] << " " << v[2] << endl;
	} while (prev_permutation(v.begin(), v.end()));//  前一个序列
}
////////////////////////////////////////////////////////////////////////
/*
//unique
//1. 该函数并不是将重复性的元素删除掉 而是用后面不重复的元素将前面重复的元素覆盖掉了
//2. 返回值是一个迭代器  指向的是去重后容器中不重复最后一个元素的下一个位置
//3. 该函数需要配合erase才能真正的将元素删除掉
void  main()
{
	vector<int> v{ 4, 1, 8, 0, 5, 5, 5, 9, 3, 5, 7, 5, 5, 2, 6 };  //sort
	for (auto &e : v)
		cout << e << " ";
	cout << endl;
	sort(v.begin(), v.end()); //交换 选择 插入 快排
	for (auto &e : v)
		cout << e << " ";
	cout << endl;
	auto it = unique(v.begin(), v.end());//本不去重 返回一个迭代器指向不重复最后一个位置 配合erase 删除
	v.erase(it, v.end());
	for (auto &e : v)
		cout << e << " ";
	cout << endl;
}
//////////////////////////////////////////////////////////////////////////////////
/*
//map  set --> key// 不可以转置  因为不可修改其关键值 但是序列式容器（list）就可以
void main()
{
	list<int> v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (auto &e : v)
		cout << e << " ";
	cout << endl;
	reverse(v.begin(), v.end());
	for (auto &e : v)
		cout << e << " ";
	cout << endl;
}
/*
//reverse该算法的作用是对区间中的元素进行逆置
void main()
{
	vector<int> v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (auto &e : v)
		cout << e << " ";
	cout << endl;
	reverse(v.begin(), v.end());
	for (auto &e : v)
		cout << e << " ";
	cout << endl;
}
/////////////////////////////////////////////////////////////////////////////
/*
//partition
//该算法的作用是按照条件对区间中的元素进行划分 使用时必须包含头文件
bool isOdd(int x)
{
	return (x % 2 == 1); //0   1
}
void main()
{
	vector<int> v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto pos = partition(v.begin(), v.end(), isOdd);// 划分之后但是不排序
	for (auto it = v.begin(); it != pos; ++it) 
		cout << *it << " ";
	cout << endl;
	for (auto it = pos; it != v.end(); ++it)
		cout << *it << " ";
	cout << endl;
}
///////////////////////////////////////////////////////////////////////
/*
//partial_sort 部分排序  比如找前几小数 前几大数
void  main()
{
	vector<int> v1{ 4, 1, 8, 0, 5, 9, 3, 7, 2, 6 };
	//             first         mid         last
	partial_sort(v1.begin(), v1.begin() + 3, v1.end(), greater<int>());//从大到小排序前三个数  所以排完为 9  8  7
	for (int i = 0; i < 3; ++i)
		cout << v1[i] << " ";
	cout << endl;
}

///////////////////////////////////////////////////////////////////////////
/*
//merge
//该算法作用将两个有序序列合并成一个有序序列, 使用时必须包含头文件
//  如数据无序 先可以将数据排序在合并
void main()
{
	list<int> v1 = { 1, 9, 5, 7, 3 };// 哪怕类型不同也可以合
	vector<int> v2 = { 2, 8, 10, 4, 6 };
	//vector<int> v(v1.size() + v2.size());
	//merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());
	v1.sort();
	sort(v2.begin(), v2.end());
	int ar[10] = { 0 };
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), ar);
	for (auto &e : ar)
		cout << e << " ";
	cout << endl;
}
/*
void main()
{
	vector<int> v1 = { 1, 9, 5, 7, 3 };
	vector<int> v2 = { 2, 8, 10, 4, 6 };
	//vector<int> v(v1.size() + v2.size());
	//merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	int ar[10] = { 0 };
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), ar);
	for (auto &e : ar)
		cout << e << " ";
	cout << endl;
}

/*
void main()
{
	vector<int> v1 = { 1, 3, 5, 7, 9 };  并
	vector<int> v2 = { 2, 4, 6, 8, 10 };
	//vector<int> v(v1.size() + v2.size());  合并肯定要将大小也要够用 所以将两个空间大小和起来
	//merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());
	int ar[10] = { 0 };
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), ar);
	for (auto &e : ar)
		cout << e << " ";
	cout << endl;
}
////////////////////////////////////////////////////////////////////////
/*
void main()
{
	cout << max(10, 20) << endl;
	cout << min(10, 20) << endl;
}
////////////////////////////////////////////////////////////////////
/*
bool Greater3(int x)
{
	return x > 3;
}
void main()
{
	vector<int> v2{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 13 };
	auto rit = find(v2.begin(), v2.end(), 9);
	if (rit != v2.end())
		cout << "rit = " << *rit << endl;
	else
		cout << "没有这个数据." << endl;
	rit = find_if(v2.begin(), v2.end(), Greater3);//  大于三的第一个数是4
	if (rit != v2.end())
		cout << "rit = " << *rit << endl;
	else
		cout << "没有这个数据." << endl;
}
////////////////////////////////////////////////////////////////////////////
/*
//奇数的个数
bool isOdd(int x)
{
	return (x % 2 == 1); //0   1
}
bool Greater3(int x)//  统计大于三的个数
{
	return x > 3;
}
struct less5
{
	bool operator()(int x)
	{
		return x < 5;
	}
};
void main()
{
	vector<int> v1{ 10, 20, 30, 30, 20, 10, 10, 20, 10, 10 };
	cout << "10 count = " << count(v1.begin(), v1.end(), 10) << endl;// count 找出一个数 （10）出现的次数
	vector<int> v2{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 13 };
	cout << "odd count = " << count_if(v2.begin(), v2.end(), isOdd) << endl;//  统计奇数
	cout << ">3 count = " << count_if(v2.begin(), v2.end(), Greater3) << endl;
	cout << "<5 count = " << count_if(v2.begin(), v2.end(), less5()) << endl;
}
///////////////////////////////////////////////////////////////////////////
/*
int Mul2(int x, int y)
{
	return x + 2 * y;
}
void main()
{
	vector<int> iv{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int sum1 = accumulate(iv.begin(), iv.end(), 0);
	cout << "sum1 = " << sum1 << endl;
	int sum2 = accumulate(iv.begin(), iv.end(), 0, Mul2);
	cout << "sum2 = " << sum2 << endl;
}

/*
struct Mul2 
{
	int operator()(int x, int y)
	{
		return x + 2 * y;
	}
};
void main()
{
	vector<int> iv{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int sum1 = accumulate(iv.begin(), iv.end(), 0);
	cout << "sum1 = " << sum1 << endl;
	int sum2 = accumulate(iv.begin(), iv.end(), 0, Mul2());//相当整体求和的二倍
	cout << "sum2 = " << sum2 << endl;
}
/*
void main()
{
	vector<int> iv{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int sum = 0;
	for (auto &e : iv)
		sum += e;
	cout << "sum = " << sum << endl;
	auto pos = find(iv.begin(), iv.end(), 6);
	int sum1 = accumulate(iv.begin(), pos, 100);//accumulate 累加算法 100就是初始值 代表从100开始加起  
	cout << "sum1 = " << sum1 << endl;
}
/////////////////////////////////////////////////////////////////////////////
/*
//STL讲究的通用性 所以就是必须什么类型都可以  比如下面的
class Test
{};
void main()
{
	list<int> mylist;
	list<double> youlist;
	list<Test> hilist;
}
*/