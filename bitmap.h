#pragma once
#include<iostream>
#include<vector>
using namespace std;

class BitMap
{
public:
	BitMap(size_t size)
	{
		_bitMap.resize((size>>5)+1);
	}
	void Set(const int& x)
	{
		int index = x >> 5;   //除效率不高，所以这里用右移5位表示除以32，得到x所在的数据个数
		int bit = x % 32;     //得到x的位

		_bitMap[index] |= (1 << bit);
	}
	void ReSet(const int& x)
	{
		int index = x >> 5;
		int bit = x % 32;

		_bitMap[index] &= (~(1 << bit));
	}
	bool Test(const int& x)
	{
		int index = x >> 5;
		int bit = x % 32;

		return _bitMap[index] & (1 << bit);
	}
private:
	vector<size_t> _bitMap;
};

void TestBitMap()
{
	BitMap bm(40);
	bm.Set(10);
	bm.Test(10);
	bm.Test(20);
}