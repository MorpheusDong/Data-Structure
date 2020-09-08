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

//建图测试（无向图）
string g1 = "0123#103#203#3012##" ;
string g2 = "0123#10245#2016#304#4135#5146#625##";

int main()
{

}