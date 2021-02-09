#include<iostream>
#include<vector>
#include <string>
using namespace std;
//        �ձ��  ���ڱ��  ɾ�����
enum State{ EMPTY, EXIST, DELETE };
template<class Type>
class HashTable
{
	struct Elem
	{
		//pair<K, V> _val;  //ֵ
		Type  _val;
		State _state;     //״̬
	};
public:
	HashTable(size_t capacity = 3) : _ht(capacity), _size(0)
	{
		for (size_t i = 0; i < capacity; ++i)
			_ht[i]._state = EMPTY;//   �Ƚ�״̬������ձ��
	}
	bool Insert(const Type& val)
	{
		// ����ϣ��ײ�ռ��Ƿ����
		_CheckCapacity();
		size_t hashAddr = HashFunc(val);
		size_t old_hashAddr = hashAddr;
		while (_ht[hashAddr]._state == EXIST) //������ͻ
		{
			if (_ht[hashAddr]._state == EXIST && _ht[hashAddr]._val == val)//  ���ܲ����ظ�ֵ
				return false;
			hashAddr = (hashAddr + 1) % (_ht.capacity());
			if (hashAddr == old_hashAddr)//   ��˼����һȦ  ����к�ԭ���ĵ�ַ�����  ˵���ռ�����
				//hashAddr = 0;
				return false;
		}
		// ����Ԫ��
		_ht[hashAddr]._state = EXIST;
		_ht[hashAddr]._val = val;
		_size++;
		return true;
	}
	int Find(const Type& key)
	{
		size_t hashAddr = HashFunc(key);
		while (_ht[hashAddr]._state != EMPTY)
		{
			if (_ht[hashAddr]._state == EXIST && _ht[hashAddr]._val == key)
				return hashAddr;
			hashAddr = (hashAddr + 1) % (_ht.capacity());
		}
		return -1;
	}
	bool Erase(const Type& key)
	{
		int index = Find(key);
		if (-1 != index)
		{
			_ht[index]._state = DELETE;
			_size--;
			return true;
		}
		return false;
	}
	size_t Size()const
	{
		return _size;
	}
	bool Empty() const
	{
		return _size() == 0;
	}
	void Swap(HashTable<Type>& ht)
	{
		std::swap(_ht, ht._ht);
	}
private:
	size_t HashFunc(const Type& key)
	{
		//return key() % _ht.capacity();   //����������
		return key % _ht.capacity();   //����������
	}
protected:
	void _CheckCapacity()
	{
		if (_size * 10 / _ht.capacity() >= 7) //ת��Ϊ����   //װ������0.7
		{
			HashTable<Type> newHt(GetNextPrime(_ht.capacity()));//  ��ȡ��һ������ ��ȡ�ռ�
			//��Ҫ���µ�������
			for (size_t i = 0; i < _ht.capacity(); ++i)
			{
				if (_ht[i]._state == EXIST)
					newHt.Insert(_ht[i]._val);
			}
			Swap(newHt);
		}
	}
private:
	vector<Elem> _ht;  //  �����ŵ��Ƕ���õĽṹ��
	size_t       _size;
};
/////////////////////////////////////////////////////////////////////
size_t BKDRHash(const char *str)
{
	register size_t hash = 0;
	while (size_t ch = (size_t)*str++)//  �ַ�����ϣ�÷� Ч�ʽϸ�
	{
		hash = hash * 131 + ch;
	}
	return hash;
}
size_t SDBMHash(const char *str)//  �ַ�����ϣ�÷�
{
	register size_t hash = 0;
	while (size_t ch = (size_t)*str++)
	{
		hash = 65599 * hash + ch;
		//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
	}
	return hash;
}
void main()
{
	string str0 = "www.baidu_com";
	string str1 = "www.baidu.com";
	char  *str2 = "www.taobao.com";
	size_t index0 = BKDRHash(str0.c_str());
	size_t index1 = SDBMHash(str0.c_str());
}
/*
class Student
{
public:
	bool operator==(const Student &s)
	{
		return (id == s.id && name == s.name);
	}
	const int operator()()const
	{
		return id;
	}
public:
	int id;
	string name;
};
void main()
{
	vector<int> iv = { 1, 8, 15, 22, 29, 36, 43, 50 };
	HashTable<int> ht(3);
	for (auto &e : iv)
		ht.Insert(e);
	ht.Erase(29);
	ht.Insert(50);
}
/*
void main()
{
	Student stu[] = { { 1, "abc" }, { 8, "xyz" } };
	HashTable<Student> ht(7);
	ht.Insert(stu[0]);
	ht.Insert(stu[1]);
}
/*
void main()
{
	vector<int> iv = { 1, 8, 15, 22, 29, 36, 43, 50 };
	HashTable<int> ht(3);
	for (auto &e : iv)
		ht.Insert(e);
	ht.Erase(29);
	ht.Insert(50);
}
*/