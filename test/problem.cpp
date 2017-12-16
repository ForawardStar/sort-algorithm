#include "problem.h"
#include <time.h>
#include <vector>
#include <stack>
#include <fstream>
#include <windows.h>

vector<int> a;

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



void generateRand(int sr,int number)
{
	srand(sr);
	for(int i = 0; i < number;i++ ) 
	{
		//随机生成待排序的数组，为了避免数组中有大量重复的元素，我设定随机数的范围为0到2*number
		a.push_back(rand()%(2*number-0+1)+0);  
	}
}

void problem1(int number)
{   //参数number用于设定待排序元素的个数，我通过不断改变number的取值，寻找每个排序算法在不同时间能够排序的个数
	srand(1);      //设置一种随机数种子，使得每次产生的随机序列相同
	for(int i = 0; i < number;i++ ) 
		a.push_back(rand()%(2*number-0+1)+0);     //随机生成待排序的数组，为了避免数组中有大量重复的元素，我设定随机数的范围为0到2*number

	clock_t start = clock();   //开始时间

	//以下为5种排序算法

	BubbleSort(number);
	//InsertSort(number);
	//quickSortNorecusive(a,0,number-1);
	//quickSortNorecusive(aa,0,number-1);
	//MergeSort(0,number-1);
	//HeapSort(number);

	clock_t end = clock();   //结束时间
	printf("%f\n",((double)(end-start))/CLOCKS_PER_SEC);
	a.clear();
}



void problem2()
{
	double eachtime[5];  //用于分别记录同一种排序算法进行5次排序的运行时间
	int number;     //表示排序的规模
	double alpha[4] = {0.05,0.10,0.5,1};     //表示5%M，10%M，50%M和M这四个档次
	int order = 0;
	int sortType = 5;
	//第一层循环，用于遍历排序个数为5%M，10%M，50%M和M这四个档次
	ofstream oFile;
	oFile.open("problem2.csv",ios::binary);
	oFile<<"排序算法"<<","<<"5%M first"<<","<<"5%M second"<<","<<"5%M third"<<","<<"5%M forth"<<","<<"5%M fifth"<<",";
	oFile<<"排序算法"<<","<<"10%M first"<<","<<"10%M second"<<","<<"10%M third"<<","<<"10%M forth"<<","<<"10%M fifth"<<",";
	oFile<<"排序算法"<<","<<"50%M first"<<","<<"50%M second"<<","<<"50%M third"<<","<<"50%M forth"<<","<<"50%M fifth"<<",";
	oFile<<"排序算法"<<","<<"M first"<<","<<"M second"<<","<<"M third"<<","<<"M forth"<<","<<"M fifth"<<","<<endl;
	while(sortType--)
	{
		order = 0;
		while(true)
		{
			
			number = 12000 * alpha[order++];     //冒泡排序10秒大约能排11800个数，这里取12000

			a.clear();  //排完序之后清空数组a
			//srand(1);
			//for(int i = 0; i < number;i++ ) 
			//{
				//随机生成待排序的数组，为了避免数组中有大量重复的元素，我设定随机数的范围为0到2*number
				//a.push_back(rand()%(2*number-0+1)+0);  
			//}
			generateRand(1,number);

			clock_t start;
			clock_t end;
			if(sortType == 4)
			{
				BubbleSort(number);
				oFile<<"BubbleSort"<<",";
			}
			else if(sortType == 3)
			{
				InsertSort(number);
				oFile<<"InsertSort"<<",";
			}
			else if(sortType == 2)
			{
				quickSortNorecusive(a,0,number-1);
				oFile<<"QuickSort"<<",";
			}
			else if(sortType == 1)
			{
				MergeSort(0,number-1);
				oFile<<"MergeSort"<<",";
			}
			else
			{
				HeapSort(number);
				oFile<<"HeapSort"<<",";
			}   
			
		
			int ccount = 5;
			int index = 0;
			//第二层循环，用于计算后四次排序的运行时间
			while(ccount--)
			{
				//将数组a恢复到排序前的状态
				a.clear();
				generateRand(1,number);
				
			
				if(sortType == 4)
				{
					start = clock();
					BubbleSort(number);
				}
				else if(sortType == 3)
				{
					start = clock();
					InsertSort(number);
				}
				else if(sortType == 2)
				{
					start = clock();
					quickSortNorecusive(a,0,number-1);
				}
				else if(sortType == 1)
				{
					start = clock();
					MergeSort(0,number-1);
				}
				else
				{
					start = clock();
					HeapSort(number);
				}   
				end = clock();
			
				double temp = ((double)end-(double)start)/CLOCKS_PER_SEC;
				eachtime[index++] = temp;  //计算第一次排序之后四次排序的运行时间
				oFile<<eachtime[index-1]<<",";
			}
		
			if(order == 4) //当5%M，10%M，50%M和M均运行完成时，跳出循环
				break;
		}
		oFile<<endl;
	}
	oFile.close();
}

