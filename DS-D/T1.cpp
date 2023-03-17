/********
2021.11.18  1:49 
数据结构实验第一题 
1. 线性表：现有两个数组 A=[12, 1, 23, 35, 21, 60]，B=[90, 60, 10, 15,
25, 56]，根据数组 A 和 B 建立两个非递减有序单向链表，然后合并成一个非递
减链表。题目中数组 A 和 B 仅供参考，实验中需自行生成，验证不同数据输入情
况下结果是否正确。
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
void DispList(LinkNode* L,int n);//输出表 
void CreatListByAscendingOrder(LinkNode*& L,int a[],int n);//按升序建表 
void CombineTwoListByAscendingOrder(LinkNode* &L1,LinkNode* &L2,LinkNode* &L,int n1,int n2); //合成升序表 

int main()
{
	//输入并创建链表L1 
	cout<<"请输入数组L1中元素的个数:";
	int n1;
	cin>>n1;
	cout<<endl;
	cout<<"请输入"<<n1<<"个整数作为数组L1元素:";
	int a1[n1];
	for(int i=0;i<n1;i++)
	{
		cin>>a1[i];
	} 
	cout<<endl;
	LinkNode* L1;
	InitializeList(L1);
	CreatListByAscendingOrder(L1,a1,n1);
	
	//输入并创建链表L2
	cout<<"请输入数组L2中元素的个数:";
	int n2;
	cin>>n2;
	cout<<endl;
	cout<<"请输入"<<n2<<"个整数作为数组L2元素:";
	int a2[n2];
	for(int i=0;i<n2;i++)
	{
		cin>>a2[i];
	}
	cout<<endl;
	LinkNode* L2;	
	CreatListByAscendingOrder(L2,a2,n2);
	
	//输出非递减的链表 
	cout<<"链表L1中的元素分别为："; 
	DispList(L1,n1);
	cout<<endl;
	cout<<"链表L2中的元素分别为："; 
	DispList(L2,n2);
	cout<<endl;	
	
	//创建与输出合并后的链表 
	LinkNode* L;
	InitializeList(L);
	CombineTwoListByAscendingOrder(L1,L2,L,n1,n2);
	cout<<"合成链表L中的元素分别为："; 
	DispList(L,n1+n2);
	
	
	DestroyList(L1);
	DestroyList(L2);
	return 0;
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

void CreatListByAscendingOrder(LinkNode*& L,int a[],int n)
{
	int i=0;
	int k;
	LinkNode* r=L;
	LinkNode* s;
	while(i<n)
	{
		//找到数组中最小的元素 
		int min = 0x7fffffff;
		for(int j=0;j<n;j++)
		{
			if(min>a[j])
			{
				min=a[j];
				k=j;
			}
		}
		//尾插法建表 
		s=(LinkNode*)malloc (sizeof(LinkNode));
		s->data=min;
		r->next=s;
		r=s;
		a[k]= 0x7fffffff;//排除已经进入链表的元素 
		i++;
	}
	r->next=NULL;	
} 

void CombineTwoListByAscendingOrder(LinkNode* &L1,LinkNode* &L2,LinkNode* &L,int n1,int n2) 
{
	LinkNode* s1=L1->next;
	LinkNode* s2=L2->next;
	LinkNode* r=L;
	LinkNode* s;
	int i=0; 
	//用以标记是否链表已读完，true表示未读完 
	bool scanL1=true;
	bool scanL2=true;
	
	while(i<n1+n2)
	{
		//当s1指向的数据小于s2，且L1可未读完，或L2已经读完时选择这条分支 
		if((s1->data<s2->data&&scanL1)||!scanL2)
		{
			//cout<<"1" <<endl;
			s=(LinkNode*)malloc (sizeof(LinkNode));
			s->data=s1->data;
			//if(s1!=NULL) cout<<s1->data<<"进入"<<endl;
			r->next=s;
			r=s;
			i++;
			if(s1->next!=NULL) 
			{
				s1=s1->next;
				//cout<<"s1为"<<s1->data<<endl; 
			}
			else
			{
				scanL1=false;
			}
		}
		else if((s1->data>=s2->data&&scanL2)||!scanL1)
		{
			//cout<<"2" <<endl;
			s=(LinkNode*)malloc (sizeof(LinkNode));
			s->data=s2->data;
			//if(s2!=NULL) cout<<s2->data<<"进入"<<endl;
			r->next=s;
			r=s;
			i++;
			if(s2->next!=NULL) 
			{
				s2=s2->next;
			}
			else
			{
				scanL2=false;
			}		
		}
	}
} 
