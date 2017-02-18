//#pragma once
//#include<iostream>
//
//using namespace std;
//
//template<class K>
//struct SelectBinaryTreeNode
//{
//	typedef SelectBinaryTreeNode<K> Node;
//	K _key;
//	Node* _left;
//	Node* _right;
//	SelectBinaryTreeNode(const K& key)
//		:_key(key)
//		, _left(NULL)
//		, _right(NULL)
//	{}
//};
//
//template<class K>
//class SelectBinaryTree
//{
//public:
//	typedef SelectBinaryTreeNode<K> Node;
//	SelectBinaryTree()
//	{}
//	~SelectBinaryTree()   //析构，递归实现
//	{
//		_Destory(_root);
//	}
//
//	bool Insert(const K& key)    //非递归插入
//	{
//		if (NULL == _root)
//		{
//			_root = new Node(key);
//			return true;
//		}
//		Node* cur = _root;
//		Node* parent = NULL;
//		while (cur)
//		{
//			if (cur->_key < key)
//			{
//				parent = cur;
//				cur = cur->_right;
//			}
//			else if (cur->_key>key)
//			{
//				parent = cur;
//				cur = cur->_left;
//			}
//			else
//				return false;
//		}
//		if (parent->_key < key)
//		{
//			parent->_right = new Node(key);
//		}
//		else
//			parent->_left = new Node(key);
//		return true;
//	}
//
//	bool InsertR(const K& key)    //递归插入
//	{
//		return _InsertR(_root, key);
//	}
//	Node* Find(const K& k)
//	{
//		return _FindR(_root, k);
//	}
//	K FindNearestParent(const K& key1, const K& key2)
//	{
//		Node* node1 = Find(key1);
//		Node* node2 = Find(key2);
//		if (node1 == NULL || node2 == NULL)
//		{
//			return -1;
//		}
//		K min = 0;
//		K max = 0;
//		if (key1 > key2)
//		{
//			min = key2;
//			max = key1;
//		}
//		else
//		{
//			min = key1;
//			max = key2;
//		}
//		Node* cur = _root;
//		while (cur)
//		{
//			if (cur->_key >= min && cur->_key <= max)
//			{
//				return cur->_key;
//			}
//			else if (cur->_key <= min && cur->_key <= max)
//			{
//				cur = cur->_right;
//			}
//			else
//			{
//				cur = cur->_left;
//			}
//		}
//		return -1;
//	}
//protected:
//	Node* _FindR(Node* root, const K& key)
//	{
//		if (NULL == root)
//			return NULL;
//		if (root->_key == key)
//			return root;
//		else if (root->_key < key)
//			_FindR(root->_right, key);
//		else if (root->_key>key)
//			_FindR(root->_left, key);
//
//	}
//	bool _InsertR(Node*& root, const K& key)
//	{
//		if (NULL == root)
//		{
//			root = new Node(key);
//			return true;
//		}
//		if (root->_key < key)
//			return _InsertR(root->_right, key);
//		else if (root->_key>key)
//			return _InsertR(root->_left, key);
//		else
//			return false;
//	}
//
//	void _Destory(Node* root)
//	{
//		Node* cur = root;
//		while (cur)
//		{
//			Node* del = cur;
//			cur = cur->_right;
//			delete del;
//		}
//	}
//
//private:
//	Node* _root;
//};
//
//void TestFindNearestParent()
//{
//	SelectBinaryTree<int> sbt;
//	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
//	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++)
//	{
//		sbt.InsertR(a[i]);
//	}
//	cout << sbt.FindNearestParent(8, 9) << endl;
//
//}
//
//普通二叉树寻找最近的父节点
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
//
//	node* Find(const t& n)
//	{
//		return _Find(_root, n);
//	}
//	t FindNearParent(const t& n1, const t& n2)
//	{
//		node* node1 = Find(n1);
//		node* node2 = Find(n2);
//		if (node1 == NULL || node2 == NULL)  //若传过来的结点不在树内
//		{
//			throw std::invalid_argument("结点不在树内");
//		}
//		node* ret=_FindNearParent(_root, node1, node2);
//		return ret->_value;
//	}
//protected:
//	node* _FindNearParent(node* root, node* n1, node*n2)
//	{
//		if (NULL == root)
//			return NULL;
//		if (root == n1 || root == n2)  //找到了其中一个结点
//		{
//			return root;
//		}
//		node* left = _FindNearParent(root->_left, n1, n2);
//		node* right = _FindNearParent(root->_right, n1, n2);
//		if (left&&right)   //left和right都存在，说明结点分别在root的左右
//		{
//			return root;
//		}
//		return left ? left : right;  //左右哪个不为空返回哪个，说明两个结点都在一侧
//	}
//	node* _Find(node* root,const t& n)
//	{
//		
//		if (root == NULL)
//			return NULL;
//		if (root->_value == n)
//			return root;
//		 node* left=_Find(root->_left, n);
//		 node* right=_Find(root->_right, n);
//		 return left ? left : right;
//	}
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
//void TestFindNearParent()
//{
//		int array1[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
//		binarytree<int> bt(array1, 15, '#');
//		try{
//			cout << bt.FindNearParent(0, 8);
//		}
//		catch (exception &e)
//		{
//			cout << e.what() << endl;
//		}
//}