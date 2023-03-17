/********
2021.10.5  23:48
数据结构作业一 栈和队列 第一题 
1. 设从键盘输入一序列的字符 a 1 , a 2 , …, a n ， 设计一个算法实现这样的功能：若 a i 为数字字符，a i 进队；若 a i 为小写字母，将队首元素出队；若 a i 为其他字符，表示输入结束。要求使用环形队列。
*********/
#include <iostream>
using namespace std;
#define MaxSize 105

typedef struct
{
	int front,rear;
	int data[MaxSize];
}Queue;

void InitializeQueue(Queue*& Q);//初始化队列 
void DestroyQueue(Queue*& Q);//销毁队列 
void EnQueue(Queue*& Q,int a);//进队 
void DeQueue(Queue*& Q);//出队 
void DispQueue(Queue*& Q);//输出队中元素 
void StringInput(Queue*& Q);//判断输入序列进队条件的算法 

int main()
{
	Queue* Q;
	InitializeQueue(Q);
	StringInput(Q);
	DispQueue(Q);
	DestroyQueue(Q);
	return 0;
}

void InitializeQueue(Queue*& Q)
{
	Q=(Queue*)malloc (sizeof(Queue));
	Q->front=Q->rear=0;	
}

void DestroyQueue(Queue*& Q)
{
	free(Q);
}

void EnQueue(Queue*& Q,int a)
{
	if((Q->rear+1)%MaxSize==Q->front)
	{
		return;
	}
	Q->rear=(Q->rear+1)%MaxSize;
	Q->data[Q->rear]=a;
}

void DeQueue(Queue*& Q)
{
	if(Q->front==Q->rear)
	{
		return;
	}
	Q->front=(Q->front+1)%MaxSize;
}

void DispQueue(Queue*& Q)
{
	cout<<"目前队中的元素为："; 
	int count=(Q->rear-Q->front+MaxSize)%MaxSize;
	for(int i=1;i<=count;i++)
	{
		cout<<Q->data[(Q->front+i)%MaxSize]-'0'<<" ";
	}
	
}

void StringInput(Queue*& Q)
{
	cout<<"请输入字符序列：";
	for(int i=0;i<MaxSize;i++)
	{
		char temp;
		cin>>temp;
		if('0'<=temp&&temp<='9')
		{
			EnQueue(Q,temp);
		}
		else if('a'<=temp&&temp<='z')
		{
			DeQueue(Q);
		}
		else
		{
			break;
		}
	}
}











