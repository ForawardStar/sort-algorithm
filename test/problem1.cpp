#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <string>
#include <time.h>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <stack>

using namespace std;

vector<int> a;   //为了防止内存溢出，我将待排序的数组设为动态数组，并将其作为全局变量

void Merge2sortedSubArr(int p,int q,int r)
{
	
	int *b = new int[r + 1];
	
	int i = p,j = q + 1,k = p;
	while(i <= q&&j <= r)
	{
		if(a[i] <= a[j])
		{
			b[k++] = a[i++];
		}
		else
		{
			b[k++] = a[j++];
		}
			
	}
	if(i == q+1)
		for(;j <= r;++j)
		{
			b[k++] = a[j];
		}
	else
		for(;i <= q;++i)
		{
			b[k++] = a[i];
		}
	for(i = p;i <= r;++i)
	{
		a[i] = b[i];
	}
	
	delete b;
}

//合并排序
void MergeSort(int low,int high)
{
	if(low < high)
	{
		int mid = (low + high) / 2;

		MergeSort(low,mid);
		MergeSort(mid+1,high);
		Merge2sortedSubArr(low,mid,high);
	}
}

//冒泡排序
void BubbleSort(int n)
{
	for(int i = n - 1;i >= 1;--i)
	{
		bool hasswap = false;
		for(int j = 0;j <= i - 1;++j)
		{
			if(a[j] > a[j + 1])
			{
				swap(a[j],a[j+1]);
				hasswap = true;
			}
		}
		if(!hasswap)
			break;
	}
	
}

//插入排序
void InsertSort(int n)
{
	int x,j;
	for(int i = 1;i < n;++i)
	{
		x = a[i];
		j = i - 1;
		while(j >= 0&&a[j] > x)
		{
			a[j+1] = a[j];
			--j;
		}
		a[j+1] = x;
	}
}

int partitions(vector<int>& data,int l,int r)  
{  
    int x = data[r];    //基准  
    if(l >= r)  
        return l;  
    while(l < r){  
        while(l < r && data[l] < x){  
            l++;  
        }  
        if(l < r){  
            data[r] = data[l];  
            r--;  
        }  
        while(l < r && data[r] > x){  
            r--;  
        }  
        if(l < r){  
            data[l] = data[r];  
            l++;  
        }  
    }  
    data[l] = x;  
    return l;  
}  

//非递归的快速排序
void quickSortNorecusive(vector<int>& data,int l,int r)    
{  
    stack<int> st;  //定义了一个栈
    if(l < r)  
    {  
        int tmp = partitions(data,l,r);  
        if(tmp-1 > l)    //左边不止一个元素  
        {  
            st.push(tmp-1);  
            st.push(l);  
        }  
        if(tmp+1 < r)  
        {  
            st.push(r);  
            st.push(tmp+1);  
        }  
        while(!st.empty()){  
            int start = st.top();  
            st.pop();  
            int end = st.top();  
            st.pop();  
              
            int tmp = partitions(data,start,end);  
            if(tmp-1 > start)    //左边不止一个元素  
            {  
                st.push(tmp-1);  
                st.push(start);  
            }  
            if(tmp+1 < end)  
            {  
                st.push(end);  
                st.push(tmp+1);  
            }  
        }  
    }  
}  

void SiftDown(int n,int i)
{
	bool done = true;
	while(done&&(i = 2*i+1)< n)
	{
		if((i+1)<n&&a[i+1]>a[i])
		{
			i = i + 1;
		}

		if(a[(i-1)/2]<a[i])
		{
			swap(a[(i-1)/2],a[i]);
		}
		else
			done = false;
	}
	
}

void MakeHeap(int n)
{
	for(int i = n/2 - 1;i >= 0;--i)
	{
		SiftDown(n,i);
	}
}

//堆排序
void HeapSort(int n)
{
	MakeHeap(n);

	for(int i = n - 1;i > 0;--i)
	{
		swap(a[0],a[i]);
		SiftDown(i,0);
	}
}


int main()
{
	//12000
	int number = 600;           //number用于设定待排序元素的个数，我通过不断number的取值，寻找每个排序算法在不同时间能够排序的个数
	srand((unsigned)time(NULL));
	for(int i = 0; i < number;i++ ) 
		a.push_back(rand()%(2*number-0+1)+0);     //随机生成待排序的数组，为了避免数组中有大量重复的元素，我设定随机数的范围为0到2*number

	clock_t start = clock();   //开始时间

	//以下为5种排序算法

	//BubbleSort(number);
	//InsertSort(number);
	//quickSortNorecusive(a,0,number-1);
	//quickSortNorecusive(aa,0,number-1);
	//MergeSort(0,number-1);
	//HeapSort(number);

	clock_t end = clock();   //结束时间
	printf("%f\n",((double)(end-start))/CLOCKS_PER_SEC);
	a.clear();
	return 0;
}

