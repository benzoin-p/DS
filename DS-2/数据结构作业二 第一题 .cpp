/********
2021.11.2  13:06
数据结构作业二 第一题 
1. 假设二叉树中每个结点值为单个字符，采用二叉链存储结构存储。设计算法分别求解:
(1) 二叉树 b中最小值的结点值。
(2) 二叉树 b中第 k 层上叶子结点个数。
(3) 采用先序遍历方法输出二叉树 b 中值为 x 的结点的子孙，假设值为 x 的结点唯一。
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


void CreatBTree(BTree* &b,char* str); 
void DestroyBTree(BTree* &b);
void DispBTreeChildren(BTree* b);
void FindMinBNodeByPreOrder(BTree* b,char &min);
void FindLeafNodeNumber(BTree* b,int k,int h,int &n); 
void DispChildrenByPreOrder(BTree* b,char x);

int main()
{
	cout<<"假设二叉树中每个结点值为单个字符，采用二叉链存储结构存储。设计算法分别求解:"<<endl;
	cout<<"(1) 二叉树 b 中最小值的结点值"<<endl<<"(2) 二叉树 b 中第 k 层上叶子结点个数"<<endl;
	cout<<"(3) 采用先序遍历方法输出二叉树 b 中值为 x 的结点的子孙，假设值为 x 的结点唯一"<<endl;
	
	int k;
	cout<<endl<<"请输入（2）中的层次k:";
	cin>>k;
	cout<<endl;
	
	char x;
	cout<<"请输入（3）中的值x:";
	cin>>x;
	cout<<endl;
	
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
	//cout<<"已成功进入数组"<<endl;
	BTree* b; 
	CreatBTree(b,str);
	//cout<<"二叉树创建已完成";
	//DispBTree(b);
	
	//第一问 
	char min='z';
	FindMinBNodeByPreOrder(b,min);
	cout<<endl<<"（1）最小值的结点值为："<<min<<endl;
	
	//第二问 
	int n=0,h=1;
	FindLeafNodeNumber(b,k,h,n);
	cout<<"（2）第"<<k<<"层的叶结点个数为："<<n<<endl; 
	
	//第三问
	cout<<"（3）值为"<<x<<"的子孙为："; 
	DispChildrenByPreOrder(b,x); 
	
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

void FindMinBNodeByPreOrder(BTree* b,char &min)
{
	if(b!=NULL)
	{
		if(b->data<min)
		{
			min=b->data;
		}
		FindMinBNodeByPreOrder(b->leftchild,min);
		FindMinBNodeByPreOrder(b->rightchild,min);
	}
}

void FindLeafNodeNumber(BTree* b,int k,int h,int &n)
{
	if(b==NULL)
	{
		return;
	}
	else
	{
		if(h==k&&b->leftchild==NULL&&b->rightchild==NULL)
		{
			n++;
		}
		else if(h<k)
		{
			FindLeafNodeNumber(b->leftchild,k,h+1,n);
			FindLeafNodeNumber(b->rightchild,k,h+1,n);
		}
	}
	return;
}

void DispChildrenByPreOrder(BTree* b,char x)
{
	if(b!=NULL)
	{
		if(b->data==x)
		{
			DispBTreeChildren(b->leftchild);
			DispBTreeChildren(b->rightchild);
			return;
		}
		else
		{
			DispChildrenByPreOrder(b->leftchild,x);
			DispChildrenByPreOrder(b->rightchild,x);
		}
	}
}


//P(r(o(p,h(,e)),s(y)),O(N,E))
//S(c(a(r,l),e(t,W)),i(n(g),s))
