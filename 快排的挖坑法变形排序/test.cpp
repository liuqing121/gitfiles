#include<iostream>
using namespace std;

void SwapSort(int*pArr, int*pPos, size_t n)
{
	size_t i = 0;
	int tmp = 0;
	tmp = pArr[i];         //第一个坑
	while (--n)         //总共交换n-1次
	{
		if (i != pPos[i])
		{

			pArr[i] = pArr[pPos[i]];
			i = pPos[i];
		}
	}
	pArr[i] = tmp;    //把最开始坑里的数据填到最后一个坑的位置
}
int main()
{
	int arr[] = { 'A', 'B', 'C', 'D', 'E' };
	int pos[] = { 3, 0, 1, 4, 2 };
	SwapSort(arr, pos, sizeof(arr)/sizeof(arr[0]));
	for (size_t i = 0; i < 5; i++)
	{
		cout << (char)arr[i] << " ";
	}
	cout << endl;
	getchar();
	return 0;
}