#pragma once 
#include<iostream>
using namespace std;

void ShellSort(int*a, size_t size)
{
	size_t gap = size;  //增量
	
	while (gap>1)
	{
		gap = gap / 3 + 1;  //保证最后一次是直接插入排序
		int pos = 0;
		for (int index = pos + gap; index < size; index++)
		{
			int tmp = a[index];
			pos = index - gap;
			while (pos >= 0 && a[pos]>tmp)
			{
				a[pos + gap] = a[pos];
				pos -= gap;
			}
			a[pos + gap] = tmp;

		}
	}
}

void TestShellSort()
{
	int a[] = { 9, 5, 4, 2, 3, 6, 8, 7, 1, 0 };
	ShellSort(a, sizeof(a) / sizeof(a[0]));
	PrintArr(a, sizeof(a) / sizeof(a[0]));
}