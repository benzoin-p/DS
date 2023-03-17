/********
2021.10.5  13:47
数据结构作业一 栈和队列 第二题 
2. 假设表达式中允许包含圆括号、方括号和大括号 3 种括号，编写一个算法判断
表达式中的括号是否正确配对。
*********/
#include <iostream>
#include <string.h>
using namespace std;
#define MaxSize 105

typedef struct
{
	char data[MaxSize];
	int top;
}Stack;

void InitializeStack(Stack*& S);
void DestroyStack(Stack*& S);
void Push(Stack*& S,char a);
void Pop(Stack*& S);
bool isStackEmpty(Stack*& S);
void getTop(Stack* S,char& a);
void StringInput(Stack*& S);

int main()
{
	Stack *S;
	InitializeStack(S);
	StringInput(S);
	DestroyStack(S);
	return 0;
} 

void InitializeStack(Stack*& S)
{
	S=(Stack*)malloc (sizeof(Stack));
	S->top=-1;
}

void DestroyStack(Stack*& S)
{
	free(S);
}

void Push(Stack*& S,char a)
{
	if(S->top==MaxSize-1)
	{
		return;
	}
	S->top++;
	S->data[S->top]=a; 
}

void Pop(Stack*& S)
{
	if(S->top==-1)
	{
		return;
	}
	S->top--;
}

bool isStackEmpty(Stack*& S)
{
	return (S->top==-1);
}

void getTop(Stack* S,char& a)
{
	if(S->top==-1)
	{
		return;
	}
	a=S->data[S->top];
}

void StringInput(Stack*& S)
{
	cout<<"请输入括号字符序列："; 
	char temp;
	while(cin>>temp)
	{	
		if(temp=='('||temp=='['||temp=='{')
		{
			Push(S,temp);
		}
		else if(temp==')'||temp==']'||temp=='}')
		{
			char t='\0';
			getTop(S,t);
			if((t=='('&&temp==')')||(t=='['&&temp==']')||(t=='{'&&temp=='}'))
			{
			Pop(S);
			}
			else
			{
				cout<<"括号未正确配对";
				return;
			}
		}	
	}
	if(isStackEmpty(S))
	{
		cout<<"括号正确配对";
	}
	else
	{
	cout<<"括号未正确配对";
	}
}