void problem3()
{
	double eachtime[5];  //用于分别记录同一种排序算法进行5次排序的运行时间
	int number;     //表示排序的规模
	double alpha[4] = {0.05,0.10,0.5,1};     //表示5%M，10%M，50%M和M这四个档次
	int order = 0;
	int sortType = 5;
	//第一层循环，用于遍历排序个数为5%M，10%M，50%M和M这四个档次
	ofstream oFile;
	oFile.open("problem3.csv",ios::binary);
	oFile<<"排序算法"<<","<<"5%M first"<<","<<"5%M second"<<","<<"5%M third"<<","<<"5%M forth"<<","<<"5%M fifth"<<",";
	oFile<<"排序算法"<<","<<"10%M first"<<","<<"10%M second"<<","<<"10%M third"<<","<<"10%M forth"<<","<<"10%M fifth"<<",";
	oFile<<"排序算法"<<","<<"50%M first"<<","<<"50%M second"<<","<<"50%M third"<<","<<"50%M forth"<<","<<"50%M fifth"<<",";
	oFile<<"排序算法"<<","<<"M first"<<","<<"M second"<<","<<"M third"<<","<<"M forth"<<","<<"M fifth"<<","<<endl;
	while(sortType--)
	{
		order = 0;
		while(true)
		{
			
			number = 12000 * alpha[order++];     //冒泡排序10秒大约能排11800个数，这里取12000

			a.clear();  //排完序之后清空数组a
			srand(1);
			for(int i = 0; i < number;i++ ) 
			{
				//随机生成待排序的数组，为了避免数组中有大量重复的元素，我设定随机数的范围为0到2*number
				a.push_back(rand()%(2*number-0+1)+0);  
			}

			clock_t start;
			clock_t end;
			if(sortType == 4)
			{
				BubbleSort(number);
				oFile<<"BubbleSort"<<",";
			}
			else if(sortType == 3)
			{
				InsertSort(number);
				oFile<<"InsertSort"<<",";
			}
			else if(sortType == 2)
			{
				quickSortNorecusive(a,0,number-1);
				oFile<<"QuickSort"<<",";
			}
			else if(sortType == 1)
			{
				MergeSort(0,number-1);
				oFile<<"MergeSort"<<",";
			}
			else
			{
				HeapSort(number);
				oFile<<"HeapSort"<<",";
			}   
			
		
			int ccount = 5;
			int index = 0;
			//第二层循环，用于计算后四次排序的运行时间
			while(ccount--)
			{
				//将数组a恢复到排序前的状态
				
			
				if(sortType == 4)
				{
					start = clock();
					BubbleSort(number);
				}
				else if(sortType == 3)
				{
					start = clock();
					InsertSort(number);
				}
				else if(sortType == 2)
				{
					start = clock();
					quickSortNorecusive(a,0,number-1);
				}
				else if(sortType == 1)
				{
					start = clock();
					MergeSort(0,number-1);
				}
				else
				{
					start = clock();
					HeapSort(number);
				}   
				end = clock();
			
				double temp = ((double)end-(double)start)/CLOCKS_PER_SEC;
				eachtime[index++] = temp;  //计算第一次排序之后四次排序的运行时间
				oFile<<eachtime[index-1]<<",";
			}
		
			if(order == 4) //当5%M，10%M，50%M和M均运行完成时，跳出循环
				break;
		}
		oFile<<endl;
	}
	oFile.close();
}

