
#define INF    999

//迪杰斯特拉算法
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