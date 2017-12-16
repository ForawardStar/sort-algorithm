#pragma once
#ifndef CIRCLE_H
#define CIRCLE_H
#include <vector>

using namespace std;

extern vector<int> a;  //用于存放待排序元素的动态数组，这里设为全局变量

void MergeSort(int low,int high);    //合并排序
void Merge2sortedSubArr(int p,int q,int r);

void BubbleSort(int n);       //冒泡排序

void InsertSort(int n);        //插入排序

void quickSortNorecusive(vector<int>& data,int l,int r);    //非递归的快速排序
int partitions(vector<int>& data,int l,int r);  

void HeapSort(int n);     //堆排序
void SiftDown(int n,int i);
void MakeHeap(int n);

void problem1(int number);    //第一问的函数
void problem2();              //第二问的函数
void problem3();              //第三问的函数
void problem4();              //第四问的函数

void generateRand(int sr,int number);  //产生长度为number,随机数种子为sr的随机数组

#endif