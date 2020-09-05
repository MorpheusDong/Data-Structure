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

//基本方法
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

//链栈的定义，给非递归遍历使用
typedef struct linkStack    
{
	BiNode* pNode;    //指向树节点的指针
	linkStack* next;
}LNode,liStack;

void init(liStack* &s)    //栈初始化
{
	s = (liStack*)malloc(sizeof(liStack));
	s->next = NULL;
}

void push(liStack* &s,BiNode* bNode)    //入栈
{
	liStack *q;
	q = (liStack*)malloc(sizeof(liStack));
	q->pNode = bNode;    //树节点入栈（栈指针指向该树节点）
	q->next = s->next;
	s->next = q;
}

void pop(liStack* &s,BiNode* &bNode)    //出栈
{
	liStack *u = s->next;
	if(u)
	{
		bNode = u->pNode;    //树节点出栈（bNode指向树节点）
		s->next = u->next;
		free(u);
	}
}

bool isStackEmpty(liStack* s)    //栈空
{
	if(s->next == NULL)
		return true;
	else
		return false;
}

void getTop(liStack* s,BiNode* &bNode)    //获取栈顶的树节点
{
	bNode = s->next->pNode;
}

//链队的定义，给层次遍历使用
typedef struct linkQueue
{
	LNode* node;
	LNode* front;
	LNode* rear;
}liQueue;

void initQueue(liQueue* Q)    //队列初始化
{
	Q->node = (LNode*)malloc(sizeof(LNode));
	Q->node->next = NULL;
	Q->front = NULL;
	Q->rear = NULL;
}

void enQueue(liQueue* Q,BiNode* bNode)    //入队
{
	LNode* q;
	q = (LNode*)malloc(sizeof(LNode));
	q->pNode = bNode;
	if(Q->rear == NULL)
	{
		Q->front = q;
		Q->rear = q;
	}
	else
	{
		Q->rear->next = q;
		Q->rear = Q->rear->next;
	}
}

void deQueue(liQueue* Q,BiNode* &bNode)    //出队
{
	if(Q->rear == NULL)
		return;
	
	if(Q->front == Q->rear)
	{
		LNode* u;
		u = Q->front;
		bNode = u->pNode;
		Q->front = NULL;
		Q->rear = NULL;
	}
	else
	{
		LNode* u;
		u = Q->front;
		bNode = u->pNode;
		Q->front = u->next;
	}
}

bool isQueueEmpty(liQueue* Q)    //队空
{
	if(Q->rear == NULL)
		return true;
	else
		return false;
}

//01.假设二叉树顺序存储，编写算法找出两个节点的最近的公共祖先
ElemType commonAncestor(SqTree T,int i,int j)    //SqTree假设为定义好的数组
{
	if(T[i]!='#' && T[j]!='#')    //节点存在
	{
		while(i!=j)
		{
			if(i>j)    
				i = i/2;    //节点标号i>j，则要么i在j同层的右侧，要么在下一层，则应顺着i的祖先向上找
			else
				j = j/2;    //j>i同理，谁更深就顺着谁的祖先向上，直到祖先为同一个为止
		}
	}
	return T[i];
}

//02.遍历的非递归写法
//先序遍历的非递归写法
void preOrder2(BiNode* T)    
{
	liStack *S;    
    init(S);
	BiNode* p = T;    //p为工作指针，遍历树节点
	while(p || !isStackEmpty(S))    //p遍历到底且栈是空的表示遍历完成
	{
		if(p)    //p走到底
		{
			cout<<p->data;    //访问操作
			push(S,p);    
			p = p->lchild;    //p往左走到底
		}
		else    ///进入子树左下角
		{
			pop(S,p);
			p = p->rchild;    //继续查看右子树
		}
	}
}

//中序遍历的非递归写法
void inOrder2(BiNode* T)    
{
	liStack *S;    
    init(S);
	BiNode* p = T;    //p为工作指针，遍历树节点
	while(p || !isStackEmpty(S))    //p遍历到底且栈是空的表示遍历完成
	{
		if(p)    //p走到底
		{
			push(S,p);    
			p = p->lchild;    //p往左走到底
		}
		else    //进入子树左下角
		{
			pop(S,p);
			cout<<p->data;    //访问操作
			p = p->rchild;    //继续查看右子树
		}
	}
}

