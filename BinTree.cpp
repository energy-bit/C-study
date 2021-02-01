#include <iostream>
#include <string>
using namespace std;
//  ����������
template <class Type>
class BST;
template <class Type>
class BSTNode
{
	friend class BST<Type>;
public :
	BSTNode(Type d = Type(), BSTNode<Type> *left = nullptr, BSTNode<Type> *right = nullptr)
		:data(d), leftChild(left), rightChild(right)
	{

	}
	~BSTNode()
	{

	}

private:
	Type data;
	BSTNode  <Type> *leftChild;
	BSTNode  <Type> *rightChild;
};
template <class Type>
class BST
{
public:
	BST() :root(nullptr)
	{

	}
	BST(Type ar[], int n) :root(nullptr)
	{
		for (int i = 0; i < n; i++)
		{
			Insert(ar[i]);
		}
	}
	~BST()
	{
		MakeEmpty(root);
		root = nullptr;
	}
public:
	bool Insert(const Type &x)
	{
		return Insert(root, x);
	}
	bool Remove(const Type &key)
	{
		return Remove(root, key);
	}
	BSTNode <Type> *Search(const Type &key)//   ����һ����
	{
		return Search(root, key);
	}
	void Sort() // ˵������ ��ʵ���������
	{
		Sort(root);
	}
	void Sortpair()
	{
		Sortpair(root);
	}
	void MakeEmpty()  //  �����ÿ�
	{
		MakeEmpty(root);
	}
	Type Min()const  //   ��ȡ��Сֵ
	{
		return Min(root);
	}
	Type Max()const  //   ��ȡ���ֵ  
	{
		return Max(root);
	}
protected:
	Type& Max(BSTNode <Type> *t)const //  ��ȡ���ֵ��ʵ�ַ���
	{
		while (t->rightChild != nullptr)
			t = t->rightChild;
			return t->data;
	}
	Type& Min(BSTNode <Type> *t)const  //   ��ȡ��Сֵʵ�ַ���  ������һֱ�ߵ������ľ�ͷ ������Сֵ
	{
		while (t->leftChild != nullptr)
			t = t->leftChild;
		return t->data;
	}
	bool Insert(BSTNode <Type> *&t, const Type &x)
	{
		if (t == nullptr)
		{
			t = new BSTNode<Type>(x);
		}
		else if (x<t->data)
		{
			Insert(t->leftChild, x);
		}
		else if (x>t->data)
		{
			Insert(t->rightChild, x);
		}
		else                 // �Ȳ���������ȵ�Ԫ��
			return false;
	}
	bool Remove(BSTNode<Type> *&t, const Type &key)
	{
		BSTNode <Type> *p = nullptr;                                             //  1  �ڵ�����������
		if (t != nullptr)                             //   2  �ڵ����ֻ��һ������
		{
			if (key < t->data)
				Remove(t->leftChild, key);
			else if (key>t->data)
				Remove(t->rightChild, key);
			else if (t->leftChild != nullptr&&t->rightChild != nullptr)
			{
				p = t->leftChild;
				while (p->rightChild != nullptr)
					p = p->rightChild;
				t->data = p->data;
				Remove(t->leftChild, p->data);
			}
			else
			{
				p = t;
				if (t->leftChild != nullptr)
					t = p->leftChild;
				else
					t = p->rightChild;
				delete p;
				return true;
			}
		}
		return false;
	}

//����Ĵ������⵫�����Ż��ĵط�  ��������
//////////////////////////////////////////////////////////////////////////////////////////////
	//bool Remove(BSTNode<Type> *&t, const Type &key)  //  ɾ�����⼸�����
	//{                                                  //  1  �ڵ�û��������
	//	if (t != nullptr)                             //   2  �ڵ��������������� 
	//	{                                             //   3   �ڵ���������������
	//		if (key < t->data)                        //   4    �ڵ�������Ҳ������
	//			Remove(t->leftChild, key);
	//		if (key>t->data)
	//			Remove(t->rightChild, key);
	//		else
	//		{
	//			BSTNode <Type> *p = nullptr;
	//			if (t->leftChild == nullptr&&t->rightChild == nullptr)
	//			{
	//				delete t;
	//				t = nullptr;
	//			}
	//			else if (t->leftChild != nullptr&&t->rightChild == nullptr)
	//			{
	//				//   ˵������ڵ�������  //  ��ôҪɾ����  ����������һ���ڵ�ָ����������
	//				p = t;
	//				t = p->leftChild;
	//				delete p;
	//			}
	//			else if (t->leftChild == nullptr&&t->rightChild != nullptr)
	//			{
	//				// �����������  ͬ��Ҫɾ������Ҫ������һ���ڵ�ָ����������
	//				p = t;
	//				t = p->rightChild;
	//				delete p;
	//			}
	//			else  //  ������������
	//			{
	//				// ��Ҫ����ǰ���ڵ��ֵ������  Ȼ����ɾ������ǰ������ֵ
	//				p = t->leftChild;
	//				while (p->rightChild != nullptr)
	//					p = p->rightChild;
	//				t->data = p->data;
	//				Remove(t->leftChild, p->data);

	//			}
	//			return true;
	//		}
	//	}
	//	return false;
	//}
	BSTNode <Type> *Search(BSTNode <Type> *t, const Type &key)
	{
		if (t == nullptr)
			return nullptr;
		if (t->data == key)
			return t;
		else if (key < t->data)
			return Search(t->leftChild, key);
		else
			return Search(t->rightChild, key);
	}
	void Sort(BSTNode<Type> *t)
	{
		if (t!=nullptr)
		{
			Sort(t->leftChild);
			cout << t->data<<" ";
			Sort(t->rightChild);

		}
	}
	void Sortpair(BSTNode<Type> *t)
	{
		if (t != nullptr)
		{
			Sortpair(t->leftChild);
			cout << (t->data).first << ":" << (t->data).second << endl;
			Sortpair(t->rightChild);
		}
	}
	void MakeEmpty(BSTNode <Type> *&t)
	{
		if (t != nullptr)
		{
			MakeEmpty(t->leftChild);
			MakeEmpty(t->rightChild);
			delete t;
		}	
	}
private:
	BSTNode<Type> *root;//  ����
};
void  main()
{
	   //keyֵ valueʵֵ   �γɼ�ֵ��
	pair<int, string> v1 = { 1, "abc" };//  ��ֵ�Ծ����൱��  ѧ�ź����� ��һ��
	pair<int, string> v2 = { 2, "xyz" };
	pair<int, string> v3 = { 3, "hjk" };
	BST<pair<int, string>>bst;
	bst.Insert(v1);
	bst.Insert(v2);
	bst.Insert(v3);
	bst.Sortpair();
}
////////////////////////////////////////////////////////////////////////////
/*
int main()
{
	int ar[] = { 53, 78, 65, 17, 87, 9, 81, 45, 23 };
	int n = sizeof(ar) / sizeof(ar[0]);
	BST<int> bst(ar,n);
	bst.Sort();
	cout << endl;
	cout << "Min=" << bst.Min() << endl;
	cout << "Max=" << bst.Max() << endl;
	int key = 45;
	BSTNode<int> *p = bst.Search(key);
	 key = 53;
	bst.Remove(key);
	bst.Sort();
	return 0;
}
///////////////////////////////////////////////////////////////////////////

void main()
{
	int ar[] = { 53, 78, 65, 17, 87, 9, 81, 45, 23 };
	int n = sizeof(ar) / sizeof(ar[0]);
	BST<int> bst;
	for (int i = 0; i < n; i++)
	{
		bst.Insert(ar[i]);
	}
	bst.Sort();
}
*/