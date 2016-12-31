#include<iostream>
#include<vector>
using namespace std;

enum status
{
	EXIST,
	EMPTY,
	DELETE,
};

template<class K,class V>
struct HashNode
{
	K _key;
	V _value;
	status _sta;
	HashNode(const K& key, const V& value)
		:_key(key),
		_value(value),
		_sta(EMPTY)
	{}
	HashNode()
		:_sta(EMPTY)
	{}
};

template<class K,class V>
class HashTable
{
	typedef HashNode<K, V> Node;
public:
	HashTable()
		:_size(0)
	{
		_tables.resize(_GetSize(0));
	}

	bool Insert(const K& key, const V& value)
	{
		_CheckSize();
		int index = _HashFunc(key);
		while (_tables[index]._sta ==EXIST) //线性探测，找到空或者删除过的位置
		{
			if (_tables[index]._key == key)
				return false;

			if (index == _tables.size())
				index = 0;
			++index;
		}
		_tables[index]._key = key;
		_tables[index]._value = value;
		_tables[index]._sta = EXIST;
		_size++;
		return true;
	}

	bool Remove(const K& key)
	{
		if (_size == 0)
			return false;
		int index = _HashFunc(key);

		while (_tables[index]._sta != EMPTY)
		{
			if (_tables[index]._key == key&& _tables[index]._sta==EXIST)
			{
				_tables[index]._sta = DELETE;
				_size--;
			}
			if (_tables[index]._key == key&& _tables[index]._sta == DELETE)  //已经删除过了
			{
				return false;
			}
			++index;
			if (index == _HashFunc(key)) //没找到要删除的对象
				return false;
		}
		return false;
	}
	Node* Find(const K& key)
	{
		int index = _HashFunc(key);
		while (_tables[index]._sta != EMPTY)
		{
			if (_tables[index]._key == key&&_tables[index]._sta==EXIST)
				return &_tables[index];
			if (_tables[index]._key == key&&_tables[index]._sta == DELETE)//找到了但是却被删除了
				return NULL;
			++index;

			if (index == _tables.size())  //找到表尾，从头开始找
				index = 0;
			if (index == _HashFunc(key))  //找了一遍了，没找到，说明不存在
				return NULL;


		}
		return NULL;
	}
protected:
	void _CheckSize()
	{
		if (_tables.size() == 0 || (_size * 10) / _tables.size() > 8)
		{
			int newsize = _GetSize(_tables.size());
			HashTable<K,V> tmp;
			tmp._tables.resize(newsize);
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i]._sta == EXIST)
				{
					tmp.Insert(_tables[i]._key, _tables[i]._value);
				}
			}
			swap(tmp, *this);
		}
	}
	int _HashFunc(const K& key)
	{
		return key%_tables.size();
	}
	int _GetSize(size_t num)
	{
		const int _PrimeSize = 28;  
		static const unsigned long _PrimeList[_PrimeSize] = 
		{ 
			53ul, 97ul, 193ul, 389ul, 769ul, 1543ul, 3079ul, 6151ul,
			12289ul, 24593ul, 49157ul, 98317ul, 196613ul, 393241ul, 
			786433ul, 1572869ul, 3145739ul, 6291469ul, 12582917ul, 
			25165843ul, 50331653ul, 100663319ul, 201326611ul, 402653189ul, 
			805306457ul, 1610612741ul, 3221225473ul, 4294967291ul 
		};
		for (size_t i = 0; i < _PrimeSize; ++i)
		{
			if (_PrimeList[i]>num)
			    return _PrimeList[i];
		}
		return _PrimeList[_PrimeSize - 1];
	}
private:
	vector<Node> _tables;
	size_t _size;
};

void TestHash()
{
	HashTable<int, int> ht;
	int a[] = { 89, 18, 49, 58, 9 };
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		ht.Insert(a[i], i);
	}
	HashNode<int, int>* Node = ht.Find(89);
	if (Node)
	    cout << Node->_key<<endl;
	 Node = ht.Find(40);
	if (Node)
		cout << Node->_key;
	else
		cout << "不存在" << endl;

	ht.Remove(89);
	ht.Remove(9);
	HashTable<int, int> ht1;
	for (int i = 0; i < 100; i++)  //测试扩容
	{
		ht1.Insert(i, i);
	}
}