void problem4()
{
	int randNumber;
	double eachtime[5];  //用于分别记录同一种排序算法进行5次排序的运行时间
	double sum = 0;  //用于求解5次运行时间的平均值
	int number;     //表示排序的规模
	double alpha[4] = {0.05,0.10,0.5,1};     //表示5%M，10%M，50%M和M这四个档次
	int order = 0;
	int sortType = 5;
	//第一层循环，用于遍历排序个数为5%M，10%M，50%M和M这四个档次
	ofstream oFile;
	oFile.open("problem4.csv",ios::app);
	for(int i = 0;i < 5;++i)
	{
		printf("第%d组随机数\n",i+1);
		sortType = 5;
		randNumber = (unsigned)time(NULL);
		
		oFile<<"排序算法"<<","<<"5%M first"<<","<<"5%M second"<<","<<"5%M third"<<","<<"5%M forth"<<","<<"5%M fifth"<<",";
		oFile<<"排序算法"<<","<<"10%M first"<<","<<"10%M second"<<","<<"10%M third"<<","<<"10%M forth"<<","<<"10%M fifth"<<",";
		oFile<<"排序算法"<<","<<"50%M first"<<","<<"50%M second"<<","<<"50%M third"<<","<<"50%M forth"<<","<<"50%M fifth"<<",";
		oFile<<"排序算法"<<","<<"M first"<<","<<"M second"<<","<<"M third"<<","<<"M forth"<<","<<"M fifth"<<","<<endl;
		while(sortType--)
		{
			order = 0;
			while(true)
			{
			
				number = 12000 * alpha[order++];     //冒泡排序10秒大约能排11800个数，这里取12000

				a.clear();  //排完序之后清空数组a
				
				generateRand(randNumber,number);

				clock_t start;
				clock_t end;
				if(sortType == 4)
				{
					BubbleSort(number);
					oFile<<"BubbleSort"<<",";
				}
				else if(sortType == 3)
				{
					//InsertSort(number);
					oFile<<"InsertSort"<<",";
				}
				else if(sortType == 2)
				{
					//quickSortNorecusive(a,0,number-1);
					oFile<<"QuickSort"<<",";
				}
				else if(sortType == 1)
				{
					//MergeSort(0,number-1);
					oFile<<"MergeSort"<<",";
				}
				else
				{
					//HeapSort(number);
					oFile<<"HeapSort"<<",";
				}   
			
		
				int ccount = 5;
				int index = 0;
				sum = 0;
				//第二层循环，用于计算后四次排序的运行时间
				while(ccount--)
				{
					//将数组a恢复到排序前的状态
					a.clear();
					generateRand(randNumber,number);
				
			
					if(sortType == 4)
					{
						start = clock();
						BubbleSort(number);
					}
					else if(sortType == 3)
					{
						start = clock();
						InsertSort(number);
					}
					else if(sortType == 2)
					{
						start = clock();
						quickSortNorecusive(a,0,number-1);
					}
					else if(sortType == 1)
					{
						start = clock();
						MergeSort(0,number-1);
					}
					else
					{
						start = clock();
						HeapSort(number);
					}   
					end = clock();
			
					double temp = ((double)end-(double)start)/CLOCKS_PER_SEC;
					sum += temp;
					eachtime[index++] = temp;  //计算第一次排序之后四次排序的运行时间
					oFile<<eachtime[index-1]<<",";
				}
		
				if(order == 4) //当5%M，10%M，50%M和M均运行完成时，跳出循环
					break;
			}
			oFile<<endl;
		}
		oFile<<endl;
	}
	oFile.close();
}