#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <functional>
using namespace std;


void main()
{
	set <int> is = { 4, 8, 9, 0, 2, 5, 1, 7 };
	is.erase(5); //按值删除
		auto pos = is.find(7);//  按位置删除  两种方法
	//is.erase(pos);
		is.erase(is.begin(), is.end());  //  按区间删除
	auto it = is.begin();
	while (it != is.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
//////////////////////////////////////////////////////////////////
/*
void main()
{
	set<int> is;  //   空构造
	for (auto &e : is)
		cout << e << " ";
	cout << endl;

	int ar[] = { 4, 8, 9, 0, 2, 5, 1, 7 };
	int n = sizeof(ar) / sizeof(ar[0]);
	set<int> is_1(ar, ar + n);
	for (auto &e : is_1)
		cout << e << " ";
	cout << endl;

	vector <int> iv = { 4, 8, 9, 0, 2, 5, 1, 7 };
	set<int> is_2(iv.begin(), iv.end());
	for (auto &e : is_2)
		cout << e << " ";
	cout << endl;
	//  拷贝构造
	set<int> is_3 = is_2;
	for (auto &e : is_3)
		cout << e << " ";
	cout << endl;
}
////////////////////////////////////////////////////////////////////
void main()
{
	//  不能够有重复数据  只会排序一个
	set<int> is = { 4, 8, 5, 9, 0, 2, 5, 5, 5, 1, 5, 7 };
	for (auto &e : is)
		cout << e << " ";   
	cout << endl;
	//  允许有重复数据 并且可以按照顺序排列好
	multiset<int> multi_is = { 4, 8, 5, 9, 0, 2, 5, 5, 5, 1, 5, 7 };
	for (auto &e : multi_is)
		cout << e << " ";
	cout << endl;
}
/////////////////////////////////////////////////////////////////////
void main()
{
	set<int,greater<int>> is = { 4, 8, 9, 0, 2, 5, 1, 7 };//   从大到小排序
	//set<int> is = { 4, 8, 9, 0, 2, 5, 1, 7 };
	auto it = is.begin();
	// *it = 100;  这是不可能的   因为底层是红黑树  要改变值得化  势必会造成树的不平衡
	is.erase(it);  //但是可以删除值 在重新插入
	is.insert(100);
	//  切记一定要防止迭代器失效
	it = is.begin();
	while (it != is.end())
	{

		cout << *it << " ";
		it++;
	}
	cout << endl;
}

///////////////////////////////////////////////////////////////////////////////

void main()
{
	vector<int> iv = { 4, 8, 9, 0, 2, 5, 1, 7 };
	set<int> is;
	for (int e : iv)
		is.insert(e);
	for (int e : iv)
		cout << e << " ";
	cout << endl;
	for (auto &e :is)//   set  会给数据自动排序  底层使用红黑树实现
		cout << e << " ";
	cout << endl;

}

/////////////////////////////////////////////////////////////////////////
void main()
{
// 键值对
	pair<int, string> ivs = { 1, "abc" };
	cout << ivs.first << ":" << ivs.second << endl;
}
*/

