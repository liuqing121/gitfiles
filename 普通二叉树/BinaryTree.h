#pragma once
#include<iostream>
#include<queue>
using namespace std;

template<class t>
struct binarytreenode
{
	binarytreenode(t value=0)
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
		_root=_creattree( a, size,index, invalid);
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
		_root=_distory(_root);
	}

	void prevorder()
	{
		_prevorder(_root);
		cout << endl;
	}
	void inorder()
	{
		_inorder(_root);
		cout << endl;
	}
	void postorder()
	{
		_postorder(_root);
		cout << endl;
	}
	void levelorder()  //层序遍历
	{
		_levelorder(_root);
		cout << endl;
	}

	size_t size()
	{
		return _size(_root);
	}
	size_t depth()
	{
		return _depth(_root);
	}
	size_t leafsize()
	{
		return _leafsize(_root);
	}
	size_t getklevel(size_t k)  //第k层结点个数
	{

	}
protected:

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
	node* _creattree( t*a, size_t size,size_t& index,const t& invalid)
	{
		node* root = NULL;
		if ((index < size)&&(a[index] != invalid))
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
		if (copyroot!=NULL)
		{
			root = new node(copyroot->_value);
			root->_left = _copy(copyroot->_left);
			root->_right = _copy(copyroot->_right);
		}
		return root;
	}

	node* _prevorder(node* root)
	{
		if (root)
		{
			cout << root->_value << " ";
			_prevorder(root->_left);
			_prevorder(root->_right);
		}
		return root;
	}

	node* _inorder(node* root)
	{
		if (root)
		{
			_inorder(root->_left);
			cout << root->_value<<" ";
			_inorder(root->_right);
		}
		return root;
	}

	node* _postorder(node* root)
	{
		if (root)
		{
			_postorder(root->_left);
			_postorder(root->_right);
			cout << root->_value << " ";
		}
		return root;
	}

	void _levelorder(node* root)
	{
		queue<node*> q;
		q.push(root);
		while (!q.empty())
		{
			node* tmp = q.front();
			cout << tmp->_value<<" ";
			
			if (tmp->_left)
				q.push(tmp->_left);
			if (tmp->_right)
				q.push(tmp->_right);
			q.pop();
		}
	}

	size_t _size(node* root)
	{
		size_t size = 0;
		if (root)
		{
			size = _size(root->_left) + _size(root->_right)+1;
		}
		return size;
	}

	size_t _depth(node* root)
	{
		size_t depth1 = 0;
		size_t depth2 = 0;
		if (root)
		{
			depth1 = _depth(root->_left) + 1;
			depth2 = _depth(root->_right) + 1;
		}
		return depth1 > depth2 ? depth1 : depth2;
	}

	size_t _leafsize(node* root)
	{
		if (root == NULL)
			return 0;
		else if (root->_left == NULL&&root->_right == NULL)
			return 1;
		return _leafsize(root->_left) + _leafsize(root->_right);
	}
private:
	node* _root;
};

void test()
{
	int array[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int array1[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	binarytree<int> bt(array, 10, '#');
	bt.prevorder();
	bt.inorder();
	bt.postorder();
	cout << bt.size() << endl;
	cout << bt.depth() << endl;
	cout << bt.leafsize() << endl;
	binarytree<int> bt2(array1, 15, '#');
	bt2.inorder();
	cout << bt2.depth() << endl;
	cout << bt2.leafsize() << endl;
	binarytree<int> bt3(bt);
	bt3.prevorder();
	binarytree<int> bt4=bt3;
	bt4.prevorder();
	bt4.levelorder();
}