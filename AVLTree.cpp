#include <iostream>
#include <stack>
using namespace std;
//   ������������£�����������Ϊ��ȫ����������ƽ���Ƚϴ���Ϊ��log��N��
//�������£������������˻�Ϊ��֧������ƽ���Ƚϴ���Ϊ��N/2   �������еĽ�ڶ���������������������������������
// ���⣺����˻��ɵ�֧�������������������ܾ�ʧȥ�ˡ����ܷ���иĽ������۰���ʲô�������ؼ��룬// �������Ƕ�����������������ѣ�  ����AVL��������//�����������ĸ߶Ȳ�ܳ���һ   ƽ������
template<class Type>
class AVLTree;

//�ڵ�ṹ
template<class Type>
class AVLNode
{
	friend class AVLTree<Type>;
public:
	AVLNode(Type d = Type(), AVLNode<Type>*left = nullptr, AVLNode<Type>*right = nullptr)
		: data(d), leftChild(left), rightChild(right), bf(0)
	{}
	~AVLNode()
	{}

private:
	Type data;
	AVLNode<Type> *leftChild;
	AVLNode<Type> *rightChild;
	int            bf; //ƽ������
};
template<class Type>
class AVLTree
{
public:
	AVLTree() :root(nullptr)
	{}
public:
	bool Insert(const Type &x)
	{
		return Insert(root, x);
	}
protected:
	bool Insert(AVLNode<Type> *&t, const Type &x);
	void RotateR(AVLNode<Type> *&prt);  // ����
	void RotateLR(AVLNode<Type> *&prt); // �������
	void RotateL(AVLNode<Type> *&prt);  // ����
	void RotateRL(AVLNode<Type> *&prt); // ���Һ���
private:
	AVLNode<Type> *root;
};

//ʵ�ֵ���ƽ�� 
template <class Type>
void AVLTree<Type>::RotateR(AVLNode<Type> *&ptr) // ����
{
	AVLNode<Type> *subR = ptr;
	ptr = subR->leftChild;
	subR->leftChild = ptr->rightChild;
	ptr->rightChild = subR;
	ptr->bf = subR->bf = 0;
}
template <class Type>
void AVLTree<Type>::RotateLR(AVLNode<Type> *&ptr) // �������
{
	AVLNode<Type> *subL = ptr->leftChild;
	AVLNode<Type> *subR = ptr;
	ptr = subL->rightChild;

	subL->rightChild = ptr->leftChild;  //����
	ptr->leftChild = subL;
	//  ����subLƽ������
	if (ptr->bf <= 0)
		subL->bf = 0;
	else
		subL->bf = -1;

	subR->leftChild = ptr->leftChild;//  ����
	ptr->rightChild = subR;
	// ����subR��ƽ������ 
	if (ptr->bf >= 0)
		subR->bf = 0;
	else
		subR->bf = 1;

	ptr->bf = 0;
}
template <class Type>
void AVLTree<Type>::RotateL(AVLNode<Type> *&ptr)  // ����
{
	AVLNode<Type> *subL = ptr;
	ptr = subL->rightChild;
	subL->rightChild = ptr->leftChild;
	ptr->leftChild = subL;
	ptr->bf = subL->bf = 0;

}

template <class Type>
void AVLTree<Type>::RotateRL(AVLNode<Type> *&ptr) // ���Һ���
{
	AVLNode<Type> *subL = ptr;
	AVLNode<Type> *subR = ptr->rightChild;
	ptr = subR->leftChild;

	subR->leftChild = ptr->leftChild;//  ����
	ptr->rightChild = subR;
	// ����subR��ƽ������ 
	if (ptr->bf >= 0)
		subR->bf = 0;
	else
		subR->bf = 1;
	subL->rightChild = ptr->leftChild;  //����
	ptr->leftChild = subL;
	//  ����subLƽ������
	if (ptr->bf == 1)
		subL->bf = -1;
	else
		subL->bf = 0;

	ptr->bf = 0;
}

template<class Type>
bool AVLTree<Type>::Insert(AVLNode<Type> *&t, const Type &x)
{


	// 1  ����BST�������ڵ�   �ǵݹ�
	AVLNode<Type> *pr = nullptr;//  ���ڵ�
	AVLNode<Type> *p = t;
	stack<AVLNode <Type>*> st;   //  ����ԭ������ڵ��·��  Ϊ����ƽ��������׼��

	while (p != nullptr)
	{
		//  ���ڲ���x�Ĳ���λ��
		if (x == p->data)
			return false; //  ���ų�������ͬ������

		pr = p;
		st.push(pr);//����ԭ������ڵ��·��   ��ջ

		if (x < p->data)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	p = new AVLNode<Type>(x);
	if (pr == nullptr)   //���ڵ�Ϊ�յĻ� �����½ڵ�  ֱ�� ����
	{
		t = p;
		return true;
	}
	//  �½��ڵ������
	if (x < pr->data)
		pr->leftChild = p;
	else
		pr->rightChild = p;

	//  2  ���������ƽ��  ��Ҫ����ƽ��
	while (!st.empty())
	{
		pr = st.top();
		st.pop();
		if (p == pr->leftChild)
			pr->bf--;
		else
			pr->bf++;
		if (pr->bf == 0)//   ƽ������Ϊ0  ˵����ƽ���
			break;
		if (pr->bf == 1 || pr->bf == -1)//  ˵����ƽ��  Ӧ�����ϻ���  ���ж�
			p = pr;
		else
		{
			// ƽ�����Ӵ���2��  ��ƽ���� ����
			if (p == pr->leftChild)  // ���֧  
			{
				if (p->bf < 0)  //  ��ת    / ��״
				{
					RotateR(pr);
				}
				else//  ���������ת  < ��״
				{
					RotateLR(pr);
				}
			}
			else   // �ҷ�֧
			{

				if (p->bf > 0)  // ����ת  \��״
				{
					RotateL(pr);
				}
				else //  ���Һ�����ת    >��״
				{
					RotateRL(pr);
				}
			}
			break;
		}
	}
	//  ��������
	if (st.empty())
		t = pr;
	else
	{
		AVLNode<Type> *ppr = st.top();
		if (ppr->data > pr->data)
			ppr->leftChild = pr;
		else
			ppr->rightChild = pr;

	}
	return true;
}

void main()
{
	int ar[] = { 16, 3, 1, 7, 11, 9, 26, 18, 14, 15 };
	int n = sizeof(ar) / sizeof(ar[0]);
	AVLTree<int> avl;
	for (int i = 0; i < n; i++)
	{
		avl.Insert(ar[i]);
	}
}
