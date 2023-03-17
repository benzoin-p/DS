/********
2021.10.7  3：19 
2. 采用顺序结构存储串，设计一个实现串通配符匹配的算法 pattern_index(),其中的通配符只有‘?’，它可以和任何一个字符匹配成功。
*********/

#include <iostream>
#include <string.h>
using namespace std;
#define MaxSize 105

typedef struct
{
	int length;
	char data[MaxSize];
}SqString;

void InitializString(SqString& S);
void StringAssign(SqString& S,string str);
int getStringLength(SqString S);
int pattern_index(SqString t,SqString s);

int main()
{
	SqString s,t;
	string ss,tt;
	InitializString(s);
	InitializString(t);
	cout<<"请输入目标字符串s：" ; 
	getline(cin,ss); //避免输入空格导致cin无法读入模式串 
	StringAssign(s,ss);	
	cout<<"请输入模式字符串t，其中'?'为通配符：" ;
	cin>>tt; 
	StringAssign(t,tt);
	int u=pattern_index(t,s);
	cout<<u;
	return 0;
}

void InitializString(SqString& S)
{
	S.length=0;
} 

void StringAssign(SqString& S,string str)
{
	S.length=str.length();
	for(int i=0;i<S.length;i++)
	{
		S.data[i]=str[i];
	}
}
int getStringLength(SqString S)
{
	return S.length;
}

int pattern_index(SqString t,SqString s)//暴力匹配 
{
	int p=0;//计数器 
	for(int i=0;i<getStringLength(s);i++)
	{
		int k=i;
		for(int j=0;j<getStringLength(t);j++)
		{
			if(t.data[j]=='?'||s.data[k]==t.data[j])
			{
				k++;
				if(j==getStringLength(t)-1)//目标串的子串与模式串匹配 
				{
					p++;									
				}
			}
			else
			{
				break;
			}
		}
	}
	return p;
}
