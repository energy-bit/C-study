#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>
using namespace std;
void main()
{
	//   �������ظ�ֵ
	map<int, string> is =
	{ { 1, "you" }, { 3, "he" }, { 4, "she" }, { 2, "me" },
	{ 1, "you" }, { 3, "he" }, { 4, "she" }, { 2, "me" } };
	for (auto &e : is)
		cout << e.first << ":" << e.second << endl;
	//  �������ظ�ֵ      �ؼ�ֵ�����������
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
	//  ��ʼ���б�ķ�ʽ ��map���г�ʼ��             �ؼ�ֵ   ʵֵ
	map<int, string> is = { { 1, "you" }, { 3, "he" }, { 4, "she" }, { 2, "me" } };
	for (auto &e : is)
		cout << e.first << ":" << e.second << endl;

	is[1] = "��";
	is[3] = "��";
	is[4] = "��";
	is[2] = "��";
	//  ����˵���ؼ�ֵ 1 3 4 2 �������޸������е�second��ֵ 
	//  �������� ���������
	is[5] = "��";
	for (auto &e : is)
		cout << e.first << ":" << e.second << endl;
}
////////////////////////////////////////////////////////////////

void main()
{
	//   ��ʱ�б�ʽ
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
	//map<int, string> is;  // �Զ�����  ��С����
	map<int, string,greater<int>> is;  //�Ӵ�С
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