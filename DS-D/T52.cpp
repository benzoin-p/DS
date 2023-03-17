/********
2021.12.1  2:55	 
数据结构实验 第五题第二问 
*********/
#include <bits/stdc++.h>
using namespace std;
#define MaxSize 1000000
int t[MaxSize];//用于改变数据位置的数组 
int a[MaxSize];//用于保存原始数据位置的数组  

void renew(int t[],int a[],int n);//恢复数据顺序 
void InsertSort(int t[],int n);//直接插入排序 
void BinInsertSort(int t[],int n);//折半插入排序 
void ShellSort(int t[],int n);//希尔排序 
void BubbleSort(int t[],int n);//冒泡排序 
void QSort(int t[],int p,int q);//快速排序的递归过程 
void QuickSort(int t[],int p,int q);//快速排序 
void Merge(int t[],int low,int mid,int high);//归并两个有序表 
void MSort(int t[],int low,int high);//归并排序的递归过程 
void MergeSort(int t[],int low,int high);//二路归并排序 


int main()
{
	cout<<"请输入数据的规模n："<<endl<<"A 1万 B 10万 C 100万"<<endl;
	char nn; 
	cin>>nn;
	cout<<endl;
	int n;
	if(nn=='A')
	{
		n=10000;
		freopen("test1.txt","r",stdin);
	}
	else if(nn=='B')
	{
		n=100000;
		freopen("test2.txt","r",stdin);
	}
	else if(nn=='C')
	{ 
		n=1000000;
		freopen("test3.txt","r",stdin);		
	}
	else
	{
		cout<<"输入数据错误";
		return 0; 
	}

	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		t[i]=a[i];
	}
	fclose(stdin);
	
	InsertSort(t,n);
	renew(t,a,n);
	
	BinInsertSort(t,n);
	renew(t,a,n);	
	
	ShellSort(t,n);
	renew(t,a,n);
	
	BubbleSort(t,n);
	renew(t,a,n);
	
	QuickSort(t,0,n-1);
	renew(t,a,n);
	
	MergeSort(t,0,n-1);
	renew(t,a,n);	
	
	return 0;
} 

void renew(int t[],int a[],int n)
{
	for(int i=0;i<n;i++)
		{
			t[i]=a[i];
		}
}

void InsertSort(int t[],int n)
{
	double starttime= clock();
	int temp;
	int j;//j用来确定插入的位置
	for(int i=1;i<n;i++)
	{
		double nowtime=clock();
		if((double)(nowtime-starttime)/CLK_TCK>600.0)
		{
			cout<<"直接插入排序超过十分钟"<<endl;
			return; 
		}		
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
	double endtime= clock();
	cout<<"以下是直接插入排序的时间："<<(double)(endtime-starttime)/CLK_TCK<<"s"<<endl; 
}

void BinInsertSort(int t[],int n)
{
	double starttime= clock();
	int temp;
	int j;//j用来确定插入的位置
	int low,high,mid;
	for(int i=1;i<n;i++)
	{
		double nowtime=clock();
		if((double)(nowtime-starttime)/CLK_TCK>600.0)
		{
			cout<<"二分插入排序超过十分钟"<<endl;
			return; 
		}
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
	double endtime= clock();
	cout<<"以下是二分插入排序的时间："<<(double)(endtime-starttime)/CLK_TCK<<"s"<<endl; 	
}

void ShellSort(int t[],int n)
{
	double starttime= clock();
	int temp;
	int j;
	//采取d[1]=n/2，d[i+1]=d[i]/2 
	for(int d=n/2;d>=1;d/=2)
	{
		double nowtime=clock();
		if((double)(nowtime-starttime)/CLK_TCK>600.0)
		{
			cout<<"希尔排序超过十分钟"<<endl;
			return; 
		}		
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
	double endtime= clock();
	cout<<"以下是希尔排序的时间："<<(double)(endtime-starttime)/CLK_TCK<<"s"<<endl; 	
}

void BubbleSort(int t[],int n)
{
	double starttime= clock();
	bool exchange;
	for(int i=n-1;i>0;i--)
	{
		double nowtime=clock();
		if((double)(nowtime-starttime)/CLK_TCK>600.0)
		{
			cout<<"冒泡排序超过十分钟"<<endl;
			return; 
		}		
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
			double endtime= clock();
			cout<<"以下是冒泡排序的时间："<<(double)(endtime-starttime)/CLK_TCK<<"s"<<endl; 	
			return;
		} 
	}
	double endtime= clock();
	cout<<"以下是冒泡排序的时间："<<(double)(endtime-starttime)/CLK_TCK<<"s"<<endl; 	 	
}

void QSort(int t[],int p,int q)
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
void QuickSort(int t[],int p,int q)
{
	double starttime= clock();
	QSort(t,p,q);
	double endtime= clock();
	cout<<"以下是快速排序的时间："<<(double)(endtime-starttime)/CLK_TCK<<"s"<<endl;			
} 

void Merge(int t[],int low,int mid,int high)
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
void MSort(int t[],int low,int high)
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
void MergeSort(int t[],int low,int high)
{
	double starttime= clock();
	MSort(t,low,high);
	double endtime= clock();
	cout<<"以下是归并排序的时间："<<(double)(endtime-starttime)/CLK_TCK<<"s"<<endl;		
} 
