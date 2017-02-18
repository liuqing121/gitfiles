//#pragma once
//#include<iostream>
//#include<queue>
//#include<stack>
//using namespace std;
//
//template<class t>
//struct binarytreenode
//{
//	binarytreenode(t value = 0)
//	:_value(value), _left(NULL), _right(NULL)
//	{}
//	t _value;
//	binarytreenode<t>* _left;
//	binarytreenode<t>* _right;
//};
//
//template<class t>
//class binarytree
//{
//public:
//	typedef binarytreenode<t> node;
//	binarytree()
//	{}
//	binarytree(t* a, size_t size, const t& invalid)
//	{
//		size_t index = 0;
//		_root = _creattree(a, size, index, invalid);
//	}
//	binarytree(const binarytree<t>& bt)
//	{
//		_root = _copy(bt._root);
//	}
//	binarytree<t>& operator=(binarytree<t>& bt)
//	{
//		if (this != &bt)
//		{
//			binarytree<t> tmp(bt);
//			swap(tmp._root, _root);
//
//		}
//	}
//	~binarytree()
//	{
//		_root = _distory(_root);
//	}
//	bool IsCompleteTree()
//	{
//		queue<node*> q;
//		q.push(_root);
//		node* cur = q.front();
//		while ((cur = q.front()) != NULL)
//		{
//			q.push(cur->_left);
//			q.push(cur->_right);
//			q.pop();
//		}
//		while (!q.empty())
//		{
//			cur = q.front();
//			if (cur != NULL)
//				return false;
//			q.pop();
//		}
//		return true;
//
//	}
//
//
//protected:
//
//	node* _distory(node* root)
//	{
//		if (root)
//		{
//			_distory(root->_left);
//			_distory(root->_right);
//			node* del = root;
//			delete del;
//		}
//		return root;
//	}
//	node* _creattree(t*a, size_t size, size_t& index, const t& invalid)
//	{
//		node* root = NULL;
//		if ((index < size) && (a[index] != invalid))
//		{
//			root = new node(a[index]);
//			root->_left = _creattree(a, size, ++index, invalid);
//			root->_right = _creattree(a, size, ++index, invalid);
//		}
//		return root;
//	}
//
//	node* _copy(node* copyroot)
//	{
//		node* root = NULL;
//		if (copyroot != NULL)
//		{
//			root = new node(copyroot->_value);
//			root->_left = _copy(copyroot->_left);
//			root->_right = _copy(copyroot->_right);
//		}
//		return root;
//	}
//private:
//	node* _root;
//};
//
//void TestIsCompleteTree()
//{
//	int array[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
//	int array1[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
//	binarytree<int> bt(array1, 15, '#');
//	cout<<bt.IsCompleteTree();
//}