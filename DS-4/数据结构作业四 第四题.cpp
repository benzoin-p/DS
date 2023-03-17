/********
2021.12.8  15:48
数据结构作业四 第四题 
4. 设计一个算法，判断给定的二叉树是否是二叉排序树。假设二叉树中结点关键字均为正
整数且均不相同。
*********/
#include <iostream>
#include <cstring>
using namespace std;
#define MaxSize 105

typedef struct node
{
	int data;
	node* leftchild;
	node* rightchild;
}BTree;

typedef struct 
{
	int front,rear;
	node* data[MaxSize];
}SqQueue;

void CreatBTree(BTree* &b,int* a,int& j); 
void DestroyBTree(BTree* &b);
void DispBTreeChildren(BTree* b);
void LDR(BTree* b,int* c,int &i);//中序遍历 
bool isSortBTree(BTree* b);//判断是否为二叉排序树 

int main()
{
	cout<<"设计一个算法，判断给定的二叉树是否是二叉排序树。假设二叉树中结点关键字均为正整数且均不相同。"<<endl<<endl;
	cout<<"请按前序序列输入正整数结点值以构建二叉树，其中空结点用-1表示,0表示输入结束："<<endl;
	int temp;
	int a[MaxSize];
	for(int i=0;i<MaxSize;i++)
	{
		a[i]=0;
	}
	int i=0;
	while(cin>>temp)
	{
		a[i]=temp;
		i++;
	}
	//cout<<"已成功进入数组"<<endl;
	BTree* b; 
	int j=0;
	CreatBTree(b,a,j);
	//cout<<"二叉树创建已完成";
	//DispBTreeChildren(b);
	

	if(isSortBTree(b)==true)
	{
		cout<<"输入为二叉排序树"<<endl; 
	}
	else
	{
		cout<<"输入不为二叉排序树"<<endl;
	}

	DestroyBTree(b);
	return 0;
}


void CreatBTree(BTree* &b,int* a,int &j)
{
	int i=a[j];
	if(i==-1||i==0)
	{
		j++; 
		return;
	}
	else
	{
		b=(BTree*)malloc(sizeof(BTree));
		b->data=i;
		b->leftchild=b->rightchild=NULL;
		j++;
		//cout<<b->data<<"进入"<<endl;
		CreatBTree(b->leftchild,a,j);
		//cout<<b->data<<"左进入"<<endl;
		CreatBTree(b->rightchild,a,j);	
		//cout<<b->data<<"右进入"<<endl;		
	}

	//cout<<"二叉树构建完成" ;
}

void DestroyBTree(BTree* &b)
{
	if(b==NULL)
	{
		return;
	}
	else
	{
		DestroyBTree(b->leftchild);
		DestroyBTree(b->rightchild);
		free(b);
		return ;
	}
}

void DispBTreeChildren(BTree* b)
{
	if(b!=NULL)
	{
		cout<<b->data<<" ";
		if(b->leftchild!=NULL||b->rightchild!=NULL)
		{
			DispBTreeChildren(b->leftchild);
			DispBTreeChildren(b->rightchild);
		}
	}
	return;
}

void LDR(BTree* b,int* c,int &i)
{
	if(b!=NULL)
	{
		if(b->leftchild!=NULL)
		{
			LDR(b->leftchild,c,i);
		}
		c[i]=b->data;
		//cout<<c[i]<<" "; 
		i++;
		if(b->rightchild!=NULL)
		{
			LDR(b->rightchild,c,i);
		}		
	}
} 

bool isSortBTree(BTree* b)
{
	int c[MaxSize];
	int i=0;
	LDR(b,c,i);
	//比较中序遍历结果是否递增 
	for(int j=0;j<i-1;j++)
	{
		if(c[j]>c[j+1])
		{
			return false;
		}
	}
	return true;
}

//测试数据1（二叉排序树）：5 3 -1 4 -1 -1 6 -1 8 7 -1 -1 9 0
//测试数据2（非二叉排序树）：3 1 2 -1 -1 -1 6 5 -1 -1 7 -1 -1 0 
//测试数据3（平衡二叉树）：4 2 1 -1 -1 3 -1 -1 6 5 -1 -1 7 -1 -1 0
