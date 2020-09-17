#include<iostream>
#include<string>
using namespace std;

#define maxsize 10
#define charToNum(x) (int(x) - int('0'))

//邻接矩阵定义
typedef struct
{
	int no;
	//char info;
}VertexType;

typedef struct
{
	int edges[maxsize][maxsize];
	int n, e;
	VertexType v[maxsize];
}MGraph;

//邻接表定义
typedef struct ArcNode
{
	int data;
	ArcNode* next;
}ArcNode;

typedef struct
{
	char data;
	ArcNode* firstArc;
}VNode;

typedef struct
{
	VNode adjlist[maxsize];
	int n, e;
}AGraph;

//队列定义
typedef struct Queue
{
	int front;
	int rear;
	int data[maxsize];
}Queue;

//邻接矩阵初始化
void initMGraph(MGraph& G)
{
	for (int i = 0; i < maxsize; ++i)
	{
		for (int j = 0; j < maxsize; ++j)
		{
			G.edges[i][j] = 0;
		}
	}
	for (int i = 0; i < maxsize; ++i)
		G.v[i].no = i;
	G.n = 0;
	G.e = 0;
}

//邻接矩阵建图
void createMGraph(MGraph& G)
{
	char i, j;
	cin >> i;    //输入首节点
	while (i != '#')
	{
		cin >> j;
		while (j != '#')
		{
			G.edges[charToNum(i)][charToNum(j)] = 1;
			++(G.e);
			cin >> j;    //输入相邻节点
		}
		++(G.n);    //统计节点数
		G.v[charToNum(i)].no = charToNum(i);    //统计节点编号
		cin >> i;
	}
	G.e = G.e / 2;    //无向图边数减半
}

//重载使用字符串
void createMGraph(MGraph& G,string s)
{
	char i, j;
	int k = 0;
	i = s[0];
	while(i != '#')
	{ 
		j = s[++k];
		while (j != '#')
		{
			G.edges[charToNum(i)][charToNum(j)] = 1;
			++(G.e);
			j = s[++k];
		}
		++(G.n);    
		G.v[charToNum(i)].no = charToNum(i);    
		i = s[++k];
	}
	G.e = G.e / 2;   
}

//显示邻接矩阵
void showMGraph(MGraph G)
{
	for (int i = 0; i < G.n; ++i)
	{
		for (int j = 0; j < G.n; ++j)
		{
			cout << G.edges[i][j] << " ";
		}
		cout << endl;
	}
}

//找某节点的第一个相邻点（邻接矩阵）
int firstNeighbor(MGraph G, int v)
{
	int i = 0;
	for (i = (v == 0) ? 1 : 0; G.edges[v][i] != 1 && i < G.n; ++i);
	if (G.edges[v][i] == 1)
		return i;
	else
		return -1;
}

//找某节点的下一个相邻点
int nextNeighbor(MGraph G, int v,int j)    //j为上一个相邻点
{
	int i = 0;
	for (i = j + 1; G.edges[v][i] != 1 && i < G.n; ++i);
	if (G.edges[v][i] == 1)
		return i;
	else
		return -1;
}

//队列方法定义，给遍历使用
void initQueue(Queue& Q)
{
	Q.front = 0;
	Q.rear = 0;
}

void enQueue(Queue& Q, int v)
{
	if ((Q.rear + 1) % maxsize != Q.front)    
	{
		Q.data[Q.rear] = v;
		Q.rear = (Q.rear + 1) % maxsize;
	}
}

void deQueue(Queue& Q, int& v)
{
	if (Q.front != Q.rear)
	{
		v = Q.data[Q.front];
		Q.front = (Q.front + 1) % maxsize;
	}
}

bool isQueueEmpty(Queue Q)
{
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}

void visit(int v)    //访问操作
{
	cout << "(" << v << ")";
}

//01.将邻接表转换为邻接矩阵
//思想：遍历邻接表头节点对应的边节点链表，把邻接矩阵里对应的一项置成1即可
void graphAtoM(AGraph A, MGraph M)    
{
	for (int i = 0; i < M.n; ++i)
	{
		ArcNode* p = A.adjlist[i].firstArc;
		while (p != NULL)
		{
			M.edges[i][p->data] = 1;
			p = p->next;
		}
	}
}

//02.判断一个无向图是否是一棵树，是则返回true，否则返回false。无向图用邻接矩阵存储。
//思想：判断图是否为树的条件是图是否为n-1条边的连通图。
//深度优先遍历，若能一次遍历到所有节点，则连通。
//用vNum和eNum统计遍历到的节点数和边数，作为递归参数向下传递，最后检查是否符合条件即可
bool visited[maxsize];

void DFS(MGraph G, int v, int& vNum, int& eNum)
{
	visited[v] = true;
	++vNum;    //统计遍历节点数
	int w = firstNeighbor(G, v);
	while (w != -1)
	{
		++eNum;    //统计遍历边数
		if (!visited[w])
			DFS(G, w, vNum, eNum);
		w = nextNeighbor(G, v, w);
	}
}

bool isTree(MGraph G)
{
	for (int i = 0; i < G.n; ++i)
		visited[i] = false;    //初始化
	int vNum = 0, eNum = 0;
	DFS(G, 0, vNum, eNum);
	if (vNum == G.n && eNum == 2 * (G.n - 1))    //注意无向图的边数/2才是实际边数
		return true;
	else
		return false;
}

//栈定义，给第3题使用
typedef struct stack
{
	int top;
	int data[maxsize];
}Stack;

void initStack(Stack &S)
{
	S.top = -1;
	for (int i = 0; i < maxsize; ++i)
		S.data[i] = 0;
}

void push(Stack &S, int x)
{
	++(S.top);
	S.data[S.top] = x;
}

void pop(Stack &S, int& x)
{
	x = S.data[S.top];
	--(S.top);
}

bool isStackEmpty(Stack S)
{
	if (S.top == -1)
		return true;
	else
		return false;
}

//03.深度优先搜索的非递归实现
//思想：用栈辅助，visited数组标记，置成true的不重复入栈。
//注意遍历时顺序会反过来。使用邻接矩阵还是邻接表存储差别不大，关键在于获取相邻节点的函数
void DFS_non_rec(MGraph G, int v)
{
	Stack S;
	initStack(S);
	for (int i = 0; i < G.n; ++i)
		visited[i] = false;    //初始化
	visited[v] = true;
	push(S, v);
	while (!isStackEmpty(S))
	{
		pop(S, v);
		visit(v);    //出栈访问
		for (int w = firstNeighbor(G, v); w >= 0; w = nextNeighbor(G, v, w))    //遍历邻点
		{
			if (!visited[w])
			{
				visited[w] = true;
				push(S, w);
			}
		}
	}
}





//建图测试（无向图）
string g1 = "0123#103#203#3012##" ;
string g2 = "0123#10245#2016#304#4135#5146#625##";
string g3 = "2016#304#625#0123#10245#5146#4135##";
string g4 = "0123#104#2056#30#41#52#62##";    //tree

int main()
{
	MGraph B;
	initMGraph(B);
	createMGraph(B, g4);
	showMGraph(B);
	
	if (isTree(B))
		cout << "it's a tree.\n";
	else
		cout << "not a tree.\n";
}
