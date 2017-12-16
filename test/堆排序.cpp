/*#include <cstdio>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;


void SiftDown(struct HH H[],int n,int i)
{
	ofstream oFile;
	oFile.open("headsort1.csv",ios::app);
	
	
	bool done = true;
	while(done&&(i = 2*i+1)< n)
	{
		//oFile<<cccount<<","<<state<<","<<H[0].number<<"("<<H[0].index<<")"<<","<<H[1].number<<"("<<H[1].index<<")"<<","<<H[2].number<<"("<<H[2].index<<")"<<","<<H[3].number<<"("<<H[3].index<<")"<<","<<H[4].number<<"("<<H[4].index<<")"<<","<<H[5].number<<"("<<H[5].index<<")"<<","<<numberOfCompare<<","<<numberOfSwap<<endl;
		cccount++;
		//oFile.close();
		printf("%c   ",state);
		for(int ll = 0;ll < 6;++ll)
		{
			printf("%d(%d)   ",H[ll].number,H[ll].index);
		}
		printf("%d   %d\n",numberOfCompare,numberOfSwap);

		if((i+1)<n&&H[i+1].number>H[i].number)
		{
			i = i + 1;
		}
		if(H[(i-1)/2].number<H[i].number)
		{
			int temp;
			temp = H[i].number;
			H[i].number = H[(i-1)/2].number;
			H[(i-1)/2].number = temp;
			temp = H[i].index;
			H[i].index = H[(i-1)/2].index;
			H[(i-1)/2].index = temp;
			++numberOfSwap;
		}
		else
			done = false;
		++numberOfCompare;
		
	}
	
}

void MakeHeap(struct HH H[],int n)
{
	for(int i = n/2 - 1;i >= 0;--i)
	{
		SiftDown(H,n,i);
	}
}

void HeapSort(struct HH H[],int n)
{
	MakeHeap(H,n);
	state = 'S';
	for(int i = n - 1;i >= 0;--i)
	{
		
		int temp;
		temp = H[0].number;
		H[0].number = H[i].number;
		H[i].number = temp;
		temp = H[0].index;
		H[0].index = H[i].index;
		H[i].index = temp;

		SiftDown(H,i,0);
		
	}
}

int main()
{
	int b[6] = {49,73,14,59,35,47};
	//int b[6] = {25,31,25,11,9,25};
	ofstream oFile;
	//oFile.open("headsort1.csv",ios::app);
	//oFile<<"行号"<<","<<"建堆或排序"<<","<<"0号节点"<<","<<"1号节点"<<","<<"2号节点"<<","<<"3号节点"<<","<<"4号节点"<<","<<"5号节点"<<","<<"比较次数"<<","<<"交换次数"<<endl;
	//oFile.close();
	printf("状态   1   2   3   4   5   6   比较次数   交换次数\n");
	for(int i = 0;i < 6;++i)
	{
		H[i].number = b[i];
		H[i].index = i;
		
	}

	printf("%c   ",state);
		for(int ll = 0;ll < 6;++ll)
		{
			printf("%d(%d)   ",H[ll].number,H[ll].index);
		}
		printf("%d   %d\n",numberOfCompare,numberOfSwap);

	HeapSort(H,6);
	//ofstream ooFile;
	//ooFile.open("headsort1.csv",ios::app);
	//ooFile<<cccount<<","<<state<<","<<H[0].number<<"("<<H[0].index<<")"<<","<<H[1].number<<"("<<H[1].index<<")"<<","<<H[2].number<<"("<<H[2].index<<")"<<","<<H[3].number<<"("<<H[3].index<<")"<<","<<H[4].number<<"("<<H[4].index<<")"<<","<<H[5].number<<"("<<H[5].index<<")"<<","<<numberOfCompare<<","<<numberOfSwap<<endl;
	//ooFile.close();
	return 0;
}*/
/*
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <stdio.h>
#include <string>
#include <time.h>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace cv;

struct aa
{
	int number;
	int index;
}a[6];

int ccount = 0;
int numberOfSwap = 0;
int numberOfCompare = 0;

int partition(struct aa a[],int low,int high)
{
	++ccount;
	ofstream oFile;
	oFile.open("anthortest.csv",ios::app);
	oFile<<ccount<<","<<a[0].number<<"("<<a[0].index<<")"<<","<<a[1].number<<"("<<a[1].index<<")"<<","<<a[2].number<<"("<<a[2].index<<")"<<","<<a[3].number<<"("<<a[3].index<<")"<<","<<a[4].number<<"("<<a[4].index<<")"<<","<<a[5].number<<"("<<a[5].index<<")"<<","<<numberOfSwap<<","<<numberOfCompare<<endl;
	oFile.close();
	
	int pivot = a[high].number;
	int i = low - 1;
	for(int j = low;j<=high-1;++j)
	{
		if(a[j].number<pivot)
		{
			i++;
			++numberOfCompare;
			if(i<j)
			{
				int temp1,temp2;
				temp1 = a[i].number;
				temp2 = a[i].index;
				a[i].number = a[j].number;
				a[i].index = a[j].index;
				a[j].number = temp1;
				a[j].index = temp2;
				++numberOfSwap;
			}
		}

	}
	if(a[high].number<a[i+1].number)
	{
		int temp1,temp2;
				temp1 = a[i+1].number;
				temp2 = a[i+1].index;
				a[i+1].number = a[high].number;
				a[i+1].index = a[high].index;
				a[high].number = temp1;
				a[high].index = temp2;
		++numberOfSwap;
	}
	return i+1;
}

void QuickSort(struct aa a[],int low,int high)
{
	if(low < high)
	{
		int p = partition(a,low,high);
		QuickSort(a,low,p-1);
		QuickSort(a,p+1,high);

	}
}

int main()
{
	ofstream oFile;
	oFile.open("anthortest.csv",ios::app);
	oFile<<"行数"<<","<<"first"<<","<<"second"<<","<<"third"<<","<<"forth"<<","<<"fifth"<<","<<"sixth"<<","<<"交换次数"<<","<<"比较次数"<<endl;
	oFile.close();
	int b[6] = {12,31,25,11,9,25};
	for(int i = 0;i < 6;++i)
	{
		a[i].number = b[i];
		a[i].index = i;
	}
	QuickSort(a,0,5);

	++ccount;
	ofstream ooFile;
	ooFile.open("anthortest.csv",ios::app);
	ooFile<<ccount<<","<<a[0].number<<"("<<a[0].index<<")"<<","<<a[1].number<<"("<<a[1].index<<")"<<","<<a[2].number<<"("<<a[2].index<<")"<<","<<a[3].number<<"("<<a[3].index<<")"<<","<<a[4].number<<"("<<a[4].index<<")"<<","<<a[5].number<<"("<<a[5].index<<")"<<","<<numberOfSwap<<","<<numberOfCompare<<endl;
	ooFile.close();
	
	return 0;
}*/