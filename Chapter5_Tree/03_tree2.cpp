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

int main()
{
	string s;
	BiNode* root;
	root = (BiNode*)malloc(sizeof(BiNode));

	cin >> s;
	createBST(root,s);
	inOrder(root);
}



