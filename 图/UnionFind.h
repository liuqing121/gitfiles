#pragma once
#include<iostream>

using namespace std;
class UnionFind
{
public:
	UnionFind(size_t n)    //开辟n+1大小的数组,下标为0的不使用
		:_a(new int[n + 1])
		, _size(n + 1)
	{
		memset(_a, -1, sizeof(int)*(n + 1));
	}

	void Merge(int x, int y)   //建立关系
	{
		int root1 = GetRoot(x);
		int root2 = GetRoot(y);

		if (root1 != root2)   //如果本来就在一个集合里就不用建立关系了
		{
			_a[root1] += _a[root2];
			_a[root2] = root1;   //孩子存放父亲的下标
		}
	}

	int CountUnion()   //统计有几个集合
	{
		int count = 0;
		for (size_t i = 0; i < _size; i++)
		{
			if (_a[i] < 0)
				count++;
		}
		return count - 1;   //减去下标为0的位置
	}

	int GetRoot(int index)
	{
		int root = index;
		while (_a[root] >= 0)
		{
			root = _a[root];
		}
		return root;
	}
protected:
	int* _a;
	size_t _size;
};

int friends(int n, int m, int r[][2])
{
	UnionFind uf(n);
	uf.Merge(r[0][0], r[0][1]);
	uf.Merge(r[1][0], r[1][1]);
	uf.Merge(r[2][0], r[2][1]);
	return uf.CountUnion();
}

void TestUnionFind()
{
	const int n = 5;
	const int m = 3;
	int r[m][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 } };
	cout << friends(n, m, r);
}