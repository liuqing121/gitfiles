#pragma once
#include<iostream>

using namespace std;

void SelectSort(int *a,size_t n)
{
	size_t max, min;

	size_t left = 0;
	size_t right = n - 1;

	while (left < right)
	{
		min = max = left;
		for (size_t j = left; j <= right; j++)
		{
			if (a[j] <= a[min])
				min = j;
			if (a[j]>=a[max])
				max = j;
		}
		swap(a[left], a[min]);
		if (left == max)
		{
			max = min;
		}
		swap(a[right], a[max]);
		left++;
		right--;
	}
}

void PrintArr(int* a,size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void TestSelectSort()
{
	int a[] = { 9, 5, 4, 2, 3, 6, 8, 7, 1, 0 };
	SelectSort(a, sizeof(a) / sizeof(a[0]));
	PrintArr(a, sizeof(a) / sizeof(a[0]));
}