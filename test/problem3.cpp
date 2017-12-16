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

//Ϊ�˷�ֹ�ڴ�������ҽ��������������Ϊ��̬���飬��������Ϊȫ�ֱ���
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

//�ϲ�����
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

//ð������
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


//��������
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
    int x = data[r];    //��׼  
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

//�ǵݹ�Ŀ�������
void quickSortNorecusive(vector<int>& data,int l,int r)  
{  
    stack<int> st;  //������һ��ջ
    if(l < r)  
    {  
        int tmp = partitions(data,l,r);  
        if(tmp-1 > l)    //��߲�ֹһ��Ԫ��  
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
            if(tmp-1 > start)    //��߲�ֹһ��Ԫ��  
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

//������
void HeapSort(int n)
{
	MakeHeap(n);

	for(int i = n - 1;i > 0;--i)
	{
		swap(a[0],a[i]);
		SiftDown(i,0);
	}
}

//�����׼��
double caculateBiase(double eachtime[],int n,double mean)
{
	double ssum = 0;
	for(int i = 0;i < n;++i)
	{
		ssum += (eachtime[i] - mean)*(eachtime[i] - mean);
	}
	return sqrt(ssum/(double)n);
}

//������ʾ5�����������ʱ��;�ֵ������
void display(double eachtime[],double mean,double biase)
{
	printf("5������ʱ��ֱ�Ϊ��");
	for(int i = 0;i < 5;++i)
	{
		printf("%f  ",eachtime[i]);
	}
	printf("\n");
	printf("��ֵΪ��%f\n",mean);
	printf("��׼��Ϊ��%f\n\n",biase);
}

int main()
{
	double eachtime[5];  //���ڷֱ��¼ͬһ�������㷨����5�����������ʱ��
	double sum = 0;  //�������5������ʱ���ƽ��ֵ
	int number;     //��ʾ����Ĺ�ģ
	double alpha[4] = {0.05,0.10,0.5,1};     //��ʾ5%M��10%M��50%M��M���ĸ�����
	int order = 0;
	
	//��һ��ѭ�������ڱ����������Ϊ5%M��10%M��50%M��M���ĸ�����
	while(true)
	{
		number = 12000 * alpha[order++];     //ð������10���Լ����11800����������ȡ12000
		printf("��������� :%d\n",number);

		srand((unsigned)time(NULL));
		for(int i = 0; i < number;i++ ) 
		{
			int temp = rand()%(2*number-0+1)+0;     //������ɴ���������飬Ϊ�˱����������д����ظ���Ԫ�أ����趨������ķ�ΧΪ0��2*number
			//a�Ǵ��������飬b��¼����a����ǰ��״̬������������a�����ָ�����a
			a.push_back(temp);  
			b.push_back(temp);   
		}

		InsertSort(number);  //������a��������

		clock_t start = clock();
		//BubbleSort(number);
		//InsertSort(number);
		//quickSortNorecusive(a,0,number-1);
		//MergeSort(0,number-1);
		//HeapSort(number);
		clock_t end = clock();
	
		sum += ((double)end-(double)start)/CLOCKS_PER_SEC;
		eachtime[0] = ((double)end-(double)start)/CLOCKS_PER_SEC;  //��һ�����������ʱ��
	
		int ccount = 4;
		int index = 1;
		//�ڶ���ѭ�������ڼ�����Ĵ����������ʱ��
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
			eachtime[index++] = ((double)end-(double)start)/CLOCKS_PER_SEC;  //�����һ������֮���Ĵ����������ʱ��

		}
		a.clear();
		b.clear();
		sum /= 5;  //�����ֵ
		double biase = caculateBiase(eachtime,5,sum);   //�����׼��
	
		display(eachtime,sum,biase);   //��5�����������ʱ�����5������ľ�ֵ����׼���ӡ����Ļ��
		
		if(order == 4) //��5%M��10%M��50%M��M���������ʱ������ѭ��
			break;
	}
	return 0;
}