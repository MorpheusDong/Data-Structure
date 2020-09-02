#include<iostream>
using namespace std;

typedef char ElemType;

//数据类型定义
typedef struct BinaryNode
{
	ElemType data;
	BinaryNode* lchild;
	BinaryNode* rchild;
}BiNode;

//二叉树建树（先序），用#表示空指针域
void createBiTree(BiNode *& bNode)
{
	ElemType c;
	cin>>c;
	if(c == '#')
		bNode = NULL;    
	else
	{
		bNode = (BiNode*)malloc(sizeof(BiNode));
		bNode->data = c;
		createBiTree(bNode->lchild);
		createBiTree(bNode->rchild);
	}
}

//先序遍历输出
void preOrder(BiNode* bNode)
{
	if (bNode == NULL)
		cout << "#";
	else
	{
		cout << bNode->data;
		preOrder(bNode->lchild);
		preOrder(bNode->rchild);
	}
}

//中序遍历输出
void inOrder(BiNode* bNode)
{
	if (bNode == NULL)
		cout << "#";
	else
	{
		inOrder(bNode->lchild);
		cout << bNode->data;
		inOrder(bNode->rchild);
	}
}

//后序遍历输出
void postOrder(BiNode* bNode)
{
	if (bNode == NULL)
		cout << "#";
	else
	{
		postOrder(bNode->lchild);
		postOrder(bNode->rchild);
		cout << bNode->data;
	}
}

//测试主函数
int main()
{
	BiNode* root;
	createBiTree(root);
	preOrder(root);
	
}