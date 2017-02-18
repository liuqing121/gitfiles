#pragma once
#include<iostream>
#include<stack>
#include<cassert>
using namespace std;
//key取值的优化
int GetBestKey(int* a,int begin,int end)
{
	if ((end - begin) < 1)
		return end;
	int mid = begin + (end - begin) / 2;
	if (a[begin] < a[end])
	{
		if (a[mid] < a[begin])
			return begin;
		else if (a[mid]>a[end])
			return end;
		else
			return mid;
	}
	else
	{
		if (a[end] > a[mid])
			return end;
		else if (a[mid] > a[begin])
			return begin;
		else
			return mid;
	}
}
//挖坑法
int PartSort1(int*a, int begin, int end)
{
	int mid = GetBestKey(a, begin, end);
	swap(a[mid], a[end]);
	int key = a[end];
	int left = begin;
	int right = end;
	while (left < right)
	{
		while (left < right && a[left] <= key)
		{
			left++;
		}
		a[right] = a[left];
		while (left<right && a[right] >= key)
		{
			right--;
		}
		a[left] = a[right];
	}
	a[left] = key;
	return left;
}

//前后指针法
int PartSort2(int*a, int begin, int end)
{
	int prev = begin - 1;
	int cur = begin;
	int mid = GetBestKey(a, begin, end);
	swap(a[mid], a[end]);
	int key = a[end];
	while (cur < end)
	{
		while (a[cur] < key && ++prev != cur)
		{
			swap(a[cur], a[prev]);
		}
		++cur;
	}
	swap(a[end], a[++prev]);
	return prev;
}

//左右指针法
int PartSort(int* a, int begin, int end)  //单趟排序
{
	int left = begin;
	int right = end;
	int mid = GetBestKey(a, begin, end);
	swap(a[mid], a[end]);
	int key =a[end];
	while (left < right)
	{
		while (left < right && a[left] <= key)
		{
			left++;
		}
		
		while (left < right && a[right] >= key)
		{
			right--;
		}
		if (a[left]>a[right])
		    swap(a[left], a[right]);
			
	}
	swap(a[left], a[end]);
	return left;
}

void QuickSortNoR(int *a, int begin, int end)//非递归
{
	assert(a);
	stack<int> s;
	if (begin < end)
	{
		s.push(end);
		s.push(begin);

		while (!s.empty())
		{
			int left = s.top();
			s.pop();
			int right = s.top();
			s.pop();
			int mid = PartSort2(a, left, right);
			if (mid - 1 > left)
			{
				s.push(mid - 1);
				s.push(left);
			}
			if (right > mid + 1)
			{
				s.push(right);
				s.push(mid + 1);
			}

		}
	}
}

void QuickSortR(int* a,int begin,int end)   //递归版
{
	int mid;
	
	if (begin < end)
	{
		//mid = PartSort(a, begin, end);
		//mid = PartSort1(a, begin, end);
		mid = PartSort2(a, begin, end);
		QuickSortR(a, begin, mid - 1);
		QuickSortR(a, mid + 1, end);
	}
}

void TestQuickSort()
{
	int a[] = { 9, 5, 4, 2, 3, 6, 8, 7, 1, 0 };
	//QuickSortR(a,0, sizeof(a) / sizeof(a[0])-1);
	QuickSortNoR(a, 0, sizeof(a) / sizeof(a[0]) - 1);
	PrintArr(a, sizeof(a) / sizeof(a[0]));
}