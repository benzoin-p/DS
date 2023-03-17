/********
2021.11.5  2:45
数据结构作业二 第二题 
2. 假设二叉树以二叉链存储，设计一个算法，判断一棵二叉树 b 是否为完全二叉树。
*********/
#include <iostream>
using namespace std;
#define MaxSize 105

typedef struct node
{
	char data;
	node* leftchild;
	node* rightchild;
}BTree;

typedef struct 
{
	int front,rear;
	node* data[MaxSize];
}SqQueue;

void CreatBTree(BTree* &b,char* str); 
void DestroyBTree(BTree* &b);
void DispBTreeChildren(BTree* b);
void InitializeQueue(SqQueue* &Q);
void EnQueue(SqQueue* &Q,node* node);
void DeQueue(SqQueue* &Q);
bool isCompeleteBTree(BTree* b);

int main()
{
	cout<<"假设二叉树以二叉链存储，设计一个算法，判断一棵二叉树 b 是否为完全二叉树"<<endl;
	cout<<"请输入结点值为字符的括号表示法字符串以构建二叉树：";
	char temp;
	char str[MaxSize];
	int i=0;
	while(cin>>temp)
	{
		str[i]=temp;
		i++;
	}
	str[i++]='\0';
	//cout<<"已成功进入数组"<<endl;
	BTree* b; 
	CreatBTree(b,str);
	//cout<<"二叉树创建已完成";
	//DispBTree(b);
	
	if(isCompeleteBTree(b)==true)
	{
		cout<<"b为完全二叉树"<<endl; 
	}
	else
	{
		cout<<"b不为完全二叉树"<<endl;
	}
	
	DestroyBTree(b);
	return 0;
}


void CreatBTree(BTree* &b,char* str)
{
	BTree *Stack[MaxSize]; 
	BTree *p;
	int top=-1;
	int k,j=0;
	char ch=str[j];
	b=NULL;
	while(ch!='\0')
	{
		switch(ch)
		{
			case '(':
				top++;
				Stack[top]=p;
				k=1;
				break;
			case ')':
				top--;
				break;
			case ',':
				k=2;
				break;
			default:
				p=(BTree*)malloc(sizeof(BTree));
				p->data=ch;
				p->leftchild=p->rightchild=NULL;
				if(b==NULL)
				{
					b=p;
					//cout<<"值为"<<p->data<<"的根节点创造完成"<<endl; 
				}
				else
				{
					switch(k)
					{
						case 1:
							Stack[top]->leftchild=p;
							//cout<<"值为"<<p->data<<"的左子节点创造完成"<<endl; 
							break;
						case 2:
							Stack[top]->rightchild=p;
							//cout<<"值为"<<p->data<<"的右子节点创造完成"<<endl; 
							break;
					}
				}	
		}
		j++;
		ch=str[j];
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

void InitializeQueue(SqQueue* &Q)
{
		Q=(SqQueue*)malloc (sizeof(SqQueue));
		Q->front=Q->rear=0;
}

void EnQueue(SqQueue* &Q,node* node)
{
	if((Q->rear+1)%MaxSize==Q->front)
	{
		return;
	}
	Q->rear=(Q->rear+1)%MaxSize;
	Q->data[Q->rear]=node;
	//cout<<"现在队首为"<< Q->front<<"捏！"<<"现在队尾为"<< Q->rear<<"捏！"<<endl;
}

void DeQueue(SqQueue* &Q)
{
	
		if(Q->front==Q->rear)
		{
			return;
		}
		Q->front=(Q->front+1)%MaxSize;
		//cout<<"现在队首为"<< Q->front<<"捏！"<<"现在队尾为"<< Q->rear<<"捏！"<<endl;
}

bool isCompeleteBTree(BTree* b)
{
	if(b==NULL)
	{
		return true;
	}
	BTree* p;
	SqQueue* Q;
	InitializeQueue(Q);
	//cout<<"初始队列完成!"<<endl;
	EnQueue(Q,b);
	bool t=false;	
	while(Q->front!=Q->rear)
	{
		//cout<<"循环开始！"<<endl;
		p=Q->data[(Q->front+1)%MaxSize];
		//cout<<"出队！"<<endl;
		DeQueue(Q);
		if(p!=NULL)
		{
			//cout<<"p不为空！"<<endl; 
			if(t==true)
			{
				return false;
			}			
			EnQueue(Q,p->leftchild);
			//cout<<p->leftchild->data<<"已进队"<<endl; 
			EnQueue(Q,p->rightchild);
			//cout<<p->rightchild->data<<"已进队"<<endl;
		}
		else
		{
			//cout<<"t为真！"<<endl; 
			t=true;		
		}
	}
	return true;
}

//测试数据1（非完全二叉树）：P(r(o(p,h(,e)),s(y)),O(N,E))
//测试数据2（完全二叉树）： S(c(a(r,l),e(t,W)),i(n(g),s))
//测试数据3（满二叉树）：O(s(h(a,m),a(S,c)),r(a(m,b),l(e,!)) 
//测试数据4（空二叉树）： 
