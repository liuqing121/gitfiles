//#pragma once
//#include<iostream>
//#include<cassert>
//#include<queue>
//#include<stack>
//using namespace std;
//
//template<class T>
//struct BinaryTreeNode
//{
//	BinaryTreeNode(T value = 0)
//	:_value(value), _left(NULL), _right(NULL)
//	{}
//	T _value;
//	BinaryTreeNode<T>* _left;
//	BinaryTreeNode<T>* _right;
//};
//
//template<class T>
//class BinaryTree
//{
//public:
//	typedef BinaryTreeNode<T> Node;
//	BinaryTree()
//	{}
//	explicit BinaryTree(T* a, size_t size, const T& invalid)
//	{
//		stack<Node*> s;
//		size_t index = 0;
//		Node* cur = NULL;
//		while (index < size)
//		{
//			while ((index < size) && (a[index] != invalid))
//			{
//				if (index == 0)
//				{
//					_root = new Node(a[index++]);
//					cur = _root;
//				}
//				else
//				{
//					cur->_left = new Node(a[index++]);
//					cur = cur->_left;
//				}
//				s.push(cur);
//			}
//			index++;
//			Node* top = s.top();
//			s.pop();
//			if ((index < size) && (a[index] != invalid))
//			{
//				cur = top;
//				cur->_right = new Node(a[index++]);
//				cur = cur->_right;
//				s.push(cur);
//			}
//		}
//	}
//
//	BinaryTree(const BinaryTree<T>& bt)
//	{
//		Node* cur = bt._root;
//		Node* root = NULL;
//		stack<Node*>s;
//		stack<Node*>s1;
//		while (cur || !s.empty())
//		{
//			while (cur)
//			{
//				s.push(cur);
//				if (root == NULL)
//				{
//					root = new Node(cur->_value);
//					_root = root;
//				}
//				else
//				{
//					root->_left = new Node(cur->_value);
//					root = root->_left;
//				}
//				cur = cur->_left;
//				s1.push(root);
//			}
//			Node* top = s.top();
//			Node* top1 = s1.top();
//			s.pop();
//			s1.pop();
//
//			cur = top->_right;
//			if (cur)
//			{
//				root = top1;
//				root->_right = new Node(cur->_value);
//				root = root->_right;
//				cur = cur->_left;
//			}
//		}
//	}
//
//	BinaryTree<T>& operator=(BinaryTree<T> bt)
//	{
//		swap(_root, bt._root);
//		return *this;
//	}
//
//	void PrevOrderNoR()
//	{
//		Node* cur = _root;
//		stack<Node*> s;
//		while (cur || !s.empty())
//		{
//			while (cur)
//			{
//				cout << cur->_value << " ";
//				s.push(cur);
//				cur = cur->_left;
//			}
//			Node* top = s.top();
//			s.pop();
//			cur = top->_right;
//		}
//		cout << endl;
//	}
//	void InOrderNoR()
//	{
//		Node* cur = _root;
//		stack<Node*> s;
//		while (cur || !s.empty())
//		{
//			while (cur)
//			{
//				s.push(cur);
//				cur = cur->_left;
//			}
//			Node* top = s.top();
//			s.pop();
//			cout << top->_value << " ";
//			cur = top->_right;
//		}
//		cout << endl;
//	}
//
//	void PostOrderNoR()
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
//			if ((top->_right == NULL) || (prev == top->_right))
//			{
//				prev = top;
//				cout << top->_value << " ";
//				s.pop();
//				//cur = top->_right;
//			}
//			else
//				cur = top->_right;
//		}
//		cout << endl;
//	}
//
//	size_t SizeNoR()
//	{
//		size_t size = 0;
//		Node* cur = _root;
//		stack<Node*> s;
//		while (cur || !s.empty())
//		{
//			while (cur)
//			{
//				s.push(cur);
//				size++;
//				cur = cur->_left;
//			}
//			Node* top = s.top();
//			s.pop();
//			cur = top->_right;
//		}
//		return size;
//	}
//
//	size_t DepthNoR()
//	{
//		if (_root == NULL)
//			return 0;
//		size_t depth = 0;
//		Node* cur = NULL;
//		queue<Node*> q;
//		size_t VisitNum = 0;  //有多少数据出栈
//		size_t NodeNum = 1;
//		size_t LeveNum = 1;  //每一层最后一个数据的序号
//		q.push(_root);
//		while (!q.empty())
//		{
//			cur = q.front();
//			q.pop();
//			VisitNum++;
//			
//			if (cur->_left)
//			{
//				NodeNum++;
//				q.push(cur->_left);
//			}
//			if (cur->_right)
//			{
//				NodeNum++;
//				q.push(cur->_right);
//			}
//			if (LeveNum == VisitNum)
//			{
//				depth++;
//				LeveNum = NodeNum;
//			}
//		}
//		return depth;
//	}
//
//	size_t LeveNum()  //叶子节点个数
//	{
//		size_t count = 0;
//		Node* cur = _root;
//		stack<Node*> s; 
//		while (cur || !s.empty())
//		{
//			while (cur)
//			{
//				s.push(cur);
//				if ((cur->_left == NULL) && (cur->_right == NULL))
//					count++;
//				cur = cur->_left;
//			}
//
//			Node* top = s.top();
//			s.pop();
//			cur = top->_right;
//		}
//		return count;
//	}
//	size_t GetKLeve(size_t k)  //得到第k层结点个数。
//	{
//		assert(k <= DepthNoR());
//		if (k == 1)
//			return 1;
//		queue<Node*>q;
//		size_t NodeNum = 1;
//		size_t LeveNum = 1;
//		size_t VisitNum = 0;
//		size_t leve = 1;
//		q.push(_root);
//		while (!q.empty())
//		{
//			Node* cur = q.front();
//			q.pop();
//			VisitNum++;
//			if (cur->_left)
//			{
//				q.push(cur->_left);
//				NodeNum++;
//			}
//			if (cur->_right)
//			{
//				q.push(cur->_right);
//				NodeNum++;
//			}
//			if (LeveNum == VisitNum)
//			{
//				leve++;
//				if (leve == k)
//					break;
//				LeveNum = NodeNum;
//			}
//		}
//		return NodeNum - VisitNum;
//	}
//private:
//	Node* _root;
//};
//
//void test()
//{
//	int array[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
//	BinaryTree<int> bt(array, 10, '#');
//	bt.PrevOrderNoR();
//	bt.InOrderNoR();
//	bt.PostOrderNoR();
//	BinaryTree<int> bt1(bt);
//	bt1.PrevOrderNoR();
//	BinaryTree<int> bt2 = bt1;
//	bt2.PrevOrderNoR();
//	cout << bt.SizeNoR() << endl;
//	cout << bt.DepthNoR() << endl;
//	cout << bt.LeveNum() << endl;
//	cout << bt.GetKLeve(3) << endl;
//}