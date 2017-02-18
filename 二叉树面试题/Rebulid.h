#include<iostream>
#include<vector>
#include<cassert>
using namespace std;
template<class T>
struct Node
{
	T _value;
	Node<T>* _left;
	Node<T>* _right;
	Node(T value)
		:_value(value)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class T>
class Rebuild
{
public:
	typedef Node<T> Node;
	Rebuild(vector<T> InOrder, vector<T> PrevOrder)
	{
		assert(InOrder.size() == PrevOrder.size());
		assert(InOrder.size() != 0);
		_root = new Node(PrevOrder[0]);
		if (InOrder.size() == 1)
			return;
		_root=_Rebulid(InOrder, PrevOrder,_root);
	}

	void PrevOrder()
	{
		_PrevOrder(_root);
	}
protected:
	void _PrevOrder(Node* root)
	{
		if (root == NULL)
			return;
		
		cout << root->_value<<" ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
	Node* _Rebulid(vector<T>InOrder,vector<T>PrevOrder,Node*& root)
	{
		if (InOrder.size() == 0)
			return NULL;
		root = new Node(PrevOrder[0]);
		size_t i = 0;
		for (; i < InOrder.size(); i++)  //找到中序数组里根节点的位置
		{
			if (InOrder[i] == PrevOrder[0])
				break;
		}
		vector<T> InOrderLeft;
		vector<T> InOrderRight;
		vector<T> PrevOrderLeft;
		vector<T> PrevOrderRight;
		size_t j = 0;
		for (; j<i; j++)
		{
			InOrderLeft.push_back(InOrder[j]);
			PrevOrderLeft.push_back(PrevOrder[j + 1]);
		}
	

		for (size_t k = i + 1; k < InOrder.size(); k++)
		{
			InOrderRight.push_back(InOrder[k]);
			PrevOrderRight.push_back(PrevOrder[k]);
		}
		root->_left = _Rebulid(InOrderLeft, PrevOrderLeft, root->_left);
		root->_right = _Rebulid(InOrderRight, PrevOrderRight, root->_right);
		return root;
	}
private:
	Node* _root;
};

void TestRebuild()
{
	int prev[] = { 1, 2, 3, 4, 5, 6 };
	vector<int> PrevOrder(prev,prev+6);
	int in[] = { 3, 2, 4, 1, 6, 5 };
	vector<int> InOrder(in, in + 6);
	Rebuild<int> rb(InOrder,PrevOrder);
	rb.PrevOrder();
}