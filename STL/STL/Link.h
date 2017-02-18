//#pragma once
//#include<iostream>
//#include<cassert>
//using namespace std;
//
//template <class T>
//struct LinkNode
//{
//	typedef LinkNode<T> node;
//	LinkNode(T n=0)
//		:_data(n), _prev(0), _next(0)
//	{}
//	T _data;
//	node * _prev;
//	node * _next;
//};
//
//
//template <class T,class Ptr,class Ref>
//class LinkIterator
//{
//public:
//	typedef LinkIterator<T, Ptr, Ref> Self;
//	typedef LinkIterator<T, T*, T&> Iterator;
//	typedef LinkNode<T> node;
//
//	LinkIterator(node* x)
//		:_node(x)
//	{}
//	LinkIterator()
//	{}
//	LinkIterator(const Self& it)
//	{
//		_node = it._node;
//	}
//	bool operator==(const Self& it)
//	{
//		return _node == it._node;
//	}
//	bool operator!=(const Self& it)
//	{
//		return _node != it._node;
//	}
//	Ref operator*()
//	{
//		return _node->_data;
//	}
//
//	Ptr operator->()
//	{
//		return &(_node->_data);
//	}
//
//	Self& operator++()
//	{
//		_node = _node->_next;
//		return *this;
//	}
//
//	Self operator++(int)
//	{
//		Self tmp(*this);
//		_node = _node->_next;
//		return tmp;
//	}
//
//	Self& operator--()
//	{
//		_node = _node->_prev;
//		return *this;
//	}
//
//	Self operator--(int)
//	{
//		Self tmp(*this);
//		_node = _node->_prev;
//		return tmp;
//	}
//	node* _node;
//
//};
//template <class T>
//class Link
//{
//public:
////	typedef LinkIterator<T, Ptr, Ref> Self;
//	typedef LinkIterator<T, T*, T&> Iterator;
//	typedef Link<T> link;
//	typedef LinkNode<T> node;
//	typedef node* node_type;
//	Link()
//		:_head(new node(T()))
//	{
//		_head->_next = _head;
//		_head->_prev = _head;
//	}
//	~Link()
//	{
//		Clear();
//		delete _head;
//		_head = NULL;
//	}
//	/*****************插入相关操作**********************/
//	void PushBack(T x)   //尾插
//	{
//		/*node* NewNode = BuyNewNode(x);
//		node* tmp = _head->_prev;
//		NewNode->_prev = tmp;
//		NewNode->_next = _head;
//		tmp->_next = NewNode;
//		_head->_prev = NewNode;*/
//		Insert(End(), x);
//	}
//	void PushFront(T x)   //头插
//	{
//		Insert(Begin(), x);
//	}
//
//	Iterator Insert(Iterator pos, const T& x) // 在pos前插入值t的元素，返回新添加元素的迭代器  
//	{
//		node_type NewNode = BuyNewNode(x);
//		node_type cur = pos._node;
//		NewNode->_next = cur;
//		cur->_prev->_next = NewNode;
//		NewNode->_prev = cur->_prev;
//		cur->_prev = NewNode;
//		return Iterator(NewNode);
//	}
//
//	void Insert(Iterator pos, size_t n, const T &t)//在pos前插入n个值为t的元素 
//	{
//		for (size_t i = 0; i < n; i++)
//		{
//			Insert(pos, t);
//		}
//	}
//	void Insert(Iterator pos, Iterator b, Iterator e)//在pos前插入[b,e)范围的元素
//	{
//		for (Iterator tmp = b; tmp != e; tmp++)
//		{
//			Insert(pos, tmp._node->_data);
//		}
//	}
//	node* BuyNewNode(T x=0)
//	{
//		node*tmp = new node(x);
//		tmp->_next = tmp;
//		tmp->_prev = tmp;
//		return tmp;
//	}
//
//
//	
//	/**********删除相关操作*******************/
//	Iterator Erase(Iterator it)//删除it所指向的元素，返回所删除元素的下一个元素对应的迭代器  
//	{
//		assert(it != End());
//		node_type cur = it._node;
//		node_type del = cur;
//		cur = cur->_next;
//		cur->_prev = del->_prev;
//		del->_prev->_next = cur;
//		delete del;
//		del = NULL;
//		return Iterator(cur);
//	}
//	void Clear()//删除容器内的所有元素  
//	{
//		node_type cur = _head->_next;
//		while (cur != _head)
//		{
//			node* del = cur;
//			cur = cur->_next;
//			delete del;
//			del = NULL;
//		}
//	}
//	void PopBack()//删除容器内最后一个有效的元素  
//	{
//		Erase(--End());
//	}
//	void PopFront()//删除容器内第一个有效的元素 
//	{
//		Erase(Begin());
//	}
//	/***************访问相关*******************/
//	Iterator Begin()
//	{
//		return Iterator(_head->_next);
//	}
//
//	Iterator End()
//	{
//		return Iterator(_head);
//	}
//
//	T& Front()
//	{
//		return _head->_next->_data;
//	}
//
//	T& Back()
//	{
//		return _head->_prev->_data;
//	}
//	bool Empty() const
//	{
//		return _head->_next == _head;
//	}
//
//	size_t Size()
//	{
//		size_t count = 0;
//		for (Iterator it = Begin(); it != End(); it++)
//		{
//			count++;
//		}
//		return count;
//	}
//
//	
//
//
//private:
//	node_type _head;
//};