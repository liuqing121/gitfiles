//#pragma once
//#include<iostream>
//#include<stack>
//using namespace std;
//enum PointerTag
//{
//	THREND,
//	LINK,
//};
//template<class T>
//struct BinaryTreeThdNode
//{
//	typedef BinaryTreeThdNode<T> Node;
//	BinaryTreeThdNode(T data)
//		:_data(data), _left(NULL), _right(NULL),_father(NULL), _leftTag(LINK), _rightTag(LINK)
//	{}
//	T _data;
//	Node* _left;
//	Node* _right;
//	Node* _father;
//	PointerTag _leftTag;
//	PointerTag _rightTag;
//};
//
//template<class T,class Ptr,class Ref>
//class TreeIterator
//{
//public: 
//	typedef TreeIterator<T, Ptr, Ref> self;
//	typedef TreeIterator<T, T*, T&> Iterator;
//	typedef BinaryTreeThdNode<T> Node;
//	TreeIterator(Node* p)
//		:ptr(p)
//	{}
//	TreeIterator()
//	{}
//
//	self& operator++()
//	{
//		if (ptr->_rightTag == THREND)
//		{
//			ptr = ptr->_right;
//		}
//		else if (ptr->_rightTag == LINK)
//		{
//			Node* tmp = ptr->_right;
//			while (tmp&&tmp->_leftTag == LINK)
//			{
//				tmp = tmp->_left;
//			}
//			ptr = tmp;
//		}
//		return *this;
//	}
//	bool operator!=(Iterator it)
//	{
//		return !(ptr == it.ptr);
//	}
//	Ref operator*()
//	{
//		return ptr->_data;
//	}
//private:
//	Node* ptr;
//};
//template<class T>
//class BinaryTreeThd
//{
//public:
//	typedef BinaryTreeThdNode<T> Node;
//	typedef TreeIterator<T, T*, T&> Iterator;
//	BinaryTreeThd()
//	{}
//	BinaryTreeThd(T* arr, size_t size, T invalid)
//	{
//		stack<Node*> s;
//		size_t index = 0;
//		Node* cur = NULL;
//		while (index < size)
//		{
//			while (index < size && (arr[index] != invalid))
//			{
//				if (index == 0)
//				{
//					cur = new Node(arr[index++]);
//					_root = cur;
//				}
//				else
//				{
//					cur->_left = new Node(arr[index++]);
//					Node* tmp = cur;
//					cur = cur->_left;
//					cur->_father = tmp;
//				}
//				s.push(cur);
//			}
//			index++;
//			Node* top = s.top();
//			s.pop();
//			if ((index<size)&&(arr[index] != invalid))
//			{
//				cur = top;
//				cur->_right = new Node(arr[index++]);
//				Node* tmp = cur;
//				cur = cur->_right;
//				cur->_father = tmp;
//				s.push(cur);
//			}
//		}
//	}
//	void InorderThreading()
//	{
//		Node* prev = NULL;
//		_InorderThreading(_root, prev);
//	}
//	void _InorderThreading(Node* cur,Node*& prev)
//	{
//		if (cur == NULL)
//			return;
//		_InorderThreading(cur->_left, prev);
//		if (cur->_left == NULL)
//		{
//			cur->_leftTag = THREND;
//			cur->_left = prev;
//		}
//		if (prev && (prev->_right == NULL))
//		{
//			prev->_rightTag = THREND;
//			prev->_right = cur;
//		}
//		prev = cur;
//		_InorderThreading(cur->_right, prev);
//
//		
//	}
//	void InorderThreading()
//	{
//		Node* cur = _root;
//		Node* prev = NULL;
//		stack<Node*> s;
//		while (cur || !s.empty())
//		{
//			while (cur)
//			{
//				s.push(cur);
//				cur = cur->_left;
//			}
//			Node* top = s.top();
//		
//			if ((top->_left == NULL))
//			{
//				top->_left = prev;
//				top->_leftTag = THREND;
//			}
//			
//			if (prev&&(prev->_right == NULL))
//			{
//				prev->_rightTag = THREND;
//				prev->_right = top;
//			}
//			prev = top;
//			if (top->_right != NULL)
//				cur = top->_right;
//			s.pop();
//			
//		}
//	}
//
//
//	void InOrder()
//	{
//		Node* cur = _root;
//		while (cur)
//		{
//			while (cur->_leftTag == LINK)
//			{
//				cur = cur->_left;
//			}
//			cout << cur->_data << " ";
//			while (cur->_rightTag == THREND)
//			{
//				cur = cur->_right;
//				cout << cur->_data << " ";
//			}
//			cur = cur->_right;
//		}
//		cout << endl;
//	}
//
//	void PrevOrderThreading()
//	{
//		Node* cur = _root;
//		Node* prev = NULL;
//		stack<Node*> s;
//		s.push(cur);
//		while (cur || !s.empty())
//		{
//			Node* top = NULL;
//			if (!s.empty())
//			{
//				top = s.top();
//			}
//			else
//				return;
//			s.pop();
//			if (top->_right)
//				s.push(top->_right);
//			if (top->_left)
//				s.push(top->_left);
//
//			if (top->_left == NULL)
//			{
//				top->_leftTag = THREND;
//				top->_left = prev;
//			}
//			if (prev&&prev->_right == NULL)
//			{
//				prev->_rightTag = THREND;
//				prev->_right = top;
//			}
//			prev = top;
//		}
//
//	}
//	void PrevOrder()
//	{
//		Node* cur = _root;
//		while (cur)
//		{
//			while (cur->_leftTag == LINK)
//			{
//				cout << cur->_data << " ";
//				cur = cur->_left;
//			}
//			cout << cur->_data << " ";
//			if (cur->_rightTag == THREND)
//			{
//				
//				cur = cur->_right;
//			}
//			if (cur->_rightTag == LINK)
//				cur = cur->_right;
//			while (cur != NULL)
//			{
//				if (cur->_left&&cur->_leftTag == LINK)
//					break;
//				cout << cur->_data << " ";
//				cur = cur->_right;
//			}
//		}
//		cout << endl;
//	}
//
//	void PostOrderThd()
//	{
//		Node* prev = NULL;
//		_PostOrderThd(_root, prev);
//	}
//
//	void PostOrder()
//	{
//		Node* cur = _root;
//		Node* prev = NULL;
//		while (cur)
//		{
//			while (cur->_left!=prev&&cur->_leftTag == LINK)
//			{
//				cur = cur->_left;
//			}
//			
//			while (cur&&cur->_rightTag == THREND)
//			{
//				cout << cur->_data << " ";
//				prev = cur;
//				cur = cur->_right;
//			}
//			
//			while (cur&&(prev==cur->_right))
//			{
//				cout << cur->_data << " ";
//				prev = cur;
//				cur = cur->_father;
//			}
//			if (cur&&cur->_rightTag == LINK)
//			{
//				cur = cur->_right;
//			}
//
//		}
//		cout << endl;
//	}
//	/***************µü´úÆ÷²¿·Ö**************/
//	Iterator Begin()
//	{
//		Node* cur = _root;
//		while (cur->_leftTag)
//			cur = cur->_left;
//		return Iterator(cur);
//	}
//	Iterator End()
//	{
//		Node* cur = _root;
//		while (cur!=NULL)
//		{
//			cur = cur->_right;
//		}
//		return Iterator(cur);
//	}
//protected:
//	void _PostOrderThd(Node* cur, Node*& prev)
//	{
//		if (cur == NULL)
//			return;
//		_PostOrderThd(cur->_left, prev);
//		_PostOrderThd(cur->_right, prev);
//
//		if (cur->_left == NULL)
//		{
//			cur->_leftTag = THREND;
//			cur->_left = prev;
//		}
//		if (prev && (prev->_right == NULL))
//		{
//			prev->_rightTag = THREND;
//			prev->_right = cur;
//		}
//		prev = cur;
//	}
//private:
//	Node* _root;
//
//};
//
//void test()
//{
//	int array[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
//	int array1[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
//	BinaryTreeThd<int> bt(array, 10, '#');
//	bt.InorderThreading();
//	bt.InOrder();
//	BinaryTreeThd<int> bt1(array1, 15, '#');
//	bt1.InorderThreading();
//	bt1.InOrder();
//	/*bt.PrevOrderThreading();
//	bt.PrevOrder();
//	bt1.PrevOrderThreading();
//	bt1.PrevOrder();*/
//	bt.PostOrderThd();
//	bt.PostOrder();
//	bt1.PostOrderThd();
//	bt1.PostOrder();
//}
//
//void TestInOrderIter()
//{
//	int array[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
//	int array1[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
//	BinaryTreeThd<int> bt(array, 10, '#');
//	bt.InorderThreading();
//	BinaryTreeThd<int>::Iterator it;
//	for (it = bt.Begin(); it != bt.End();++it)
//	{
//		cout << *it << " ";
//	}
//	cout << endl;
//	BinaryTreeThd<int>bt1(array1, 15, '#');
//	bt1.InorderThreading();
//	BinaryTreeThd<int>::Iterator it1;
//	for (it1 = bt1.Begin(); it1 != bt1.End(); ++it1)
//	{
//		cout << *it1 << " ";
//	}
//	cout << endl;
//
//}