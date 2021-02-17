#include <iostream>
#include <vector>
using namespace std;
template<size_t _N>

class BitSet
{
	friend ostream& operator<<(ostream &out, const BitSet<10> &bt);
public:
	BitSet() : _bit((_N - 1) / 32 + 1), _bitCount(_N)
	{}
	~BitSet()
	{}
public:
	void Set(size_t pos)//  设置位
	{
		if (pos >= _bitCount)
			return;
		int index = pos / 32;//找出下标
		int offset = pos % 32;//找出位
		_bit[index] |= (1 << offset);//  替换为一
	}
	void ReSet(size_t pos)//  重新置零
	{
		if (pos >= _bitCount)
			return;
		int index = pos / 32;
		int offset = pos % 32;
		_bit[index] &= (~(1 << offset));
	}
	bool Test(size_t pos)const
	{
		if (pos >= _bitCount)
			return false;
		int index = pos / 32;
		int offset = pos % 32;
		return _bit[index] & (1 << offset);
	}
	size_t Count()const
	{
		//0000 0000   只求8个位的1的个数  
		int bitCnttable[256] = {
			0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2,
			3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3,
			3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3,
			4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4,
			3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5,
			6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4,
			4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
			6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5,
			3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3,
			4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6,
			6, 7, 6, 7, 7, 8 };
		size_t sum = 0;
		//00 0000 0000
		int int_count = _bit.size();
		for (size_t i = 0; i < int_count; ++i)
		{
			int value = _bit[i];
			for (int j = 0; j < 4; ++j)
			{
				unsigned char ch = value & 0xff; //0 ~ 255   char -128 ~ 127
				sum = bitCnttable[ch];
				value >= 8;
			}
		}
		return sum;
	}
	size_t size()const
	{
		return _bitCount;
	}
private:
	vector<int> _bit;
	size_t      _bitCount;
};
ostream& operator<<(ostream &out, const BitSet<10> &bt)
{
	for (size_t i = 0; i < bt._bitCount; ++i)
	{
		if (bt.Test(i))
			out << 1;
		else
			out << 0;
	}
	return out;
}
////////////////////////////////////////////////////////////////////////////////////////
struct StrToInt1
{
	size_t operator()(const string &s)
	{
		return BKDRHash(s.c_str());
	}
	size_t BKDRHash(const char *str)//哈希函数转化字符串函数
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
};
struct StrToInt2
{
	size_t operator()(const string &s)
	{
		return SDBMHash(s.c_str());
	}
	size_t SDBMHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
		}
		return hash;
	}
};
struct StrToInt3
{
	size_t operator()(const string &s)
	{
		return RSHash(s.c_str());
	}
	size_t RSHash(const char *str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
};
///////////////////////////////////////////////////////////////////////
#define  _N 1000
template<class K, class HashFunc1 = StrToInt1,
class HashFunc2 = StrToInt2,
class HashFunc3 = StrToInt3>
class BloomFilter
{
public:
	BloomFilter() : _size(0)
	{}
public:
	void Insert(const string &key)//  插入数据
	{
		size_t capacity = _bmp.size();
		size_t index1 = HashFunc1()(key) % capacity;
		_bmp.Set(index1);
		size_t index2 = HashFunc2()(key) % capacity;
		_bmp.Set(index2);
		size_t index3 = HashFunc3()(key) % capacity;
		_bmp.Set(index3);
		_size++;
	}
	bool Test(const string &key)//  查询是否存在
	{
		size_t capacity = _bmp.size();
		size_t index1 = HashFunc1()(key) % capacity;
		if (!_bmp.Test(index1))//  若为0  则一定不存在  下面同理  只要有一位为0 都不存在
			return false;
		size_t index2 = HashFunc2()(key) % capacity;
		if (!_bmp.Test(index2))
			return false;
		size_t index3 = HashFunc3()(key) % capacity;
		if (!_bmp.Test(index3))
			return false;
		return true; //可能存在  切记是可能存在  因为如果之前有的数据保存过  下标也为1  
	}
private:
	BitSet<_N * 5> _bmp;
	size_t       _size;
};
void main()
{
	string str = "www.baidu.com";
	string str1 = "www.baidu.com.";
	string str2 = "https://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html";
	BloomFilter<string> bf;
	bf.Insert(str);
	cout << bf.Test(str1) << endl;
	bf.Insert(str2);
	cout << bf.Test(str2) << endl;
}
/*
void main()
{
	BitSet<10> bt;
	cout << bt << endl;
	bt.Set(3);
	bt.Set(7);
	bt.Set(2);
	cout << bt << endl;
	//bt.ReSet(3);
	//cout<<bt<<endl;
	cout << bt.Count() << endl;
}


//   微软一个求二进制的1的个数面试题  要求不考虑空间 只要求效率
/*
size_t Count(unsigned char val)
{
	int count = 0;
	while (val)
	{
		count++;
		val &= (val - 1);
	}
	return count;
}
void main()
{
	unsigned char value = 123;  //0 ~ 255
	cout << Count(value) << endl;
}
size_t Count(unsigned char val)
{
	int count = 0;
	while (val)
	{
		count += (val & 0x01);
		val >>= 1;
	}
	return count;
}
void main()
{
	unsigned char value = 123;  //0 ~ 255
	cout << Count(value) << endl;
}
/*
size_t Count(unsigned char val)
{
	int count = 0;
	while (val)
	{
		if (val % 2 == 1)
			count++;
		val /= 2;
	}
	return count;
}
void main()
{
	unsigned char value = 255;  //0 ~ 255
	cout << Count(value) << endl;
}
*/