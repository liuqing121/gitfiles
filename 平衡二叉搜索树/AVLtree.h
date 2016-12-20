#include<iostream>

using namespace std;

template<class K,class V>
struct AVLtreeNode
{
	typedef AVLtreeNode<K, V> Node;
	Node* _left;
	Node* _right;
	Node* _parent;

	K _key;
	V _value;
	int _bf;
	AVLtreeNode(const K& key,const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _bf(0)
	{}
};

template<class K,class V>
class AVLtree
{
	typedef AVLtreeNode<K, V> Node;
public:
	AVLtree()
		:_root(NULL)
	{}
	~AVLtree()
	{

	}
	bool Insert(const K& key, const V& value)
	{
		if (NULL == _root)
		{
			_root = new Node(key, value);
			return true;
		}
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
			else
			{
				return false;
			}

		}
		if (parent->_key < key)
		{
			Node* tmp = new Node(key, value);
			parent->_right = tmp;
			tmp->_parent = parent;
			parent->_bf++;
		}
		if (parent->_key>key)
		{
			Node* tmp = new Node(key, value);
			parent->_left = tmp;
			tmp->_parent = parent;
			parent->_bf--;
		}
		while (parent)
		{
			if (parent->_bf == 0)  //原来是1或者-1，那插入以后不会对树的高度有影响;
			{
				return true;
			}
			else if (parent->_bf == 1 || parent->_bf == -1) //原来是0，对树的高度有影响
			{
				Node* pparent = parent->_parent;
				if (pparent != NULL)
				{
					if (pparent->_left == parent)// 左树上高度增加
						pparent->_bf--;
					else //右树上高度增加
						pparent->_bf++;
				}

				parent = pparent;
			}
			else //平衡因子是2/-2，从1或者-1变过来，不满足平衡树，需要旋转
			{
				if (parent->_bf == 2)  //右树过高
				{
					if (parent->_right->_bf == 1) //需要左旋结构
					{
						_RotateL(parent);
						return true;
					}
					else if (parent->_right->_bf = -1)  //需要右左旋结构
					{
						_RotateRL(parent);
						return true;
					}
				}
				else //平衡因子为-2
				{
					if (parent->_left->_bf == -1)  //需要右单旋的结构
					{
						_RotateR(parent);
						return true;
					}
					else if (parent->_left->_bf == 1) //需要左右旋的结构
					{
						_RotateLR(parent);
						return true;
					}
				}
			}
		}
	}
	bool Remove(const K& key, const V& value)
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
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else    //找到了进行删除
			{
				if (parent == NULL)  //要删除的是根节点
				{
					delete _root;
					return true;
				}
				Node* del = cur;
				if (cur->_left == NULL)
				{
					if (parent->_left == cur)
					{
						parent->_left = cur->_right;
						if (cur->_right)
						cur->_right->_parent = parent;
						parent->_bf++;
					}
					else
					{
						parent->_right = cur->_right;
						if (cur->_right)
						cur->_right->_parent = parent;
						parent->_bf--;
					}
				    
				}
				else if (cur->_right == NULL)
				{
					if (parent->_left == cur)
					{
						parent->_left = cur->_left;
						if (cur->_left)
							cur->_left->_parent = parent;
						parent->_bf++;
					}
					else
					{
						parent->_right = cur->_left;
						if (cur->_left)
							cur->_left->_parent = parent;
						parent->_bf--;
					}
				}
				else  //两边都不为空
				{
					Node* pcur = cur->_right;
					Node* ppNode = pcur;
					while (pcur->_left)
					{
						ppNode = pcur;
						pcur = pcur->_left;
					}
					cur->_key = pcur->_key;
					cur->_value = pcur->_value;
					del = pcur;

					if (ppNode->_left == pcur)
					{
						ppNode->_left = pcur->_right;
						if (pcur->_right)
							pcur->_right->_parent = ppNode;
						ppNode->_bf++;
					}
					else
					{
						ppNode->_right = pcur->_right;
						if (pcur->_right)
							pcur->_right->parent = ppNode;
						ppNode->_bf--;
					}
				}
			}
			delete del;
			return true;
		}
	}

	bool IsBalance()
	{
		return _IsBalance(_root);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

protected:
	bool _IsBalance(Node* root)
	{
		if (NULL == root)
			return true;
		int bf = _Depth(root->_right) - _Depth(root->_left);
		if (bf == root->_bf)
			return true;
		else
		{
			cout << root->_key << "平衡因子异常" << endl;
			return false;
		}
			
		return _IsBalance(root->_left);
		return _IsBalance(root->_right);
	}

	int _Depth(Node* root)
	{
		if (NULL == root)
			return 0;
		int left = _Depth(root->_left)+1;
		int right = _Depth(root->_right) + 1;
		return left > right ? left : right;
	}


	void _InOrder(Node* root)
	{
		if (NULL == root)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);

	}
	void _RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		Node* pparent = parent->_parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (NULL == pparent)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if (pparent->_left == parent)
			{
				pparent->_left = subR;
				subR->_parent = pparent;
			}
			else
			{
				pparent->_right = subR;
				subR->_parent = pparent;
			}
		}
		parent->_bf = subR->_bf = 0;
	}

	void _RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node* pparent = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;

		if (pparent == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (pparent->_left == parent)
			{
				pparent->_left = subL;
				subL->_parent = pparent;
			}
			else
			{
				pparent->_right = subL;
				subL->_parent = pparent;
			}			
		}
		parent->_bf = subL->_bf = 0;
	}

	void _RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;  //必须记录下来，旋转后可能发生改变
		_RotateR(subR);
		_RotateL(parent);

		if (bf == 0)    //插入后子树根节点为0，高度没有受到影响，则调整后父节点和祖父结点的平衡因子为0
		{
			parent->_bf = subRL->_bf=subR->_bf = 0;
		}
		else if (bf == 1)  //插入后右树高，右树给了subR的左边，所以subR的平衡因子为0，左树高度低于右树，给了parent的右树所以parent的平衡因子为1
		{
			parent->_bf = -1;
			subR->_bf = subRL->_bf = 0;
		}
		else if (bf == -1)//插入后左树高，右树给了subR的左边，所以subR的平衡因子为1，左树高度低于右树，给了parent的右树所以parent的平衡因子为0
		{
			parent->_bf = subRL->_bf = 0;
			subR->_bf = 1;
		}
	}

	void _RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;
		_RotateL(subL);
		_RotateR(parent);

		if (bf == 0)
			parent->_bf =subLR->_bf= subL->_bf = 0;
		else if (bf == 1)
		{
			parent->_bf = subLR->_bf = 0;
			subL->_bf = -1;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = subLR->_bf = 0;
		}
	}
private:
	Node* _root;
};

void TestAVLtree()
{
	AVLtree<int, int> tree;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		tree.Insert(a[i], i);
		cout << "isbalance?"<<tree.IsBalance() <<"插入"<< a[i] << endl;
	}
	tree.InOrder();
	tree.IsBalance();
	AVLtree<int, int> tree1;
	int a1[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (size_t i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
	{
		tree1.Insert(a1[i], i);
		cout << "isbalance?" << tree1.IsBalance() << "插入" << a1[i] << endl;
	}
	tree1.InOrder();
}