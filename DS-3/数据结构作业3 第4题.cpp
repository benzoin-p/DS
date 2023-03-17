/********
2021.11.28  14:03
数据结构作业三 第四题 
4. 假设一个连通图采用邻接表作为存储结构，试设计一个算法，判断其中是否存在经过顶点 v 的回路。
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
void FindCircurt(AdjGraph* G,int v1,int v2,int &d,bool &hasCircurt);


int main()
{
	cout<<"假设一个连通图采用邻接表作为存储结构，试设计一个算法，判断其中是否存在经过顶点 v 的回路。"<<endl<<endl;
	cout<<"请输入连通图的顶点数n:";
	int n;
	cin>>n;
	cout<<endl;
	cout<<"请输入连通图的边数e:";
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
	
	
	cout<<"请输入顶点v的编号：";
	int v;
	cin>>v;
	cout<<endl; 
	int d=-1;//路径长度
	bool hasCircurt=false;
	FindCircurt(G,v,v,d,hasCircurt);
	if(hasCircurt)
	{
		cout<<"存在经过顶点v的回路"; 
	}
	else
	{
		cout<<"不存在经过顶点v的回路";
	}
	 	
	 	
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


void FindCircurt(AdjGraph* G,int v1,int v2,int &d,bool &hasCircurt)
{
	ArcNode* p;
	int w;
	visited[v1]=1;
	d++;
	p=G->adjlist[v1].firstarc;
	while(p!=NULL)
	{
		//DFS
		w=p->adjvex;
		//cout<<"w为："<<w<<endl;
		//cout<<"visited["<<w<<"]为："<<visited[w]<<endl;
		//cout<<"d为："<<d<<endl;				
		if(visited[w]==0)
		{
			int u=d;//防止重复增加d 
			FindCircurt(G,w,v2,u,hasCircurt);
		}
		else if(d>1&&w==v2)//保证是回路而不是一条无向通路
		{
			//cout<<d<<endl<<w<<endl<<v2<<endl;
			hasCircurt=true;
			return;
		}
		p=p->nextarc; 
	}
}



