#include<iostream>
#include<vector>
using namespace std;
template<class T>
struct Triple
{
	size_t row;
	size_t col;
	T value;
	Triple(size_t r = 0, size_t c = 0, T va = T())
		:row(r), col(c),value(va)
	{}
};
template<class T>
class SparseMatrix
{
public:
	SparseMatrix(T* a, size_t m, size_t n, const T& invalid)
		:_row(m), _col(n), _invalid(invalid)
	{
		for (size_t i = 0; i < _row; i++)
		{
			for (size_t j = 0; j < _col; j++)
			{
				if (a[i*_col + j] != _invalid)
				{
					Triple<T> t(i, j, a[i*_col + j]);
					_a.push_back(t);
				}
			}
		}
	}
	SparseMatrix()
	{}
	//~SparseMatrix()
	//{
	//	if (_a)
	//	{
	//		delete[]_a;
	//		_row = 0;
	//		_col = 0;
	//	}
	//}
	void Display()
	{
		size_t index = 0;
		for (size_t i = 0; i < _row; i++)
		{
			for (size_t j = 0; j < _col; j++)
			{
				if (index < _a.size()
					&& _a[index].row == i
					&&_a[index].col == j)
				{
					cout << _a[index].value << " ";
					index++;
				}
				else
				{
					cout << _invalid << " ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	//SparseMatrix<T> CommonTransfer()
	//{
	//	SparseMatrix<T> sm;
	//	sm._row = _col;
	//	sm._col = _row;
	//	sm._invalid = _invalid;
	//	size_t index = 0;
	//	for (size_t i = 0; i < _col; i++)
	//	{
	//		index = 0;
	//		while (index < _a.size())
	//		{
	//			if (_a[index].col == i)
	//			{
	//				Triple<T> t(_a[index].col, _a[index].row, _a[index].value);
	//					sm._a.push_back(t);
	//			}
	//			index++;
	//		}
	//	}
	//	return sm;
	//}

	SparseMatrix<T> FastTranfer()
	{
		SparseMatrix<T> sm;
		sm._a.resize(_a.size());
		sm._row = _col;
		sm._col = _row;
		sm._invalid = _invalid;
		//size_t index = 0;
		vector<int> count;
		vector<int> cpot;
		count.resize(_col);
		cpot.resize(_col);
		for (size_t i = 0; i < _a.size(); i++)
		{
			count[_a[i].col]++;
		}
		cpot[0] = 0;
		for (size_t i = 1; i < _col; i++)
		{
			cpot[i] = cpot[i - 1] + count[i - 1];
		}
		for (size_t i = 0; i < _a.size(); i++)
		{
			size_t col = _a[i].col;
			size_t index = cpot[col];
			sm._a[index].row = _a[i].col;
			sm._a[index].col = _a[i].row;
			sm._a[index].value = _a[i].value;
			++cpot[col];
		}
		return sm;
	}
private:
	vector<Triple<T>> _a;
	size_t _row;
	size_t _col;
	T _invalid;	
};

void TestSparseMatrix()
{
	int arr[6][5] = {
		{1,0,3,5,0},
		{0,0,0,4,5},
		{1,0,0,0,0},
		{0,0,0,0,3},
		{3,0,0,6,0},
		{4,0,0,0,0}
	};
	SparseMatrix<int> sm((int*)arr, 6, 5, 0);
	sm.Display();
	//SparseMatrix<int> s = sm.CommonTransfer();
	SparseMatrix<int> s = sm.FastTranfer();
	s.Display();
}