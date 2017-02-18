#include<iostream>
#include<string>
using namespace std;

template<class V,class W>
class GraphMatrix
{
public:
	GraphMatrix(V* vertex, int size, bool IsDirection=false)
		:_vertex(new V[size])
		, _weight(new W*[size])
		, _size(size)
		, _IsDirection(IsDirection)
	{
		for (int i = 0; i < size; i++)
		{
			_vertex[i] = vertex[i];
			_weight[i] = new W[size];
		}

	}
	~GraphMatrix()
	{
		delete[] _vertex;
		for (int i = 0; i < _size; i++)
		{
			delete[] _weight[i];
		}
		delete[] _weight;
	}

	int Getindex(const V& v)
	{
		for (int i = 0; i < _size; i++)
		{
			if (_vertex[i] == v)
				return i;
		}
		//到这里说明参数有误，不在跟定的顶点里
		throw std::invalid_argument("参数错误");
	}

	void AddEdge(const V& begin,const V& end,const W& w)   //增加边  给定边起始，结束顶点和权值
	{
		int src = Getindex(begin);
		int des = Getindex(end);
		_weight[src][des] = w;
		if (_IsDirection == false)
		{
			_weight[des][src] = w;
		}
	}


protected:
	V* _vertex;
	W** _weight;
	int _size;

	bool _IsDirection;
};

void TestGraphMatrix()
{
	string city[5] = { "西安", "汉中", "拉萨", "宝鸡", "延安" };
	GraphMatrix<string, int> gm(city, 5);
	gm.AddEdge("西安", "宝鸡", 200);
	gm.AddEdge("西安", "汉中", 300);
	gm.AddEdge("西安", "延安", 300);
	gm.AddEdge("汉中", "宝鸡", 100);
}