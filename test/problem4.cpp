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
#include <fstream>

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

//用于显示5次排序的运行时间和均值、方差，并写入到文件中
void display(double eachtime[],double mean,double biase,int number)
{
	ofstream oFile;
	oFile.open("problem4.csv",ios::app);

	printf("5次运行时间分别为：");
	oFile<<"5次运行时间分别为："<<endl;
	
	for(int i = 0;i < 5;++i)
	{
		printf("%f  ",eachtime[i]);
		oFile<<eachtime[i]<<",";
	}
	printf("\n");

	printf("均值为：%f\n",mean);
	printf("标准差为：%f\n\n",biase);
	oFile<<biase<<","<<mean<<endl;
	oFile.close();
}

int main()
{
	double eachtime[5];  //用于分别记录同一种排序算法进行5次排序的运行时间
	double sum = 0;   //用于求解5次运行时间的平均值
	int number;    //表示排序的规模
	double alpha[4] = {0.05,0.10,0.5,1};    //表示5%M，10%M，50%M和M这四个档次
	int order = 0;
	
	
	//第一层循环，用于遍历排序个数为5%M，10%M，50%M和M这四个档次
	while(true)
	{
		number = 12000 * alpha[order++];   

		ofstream oFile;
		oFile.open("problem4.csv",ios::app);
		printf("排序个数是 :%d\n",number);
		oFile<<number<<endl;
		oFile.close();

		srand((unsigned)time(NULL));
		for(int i = 0; i < number;i++ ) 
		{
			int temp = rand()%(2*number-0+1)+0;          //随机数的范围是0到2*number
			a.push_back(temp);
			b.push_back(temp);
		}

		//为了针对同一组数据利用5种算法进行排序，用for循环遍历5种排序算法
		for(int ll = 0;ll < 5;++ll)
		{
			sum = 0;  //用于计算均值
			clock_t start;
			ofstream oFile;
			oFile.open("problem4.csv",ios::app);
			if(ll == 0)   //第一次循环用冒泡排序
			{
				start = clock();
				BubbleSort(number);
				printf("冒泡排序：\n");
				oFile<<"冒泡排序："<<endl;
			}
			else if(ll == 1)
			{
				start = clock();
				InsertSort(number);   //第二次循环用插入排序
				printf("插入排序：\n");
				oFile<<"插入排序："<<endl;
			}	
			else if(ll == 2)
			{
				start = clock();
				quickSortNorecusive(a,0,number-1);  //第三次循环用快速排序
				printf("快速排序：\n");
				oFile<<"快速排序："<<endl;
			}
			else if(ll == 3)
			{
				start = clock();
				MergeSort(0,number-1);   //第四次循环用合并排序
				printf("合并排序：\n");
				oFile<<"合并排序："<<endl;
			}
			else
			{
				start = clock();
				HeapSort(number);   //第五次循环用堆排序
				printf("堆排序：\n");
				oFile<<"堆排序："<<endl;
			}
			oFile.close();


			clock_t end = clock();
	
			sum += ((double)end-(double)start)/CLOCKS_PER_SEC;
			eachtime[0] = ((double)end-(double)start)/CLOCKS_PER_SEC;
	
			int ccount = 4;
			int index = 1;
			//这个while循环用于计算后四次排序的运行时间
			while(ccount--)
			{
				for(int i = 0;i < number;++i)
					a[i] = b[i];
			
				if(ll == 0)
				{
					start = clock();
					BubbleSort(number);  //第一次循环用冒泡排序
				}
				else if(ll == 1)
				{
					start = clock();
					InsertSort(number);   //第二次循环用插入排序
				}	
				else if(ll == 2)
				{
					start = clock();
					quickSortNorecusive(a,0,number-1);   //第三次循环用快速排序
				}
				else if(ll == 3)
				{
					start = clock();
					MergeSort(0,number-1);   //第四次循环用合并排序
				}
				else
				{
					start = clock();
					HeapSort(number);   //第五次循环用堆排序
				}

				end = clock();
			
				sum += ((double)end-(double)start)/CLOCKS_PER_SEC;
				eachtime[index++] = ((double)end-(double)start)/CLOCKS_PER_SEC;

			}
			
			sum /= 5;
			double biase = caculateBiase(eachtime,5,sum);
	
			display(eachtime,sum,biase,number);

			for(int i = 0;i < number;++i)
					a[i] = b[i];
		}
		a.clear();
		b.clear();
		if(order == 4)
			break;
	}
	return 0;
}