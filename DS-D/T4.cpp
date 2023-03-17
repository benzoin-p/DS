/********
2021.11.23  3:36 10:49	 
数据结构实验 第四题 
4. 给定一个序列如（12, 1, 23, 35, 21, 60，90, 60, 10, 15, 25, 56），题
目中序列的数据仅供参考，实验中数据可以自行生成，根据数据构造出哈夫曼树，
对哈夫曼树采用队列进行广度优先搜索。
*********/
#include <iostream>
using namespace std;
#define Maxsize 105

typedef struct node
{
	int data;
	node* leftchild;
	node* rightchild;
}BTree;

//以二叉树作为元素的线性表 
typedef struct
{
	BTree* data[Maxsize];
	int length;	
}Forest; 

void CreatBTree(BTree* &b,BTree* &LTree,BTree* &RTree); //通过子节点创建二叉树 
void DestroyBTree(BTree* &b);//销毁二叉树 
void TraversalBTreeByPreOrder(BTree* b);//递归先序遍历二叉树 
void CreatHTree(Forest* &forest);
void HeapSort(Forest* &forest);//堆排序 
void AdjustHeap(Forest* &forest,int i,int j);//调整堆使其符合堆结构 
void BFS(BTree* b);//广度优先搜索 

int main()
{
	//完成单节点森林的构建 
	int n; 
	cout<<"请输入序列中含有元素的个数n：";
	cin>>n;
	cout<<endl;
	cout<<"请输入"<<n<<"个整数:";
	Forest *forest;
	forest=(Forest*)malloc (sizeof(Forest));
	forest->length=n;
	for(int i=0;i<forest->length;i++)
	{
		int j;
		cin>>j;
		BTree* p;
		p=(BTree*)malloc (sizeof(BTree));
		p->data=j;
		p->leftchild=p->rightchild=NULL;
		forest->data[i]=p;
	}
	cout<<endl;
	
	//通过堆排序构建哈夫曼树 
	HeapSort(forest);
	while(forest->length>1)
	{
		CreatHTree(forest);
	}
	
	//输出哈夫曼树 
	BTree* HTree=forest->data[0];
	cout<<"按先序输出，哈夫曼树为："; 
	TraversalBTreeByPreOrder(HTree);
	cout<<endl<<endl;
	
	//广度优先搜索哈夫曼树 
	cout<<"采用广度优先搜索哈夫曼树，访问节点顺序为：";
	BFS(HTree);
	cout<<endl<<endl;
	
	DestroyBTree(HTree); 
	return 0;
} 

void CreatBTree(BTree* &b,BTree* &LTree,BTree* &RTree)
{
	b=(BTree*)malloc(sizeof(BTree));
	b->leftchild=LTree;
	b->rightchild=RTree;
	b->data=b->leftchild->data+b->rightchild->data;
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
		cout<<b->data;
		//cout<<"访问"<<b->data<<"中捏！"<<endl; 
		//先访问根节点，再访问左子树，再访问右子树 
		if(b->leftchild!=NULL)
		{
			cout<<'('; 
			TraversalBTreeByPreOrder(b->leftchild);
			if(b->rightchild!=NULL)
			{
				cout<<',';
				TraversalBTreeByPreOrder(b->rightchild);
				cout<<')';
			}
		}
	}
	return;
}

void CreatHTree(Forest* &forest)
{
	BTree* b;
	//选取最小的两棵树构成新树 
	CreatBTree(b,forest->data[0],forest->data[1]);
	forest->data[0]=b;
	forest->data[forest->length]=NULL;
	forest->length--;
	//当森林中仅有一棵树时，不再合成新树 
	if(forest->length>1)
	{
	forest->data[1]=forest->data[forest->length];
	HeapSort(forest);	
	}	
}

void HeapSort(Forest* &forest)
{
	//构建最大顶堆 
	for(int i=forest->length/2-1;i>=0;i--)
	{
		AdjustHeap(forest,i,forest->length);
	}
	//交换堆顶和堆尾
	for(int k=forest->length-1;k>0;k--)
	{ 
		BTree* temp;
		temp=forest->data[0];
		forest->data[0]=forest->data[k];
		forest->data[k]=temp;
		AdjustHeap(forest,0,k);
	} 
		 
}


void AdjustHeap(Forest* &forest,int i,int k)
{
	//暂存将要交换的节点 
	BTree* t=forest->data[i];
	//从将要交换的左子节点开始比较 
	for(int j=2*i+1;j<k;j=j*2+1)
	{	
		//若右子节点小于左子节点则在右子节点中寻找大于将要交换节点的节点 
		if(j+1<k&&forest->data[j]->data<forest->data[j+1]->data)
		{
			j++;
		}
		//当子节点大于父节点时交换 
		if(forest->data[j]->data>t->data)
		{
			forest->data[i]=forest->data[j];
			i=j;
		} 
		else
		{
			break;
		}
	}
	forest->data[i]=t;
}

void BFS(BTree* b)
{
	BTree* p;
	BTree* SqQueue[Maxsize];
	int front=0;
	int rear=0;
	//根节点进队 
	if(b!=NULL)
	{
	rear=(rear+1)%Maxsize;
	SqQueue[rear]=b;	
	} 
	//当队不空时循环 
	while(front!=rear)
	{
		//队列头出队 
		front=(front+1)%Maxsize;
		p=SqQueue[front];
		cout<<p->data<<" ";
		//左子节点右子节点分别进队 
		if(p->leftchild!=NULL)
		{
			rear=(rear+1)%Maxsize;
			SqQueue[rear]=p->leftchild;			
		}
		if(p->rightchild!=NULL)
		{
			rear=(rear+1)%Maxsize;
			SqQueue[rear]=p->rightchild;
		}
	}
} 
//测试数据1：12			12 1 23 35 21 60 90 60 10 15 25 56
//测试数据2： 6		2 3 4 7 8 9
//测试数据3：5		4 5 8 6 9
