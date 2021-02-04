#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <functional>
using namespace std;


void main()
{
	set <int> is = { 4, 8, 9, 0, 2, 5, 1, 7 };
	is.erase(5); //��ֵɾ��
		auto pos = is.find(7);//  ��λ��ɾ��  ���ַ���
	//is.erase(pos);
		is.erase(is.begin(), is.end());  //  ������ɾ��
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
	set<int> is;  //   �չ���
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
	//  ��������
	set<int> is_3 = is_2;
	for (auto &e : is_3)
		cout << e << " ";
	cout << endl;
}
////////////////////////////////////////////////////////////////////
void main()
{
	//  ���ܹ����ظ�����  ֻ������һ��
	set<int> is = { 4, 8, 5, 9, 0, 2, 5, 5, 5, 1, 5, 7 };
	for (auto &e : is)
		cout << e << " ";   
	cout << endl;
	//  �������ظ����� ���ҿ��԰���˳�����к�
	multiset<int> multi_is = { 4, 8, 5, 9, 0, 2, 5, 5, 5, 1, 5, 7 };
	for (auto &e : multi_is)
		cout << e << " ";
	cout << endl;
}
/////////////////////////////////////////////////////////////////////
void main()
{
	set<int,greater<int>> is = { 4, 8, 9, 0, 2, 5, 1, 7 };//   �Ӵ�С����
	//set<int> is = { 4, 8, 9, 0, 2, 5, 1, 7 };
	auto it = is.begin();
	// *it = 100;  ���ǲ����ܵ�   ��Ϊ�ײ��Ǻ����  Ҫ�ı�ֵ�û�  �Ʊػ�������Ĳ�ƽ��
	is.erase(it);  //���ǿ���ɾ��ֵ �����²���
	is.insert(100);
	//  �м�һ��Ҫ��ֹ������ʧЧ
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
	for (auto &e :is)//   set  ��������Զ�����  �ײ�ʹ�ú����ʵ��
		cout << e << " ";
	cout << endl;

}

/////////////////////////////////////////////////////////////////////////
void main()
{
// ��ֵ��
	pair<int, string> ivs = { 1, "abc" };
	cout << ivs.first << ":" << ivs.second << endl;
}
*/

