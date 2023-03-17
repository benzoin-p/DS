/********
2021.11.28  14:49
数据结构作业三 第五题 
5. 对于一个带权有向图，设计一个算法输出从顶点 i 到顶点 j 的所有路径及其路径长度。
*********/

#include <iostream>
using namespace std;
#define Maxsize 105

typedef struct ANode
{
	int adjvex;		//边的终点的结点的编号 
	ANode* nextarc;//指向下一条边 
	int weight;//边权 
} ArcNode;

typedef struct
{
	char data; //顶点名称 
	ArcNode* firstarc; //指向第一条边 
}VNode;

typedef struct
{
	int n,e;
	VNode adjlist[Maxsize];
}AdjGraph;

int visited[Maxsize];//访问标记 

void CreatGraph(AdjGraph* &G,int n,int e,int a[Maxsize][Maxsize]);
void DestroyGraph(AdjGraph* &G);
void DispGraph(AdjGraph* G);
void FindPath(AdjGraph* G,int v1,int v2,int path[Maxsize],int length,int n);


int main()
{
	cout<<"对于一个带权有向图，设计一个算法输出从顶点 i 到顶点 j 的所有路径及其路径长度。"<<endl<<endl;
	cout<<"请输入带权有向图的顶点数n:";
	int n;
	cin>>n;
	cout<<endl;
	cout<<"请输入带权有向图的边数e:";
	int e;
	cin>>e;	
	cout<<endl;
	int a[Maxsize][Maxsize];
	for(int i=0;i<n;i++)
	{
		cout<<"请输入邻接矩阵第"<<i+1<<"行的"<<n<<"个数据:	";
		for(int j=0;j<n;j++)
		{
			cin>>a[i][j];
		} 
	}
	for(int i=0;i<n;i++)
	{
		visited[i]=0;
	}
	
	AdjGraph* G; 
	CreatGraph(G,n,e,a);
	//DispGraph(G); 
	
	
	cout<<"请输入顶点i、j的编号：";
	int i,j;
	cin>>i>>j;
	cout<<endl; 
	int length=0;
	int path[Maxsize]; 
	int t=0;
	FindPath(G,i,j,path,length,t);
	 	
	 	
	DestroyGraph(G);
	return 0;
	
}

void CreatGraph(AdjGraph* &G,int n,int e,int a[Maxsize][Maxsize])
{
	ArcNode* p;
	G=(AdjGraph*)malloc (sizeof(AdjGraph));
	//对每个顶点初始化 
	for(int i=0;i<n;i++)
	{
		G->adjlist[i].firstarc=NULL;
	 	
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
	 	{
		 	if(a[i][j]!=0&&a[i][j]!=-1)
		 	{
			 	p=(ArcNode*)malloc (sizeof(ArcNode));
			 	p->adjvex=j;
			 	p->weight=a[i][j];
			 	//头插法 
			 	p->nextarc=G->adjlist[i].firstarc;
			 	G->adjlist[i].firstarc=p; 
			}
		}
	}
	G->n=n;
	G->e=e; 
} 

void DestroyGraph(AdjGraph* &G)
{
	ArcNode* pre;
	ArcNode* p;
	for(int i=0;i<G->n;i++)
	{
		pre=G->adjlist[i].firstarc;
		if(pre!=NULL)
		{
			p=pre->nextarc;
			while(p!=NULL)
			{
				free(pre);
				pre=p;
				p=p->nextarc;
			}
			free(pre);
		}
	}
	free(G);
} 
 
void DispGraph(AdjGraph* G)
{
	ArcNode* p;
	for(int i=0;i<G->n;i++)
	{
		p=G->adjlist[i].firstarc;
		cout<<"顶点"<<i<<"可到达的边为：";
		while(p!=NULL)
		{
			cout<<p->adjvex<<"["<<p->weight<<"]"<<" ";
			p=p->nextarc;
		}
		cout<<endl;
	}
}

void FindPath(AdjGraph* G,int v1,int v2,int path[Maxsize],int length,int t)
{
	ArcNode* p;
	int w;
	path[t]=v1;
	t++;
	visited[v1]=1;
	if(v1==v2&&t>0)
	{
		cout<<"路径长度："<<length<<"  路径为：";
		for(int i=0;i<t-1;i++)
		{
			cout<<path[i]<<"->";
		}
		cout<<path[t-1]<<endl;
	}
	//DFS
	p=G->adjlist[v1].firstarc;
	while(p!=NULL)
	{
		w=p->adjvex;
		if(visited[w]==0)
		{
			FindPath(G,w,v2,path,length+p->weight,t);
		}
		p=p->nextarc;
	}
	visited[v1]=0;
}
