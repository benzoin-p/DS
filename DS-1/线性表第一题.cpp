/********
2021.10.4  14:06
数据结构作业一 线性表第一题 
1.设计一个算法， 将一个带头结点的数据域依次为 a 1 , a 2 , …, a n （n>=3）的单链表的所有节点逆置，即第一个节点的数据域变为 a n , 第二个节点的数据域变为a n-1 , … , 尾节点的数据域变为 a 1 .
*********/

#include <iostream>
using namespace std;

typedef struct LNode
{
	LNode* next;
	int data;
}LinkNode;

void InitializeList(LinkNode*& L);//初始化表 
void DestroyList(LinkNode*& L);//销毁表 
void CreateListFromRear(LinkNode*& L,int n,int a[]);//建表 
void DispList(LinkNode* L,int n);//输出表 
void ReverseList(LinkNode*& L);//逆置表中元素 

int main()
{
	LinkNode* L;
	InitializeList(L);
	cout<<"请输入链表的长度：";
	int n;
	cin>>n;
	int a[n-1];
	cout<<"请输入链表的"<<n<<"个元素：";
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	CreateListFromRear(L,n,a);
	cout<<"输入的元素为：";
	DispList(L,n);
	ReverseList(L);
	cout<<"逆置后表中的元素为：";
	DispList(L,n);
	DestroyList(L);
	return 0;
}

void ReverseList(LinkNode*& L)
{
	LinkNode* p=L->next;
	LinkNode* q;
	L->next=NULL;
	while(p!=NULL)
	{
		q=p->next;
		p->next=L->next;
		L->next=p;
		p=q;
	}

}

void InitializeList(LinkNode*& L)
	{
		L=(LinkNode*)malloc (sizeof(LinkNode));
		L->next=NULL;
	}
	
void DestroyList(LinkNode*& L)
{
	LinkNode* pre=L;
	LinkNode* p=L->next;
	while(p!=NULL)
	{
		free(pre);
		pre=p;
		p=pre->next;
	}
	free(pre);
}

void CreateListFromRear(LinkNode*& L,int n,int a[])
{
		LinkNode* r=L;
		LinkNode* s;
		for(int i=0;i<n;i++)
			{
				s=(LinkNode*)malloc (sizeof(LinkNode));
				s->data=a[i];
				r->next=s;
				r=s;	
			}
			r->next=NULL;
}

void DispList(LinkNode* L,int n)
{
	LinkNode* t;
		t=L->next;
		for(int i=0;i<n;i++)
		{
			cout<<t->data<<" ";
			t=t->next;
		}
		cout<<endl;
} 
