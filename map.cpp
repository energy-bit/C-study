#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>
using namespace std;
void main()
{
	//   不许有重复值
	map<int, string> is =
	{ { 1, "you" }, { 3, "he" }, { 4, "she" }, { 2, "me" },
	{ 1, "you" }, { 3, "he" }, { 4, "she" }, { 2, "me" } };
	for (auto &e : is)
		cout << e.first << ":" << e.second << endl;
	//  可以有重复值      关键值是排序的依据
	multimap<int, string> is1 =
	{ { 1, "you" }, { 3, "he" }, { 4, "she" }, { 2, "me" },
	{ 1, "you" }, { 3, "he" }, { 4, "she" }, { 2, "me" } };
	for (auto &e : is1)
		cout << e.first << ":" << e.second << endl;
}
/////////////////////////////////////////////////////////////////
/*
void main()
{
	//  初始化列表的方式 对map进行初始化             关键值   实值
	map<int, string> is = { { 1, "you" }, { 3, "he" }, { 4, "she" }, { 2, "me" } };
	for (auto &e : is)
		cout << e.first << ":" << e.second << endl;

	is[1] = "你";
	is[3] = "他";
	is[4] = "她";
	is[2] = "我";
	//  上面说明关键值 1 3 4 2 存在则修改了其中的second的值 
	//  若不存在 则插入数据
	is[5] = "它";
	for (auto &e : is)
		cout << e.first << ":" << e.second << endl;
}
////////////////////////////////////////////////////////////////

void main()
{
	//   临时列表方式
	map<int, string> is;
	is.insert(make_pair(1, "you"));
	is.insert(make_pair(3, "he"));
	is.insert(make_pair(4, "she"));
	is.insert(make_pair(2, "me"));
	for (auto &e : is)
		cout << e.first << ":" << e.second << endl;
}
/////////////////////////////////////////////////////////////////

void main()
{
	pair <int, string> v1 = { 1, "you" };
	pair <int, string> v2 = { 3, "he" };
	pair <int, string> v3 = { 4, "she" };
	pair <int, string> v4 = { 2, "me" };
	//map<int, string> is;  // 自动排序  从小到大
	map<int, string,greater<int>> is;  //从大到小
	is.insert(v1);
	is.insert(v2);
	is.insert(v3);
	is.insert(v4);
	auto it = is.begin();
	while (it != is.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
}
*/