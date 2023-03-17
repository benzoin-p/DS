/********
2021.11.22  23:45
数据结构实验 第三题 
3. 已知一颗二叉树采用二叉链表存储，对该二叉树实现先序遍历的递归算法和
非递归算法。二叉树的宽度是指具有结点数最多的那一层上的结点总数，设计一
个算法，求该二叉树的宽度。
*********/
#include <iostream>
using namespace std;
#define Maxsize 105

typedef struct node
{
	char data;
	node* leftchild;
	node* rightchild;
}BTree;

void CreatBTree(BTree* &b,char* str); //创建二叉树 
void DestroyBTree(BTree* &b);//销毁二叉树 
void TraversalBTreeByPreOrder(BTree* b);//递归先序遍历二叉树 
void Stack_TraversalBTreeByPreOrder(BTree* b);//非递归先序遍历二叉树
void TraversalBTreeByPreOrder(BTree* b,int h,int width[]);//用于计算二叉树每层宽度的遍历 
int getBTreeWidth(BTree* b); //输出二叉树的宽度 

int main()
{
	BTree* b;
	cout<<"请输入结点值为字符的括号表示法字符串以构建二叉树：";
	char temp;
	char str[Maxsize];
	int i=0;
	while(cin>>temp)
	{
		str[i]=temp;
		i++;
	}
	str[i++]='\0';	
	CreatBTree(b,str);
	
	cout<<"通过递归方式先序遍历二叉树：";
	TraversalBTreeByPreOrder(b);
	cout<<endl;
	
	cout<<"通过栈先序遍历二叉树：";
	Stack_TraversalBTreeByPreOrder(b);
	cout<<endl;
	
	int Max=getBTreeWidth(b);
	cout<<"二叉树的宽度为"<<Max<<endl;
	 
	DestroyBTree(b);
	return 0;
} 

void CreatBTree(BTree* &b,char* str)
{
	BTree *Stack[Maxsize]; 
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

void TraversalBTreeByPreOrder(BTree* b)
{
	if(b!=NULL)
	{
		cout<<b->data<<" ";
		//cout<<"访问"<<b->data<<"中捏！"<<endl; 
		//先访问根节点，再访问左子树，再访问右子树 
		if(b->leftchild!=NULL||b->rightchild!=NULL)
		{
			TraversalBTreeByPreOrder(b->leftchild);
			TraversalBTreeByPreOrder(b->rightchild);
		}
	}
	return;
}

void Stack_TraversalBTreeByPreOrder(BTree* b)
{
	BTree* Stack[Maxsize];
	int top=-1;
	BTree* p;
	if(b!=NULL)
	{
		//初始化栈 
		top++;
		Stack[top]=b;
		//cout<<b->data<<"已入栈了捏！"<<endl;
		while(top!=-1)
		{
			//弹出栈顶元素 
			p=Stack[top];
			top--;
			cout<<p->data<<" ";
			//右子树先入栈，左子树再入栈 
			if(p->rightchild!=NULL)
			{
				top++;
				Stack[top]=p->rightchild;
				//cout<<p->rightchild->data<<"已入栈了捏！"<<endl;
			}
			if(p->leftchild!=NULL)
			{
				top++;
				Stack[top]=p->leftchild;
				//cout<<p->leftchild->data<<"已入栈了捏！"<<endl;
			}
		}	
	} 
	return;
} 
	 
void TraversalBTreeByPreOrder(BTree* b,int h,int width[])
{
	if(b!=NULL)
	{
		width[h]++;
		if(b->leftchild!=NULL||b->rightchild!=NULL)
		{
			h++;
			//cout<<"h为"<<h<<endl;
			TraversalBTreeByPreOrder(b->leftchild,h,width);
			TraversalBTreeByPreOrder(b->rightchild,h,width);
		}
	}
	return;	
}
	 
int getBTreeWidth(BTree* b)
{
	int width[Maxsize];
	for(int i=0;i<Maxsize;i++)
		{
			width[i]=0;
		}
	if(b==NULL)
	{
		return 0;
	}
	else
	{
		int h=0;
		TraversalBTreeByPreOrder(b,h,width);
		//查找最大值 
		int Max=0;
		for(int i=0;i<Maxsize;i++)
		{
			if(width[i]>Max)
			{ 
				Max=width[i];
			}
		}
		return Max;
	}
}


//测试数据1（非完全二叉树）：P(r(o(p,h(,e)),s(y)),O(N,E))
//测试数据2（完全二叉树）： S(c(a(r,l),e(t,W)),i(n(g),s))
//测试数据3（满二叉树）：O(s(h(a,m),a(S,c)),r(a(m,b),l(e,!)) 
//测试数据4（空二叉树）： 
