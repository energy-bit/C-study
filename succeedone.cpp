#include <iostream>
#include <string>
using namespace std;

//  ���μ̳� ���μ̳��Ƕ�̳е�һ�����������
//���μ̳е����⣺������Ķ����Աģ�͹��죬���Կ������μ̳�����������Ͷ����Ե����⡣��Assistant
//�Ķ�����Person��Ա�������ݡ�/*
class A
{
public :
	int m_a = 1;
};
class B:public A
{
public:
	int m_b = 2;
};
class C :public A
{
public:
	int m_c = 3;
};
class D :public B,public C
{
public:
	int m_d = 4;
}; 
void main()
{
	D d;
	d.m_d = 40;
	d.m_c = 30;
	d.m_b = 20;
	//d.m_a = 10;//  ������
	// ���ܹ�����  ��ΪB ��C�ֱ�̳���A��m_a  
	//����D �̳���B��C��m_a ����D���ܹ��ֱ�m_a������˭��
	d.B::m_a = 100;
	d.C::m_a = 200;
	// �����Ļ� �������m_a �������ռ�  һ��B��100  һ��C��200

	//��Ҫ�̳�A��m_a ��ĩ��  ����
}

//////////////////////////////////////////////////////////////////////////////////
class A
{
public:
	int m_a = 1;
};
class B :virtual public A
{
public:
	int m_b = 2;
};
class C :virtual public A
{
public:
	int m_c = 3;
};
class D :public B, public C
{
public:
	int m_d = 4;
};
void main()
{
	D d;
	d.m_d = 40;
	d.m_c = 30;
	d.m_b = 20;
	d.m_a = 100;//  ��B C����̳� A virtual 
}
*/