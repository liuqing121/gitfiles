#pragma once
#include<iostream>

using namespace std;
void _AjustDown(int* a, size_t size, int root)
{
	size_t parient = root;
	size_t child = 2 * parient + 1;

	while (child<size)
	{

		if ((child + 1<size) && (a[child + 1]> a[child]))  //此处一定要先考虑到右孩子不存在的情况
		{
			++child;
		}
		if (a[parient] < a[child])
		{
			swap(a[parient], a[child]);
		}
		parient = child;
		child = 2 * parient + 1;
	}
}


	void HeapSort(int* a, size_t size)    
	{
		for (int i = (size - 2) / 2; i >= 0; i--)   //建好一个大堆
		{
			_AjustDown(a, size, i);
		}
		for (size_t i = 0; i < size; i++)
		{
			swap(a[0], a[size - 1-i]);    //把最大的数放在堆的最后一个结点
			_AjustDown(a, size - 1 - i, 0);   //调整除了最后一个数字的剩下的堆。
		}
		//return a;
	}

	

void TestHeapSort()
{
	int a[10] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
	HeapSort(a, 10);
}