/********
2021.12.8  16:13	 
数据结构作业四 第六题
6. 对于给定的含有 n 元素的无序数据序列（所有元素的关键字不相同），利用快速排序方法求这个序列中第 k（1≤k≤n）小元素的关键字，并分析所设计算法的最好和平均时间复杂度。
*********/
#include <bits/stdc++.h>
using namespace std;
#define MaxSize 100

int QSortToFind(int t[MaxSize],int p,int q,int k);//找到第k小的元素 

int main()
{
	cout<<"对于给定的含有 n 元素的无序数据序列（所有元素的关键字不相同），利用快速排序方法求这个序列中第 k（1≤k≤n）小元素的关键字" <<endl<<endl;
	cout<<"请输入n:";
	int n;
	cin>>n;
	int t[n];//用于改变数据位置的数组 
	cout<<endl<<"请输入"<<n<<"个整形数据："<<endl;
	
	for(int i=0;i<n;i++)
	{
		cin>>t[i];
	}
	
	cout<<"请输入k：";
	int k;
	cin>>k;
	cout<<endl;

	cout<<"第"<<k<<"小的元素值为"<<QSortToFind(t,0,n-1,k)<<endl;
	
	return 0;
} 


int QSortToFind(int t[MaxSize],int p,int q,int k)
{
	int i=p;
	int j=q;
	int temp=t[i];
	//区间中只含有一个元素的情况
	if(p==q&&p==k-1)
	{
		return t[i];
	} 
	//区间中不止一个元素的情况
	else if(p<q)
	{
		while(i<j)
		{
			while(i<j&&t[j]>=temp)//从右往左找到一个小于基准的值放到左侧 
			{
				j--;
			}
			t[i]=t[j];
			while(i<j&&t[i]<=temp)//从左往右找到一个大于基准的值放到右侧 
			{
				i++;
			}
			t[j]=t[i];
		}
		t[i]=temp;
		//此时t[i]左侧至少有i个小于t[i]的元素 
		if(i==k-1)
		{
			return t[i];
		}
		else if(i>k-1)
		{
			return QSortToFind(t,p,i-1,k);
		}
		else
		{
			return QSortToFind(t,i+1,q,k);
		}	
	}
	//发生错误 
	else
	{
		return -1;
	}
}

//测试数据： 10 	3 9 1 17 11 5 7 19 13 15 
//测试数据： 20		690 792 379 597 353 67 365 41 424 350 930 600 12 739 985 119 410 603 234 401
