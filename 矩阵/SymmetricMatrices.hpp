//#include<iostream>
//using namespace std;
//template<class T>
//class SymmetricMatrices
//{
//public:
//	explicit SymmetricMatrices(T* arr, size_t n)
//		:_size((n*(n + 1)) / 2),
//		_n(n),
//		_a(new T[(n*(n + 1)) / 2])
//	{
//		size_t index = 0;
//		for (size_t i = 0; i < _n; i++)
//		{
//			for (size_t j = 0; j < _n; j++)
//			{
//				if (i >= j)
//				{
//					_a[index++] = arr[i*_n + j];
//				}
//				else
//					continue;
//			}
//		}
//	}
//	~SymmetricMatrices()
//	{
//		while (_a)
//		{
//			delete _a;
//			_a = NULL;
//			_size = 0;
//			_n = 0;
//		}
//	}
//	T& Access(size_t i, size_t j)
//	{
//		if (i < j)
//		{
//			swap(i, j);
//		}
//		return _a[i*(i+1)/2 + j];
//	}
//	void Display()
//	{
//		for (size_t i = 0; i < _n; i++)
//		{
//			for (size_t j = 0; j < _n; j++)
//			{
//				cout << Access(i, j) << " ";
//			}
//			cout << endl;
//		}
//		cout << endl;
//	}
//protected:
//	size_t _size;
//	size_t _n;
//	T* _a;
//};
//
//void TestSymmetricMatrices()
//{
//	int arr[][5] = {
//		{ 0, 1, 2, 3, 4 },
//		{ 1, 0, 1, 2, 3 },
//		{ 2, 1, 0, 1, 2 },
//		{ 3, 2, 1, 0, 1 },
//		{ 4, 3, 2, 1, 0 }
//	};
//	SymmetricMatrices<int> sm((int*)arr, 5);
//	sm.Display();
//}