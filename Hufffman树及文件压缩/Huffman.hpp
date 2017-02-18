#pragma once
#include<iostream>
#include"Heap.h"
#include"Press.h"
using namespace std;

template<class T>
struct HuffmanTreeNode
{
	typedef HuffmanTreeNode<T> Node;
	T _weight;
	Node* _left;
	Node* _right;
	Node* _parent;
	HuffmanTreeNode(const T& w)
		:_weight(w),
		_left(NULL),
		_right(NULL),
		_parent(NULL)
	{}
};

template<class T>
class HuffmanTree
{
public:
	typedef HuffmanTreeNode<T> Node;
	HuffmanTree()
		:_root(NULL)
	{}
	~HuffmanTree()
	{
		_destory(_root);
	}
	Node* GetRoot()
	{
		return _root;
	}
	template<class T>
	struct Less
	{
		bool operator()(const T& left, const T&right)
		{
			return left->_weight < right->_weight;
		}
	};
	HuffmanTree(T* a, int size,T invalid)   //构建Huffman树
	{
		
		Heap<Node* , Less<Node*>> hp;   //建小堆
		for (int i = 0; i<size; i++)
		{
			if (a[i] != invalid)
			{
				Node* tmp = new Node(a[i]);
				hp.Push(tmp);
			}
				
		}
		while (hp.Size()>1)
		{		
			Node* left = hp.Top();
			hp.Pop();

			Node* right = hp.Top();
			hp.Pop();

			Node* parent = new Node(left->_weight + right->_weight);
			hp.Push(parent);

			parent->_left = left;
			parent->_right = right;
			left->_parent = parent;
			right->_parent = parent;
		}
		_root = hp.Top();
	}
protected:
	void _destory(Node* root)
	{
		if (NULL == root)
			return;
		_destory(root->_left);
		_destory(root->_right);
		
		delete root;
	}
private:
	Node* _root;
};