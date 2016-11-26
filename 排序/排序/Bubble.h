#pragma once
#include<iostream>

using namespace std;

void BubbleSort(int* a, size_t size)
{
	bool flag = false;
	for (int i = size; i > 0; i--)
	{
		for (size_t j = 1; j < i; j++)
		{
			if (a[j - 1]>a[j])
			{
				swap(a[j], a[j - 1]);
				flag = true;
			}
		}
		if (flag = false)
			break;
			
	}
}

void TestBubbleSort()
{
	int a[] = { 9, 5, 4, 2, 3, 6, 8, 7, 1, 0 };
	BubbleSort(a, sizeof(a) / sizeof(a[0]));
	PrintArr(a, sizeof(a) / sizeof(a[0]));
}