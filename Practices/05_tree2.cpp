#include<iostream>
#include<cstring>
using namespace std;

#define ElemType     char

typedef struct BiNode
{
	ElemType data;
	BiNode* lchild;
	BiNode* rchild;
}BiNode;

//中序遍历输出
void inOrder(BiNode* bNode)
{
	if (bNode == NULL)
		return;   
	else
	{
		inOrder(bNode->lchild);
		cout << bNode->data;
		inOrder(bNode->rchild);
	}
}

//二叉排序树的非递归查找算法
BiNode* BST_search(BiNode* T,ElemType key)
{
	while(T!=NULL && T->data!=key)
	{
		if(T->data>key)
			T = T->lchild;
		else
			T = T->rchild;
	}
	return T;
}

//二叉排序树的递归插入方法
int BST_insert(BiNode* &T,ElemType key)
{
	if(T == NULL)
	{
		T = (BiNode*)malloc(sizeof(BiNode));
		T->data = key;
		T->lchild = NULL;
		T->rchild = NULL;
		return 1;    //true
	}
	else if(T->data == key)
	{
		return 0;    //false
	}
	else if(T->data > key)
	{
		return BST_insert(T->lchild,key);
	}
	else
	{
		return BST_insert(T->rchild,key);
	}
}

//使用字符串建立二叉排序树
void createBST(BiNode* &T,string str)
{
	T = NULL;
	int i = 0;
	while(str[i] != '\0')
	{
		BST_insert(T,str[i]);
		++i;
	}
}

//01.判断一棵二叉树是否是排序二叉树
//思想：如果用中序遍历，那么一定是顺序的，每次判断后一个是不是比前面大。
//这里写的是递归，每次比较左右子树值的大小，递归下去。
int checkBST(BiNode* T)
{
	if (T == NULL)    //空树
	{
		return 1;    
	}
	else if (T->lchild == NULL && T->rchild == NULL)    //叶节点
	{
		return 1;
	}
	else if (T->lchild != NULL && T->rchild == NULL)    //只有左子树
	{
		if (T->lchild->data > T->data)
			return 0;
		else
		    return checkBST(T->lchild);
	}
	else if (T->lchild == NULL && T->rchild != NULL)    //只有右子树
	{
		if (T->rchild->data < T->data)
			return 0;
		else
			return checkBST(T->rchild);
	}
	else    //左右子树都存在
	{
		if (T->lchild->data > T->data || T->rchild->data < T->data)
			return 0;
		else
			return checkBST(T->lchild) && checkBST(T->rchild);    //且关系
	}
}

//02.给定二叉树中一个节点，查找它在树中的层次
//思想：层次就是比较次数，非递归查找即可，类似二分查找
int keyLevel(BiNode* T, BiNode* p)
{
	int n = 0;
	if (T)
	{
		++n;    //开始计数
		while (T->data != p->data)    
		{
			if (T->data > p->data)
				T = T->lchild;
			else
				T = T->rchild;
			++n;
		}
	}
	return n;
}

//03.判断一个二叉树是否平衡
//思想：后序遍历，定义两个引用参数。balance用于判断节点（对应的树）是否平衡，height求该节点的高度。
//一个节点的高度是左右子树的高度+1
//一个节点平衡的条件是，左右子树高度之差绝对值小于2，并且下面每个节点也平衡。
void checkAVL(BiNode* T, int& balance, int& height)
{
	int bl = 0, br = 0, hl = 0, hr = 0;
	if (T == NULL)
	{
		height = 0;    //空树高度为0，平衡
		balance = 1;
	}
	else if (T->lchild == NULL && T->rchild == NULL)
	{
		height = 1;    //只有一个节点/叶节点，高度为1，平衡
		balance = 1;
	}
	else
	{
		checkAVL(T->lchild, bl, hl);    //返回左子树的平衡情况和高度
		checkAVL(T->rchild, br, hr);    //返回右子树的平衡情况和高度
		height = (hl > hr ? hl : hr) + 1;    //计算当前节点的高度
		if (abs(hl - hr) < 2)    //检查此节点是否平衡
			balance = bl && br;    //检查子树节点是否也平衡
		else
			balance = 0;
	}
}

bool isBalance(BiNode* T)
{
	int b, h;
	checkAVL(T, b, h);
	if (b == 1)
		return true;
	else
		return false;
}

//04.找到二叉排序中的最小关键字和最大关键字
//思想：一个在最左下，一个在最右下
ElemType minKey(BiNode* T)
{
	while(T->lchild != NULL)
		T = T->lchild;
	
	return T->data; 
}

ElemType maxKey(BiNode* T)
{
	while(T->rchild != NULL)
		T = T->rchild;
	
	return T->data; 
}

//05.从大到小输出二叉排序树中值不小于k的关键字
//思想：从最右下角递归中序遍历，比较关键字的值，满足条件则继续
void aboveK(BiNode* T,ElemType k)
{
	if(T == NULL)
		return;
	if(T->rchild)
		aboveK(T->rchild,k);
	if(T->data >= k)
		cout<<T->data;
	if(T->lchild)
		aboveK(T->lchild,k);
}

//06.设计递归算法，找二叉排序树中第k小的关键字，返回该节点的指针。
//附加条件：二叉树中的节点类型定义除了数据域和孩子域外，还有一个count存储该节点的子节点的数量。
//思想：围绕count，从最简单的情况开始推递归模型。
//左节点不存在时，当前节点就是最小的，看k的大小决定是否要继续往右找；左节点存在时，根据左节点的数量count来判定接下来的查找。
typedef struct BSTNode
{
	ElemType data;
	BSTNode* lchild;
	BSTNode* rchild;
	int count;
}BSTNode;

BSTNode* searchSmall(BSTNode* T,int k)
{
	if(k<1 || k>T->count)
		return NULL;
	if(T->lchild == NULL)
	{
		if(k == 1)
			return T;    //没有左节点，找最小的就是当前节点
		else
			return searchSmall(T->rchild,k-1);    //否则在右子树中找k-1小的节点
	}
	else
	{
		if(T->lchild->count == k-1)    //左边有k-1个节点，那么当前节点就是第k小的
			return T;
		else if(T->lchild->count < k-1)    //左边小于k-1个节点，第k小的应在右边
			return searchSmall(T->rchild,k-(T->lchild->count+1));    //包括当前节点，左边共有左count+1个节点，所以在右边找第k-(count+1)小的节点
		else
			return searchSmall(T->lchild,k);    //左边大于k-1个节点，继续在左边找第k小的
	}
}

//简化题目要求，只是输出第k小的关键字，中序遍历计数
void minK(BiNode* T,int k)
{
	static int count = 0;
	if (T == NULL)
		return;
	if (T->lchild)
		minK(T->lchild, k);
	if (++count == k)
	{
		cout << T->data;
		exit(1);
	}
	if (T->rchild)
		minK(T->rchild, k);
}

int main()
{
	string s;
	BiNode* root;
	root = (BiNode*)malloc(sizeof(BiNode));

	cin >> s;
	createBST(root,s);
	inOrder(root);
}



