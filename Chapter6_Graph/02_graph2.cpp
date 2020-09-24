
#define INF    999

//迪杰斯特拉算法
//（求解单源最短路径）
void Dijkstra(MGraph G,int v,int dist[],int path[])
{
	int set[maxsize];
	int min,i,j,u;
	for(i = 0;i<G.n;++i)    //初始化
	{
		set[i] = 0;
		dist[i] = G.edges[v][i];
		if(G.edges[v][i]<INF)
			path[i] = v;    //v能直接到达的节点，其路径为v
		else
			path[i] = -1;   //不能直接到达的，设为-1
	}
	set[v] = 1;    //并入起始节点
	path[v] = -1;
	for(i = 0;i<G.n-1;++i)    //总共做n-1次
	{
		min = INF;
		for(j = 0;j<G.n;++j)
		{
			if(set[j]==0 && dist[j]<min)    //在剩余未并入的节点中找到距离最近的
			{
				u = j;    //更新中转点
				min = dist[j];    //更新最短距离
			}
		}    //循环结束后u是中转点
		for(j = 0;j<G.n;++j)
		{
			if(set[j] == 0 && dist[u]+G.edges[u][j] < dist[j])    //如果以u中转后能到达的节点的距离比原先的距离小，则更新最短距离和路径
			{
				dist[j] = dist[u]+G.edges[u][j];
				path[j] = u;
			}
		}	
	}
}

//打印路径
//path数组实际上是双亲存储结构的树，从孩子追溯到双亲是反序的，打印正序路径时需要借助栈。
void printPath(int path[],int a)
{
	int stack[maxsize],top = -1;
	while(path[a] != -1)
	{
		stack[++top] = a;    //压入节点
		a = path[a];    //换到前一个节点
	}
	stack[++top] = a;    //压入起始节点
	while(top != -1)
		cout<<stack[top--]<<" ";
	cout<<endl;
}

//弗洛伊德算法
//（求解任意点对之间的最短路径）
int A[maxsize][maxsize];int path[maxsize][maxsize];
void Floyd(MGraph G)
{
	int i,j,k;
	for(i = 0;i<G.n;++i)    //初始化
	{
		for(int j = 0;j<G.n;++j)
		{
			A[i][j] = G.edges[i][j];    //复制邻接矩阵。矩阵中，顶点本身值为0，可直达的点对的值为其权重，不可直达的点对的值为INF
			path[i][j] = -1;    
		}
	}
	
	for(k = 0;k<G.n;++k)    //以每个顶点作为中转点，检测到其它顶点的最短路径
	{
		for(i = 0;i<G.n;++i)
		{
			for(j = 0;j<G.n;++j)
			{
				if(A[i][j] > A[i][k] + A[k][j])
				{
					A[i][j] = A[i][k] + A[k][j];    //更新最短距离
					path[i][j] = k;    //更新路径
				}
			}
		}
	}
}

//拓扑排序算法
//（依次输出AOV网中的节点）
typedef struct ArcNode
{
	int data;
	int count;
	ArcNode* next;
}ArcNode;

typedef struct
{
	int data;
	int count;    //算法需要检测入度，假设定义在节点中
	ArcNode* firstArc;
}VNode;

typedef struct
{
	VNode adjlist[maxsize];
	int n, e;
}AGraph;

int topSort(AGraph G)
{
	int i,j,n = 0;    //n用来统计输出的节点数
	int stack[maxsize];int top = -1;    //辅助栈
	ArcNode* p;    //p用来遍历相邻点
	for(int i = 0;i<G.n;++i)
		if(G.adjlist[i]->count == 0)
			stack[++top] = i;    //将入度为0的点入栈
	while(top != -1)
	{
		i = stack[top--];    
		cout<<i<<" ";    //输出节点
		++n;
		p = G.adjlist[i]->firstArc;    //检测相邻节点
		while(p!=NULL)
		{
			j = p->data;    
			--(G.adjlist[j]->count);    //入度-1
			if(G.adjlist[j]->count == 0)
				stack[++top] = j;    //入度为0的节点入栈
			p = p->next;    //下一个相邻点
		}
	}
	if(n == G.n)
		return 1;    //true
	else
		return 0;    //false;
}

