#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include"Heap.h"
#include"UnionFind.h"
using namespace std;

template<class V,class W>
class GraphLink
{
public:
	GraphLink(const V* v,int size,bool IsDirection = false)
		:_vertex(v,v+size)
		, _tables(size,NULL)
		, _IsDirection(IsDirection)
	{}

	int GetIndex(const V& v)
	{
		for (size_t i = 0; i < _vertex.size(); i++)
		{
			if (_vertex[i] == v)
				return i;
		}
		throw std::invalid_argument("参数错误");
	}

	void CreatNewNode(const int src,const int des,const W& w)
	{
		if (_tables[src] == NULL)
			_tables[src] = new Node(src, des, w);

		else
		{
			Node* newNode = new Node(src, des, w);
			newNode->_next = _tables[src];
			_tables[src] = newNode;
		}
	}
	void AddEdge(const V& begin, const V& end, const W& w)
	{
		int src = GetIndex(begin);
		int des = GetIndex(end);
		CreatNewNode(src, des, w);
		if (_IsDirection == false)
			CreatNewNode(des, src, w);
	}

	void LSD(const V& v)  //广度优先遍历
	{
		int index = GetIndex(v);
		queue<int> q;
		q.push(index);
		vector<bool> visited(_vertex.size(), false);
		while (!q.empty())
		{
			int top = q.front();
			q.pop();
			if (visited[top] == false)
			{
				cout << _vertex[top] << ":" << top << "->";
				visited[top] = true;
			}
			Node* cur = _tables[top];
			while (cur)
			{
				if (visited[cur->_des] == false)
				{
					q.push(cur->_des);
				}
				cur = cur->_next;
			}
		}
	}



	bool Kruskal(GraphLink<V,W>& minTree)   //Kruskal算法的最小生成树
	{
		assert(_IsDirection == false);    //Kruskal是无向图的最小生成树算法
		minTree._IsDirection = _IsDirection;
		minTree._vertex = _vertex;
		minTree._tables.resize(_vertex.size());
		struct Compare
		{
			bool operator()(Node* left, Node* right)
			{
				return left->_w < right->_w;
			}
		};
		Heap<Node*, Compare> hp;
		for (size_t i = 0; i < _tables.size(); i++)
		{
			Node* cur = _tables[i];
			while (cur)
			{
				hp.Push(cur);
				cur = cur->_next;
			}
		}
		UnionFind uf(_vertex.size());
		size_t n = 0;
		while (n < _vertex.size() - 1)
		{
			if (_vertex.empty())
			{
				return false;
			}
			Node* cur = hp.Top();
			hp.Pop();
			int root1 = uf.GetRoot(cur->_src);
			int root2 = uf.GetRoot(cur->_des); 
			if (root1 != root2)   //若顶点不在集合中再增加边
			{
				uf.Merge(cur->_src, cur->_des);
				minTree.AddEdge(cur->_src, cur->_des, cur->_w);
				n++;
			}
		}
		return true;
	}

	void DFS(const V& v)   //深度优先遍历
	{
		vector<bool> visited(_vertex.size(), false);
		
		_DFS(GetIndex(v), visited);
		cout << endl;
		for (size_t i = 0; i < _vertex.size(); i++)
		{
			if (visited[i]==false)
			    _DFS(i, visited);
		}
		cout << endl;
	}

	void _DFS(int index, vector<bool>& visited)
	{
		cout << _vertex[index] << ":" << index<<"->";
		visited[index] = true;
		Node* cur = _tables[index];
		while (cur)
		{
			if (visited[cur->_des] == false)
			{
				_DFS(cur->_des, visited);
			}
			cur = cur->_next;
		}
	}
	struct Node
	{
		W _w;
		int _src;
		int _des;
		Node* _next;
		Node(const int src,const int des,const W& w)
			:_w(w), _src(src), _des(des), _next(NULL)
		{}
	};
protected:
	vector<Node*> _tables;
	vector<V> _vertex;
	bool _IsDirection;
};


void TestGraphLink()
{
	string city[5] = { "西安", "汉中", "拉萨", "宝鸡", "延安" };
	GraphLink<string, int> gm(city, 5);
	gm.AddEdge("西安", "汉中", 300);
	gm.AddEdge("汉中", "拉萨", 300);
	gm.AddEdge("拉萨", "宝鸡", 100);
	gm.AddEdge("宝鸡", "延安", 100);
	gm.AddEdge("西安", "延安", 100);
	gm.DFS("西安");
	gm.LSD("西安");
}

void TestKruskal()
{
	int a[] = { 0, 1, 2, 3, 4 };
	GraphLink<int, int> gl(a, 5);
	GraphLink<int, int> minTree(a, 5);
	gl.AddEdge(1, 2, 10);
	gl.AddEdge(2, 4, 40);
	gl.AddEdge(4, 0, 20);
	gl.AddEdge(0, 3, 10);
	gl.AddEdge(3, 1, 20);
	gl.AddEdge(1, 4, 30);
	gl.Kruskal(minTree);
	minTree.DFS(1);
}