//03.层次遍历
void levelOrder(BiNode* T)
{
	liQueue* Q;
	initQueue(Q);    //队初始化
	BiNode* p;
	enQueue(Q,T);    //根节点入队
	while(!isQueueEmpty(Q))
	{
		deQueue(Q,p);
		cout<<p->data;    //访问操作
		if(p->lchild != NULL)
			enQueue(Q,p->lchild);
		if(p->rchild != NULL)
			enQueue(Q,p->rchild);
	}
}

//04.后序遍历的非递归写法（使用链栈）
void postOrder2(BiNode* T)
{
	liStack *S;    
    init(S);
	BiNode* p = T;    //p为工作指针，遍历树节点
	BiNode* r = NULL;
	while(p || !isStackEmpty(S))    //p遍历到底且栈是空的表示遍历完成
	{
		if(p)    //p走到底
		{
			push(S,p);    //根节点入栈
			p = p->lchild;    //p往左走到底
		}
		else    //进入子树左下角
		{
			getTop(S,p);    
			if(p->rchild && p->rchild != r)    //访问根节点前，上个访问是其右孩子，不是则代表没访问过
			{
				p = p->rchild;    //转向右子树
				push(S,p);    //根节点入栈
				p = p->lchild;    //继续往左走
			}
			else    //根节点没有右孩子，或右子树访问完毕
			{
				pop(S,p);
				cout<<p->data;    //访问操作
				r = p;    //r记录上次访问的节点
				p = NULL;    //出栈代表根节点访问完，p用getTop()重置
			}
		}
	}
}

//05.实现从下到上，从右到左的层次遍历
//思想：和正常层次遍历顺序相反，在其基础上修改，出队时入栈最后再统一出栈实现倒序遍历
void levelOrder2(BiNode* T)
{
	liQueue* Q = (liQueue*)malloc(sizeof(liQueue));
	initQueue(Q);    //队初始化
	liStack *S;    
    init(S);    //栈初始化
	BiNode* p;
	enQueue(Q,T);    //根节点入队
	
	while(!isQueueEmpty(Q))
	{
		deQueue(Q,p);
		push(S,p);    //出队后入栈
		if(p->lchild != NULL)
			enQueue(Q,p->lchild);
		if(p->rchild != NULL)
			enQueue(Q,p->rchild);
	}
	
	while(!isStackEmpty(S))    //依次出栈实现倒序层次遍历
	{
		pop(S,p);
		cout<<p->data;
	}
}

//06.求二叉树的深度（书上用顺序队，这里用了链队）
//思想：从根节点开始，每次队尾就是下一层的最右节点，设为last。每次走到最右节点时，更新下一层的last。用levels计数。
int btDepth(BiNode* T)
{
	liQueue* Q = (liQueue*)malloc(sizeof(liQueue));
	initQueue(Q);
	int levels = 0;
	BiNode* last = T;
	BiNode* p;
	enQueue(Q, T);
	while (!isQueueEmpty(Q))
	{
		deQueue(Q, p);    //最后一层时这里会使队空
		if (p->lchild)
			enQueue(Q, p->lchild);
	    if (p->rchild)
			enQueue(Q, p->rchild);
		if (p == last)    //走到当前层的最右节点
		{
			++levels;
			if (Q->rear != NULL)    
				last = Q->rear->pNode;    //更新下一层的最右节点
		}
	}
	return levels;
}

//求某层节点数，求树最大宽度，遵循上面的逻辑略作修改即可

//递归写法
int treeDepth(BiNode* T)
{
	int lDepth,rDepth;
	if(T == NULL)
		return 0;
	else
	{
		lDepth = treeDepth(T->lchild);
	    rDepth = treeDepth(T->rchild);
		return (lDepth+1)>(rDepth+1)? lDepth+1:rDepth+1;
	}
}

