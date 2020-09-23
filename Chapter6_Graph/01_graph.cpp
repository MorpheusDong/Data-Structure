#include<iostream>
#include<string>
using namespace std;

#define maxsize 10
#define charToNum(x) (int(x) - int('0'))
#define INF 999

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

//邻接表初始化
void initAGraph(AGraph& G)
{
	for (int i = 0; i < maxsize; ++i)
	{
		G.adjlist[i].data = 0;
		G.adjlist[i].firstArc = (ArcNode*)malloc(sizeof(ArcNode));
		G.adjlist[i].firstArc->next = NULL;
	}
	G.n = 0;
	G.e = 0;
}

//邻接表建图
void createAGraph(AGraph& G)
{
	char i, j;
	cin >> i;    //输入首节点
	while (i != '#')
	{
		G.adjlist[charToNum(i)].firstArc->data = charToNum(i);
		cin >> j;    //输入相邻节点
		while (j != '#')
		{
			ArcNode* p;
			p = (ArcNode*)malloc(sizeof(ArcNode));
			p->data = charToNum(j);
			p->next = G.adjlist[charToNum(i)].firstArc->next;    //头插法
			G.adjlist[charToNum(i)].firstArc->next = p;
			++(G.e);    //统计边数
			cin >> j;
		}
		++(G.n);    //统计节点数
		cin >> i;
	}
	G.e = G.e / 2;    //无向图边数减半
}

//显示邻接表
void showAGraph(AGraph G)
{
	for (int i = 0; i < G.n; ++i)
	{
		ArcNode* p = G.adjlist[i].firstArc;
		while (p)
		{
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
}

//找某节点的第一个相邻点（邻接表）
int firstNeighbor(AGraph A, int v)
{
	if (A.adjlist[v].firstArc->next != NULL)
		return A.adjlist[v].firstArc->next->data;
	else
		return -1;    //not found
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

//BFS 广度优先搜索
//思想：类比树的层次遍历
bool visited[maxsize];

void BFS(MGraph G, int v)
{
	Queue Q;
	initQueue(Q);

	visit(v);
	visited[v] = true;
	enQueue(Q, v);
	while (!isQueueEmpty(Q))
	{
		deQueue(Q, v);
		for (int w = firstNeighbor(G, v); w >= 0; w = nextNeighbor(G, v, w))    //找周边相邻点
		{
			if (!visited[w])
			{
				visit(w);
				visited[w] = true;
				enQueue(Q, w);
			}
		}
	}
}

void BFSTraverse(MGraph G)
{
	for (int i = 0; i < G.n; ++i)
		visited[i] = false;
	for (int i = 0; i < G.n; ++i)    //如果是无向连通图，实际上一次BFS()就遍历完了，该for循环的意义是重新选取节点，保证非连通部分的遍历
	{
		if (!visited[i])
			BFS(G, i);
	}
}

//DFS 深度优先搜索
//思想：递归，类比树的先序遍历
void DFS(MGraph G, int v)
{
	visit(v);
	visited[v] = true;
	for (int w = firstNeighbor(G, v); w >= 0; w = nextNeighbor(G, v, w))    //随便找一个邻点
	{
		if (!visited[w])    //遍历邻点
			DFS(G, w);
	}
}

void DFSTraverse(MGraph G)
{
	for (int i = 0; i < G.n; ++i)
		visited[i] = false;
	for (int i = 0; i < G.n; ++i)
	{
		if (!visited[i])
			DFS(G, i);
	}
}

//建图测试（无向图）
string g1 = "0123#103#203#3012##" ;
string g2 = "0123#10245#2016#304#4135#5146#625##";

//测试主函数
int main()
{
	MGraph B;
	initMGraph(B);
	createMGraph(B, g2);
	showMGraph(B);
	
	int v = 0;
	int n = 0;
	cin >> v;
	//显示某节点的所有邻居
	while (v != 99)
	{
		for (n = firstNeighbor(B, v); n >= 0; n = nextNeighbor(B, v, n))
		{
			cout << "next neighbor:" << n << endl;
		}
		cin >> v;
	}

    BFSTraverse(B);

	return 0;
}