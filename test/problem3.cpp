#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <string>
#include <time.h>
#include <algorithm>
#include <time.h>
#include <stack>

using namespace std;

//为了防止内存溢出，我将待排序的数组设为动态数组，并将其作为全局变量
vector<int> a;
vector<int> b;

void Merge2sortedSubArr(int p,int q,int r)
{
	//ofstream oFile;
	//oFile.open("test1.csv",ios::app); 
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

//计算标准差
double caculateBiase(double eachtime[],int n,double mean)
{
	double ssum = 0;
	for(int i = 0;i < n;++i)
	{
		ssum += (eachtime[i] - mean)*(eachtime[i] - mean);
	}
	return sqrt(ssum/(double)n);
}

//用于显示5次排序的运行时间和均值、方差
void display(double eachtime[],double mean,double biase)
{
	printf("5次运行时间分别为：");
	for(int i = 0;i < 5;++i)
	{
		printf("%f  ",eachtime[i]);
	}
	printf("\n");
	printf("均值为：%f\n",mean);
	printf("标准差为：%f\n\n",biase);
}

int main()
{
	double eachtime[5];  //用于分别记录同一种排序算法进行5次排序的运行时间
	double sum = 0;  //用于求解5次运行时间的平均值
	int number;     //表示排序的规模
	double alpha[4] = {0.05,0.10,0.5,1};     //表示5%M，10%M，50%M和M这四个档次
	int order = 0;
	
	//第一层循环，用于遍历排序个数为5%M，10%M，50%M和M这四个档次
	while(true)
	{
		number = 12000 * alpha[order++];     //冒泡排序10秒大约能排11800个数，这里取12000
		printf("排序个数是 :%d\n",number);

		srand((unsigned)time(NULL));
		for(int i = 0; i < number;i++ ) 
		{
			int temp = rand()%(2*number-0+1)+0;     //随机生成待排序的数组，为了避免数组中有大量重复的元素，我设定随机数的范围为0到2*number
			//a是待排序数组，b记录数组a排序前的状态，用于在数组a排序后恢复数组a
			a.push_back(temp);  
			b.push_back(temp);   
		}

		InsertSort(number);  //对数组a先行排序

		clock_t start = clock();
		//BubbleSort(number);
		//InsertSort(number);
		//quickSortNorecusive(a,0,number-1);
		//MergeSort(0,number-1);
		//HeapSort(number);
		clock_t end = clock();
	
		sum += ((double)end-(double)start)/CLOCKS_PER_SEC;
		eachtime[0] = ((double)end-(double)start)/CLOCKS_PER_SEC;  //第一次排序的运行时间
	
		int ccount = 4;
		int index = 1;
		//第二层循环，用于计算后四次排序的运行时间
		while(ccount--)
		{
			
			start = clock();
			//BubbleSort(number);
			//InsertSort(number);
			//quickSortNorecusive(a,0,number-1);
			//MergeSort(0,number-1);
			//HeapSort(number);

			end = clock();
			
			sum += ((double)end-(double)start)/CLOCKS_PER_SEC;
			eachtime[index++] = ((double)end-(double)start)/CLOCKS_PER_SEC;  //计算第一次排序之后四次排序的运行时间

		}
		a.clear();
		b.clear();
		sum /= 5;  //计算均值
		double biase = caculateBiase(eachtime,5,sum);   //计算标准差
	
		display(eachtime,sum,biase);   //将5次排序的运行时间和这5次排序的均值、标准差打印到屏幕上
		
		if(order == 4) //当5%M，10%M，50%M和M均运行完成时，跳出循环
			break;
	}
	return 0;
}