//07.假设数组A[1...n]和B[1...n]分别存储先序和中序遍历的序列。用A和B建树。
//（递归方法）
void createTreePreIn(BiNode* &T, ElemType A[], ElemType B[], int length)
{
	if (length == 0)
	{
		T = NULL;    //长度为0说明一棵子树已经建到底
		return;
	}

	int i = 0, lLen = 0, rLen = 0;
	ElemType c = A[0];    //取先序序列的第一个值
	while (i < length && B[i] != c)    //查找它在中序序列中的位置
		++i;
	lLen = i;    
	rLen = length - i - 1;    //更新左右子树的长度

	T = (BiNode*)malloc(sizeof(BiNode));    //创建节点
	T->data = c;    
	createTreePreIn(T->lchild, &A[1], &B[0], lLen);    //递归建立左子树
	createTreePreIn(T->rchild, &A[lLen + 1], &B[lLen + 1], rLen);    //递归建立右子树
}

//08.判断一棵树是否是完全二叉树
//思想：层次遍历，遇到非空节点让左子树和右子树入队，遇到空节点查看队列后面是否为空，不是空则不是完全二叉树。
bool isComplete(BiNode* T)
{
	if(T == NULL)
		return true;    //空树是完全二叉树
	
	BiNode* p;
	liQueue* Q = (liQueue*)malloc(sizeof(liQueue));
	initQueue(Q);
	enQueue(Q,T);
	while(!isQueueEmpty(Q))
	{
		deQueue(Q,p);
		if(p)
		{
			enQueue(Q,p->lchild);
			enQueue(Q,p->rchild);
		}
		else
			while(!isQueueEmpty(Q))
			{
				deQueue(Q,p);
				if(p)
					return false;
			}
	}
	return true;	
}

//09.统计二叉树中的双分支节点数
int doubleBranchN(BiNode* T)
{
	if(T == NULL)
		return 0;
	else if(T->lchild && T->rchild)
		return doubleBranchN(T->lchild)+doubleBranchN(T->rchild)+1;
	else
		return doubleBranchN(T->lchild)+doubleBranchN(T->rchild);
}

//10.交换二叉树的所有左右子树
void swap(BiNode* T)
{
	if(T)
	{
		swap(T->lchild);
		swap(T->rchild);
		BiNode* temp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = temp;
	}
}

//11.按先序遍历顺序输出第k个节点的值
int i = 1;    //用全局变量计数
ElemType preOrderK(BiNode* T,int k)
{
	if(T == NULL)
		return '#';
	if(i == k)
		return T->data;
	++i;
	ElemType ch;
	ch = preOrderK(T->lchild,k);    //遍历左子树
	if(ch != '#')
		return ch;
	ch = preOrderK(T->rchild,k);    //左子树中没有，接着遍历右子树
	return ch;
}

//12.删除二叉树中节点值为x的根节点下面的子树，并释放空间
void deleteXTree(BiNode* T)    //后序遍历删除左右子树
{
	if (T)
	{
		deleteXTree(T->lchild);
		deleteXTree(T->rchild);
		free(T);
	}
}

void searchAndDelete(BiNode* T, ElemType x)    //层次遍历找到值为x的根节点，然后删除子树
{
	if (T == NULL)
		return;
	if (T->data == x)
	{
		deleteXTree(T);
		return;
	}
	BiNode* p;
	liQueue* Q;
	Q = (liQueue*)malloc(sizeof(liQueue));
	initQueue(Q);
	enQueue(Q, T);
	while (!isQueueEmpty(Q))
	{
		deQueue(Q, p);
		if (p->lchild)
		{
			if (p->lchild->data == x)
			{
				deleteXTree(p->lchild); p->lchild = NULL;
			}
			else
			{
				enQueue(Q, p->lchild);
			}
		}
		if (p->rchild)
		{
			if (p->rchild->data == x)
			{
				deleteXTree(p->rchild); p->rchild = NULL;
			}
			else
				enQueue(Q, p->rchild);
		}
	}
}
				
//13.输出二叉树中值为x的节点的所有祖先
//思想：后序遍历，找到值为x的节点时，栈内所有节点就是祖先，输出即可
typedef struct stack    //栈定义
{
	BiNode* t;
	int tag;    //tag = 0表示左子树被访问，= 1表示右子树被访问
};

