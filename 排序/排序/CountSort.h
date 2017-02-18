#pragma once
#include<iostream>

using namespace std;
/*计数排序*/
/*适合数范围比较集中的排序，属于非选择排序*/
int GetSize(int*a, int size)
{
	int max = 0;
	int min = 0;
	for (int i = 0; i < size; i++)
	{
		if (a[i]>a[max])
			max = i;
		if (a[i] < a[min])
			min = i;
	}
	return (a[max] - a[min] + 1);
}

void CountSort(int* a,int size)
{
	//找出最大和最小数的下标
	int max = 0;
	int min = 0;
	for (int i = 0; i < size; i++)
	{
		if (a[i]>a[max])
			max = i;
		if (a[i] < a[min])
			min = i;
	}
	int CountSize = a[max] - a[min] + 1;
	int* tmp = new int[CountSize];
	memset(tmp, 0, sizeof(int)*CountSize);
	int minNum = a[min];
	for (int i = 0; i < size; i++)
	{
		tmp[(a[i] - minNum)]++;
	}
	int index = 0;
	for (int i = 0; i < size; )
	{
		while (tmp[index]-- != 0)
		{
			a[i++] = index + minNum;
		}
		if (index<CountSize)
			index++;
	}
	delete[]  tmp;
}

void TestCountSort()
{
	int a[] = { 9, 5, 4, 2, 3, 6, 8, 7, 1, 5 };
	CountSort(a,sizeof(a) / sizeof(a[0]));
	PrintArr(a, sizeof(a) / sizeof(a[0]));
	int a1[] = { 900, 500, 560, 600, 700, 800, 850, 860, 861, 862 };
	CountSort(a1, sizeof(a1) / sizeof(a1[0]));
	PrintArr(a1, sizeof(a1) / sizeof(a1[0]));
}