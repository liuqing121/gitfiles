#pragma once
#include<iostream>

using namespace std;

//普通二叉树寻找最远的两个结点的距离
template<class t>
struct binarytreenode
{
	binarytreenode(t value = 0)
	:_value(value), _left(NULL), _right(NULL)
	{}
	t _value;
	binarytreenode<t>* _left;
	binarytreenode<t>* _right;
};

template<class t>
class binarytree
{
public:
	typedef binarytreenode<t> node;
	binarytree()
	{}
	binarytree(t* a, size_t size, const t& invalid)
	{
		size_t index = 0;
		_root = _creattree(a, size, index, invalid);
	}
	binarytree(const binarytree<t>& bt)
	{
		_root = _copy(bt._root);
	}
	binarytree<t>& operator=(binarytree<t>& bt)
	{
		if (this != &bt)
		{
			binarytree<t> tmp(bt);
			swap(tmp._root, _root);

		}
	}
	~binarytree()
	{
		_root = _distory(_root);
	}

	node* Find(const t& n)
	{
		return _Find(_root, n);
	}
	int FindFarthestTwoNode()
	{
		int distence = 0;
		_FindFarthestTwoNode(_root, distence);
		return distence;
	}
protected:
	int _FindFarthestTwoNode(node* root,int& distence)
	{
		if (NULL == root)  
		{
			distence = 0;     //递归到空结点把上一个结点的左右最大距离清为0
			return 0;
		}
		if (root->_left == NULL && root->_right == NULL)
		{
			return 0;
		}
		int leftd=_FindFarthestTwoNode(root->_left,distence)+1;
		int rightd=_FindFarthestTwoNode(root->_right,distence)+1;
		distence = (distence > (leftd + rightd) ? distence : (leftd + rightd));
		return leftd > rightd ? leftd : rightd;
	}
	node* _Find(node* root, const t& n)
	{

		if (root == NULL)
			return NULL;
		if (root->_value == n)
			return root;
		node* left = _Find(root->_left, n);
		node* right = _Find(root->_right, n);
		return left ? left : right;
	}
	node* _distory(node* root)
	{
		if (root)
		{
			_distory(root->_left);
			_distory(root->_right);
			node* del = root;
			delete del;
		}
		return root;
	}
	node* _creattree(t*a, size_t size, size_t& index, const t& invalid)
	{
		node* root = NULL;
		if ((index < size) && (a[index] != invalid))
		{
			root = new node(a[index]);
			root->_left = _creattree(a, size, ++index, invalid);
			root->_right = _creattree(a, size, ++index, invalid);
		}
		return root;
	}

	node* _copy(node* copyroot)
	{
		node* root = NULL;
		if (copyroot != NULL)
		{
			root = new node(copyroot->_value);
			root->_left = _copy(copyroot->_left);
			root->_right = _copy(copyroot->_right);
		}
		return root;
	}
private:
	node* _root;
};

void TestFindNearParent()
{
	int array1[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	binarytree<int> bt(array1, 15, '#');
	cout<<bt.FindFarthestTwoNode();
}