void ancestors(BiNode* T, ElemType x)
{
	stack s[10];    //假设容量足够
	int top = 0;
	BiNode* p = T;
	while (p || top > 0)
	{
		while (p && p->data != x)    //一路向左下寻找x
		{
			s[++top].t = p;    //节点入栈
			s[top].tag = 0;    //标记左子树
			p = p->lchild;
		}
		if (p && p->data == x)    //是否找到了x
		{
			cout << "ancestors of " << x << ":";
			for (int i = 1; i <= top; ++i)
			{
				cout << s[i].t->data;    //输出栈中的所有祖先
			}
			return;
		}
		while (top != 0 && s[top].tag == 1)    //右子树已被访问（右子树中没找到x）的根节点，令其出栈
		{
			--top;    //如果这里执行，将回到上个祖先（双亲）
		}
		if (top != 0)
		{
			s[top].tag = 1;    //标记根节点的右子树已被访问
			p = s[top].t->rchild;    //转向右子树，下面继续一路向左下寻找
		}
	}
}

//14.p,q是指向二叉树中任意两个节点的指针，找到p和q最近的公共祖先r
//思想：用非递归后序遍历到某个节点时，栈中的所有节点就是它的祖先。
//假设p在q的左边，先遍历到p，用一个辅助栈存储p的所有祖先。继续遍历到q，然后对q的祖先在辅助栈里匹配。
void ancestor(BiNode* root, BiNode* p, BiNode* q, BiNode* &r)
{
	BiNode* w = root;
	stack S1[10], S2[10];    //假设容量足够，S1为工作栈，S2保存p的祖先
	int top1 = 0, top2 = 0;    //top1是树遍历的栈顶指针，top2是辅助栈的栈顶指针
	while (w || top1 > 0)
	{
		while (w && w != p && w != q)    
		{
			S1[++top1].t = w;
			S1[top1].tag = 0;
			w = w->lchild;
		}
		if (w == p)    //先遍历到p
		{
			for (int i = 1; i <= top1; ++i)
			{
				S2[++top2].t = S1[i].t;    //保存p的祖先
			}
		}
		else if (w == q)    //后遍历到q
		{
			BiNode* k;    //用于比较的指针
			int i, j;    
			for (i = top1; i > 0; --i)    //从q最近的祖先（即栈顶）开始逐一去和p的祖先比较
			{
				k = S1[i].t;
				j = top2;    
				while (k != S2[j].t && j > 0)
				{
					--j;
				}
				if (k == S2[j].t)    //找到了公共祖先
				{
					r = k;
					return;
				}
			}
		}
		else {}

		while (top1 != 0 && S1[top1].tag == 1)
		{
			--top1;
		}
		if (top1 != 0)
		{
			S1[top1].tag = 1;
			w = S1[top1].t->rchild;
		}
	}
}

//15.求非空二叉树的宽度
//思想：层次遍历，统计每层的节点数。每次到达当前层最右节点时，更新宽度。
int breadth(BiNode* T)
{
	BiNode* p = T;
	BiNode* last = T;    //最右节点
	liQueue* Q = (liQueue*)malloc(sizeof(liQueue));
	initQueue(Q);

	int maxBreath = 0;
	int levelCount = 0;

	enQueue(Q, p);
	while (!isQueueEmpty(Q))
	{
		deQueue(Q, p);
		++levelCount;    
		if (p->lchild)
			enQueue(Q, p->lchild);
		if (p->rchild)
			enQueue(Q, p->rchild);
		if (p == last)    //到达当前层最右节点
		{
			if (Q->rear)
				last = Q->rear->pNode;    //更新下一层的最右节点
			maxBreath = (levelCount > maxBreath) ? levelCount : maxBreath;   //更新宽度
			levelCount = 0;    //重置每层的计数
		}
	}
	return maxBreath;
}

//16.一棵满二叉树，已知先序序列，转换为后序序列

//17.将二叉树的叶节点按从左到右的顺序链接成为链表。head指向第一个叶节点，每个节点的rchild指向下一个节点。
//思想：基于中序遍历，用前指针pre把上一个叶节点接到现在的。
BiNode* head;
BiNode* pre = NULL;
BiNode* linkLeaf(BiNode* T)
{
	if (T)
	{
		linkLeaf(T->lchild);
		if (T->lchild == NULL && T->rchild == NULL)
		{
			if (pre == NULL)    //处理第一个叶节点
			{
				head = T;
				pre = T;
			}
			else    //处理其它叶节点
			{
				pre->rchild = T;
				pre = T;
			}
		}
		linkLeaf(T->rchild);
		pre->rchild = NULL;    //处理最后一个叶节点
	}
	return head;
}

