#include <iostream>
#include <stack>
using namespace std;
//   二叉最优情况下，二叉搜索树为完全二叉树，其平均比较次数为：log（N）
//最差情况下，二叉搜索树退化为单支树，其平均比较次数为：N/2   就是所有的结节都在左子树的左子树或右子树的右子树
// 问题：如果退化成单支树，二叉搜索树的性能就失去了。那能否进行改进，不论按照什么次序插入关键码，// 都可以是二叉搜索树的性能最佳？  所以AVL树就来了//右树和左树的高度差不能超过一   平衡因子
template<class Type>
class AVLTree;

//节点结构
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
	int            bf; //平衡因子
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
	void RotateR(AVLNode<Type> *&prt);  // 右旋
	void RotateLR(AVLNode<Type> *&prt); // 先左后右
	void RotateL(AVLNode<Type> *&prt);  // 左旋
	void RotateRL(AVLNode<Type> *&prt); // 先右后左
private:
	AVLNode<Type> *root;
};

//实现调整平衡 
template <class Type>
void AVLTree<Type>::RotateR(AVLNode<Type> *&ptr) // 右旋
{
	AVLNode<Type> *subR = ptr;
	ptr = subR->leftChild;
	subR->leftChild = ptr->rightChild;
	ptr->rightChild = subR;
	ptr->bf = subR->bf = 0;
}
template <class Type>
void AVLTree<Type>::RotateLR(AVLNode<Type> *&ptr) // 先左后右
{
	AVLNode<Type> *subL = ptr->leftChild;
	AVLNode<Type> *subR = ptr;
	ptr = subL->rightChild;

	subL->rightChild = ptr->leftChild;  //先左
	ptr->leftChild = subL;
	//  更新subL平衡因子
	if (ptr->bf <= 0)
		subL->bf = 0;
	else
		subL->bf = -1;

	subR->leftChild = ptr->leftChild;//  后右
	ptr->rightChild = subR;
	// 更新subR的平衡因子 
	if (ptr->bf >= 0)
		subR->bf = 0;
	else
		subR->bf = 1;

	ptr->bf = 0;
}
template <class Type>
void AVLTree<Type>::RotateL(AVLNode<Type> *&ptr)  // 左旋
{
	AVLNode<Type> *subL = ptr;
	ptr = subL->rightChild;
	subL->rightChild = ptr->leftChild;
	ptr->leftChild = subL;
	ptr->bf = subL->bf = 0;

}

template <class Type>
void AVLTree<Type>::RotateRL(AVLNode<Type> *&ptr) // 先右后左
{
	AVLNode<Type> *subL = ptr;
	AVLNode<Type> *subR = ptr->rightChild;
	ptr = subR->leftChild;

	subR->leftChild = ptr->leftChild;//  先右
	ptr->rightChild = subR;
	// 更新subR的平衡因子 
	if (ptr->bf >= 0)
		subR->bf = 0;
	else
		subR->bf = 1;
	subL->rightChild = ptr->leftChild;  //先左
	ptr->leftChild = subL;
	//  更新subL平衡因子
	if (ptr->bf == 1)
		subL->bf = -1;
	else
		subL->bf = 0;

	ptr->bf = 0;
}

template<class Type>
bool AVLTree<Type>::Insert(AVLNode<Type> *&t, const Type &x)
{


	// 1  按照BST规则插入节点   非递归
	AVLNode<Type> *pr = nullptr;//  父节点
	AVLNode<Type> *p = t;
	stack<AVLNode <Type>*> st;   //  保留原来插入节点的路线  为调整平衡因子做准备

	while (p != nullptr)
	{
		//  用于查找x的插入位置
		if (x == p->data)
			return false; //  先排除插入相同的数据

		pr = p;
		st.push(pr);//保留原来插入节点的路线   入栈

		if (x < p->data)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	p = new AVLNode<Type>(x);
	if (pr == nullptr)   //父节点为空的话 创建新节点  直接 返回
	{
		t = p;
		return true;
	}
	//  新建节点的链接
	if (x < pr->data)
		pr->leftChild = p;
	else
		pr->rightChild = p;

	//  2  如果发生不平衡  需要调整平衡
	while (!st.empty())
	{
		pr = st.top();
		st.pop();
		if (p == pr->leftChild)
			pr->bf--;
		else
			pr->bf++;
		if (pr->bf == 0)//   平衡因子为0  说明是平衡的
			break;
		if (pr->bf == 1 || pr->bf == -1)//  说明不平衡  应该向上回溯  在判断
			p = pr;
		else
		{
			// 平衡因子大于2了  不平衡了 调整
			if (p == pr->leftChild)  // 左分支  
			{
				if (p->bf < 0)  //  右转    / 形状
				{
					RotateR(pr);
				}
				else//  先左后右旋转  < 形状
				{
					RotateLR(pr);
				}
			}
			else   // 右分支
			{

				if (p->bf > 0)  // 左旋转  \形状
				{
					RotateL(pr);
				}
				else //  先右后左旋转    >形状
				{
					RotateRL(pr);
				}
			}
			break;
		}
	}
	//  重新链接
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
