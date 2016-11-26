#pragma once
#include<iostream>
using namespace std;

void InSertSort(int* a, size_t n)
{
	int index = 1;
	size_t pos = index - 1;  //有序区间的最后一个位置

	while (pos < n - 1)
	{	
		for (int i = pos; i >= 0; i--)
		{
			if (a[i]>a[index])
			{
				swap(a[i], a[index]);
				index--;
			}
		}
		pos++;
		index = pos + 1;
	}
}

void TestInsertSort()
{
	int a[] = { 9, 5, 4, 2, 3, 6, 8, 7, 1, 0 };
	InSertSort(a, sizeof(a) / sizeof(a[0]));
	PrintArr(a, sizeof(a) / sizeof(a[0]));
}