#include<iostream>
using namespace std;


typedef enum{ RED, BLACK } Color_Type;

template<class Type>
class RBTree;

template<class Type>
class rb_iterator;

template<class Type>
class RBTreeNode
{
	friend class RBTree<Type>;
	friend class rb_iterator<Type>;
public:
	RBTreeNode(Type d = Type(), RBTreeNode<Type>*left = nullptr, RBTreeNode<Type>*right = nullptr) :
		data(d), leftChild(left), rightChild(right), parent(nullptr), color(RED)
	{}
	~RBTreeNode()
	{}
private:
	Type data;
	RBTreeNode<Type> *leftChild;
	RBTreeNode<Type> *rightChild;
	RBTreeNode<Type> *parent;//  ���ڵ�ָ��
	Color_Type        color;
};
template<class Type>
class RBTree
{
public :
	RBTree() :NIL(_Buynode()), root(NIL)
	{
		NIL->leftChild = NIL->rightChild = NIL->parent = nullptr;
		NIL->color = BLACK;
		root = NIL;
	}
public:
	bool Insert(const Type &x)
	{
		return Insert(root, x);
	}
protected:
	bool Insert(RBTreeNode<Type>*&t, const Type &x);
	bool Remove(RBTreeNode<Type>*&t, const Type &key);
protected:
	void RightRotate(RBTreeNode<Type> *&t, RBTreeNode<Type> *p);// ����ת
	void LeftRotate(RBTreeNode<Type> *&t, RBTreeNode<Type> *p);//  ����ת
	void Insert_Fixup(RBTreeNode<Type> *&t, RBTreeNode<Type> *x);
protected:
	RBTreeNode<Type>* _Buynode(const Type &x = Type())
	{
		RBTreeNode<Type>*s = new RBTreeNode<Type>(x);
		s->leftChild = s->rightChild = s->parent = NIL;
		return s;
	}
private:
	RBTreeNode<Type> *root;
	RBTreeNode<Type> *NIL;
};
template<class Type>
bool RBTree<Type>::Insert(RBTreeNode<Type>*&t, const Type &x)
{
	//1 ����bst�Ĺ������ڵ�
	RBTreeNode<Type> *pr = NIL;//  ���ڵ�
	RBTreeNode<Type> *p = t;
	while (p != NIL)
	{
		if (x == p->data)
			return false;

		pr = p;

		if (x < p->data)
			p = p->leftChild;
		else
			p = p->rightChild;
	}

	RBTreeNode<Type> *s = _Buynode(x);
	//  ���ӽڵ�
	if (pr == NIL)  
	{
		t = s;     //   ���pr�ǿ���  �����½ڵ�Ϊ��
		t->parent = NIL;  //  ���ĸ��ڵ�Ϊ��
	}
	else if (x < pr->data)  // ����Ҫ����Ľڵ�С��pr
		pr->leftChild = s;  //  ��ô�������������¿��ٵĽڵ�
	else
		pr->rightChild = s;
	
	s->parent = pr;
	//  ����ƽ��
	Insert_Fixup(t, s);
	return true;
}
//�ҵ���ת
template<class Type>
void RBTree<Type>::RightRotate(RBTreeNode<Type> *&t, RBTreeNode<Type> *p)
{
	RBTreeNode<Type> *s = p->leftChild;
	p->leftChild = s->rightChild;
	if (s->rightChild != NIL)
		s->rightChild->parent = p;
	s->parent = p->parent;
	if (p->parent == NIL)
		t = s;
	else if (p == p->parent->leftChild)
		p->parent->leftChild = s;
	else
		p->parent->rightChild = s;
	s->rightChild = p;
	p->parent = s;
}
//����ת
template<class Type>
void RBTree<Type>::LeftRotate(RBTreeNode<Type> *&t, RBTreeNode<Type> *p)
{
	RBTreeNode<Type> *s = p->rightChild;
	p->rightChild = s->leftChild;
	if (s->leftChild != NIL)
		s->leftChild->parent = p;
	s->parent = p->parent;
	if (p->parent == NIL)
		t = s;
	else if (p == p->parent->leftChild)
		p->parent->leftChild = s;
	else
		p->parent->rightChild = s;
	s->leftChild = p;
	p->parent = s;
}
template<class Type>
void RBTree<Type>::Insert_Fixup(RBTreeNode<Type> *&t, RBTreeNode<Type> *x)
{
	while (x->parent->color == RED)
	{
		RBTreeNode<Type> *s;//   �岮�ڵ�
		if (x->parent == x->parent->parent->leftChild)//  ˵�����֧
		{
			s = x->parent->parent->rightChild;
			//   ״���� ��  ���岮�ڵ�Ϊ��ɫʱ
 			if (s->color == RED)
			{
				x->parent->color = BLACK;
				s->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
				continue;
			}
				//  �����  <
			if (x == x->parent->rightChild)
			{
				x = x->parent;
				LeftRotate(t, x);
			}
			//   ���һ  /
			x->parent->color = BLACK;
			x->parent->parent->color = RED;
			RightRotate(t, x->parent->parent);
		}
		else  //   �ҷ�֧
		{
			s = x->parent->parent->leftChild;
			//  ״���� ��  
			if (s->color == RED)
			{
				x->parent->color = BLACK;
				s->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
				continue;
			}
			//  ״����
			if (x==x->parent->leftChild)
			{
				x = x->parent;
				RightRotate(t, x);
			}
			x->parent->color = BLACK;
			x->parent->parent->color = RED;
			LeftRotate(t, x->parent->parent);
		}
	}
	t->color = BLACK;

}
void main()
{
	int ar[] = { 10, 7, 8, 15, 5, 6, 11, 13, 12 };
	int n = sizeof(ar) / sizeof(ar[0]);
	RBTree<int> rb;
	for (int i = 0; i < n; i++)
	{
		rb.Insert(ar[i]);
	}
}