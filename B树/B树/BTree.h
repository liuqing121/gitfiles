#include<iostream>

using namespace std;

template<class K , int M>
struct BTreeNode
{
	typedef BTreeNode<K, M> Node;
	K _keys[M];   //多给出一个位置是为了方便分裂。
	Node* _sub[M + 1];
	Node* _parent;
	size_t _size;  //记录实际关键字的个数
	BTreeNode()
		:_parent(NULL)
		, _size(0)
	{
		for (size_t i = 0; i < M; i++)
		{
			_keys[i] = K();
			_sub[i] = 0;
		}
		_sub[M] = 0;
	}
};

template<class K,int M>
class BTree
{
public:
	typedef BTreeNode<K, M> Node;
	BTree()
		:_root(NULL)
	{}
	void InOrder()
	{
		_InOrder(_root);
	}
	~BTree()
	{
		_Destory(_root);
	}
	bool Insert(const K& key)
	{
		if (NULL == _root)
		{
			_root = new Node();
			_root->_keys[0] = key;
			_root->_size++;
			return true;
		}
		pair<Node*, size_t> tmp = _Find(key);
		if (tmp.second != -1)  //已经存在关键值为key，则不能插入
		{
			return false;
		}
		Node* cur = tmp.first;
		Node* sub = NULL;
		K newkey = key;
		while (1)
		{
			_Insertkey(cur,newkey,sub);  //先将key放进要插的节点
			//判断结点的关键字数目是否符合标准。
			if (cur->_size < M)  //该节点上插入后关键字数目正常
				return true;

			//数目超过规定值需要进行分裂
			while (cur->_size >= M)
			{
				size_t mid = cur->_size / 2;
				//1.分裂出新的结点
				Node* NewNode = new Node;
				for (size_t i = mid+1; i < cur->_size; i++)//mid之后的key值给新结点
				{
					int j = 0;
					NewNode->_keys[j] = cur->_keys[i];
					NewNode->_size++;
					//cur->_size--;  //注意此处先不要哦改动cur的size，否则会影响下一个循环
					cur->_keys[i] = K();  //赋给新结点后cur对应的key应置成初始值
					j++;
				}
				int j = 0;
				for (size_t i = mid+1 ; i < cur->_size+1; i++)
				{
					NewNode->_sub[j] = cur->_sub[i];
					if (NewNode->_sub[j])
						NewNode->_sub[j]->_parent = NewNode;
					j++;
					cur->_sub[i] = NULL;
				}
				if (cur == _root)  //创建出新的根节点
				{
					Node* tmp = new Node();
					tmp->_keys[0] = cur->_keys[mid];
					cur->_keys[mid] = K();
					cur->_size=mid;
					tmp->_size++;
					tmp->_sub[0] = cur;
					cur->_parent = tmp;
					tmp->_sub[1] = NewNode;
					NewNode->_parent = tmp;
					_root = tmp;
					return true;
				}
				newkey = cur->_keys[mid];
				cur->_keys[mid] = K();
				cur->_size = mid;   
				sub = NewNode;
			}
			
			cur = cur->_parent;
		}
	}

protected:
	void _Destory(Node* root)
	{
		if (NULL == root)
			return;

		size_t i = 0;
		for (; i < root->_size; i++)
		{
			_Destory(root->_sub[i]);
			delete root->_sub[i];
		}
		_Destory(root->_sub[i]);
		delete root->_sub[i];
	}
	void _InOrder(Node* root)
	{
		if (NULL == root)
			return;

		size_t i = 0;
		for (; i < root->_size; i++)
		{
			_InOrder(root->_sub[i]);
			cout << root->_keys[i]<<" ";

		}
		_InOrder(root->_sub[i]);
	}
	pair<Node*,size_t> _Find(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			size_t i = 0;
			while (i< cur->_size)  //找当前结点的key
			{
				
				if (cur->_keys[i] < key)
					i++;
				else if (cur->_keys[i]>key)
					//cur = cur->_sub[i];
					break;
				else   //找到了和传入key相等的关键字
					return pair<Node* ,size_t>(cur,i);
			}
			parent = cur;
			cur = cur->_sub[i];
		}
		return pair<Node* , size_t>(parent, -1);  //没找到
	}
	void _Insertkey(Node* cur,const K& key,Node*sub)
	{
		int i = cur->_size-1;
		while (i >=0)
		{
			if (cur->_keys[i] > key)
			{
				//移动关键字的位置
				cur->_keys[i + 1] = cur->_keys[i];

				//移动子树的位置
				cur->_sub[i + 2] = cur->_sub[i + 1];
				i--;
			}
			else
				break;
		}
		//i记录着要插入位置的前一个
		cur->_keys[i + 1] = key;
		cur->_sub[i + 2] = sub;
		if (sub)
			sub->_parent = cur;
		cur->_size++;
	}
private:
	Node* _root;
};

void TestBTree()
{
	BTree<int, 3> bt;
	int a[] = { 53, 75, 139, 49, 145, 36, 101 };
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		bt.Insert(a[i]);
	}
	bt.InOrder();
}