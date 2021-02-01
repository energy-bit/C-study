#include <iostream>
#include <string>
using namespace std;
//  二叉搜索树
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
	BSTNode <Type> *Search(const Type &key)//   搜索一个数
	{
		return Search(root, key);
	}
	void Sort() // 说是排序 其实是中序遍历
	{
		Sort(root);
	}
	void Sortpair()
	{
		Sortpair(root);
	}
	void MakeEmpty()  //  将树置空
	{
		MakeEmpty(root);
	}
	Type Min()const  //   获取最小值
	{
		return Min(root);
	}
	Type Max()const  //   获取最大值  
	{
		return Max(root);
	}
protected:
	Type& Max(BSTNode <Type> *t)const //  获取最大值的实现方法
	{
		while (t->rightChild != nullptr)
			t = t->rightChild;
			return t->data;
	}
	Type& Min(BSTNode <Type> *t)const  //   获取最小值实现方法  就是在一直走到左树的尽头 就是最小值
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
		else                 // 先不考虑有相等的元素
			return false;
	}
	bool Remove(BSTNode<Type> *&t, const Type &key)
	{
		BSTNode <Type> *p = nullptr;                                             //  1  节点有左右子树
		if (t != nullptr)                             //   2  节点最多只有一个字数
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

//下面的代码好理解但还有优化的地方  放在上面
//////////////////////////////////////////////////////////////////////////////////////////////
	//bool Remove(BSTNode<Type> *&t, const Type &key)  //  删除有这几种情况
	//{                                                  //  1  节点没有左右树
	//	if (t != nullptr)                             //   2  节点有左数但无右树 
	//	{                                             //   3   节点有右树但无左树
	//		if (key < t->data)                        //   4    节点有右树也有左树
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
	//				//   说明这个节点有左树  //  那么要删除它  就让它的上一个节点指向它的左树
	//				p = t;
	//				t = p->leftChild;
	//				delete p;
	//			}
	//			else if (t->leftChild == nullptr&&t->rightChild != nullptr)
	//			{
	//				// 这个树有右树  同样要删除它就要让它上一个节点指向他的右树
	//				p = t;
	//				t = p->rightChild;
	//				delete p;
	//			}
	//			else  //  具有左右子树
	//			{
	//				// 就要让它前驱节点的值覆盖它  然后在删除它的前驱结点的值
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
	BSTNode<Type> *root;//  树根
};
void  main()
{
	   //key值 value实值   形成键值对
	pair<int, string> v1 = { 1, "abc" };//  键值对就是相当与  学号和姓名 是一对
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