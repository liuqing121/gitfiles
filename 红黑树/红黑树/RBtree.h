#pragma once
#include<iostream>

using namespace std;

enum color
{
	RED,
	BLACK,
};
template<class K,class V>
struct RBtreeNode
{
	typedef RBtreeNode<K, V> Node;
	Node* _left;
	Node* _right;
	Node* _parent;

	K _key;
	V _value;
	color _color;
	RBtreeNode(const K& key, const V& value)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _key(key)
		, _value(value)
		, _color(RED)
	{}
};

template<class K,class V>
class RBtree
{
	typedef RBtreeNode<K, V> Node;
public:
	RBtree()
		:_root(NULL)
	{}
	~RBtree()
	{
		_Destory(_root);
	}
	bool IsBalance()
	{
		if (NULL == _root)
			return true;
		if (_root->_color == RED)
		{
			cout << "不平衡，根节点是黑色的" << endl;
			return false;
		}
		int count = 0; //统计最左路结点里黑结点的个数
		int num = 0;  //每路黑色结点的个数
		Node* cur = _root;
		while (cur)
		{
			if (cur->_color == BLACK)
				count++;
			cur = cur->_left;
		}
	
		return _IsBalance(_root, num, count);

	}
	bool Insert(const K& key, const V& value)
	{
		if (NULL == _root)
		{
			_root = new Node(key, value);
			_root->_color = BLACK;
		}
		Node* cur = _root;
		Node* parent = cur;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else  //关键码相同，不能插入
			{
				return false;
			}
		}
		cur = new Node(key, value);
		if (parent->_key < key)   //插右边
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else    //插左边
		{
			parent->_left = cur;
			cur->_parent=parent;
		}
		//调整颜色
		
		while (cur != _root && parent->_color == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent->_color == BLACK)
				return true;
			else   //父亲节点的颜色是红色
			{
				if (parent == grandfather->_left)
				{
					Node* uncle = grandfather->_right;
					if (uncle&&uncle->_color == RED)//uncle存在且为红
					{
						parent->_color = BLACK;
						uncle->_color = BLACK;
						grandfather->_color = RED;
						cur = grandfather;
						parent = cur->_parent;
					}
					else // (uncle->_color == BLACK)uncle不存在或者存在且为黑
					{
						if (cur == parent->_right)
						{
							_RotateL(parent);  //左旋一次转换成需要右单旋的情况
							parent = cur;
						
						}
						_RotateR(grandfather);
						parent->_color = BLACK;
						grandfather->_color = RED;

					}
				}
				else   //parent==grandfather->_right
				{
					Node* uncle = grandfather->_left;
					if (uncle&& uncle->_color == RED)
					{
						uncle->_color = parent->_color = BLACK;
						grandfather->_color = RED;
					}
					else   //uncle不存在或者存在且为黑
					{
						if (cur == parent->_left)  //把需要右左双旋的先进行右单旋，处理成左单旋的情况
						{
							_RotateR(parent);
							parent = cur;							
						}
						_RotateL(grandfather);  //此处一定是需要左单旋的
						parent->_color = BLACK;
						grandfather->_color = RED;

					}
				}
		
			}
		}
		_root->_color = BLACK;
		return true;
	}

	bool Remove()
	{
		if (NULL == _root)
			return false;
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else  //找到了进行删除
			{
				Node* del = cur;
				if (parent == NULL) //要删除的是根节点
				{
					del = _root;
				}

			}

		}
	}
protected:
	bool _IsBalance(Node* root, int num, const int&count)
	{
		if (root == NULL)
		{
			if (num == count)
				return true;
			else
			{
				cout << "黑色结点数目不相等" << endl;
				return false;
			}
		}

		if (root->_color == RED&&root->_parent->_color == RED) //连续的红结点
		{
			cout << "不平衡，连续的红结点" << root->_key << endl;
			return false;
		}
		if (root->_color == BLACK)
		{
			num++;
		}
		return _IsBalance(root->_left, num, count)&&_IsBalance(root->_right, num, count);
	}


	void _Destory(Node* root)
	{
		if (NULL == root)
			return;
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}

	void _RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		Node* ppNode = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (NULL == ppNode)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else if (parent == ppNode->_left)
		{
			ppNode->_left = subL;
			subL->_parent = ppNode;
		}
		else
		{
			ppNode->_right = subL;
			subL->_parent = ppNode;
		}

	}

	void _RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		Node* ppNode = parent->_parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (NULL == ppNode)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else if (ppNode->_left = subR)
		{
			ppNode->_left = subR;
			subR->_parent = parent;
		}
		else
		{
			ppNode->_right = subR;
			subR->_parent = parent;
		}

	}
private:
	Node* _root;
};

void TestRBtree()
{
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	RBtree<int, int> rb;
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		rb.Insert(a[i], i);
		rb.IsBalance();
	}
}