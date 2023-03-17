/********
2021.10.4  14:54
数据结构作业一 线性表第二题 第二问 
2. 用带头结点的单链表表示整数集合， 完成以下算法并分析时间复杂度：
2）假设集合中的元素按递增排列，设计一个高效算法求两个 集合 A 和 B 的差运算， 即 C=A-B， 要求算法的空间复杂度为 O(1), 并释放单链表 A 和 B 中不需要的节点。
时间复杂度为O(n) 
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
void DispList(LinkNode* L,int n);
void DispList(LinkNode* L);//输出表 
void Subtract(LinkNode*& L1,LinkNode*& L2);//当L1,L2为数据域递增的表时求L1,L2差运算 

int main()
{
	LinkNode* L1;
	LinkNode* L2;
	InitializeList(L1);
	InitializeList(L2);
	cout<<"请输入链表L1的长度：";
	int n1;
	cin>>n1;
	cout<<"请输入链表L2的长度：";
	int n2;
	cin>>n2;
	int a1[n1-1];
	int a2[n2-1];
	cout<<"请按递增顺序依次输入链表L1的"<<n1<<"个互不相同的元素：";
	for(int i=0;i<n1;i++)
	{
		cin>>a1[i];
	}
	cout<<"请按递增顺序依次输入链表L2的"<<n2<<"个互不相同的元素：";
	for(int i=0;i<n2;i++)
	{			
		cin>>a2[i];
	}
	CreateListFromRear(L1,n1,a1);
	CreateListFromRear(L2,n2,a2);
	cout<<"输入的L1元素为：";
	DispList(L1,n1);
	cout<<"输入的L2元素为：";
	DispList(L2,n2);	
	Subtract(L1,L2);
	cout<<"作差L1-L2后表中的元素为：";
	DispList(L1);
	DestroyList(L1);
	DestroyList(L2);
	return 0;
}

void Subtract(LinkNode*& L1,LinkNode*& L2)
{
	LinkNode* p=L1->next;
	LinkNode* q=L2->next;
	LinkNode* r=L1;
	LinkNode* s=L2;
	bool unequal=true;
	while(p!=NULL)//遍历表L1 
	{
		unequal=true;
		while(q!=NULL)
		{
			if(q->data>p->data)
			{
				break;
			}
			if(q->data==p->data)//当表L1中某一节点的数据域与L2中某一节点数据域相同，删除L1,L2中节点 
			{
				r->next=p->next;
				s->next=q->next;
				free(p);
				free(q);
				unequal=false;
				break;
			}
			s=q;
			q=q->next;
		}
		if(unequal==true)
		{
			r=p;
			p=p->next;
		}
		else
		{
			p=r->next;
		}
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

void DispList(LinkNode* L)
{
	LinkNode* t;
		t=L->next;
		while(t!=NULL)
		{
			cout<<t->data<<" ";
			t=t->next;
		}
		cout<<endl;
} 
