#include<iostream>
#include<vector>
#include<cassert>
using namespace std;

template<class T>
struct Grearer
{
	bool operator()(const T& left, const T& right)
	{
		return left > right;
	}
};

template<class T>
struct Less
{
	bool operator()(const T& left, const T& right)
	{
		return left < right;
	}
};
template<class T, class Compare = Grearer<T>>    //模板的模板参数，默认值为大于
class Heap
{
public:
	Heap()
	{}
	Heap(T* a, size_t size)    //建堆
	{
		for (size_t i = 0; i < size; i++)  //数组内容拷贝给成员_a
		{
			_a.push_back(a[i]);
		}
		for (int i = (size - 2) / 2; i >= 0; i--)   //从最后一个非叶子节点向下调整
		{
			_AjustDown(i);
		}
	}

	void Push(const T& x)
	{
		_a.push_back(x);     //先插到堆的最后一个位置
		_AjustUp(_a.size() - 1);   //再对最后一个数据向上进行调整
	}

	void Pop()
	{
		assert(!_a.empty());    //对空堆进行断言
		swap(_a[0], _a[_a.size() - 1]);    //交换堆的第一个数据和最后一个
		_a.pop_back();                    //相当于删除了第一个数据
		_AjustDown(0);                     //对刚放在首位置的数据进行向下调整
	}

	size_t Size()           //堆节点个数
	{
		return _a.size();
	}

	const T& Top()     //堆的首个数据
	{
		return _a[0];
	}

	bool Empty()    //堆是否为空
	{
		return _a.empty();
	}
protected:
	void _AjustUp(int root)     //向上调整
	{
		size_t child = root;
		size_t parient = (child - 1) / 2;

		while (child > 0)
		{
			Compare com;
			//if (_a[child] > _a[parient])
			if (com(_a[child], _a[parient]))
			{
				swap(_a[child], _a[parient]);
			}
			else
			{
				break;
			}
			child = parient;
			parient = (child - 1) / 2;
		}

	}
	void _AjustDown(int root)   //向下调整
	{
		size_t parient = root;
		size_t child = 2 * parient + 1;

		while (child<_a.size())
		{
			Compare com;
			if ((child + 1<_a.size()) && com(_a[child + 1], _a[child]))  //此处一定要先考虑到右孩子不存在的情况
			{
				++child;
			}
			//if (_a[parient] < _a[child])
			if (com(_a[child], _a[parient]))
			{
				swap(_a[parient], _a[child]);
			}
			parient = child;
			child = 2 * parient + 1;
		}
	}
private:
	vector<T>_a;
};
