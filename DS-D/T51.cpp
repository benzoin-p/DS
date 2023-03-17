/********
2021.12.1  2:04	 
数据结构实验 第五题第一问 
排序算法：随机生成待排序数据，待排序数据个数分为 100，1 万，10 万，100
万，分别采用六种排序算法（直接插入排序，折半插入排序，希尔排序，冒泡排
序，快速排序，二路归并排序）进行排序。
*********/
#include <bits/stdc++.h>
using namespace std;
#define MaxSize 100

void renew(int t[MaxSize],int a[MaxSize]);//恢复数据顺序 
void InsertSort(int t[MaxSize],int n);//直接插入排序 
void BinInsertSort(int t[MaxSize],int n);//折半插入排序 
void ShellSort(int t[MaxSize],int n);//希尔排序 
void BubbleSort(int t[MaxSize],int n);//冒泡排序 
void QSort(int t[MaxSize],int p,int q);//快速排序的递归过程 
void QuickSort(int t[MaxSize],int p,int q);//快速排序 
void Merge(int t[MaxSize],int low,int mid,int high);//归并两个有序表 
void MSort(int t[MaxSize],int low,int high);//归并排序的递归过程 
void MergeSort(int t[MaxSize],int low,int high);//二路归并排序 


int main()
{
	freopen("test.txt","r",stdin);
	int t[MaxSize];//用于改变数据位置的数组 
	int a[MaxSize];//用于保存原始数据位置的数组 
	for(int i=0;i<MaxSize;i++)
	{
		cin>>a[i];
		t[i]=a[i];
	}
	int n=MaxSize;
	fclose(stdin);
	
	InsertSort(t,n);
	renew(t,a);
	
	BinInsertSort(t,n);
	renew(t,a);	
	
	ShellSort(t,n);
	renew(t,a);
	
	BubbleSort(t,n);
	renew(t,a);
	
	QuickSort(t,0,n-1);
	renew(t,a);
	
	MergeSort(t,0,n-1);
	renew(t,a);	
	
	return 0;
} 

void renew(int t[MaxSize],int a[MaxSize])
{
	for(int i=0;i<MaxSize;i++)
		{
			t[i]=a[i];
		}
}

void InsertSort(int t[MaxSize],int n)
{
	int temp;
	int j;//j用来确定插入的位置
	for(int i=1;i<n;i++)
	{
		//检测无序区的首值是否小于有序区的尾值
		if(t[i]<t[i-1])
		{
			temp=t[i];
			for(j=i-1;j>=0;j--) 
			{
				if(t[j]<=temp)
				{
					//t[j+1]=temp;
					break;
				}
				t[j+1]=t[j];
			}
			t[j+1]=temp;
		} 
	}
	cout<<"以下是直接插入排序的结果："<<endl; 
	for(int i=0;i<MaxSize;i++)
	{
		cout<<t[i]<<" ";
	}
	cout<<endl;
	cout<<endl;
}

void BinInsertSort(int t[MaxSize],int n)
{
	int temp;
	int j;//j用来确定插入的位置
	int low,high,mid;
	for(int i=1;i<n;i++)
	{
		//检测无序区的首值是否小于有序区的尾值
		if(t[i]<t[i-1])
		{
			temp=t[i];
			low=0;high=i-1;
			while(low<=high)
			{
				mid=(low+high)/2;
				if(temp<t[mid])
				{
					high=mid-1;
				}
				else
				{
					low=mid+1;
				}
			}
			for(j=i-1;j>=high+1;j--) 
			{
				t[j+1]=t[j];
			}
			t[high+1]=temp;
		} 
	}
	cout<<"以下是二分插入排序的结果："<<endl; 
	for(int i=0;i<MaxSize;i++)
	{
		cout<<t[i]<<" ";
	}
	cout<<endl;
	cout<<endl;
}

void ShellSort(int t[MaxSize],int n)
{
	int temp;
	int j;
	//采取d[1]=n/2，d[i+1]=d[i]/2 
	for(int d=n/2;d>=1;d/=2)
	{
		for(int i=d;i<n;i++)
		{
			//数据间隔为d的直接插入排序 
			temp=t[i];
			 for(j=i-d;j>=0;j-=d)
			 {
			 	if(temp>=t[j])
			 	{
				 	break;
				}
				t[j+d]=t[j];
			 }
			 t[j+d]=temp;
		}	
	}
	cout<<"以下是希尔排序的结果："<<endl; 
	for(int i=0;i<MaxSize;i++)
	{
		cout<<t[i]<<" ";
	}
	cout<<endl;
	cout<<endl;	
}

void BubbleSort(int t[MaxSize],int n)
{
	bool exchange;
	for(int i=n-1;i>0;i--)
	{
		exchange=false;
		for(int j=0;j<i;j++)
		{
			if(t[j]>t[j+1])
			{
				int temp=t[j];
				t[j]=t[j+1];
				t[j+1]=temp;
				exchange=true;
			}
		}
		if(!exchange)
		{
			cout<<"以下是冒泡排序的结果："<<endl; 
			for(int i=0;i<MaxSize;i++)
			{
				cout<<t[i]<<" ";
			}
			cout<<endl;
			cout<<endl;		
			return;
		} 
	}
	cout<<"以下是冒泡排序的结果："<<endl; 
	for(int i=0;i<MaxSize;i++)
	{
		cout<<t[i]<<" ";
	}
	cout<<endl;
	cout<<endl;		
}

void QSort(int t[MaxSize],int p,int q)
{
	int i=p;
	int j=q;
	int temp=t[i];
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
	if(p<q)
	{
		QSort(t,p,i-1);
		QSort(t,i+1,q);
	}
		
}
void QuickSort(int t[MaxSize],int p,int q)
{
	QSort(t,p,q);
	cout<<"以下是快速排序的结果："<<endl; 
	for(int i=0;i<MaxSize;i++)
	{
		cout<<t[i]<<" ";
	}
	cout<<endl;
	cout<<endl;		
} 

void Merge(int t[MaxSize],int low,int mid,int high)
{
	int* tt;
	int i=low;
	int j=mid+1;
	int k=0;
	tt=(int*)malloc ((high-low+1)*sizeof(int));
	while(i<=mid&&j<=high)
	{
		if(t[i]<t[j])
		{
			tt[k]=t[i];
			i++;
			k++;
		}
		else
		{
			tt[k]=t[j];
			j++;
			k++;
		}
	} 
	while(i<=mid)
	{
		tt[k]=t[i];
		i++;
		k++;
	}
	while(j<=high)
	{
		tt[k]=t[j];
		j++;
		k++;
	}
	//将tt复制到t中 
	for(int u=low;u<=high;u++)
	{
		t[u]=tt[u-low];
	}
	free(tt);
}
void MSort(int t[MaxSize],int low,int high)
{
	int mid;
	if(low<high)
	{
		mid=(low+high)/2;
		MSort(t,low,mid);
		MSort(t,mid+1,high);
		Merge(t,low,mid,high);
	}
}
void MergeSort(int t[MaxSize],int low,int high)
{
	MSort(t,low,high);
	cout<<"以下是归并排序的结果："<<endl; 
	for(int i=0;i<MaxSize;i++)
	{
		cout<<t[i]<<" ";
	}
	cout<<endl;
	cout<<endl;		
} 
