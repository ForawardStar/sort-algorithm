#pragma once
#ifndef CIRCLE_H
#define CIRCLE_H
#include <vector>

using namespace std;

extern vector<int> a;  //���ڴ�Ŵ�����Ԫ�صĶ�̬���飬������Ϊȫ�ֱ���

void MergeSort(int low,int high);    //�ϲ�����
void Merge2sortedSubArr(int p,int q,int r);

void BubbleSort(int n);       //ð������

void InsertSort(int n);        //��������

void quickSortNorecusive(vector<int>& data,int l,int r);    //�ǵݹ�Ŀ�������
int partitions(vector<int>& data,int l,int r);  

void HeapSort(int n);     //������
void SiftDown(int n,int i);
void MakeHeap(int n);

void problem1(int number);    //��һ�ʵĺ���
void problem2();              //�ڶ��ʵĺ���
void problem3();              //�����ʵĺ���
void problem4();              //�����ʵĺ���

void generateRand(int sr,int number);  //��������Ϊnumber,���������Ϊsr���������

#endif