//18.判断两棵二叉树是否相似。相似的定义为：两棵二叉树都为空或只有一个根节点，或左子树和右子树都相似。
//思想：定义是递归的形式，看得出来这里的相似是结构上长得一样。两者同步递归遍历，按照定义判断是否相似即可。
int similar(BiNode* T1,BiNode* T2)
{
	int leftS,rightS;
	if(T1 == NULL && T2 == NULL)    //都是空树
	{
		return 1;    
	}
	else if(T1 == NULL || T2 == NULL)    //有一个为空
	{
        return 0;
	}
    else    //都不为空
	{
        leftS = similar(T1->lchild,T2->lchild);    //比较左子树
		rightS = similar(T1->rchild,T2->rchild);    //比较右子树
		return leftS&&rightS;    //左右子树是否都相似
	}
}

//19.计算一棵二叉树的权值WPL。设节点值域为weight，WPL的定义是所有叶节点的深度*weight。
//思想：用一个静态变量保存wpl保存总的WPL。基于递归先序遍历，把深度作为参数每次+1向下传递。每次遍历到叶节点，更新wpl。
typedef struct BiTNode    //数据类型定义
{
	int weight;
	BiTNode* lchild;
	BiTNode* rchild;
}BiTNode;

int WPL(BiTNode* root)
{
	return wpl_preorder(root,0);    //设根节点深度为0
}

int wpl_preorder(BiTNode* root,int deep)
{
	static int wpl = 0;
	if(root->lchild == NULL && root->rchild == NULL)
		wpl += deep*root->weight;    //更新WPL
	if(root->lchild)
		wpl_preorder(root->lchild,deep+1);
	if(root->rchild)
		wpl_preorder(root->rchild,deep+1);
	return wpl;
}

//上题如果用层次遍历：每层遍历时统计层数，当遍历到第一个叶节点开始计算wpl，持续到队空即可。（要用一个指针指示何时到达每层的最右）

//20.二叉树中已存好表达式，输出该中缀表达式，如(a+b)*(-c)。
//思想：中序遍历，用参数控制最外层的括号。
void treeToExp(BiNode* T, int deep)
{
	if (T == NULL)
		return;
	else if (T->lchild == NULL && T->rchild == NULL)    //叶节点直接输出
	{
		cout << T->data;
	}
	else
	{
		if (deep > 1)    //用向下传递的参数deep控制括号输出
			cout << "(";
		treeToExp(T->lchild, deep + 1);    //遍历左子树
		cout << T->data;
		treeToExp(T->rchild, deep + 1);    //遍历右子树
		if (deep > 1)
			cout << ")";
	}
}

void biTreeToExp(BiNode* T)
{
	treeToExp(T, 1);    //初始高度设为1，最外层不加括号
}

//21.求孩子兄弟法表示的树的叶子节点数
typedef struct nNode
{
	ElemType data;
	nNode* child;
	nNode* sibling;
}nNode;

int leaves(nNode* T)
{
	if(T == NULL)
		return 0;
	if(T->child == NULL)
		return 1+leaves(T->sibling);    //没有孩子的是叶节点，+兄弟子树的叶节点
	else
		return leaves(T->child)+leaves(T->sibling);    //递归求孩子子树和兄弟子树的叶节点
}

//22.递归法求孩子兄弟法表示的树的深度
//思想：和二叉树递归求深度没啥区别
int depth(nNode* T)
{
	int hc,hs;
	if(T == NULL)
		return 0;    //空树深度为0
	else
	{
		hc = deep(T->child);    //递归求孩子子树深度
		hs = deep(T->sibling);    //递归求兄弟子树深度
		return (hc+1)>hs ? hc+1:hs;    //返回孩子子树深度+1和兄弟子树的最大者
	}
}

//建树测试
//012##3##45###
//0123##4##5#6##7##
//*+a##b##-#c##

//测试主函数
int main()
{
	BiNode* root;
	createBiTree(root);
	
	levelorder(root);
	cout<<endl;
	biTreeToExp(root);
}