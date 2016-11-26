#include<iostream>

using namespace std;

void Merge(int*a, int left,int mid, int right,int* tmp)  //合并两个有序数组
{
	//[left,mid]  [mid+1,right]
	int first = left;
	int last = right;
	int first2 = mid + 1;
	int index = 0;
	while (first <= mid && first2 <= last)
	{
		if (a[first] < a[first2])
		{
			tmp[index++] = a[first++];
		}
		else
		{
			tmp[index++] = a[first2++];
		}
	}

	while (first <= mid)   //第一个数组没有完
	{
		tmp[index++] = a[first++];
	}

	while (first2 <= last)  //第二个数组没有完
	{
		tmp[index++] = a[first2++];
	}

	for (int i = 0; i < index; i++)  //拷回给a
	{
		a[left+i] = tmp[i];
	}

}

void MergeSort(int*a,int begin,int end)
{
	int* tmp = new int[end+1];
	if (begin < end)
	{
		int mid = begin + ((end - begin) >> 1);
		MergeSort(a, begin, mid);
		MergeSort(a, mid + 1, end);
		Merge(a, begin, mid, end, tmp);
	}
	delete[] tmp;
}

void TestMergeSort()
{
	int a[] = { 9, 5, 4, 2, 3, 6, 8, 7, 1, 5 };
	MergeSort(a, 0,sizeof(a) / sizeof(a[0])-1);
	PrintArr(a, sizeof(a) / sizeof(a[0]));
}