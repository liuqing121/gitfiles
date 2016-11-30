#pragma once
#include<iostream>
using namespace std;

enum Type
{
	VALUETYPE,
	SUBTYPE,
	HEADTYPE,
};

struct GeneralizedNode
{
	typedef GeneralizedNode Node;
	Type _type;
	Node* _next;
	union
	{
		char _value;
		Node* _sublink;
	};
	
};

class GeneralizedLink
{
public:
	typedef GeneralizedNode Node;
	GeneralizedLink(const char* str)
		:_start(NULL)
	{
		_start=_CreatGL(str);
	}
	GeneralizedLink(const GeneralizedLink& g)
	{
		_start = _Copy(g._start);
	}
	GeneralizedLink& operator=( GeneralizedLink g)
	{
		swap(g._start, _start);
	}
	~GeneralizedLink()
	{
		_Delete(_start);

	}
	size_t Size()
	{
		return _Size(_start);
	}

	size_t Depth()
	{
		return _Depth(_start);
	}


	void Print()
	{
		_Print(_start);
		cout << endl;
	}
protected:

	size_t _Depth(Node* head)
	{
		Node* cur = head;
		
		size_t maxDepth = 1;
		while (cur)
		{
			size_t depth = 1;
			if (cur->_type == SUBTYPE)
			{
				depth += _Depth(cur->_sublink);
				if (depth > maxDepth)
				{
					maxDepth = depth;
				}
			}
			cur = cur->_next;
		}
		return maxDepth;
	}
	size_t _Size(Node* head)
	{
		Node* cur = head;
		size_t size = 0;
		while (cur)
		{
			if (cur->_type == VALUETYPE)
			{
				size++;
			}
			else if (cur->_type == SUBTYPE)
			{
				size += _Size(cur->_sublink);
			}
			cur = cur->_next;
		}
		return size;
	}
	void  _Delete(Node* head)
	{
		Node* del = head;
		
		while (del)
		{
			Node* prev = del;
			if (del->_type == SUBTYPE)
			{
				_Delete(del->_sublink);
			}

			del = del->_next;
			delete prev;
		}
	}
	Node* _Copy( Node* head)
	{
		Node* NewHead = new Node();
		NewHead->_type = HEADTYPE;
		Node* cur = head->_next;
		Node* _cur = NewHead;
		while (cur)
		{
			
			if (cur->_type == VALUETYPE)
			{
				Node* tmp = new Node();
				tmp->_type = cur->_type;
				tmp->_value = cur->_value;
				_cur->_next = tmp;
				_cur = _cur->_next;
			}
			else if (cur->_type==SUBTYPE)
			{
				Node* tmp = new Node();
				tmp->_type = cur->_type;				
				tmp->_sublink = _Copy(cur->_sublink);
				_cur->_next = tmp;
				_cur = _cur->_next;
			}
			cur = cur->_next;
		}
		return NewHead;
	}

	Node* _Print(Node* head)
	{
		

		Node* cur = head;
		while (cur)
		{
			if (cur->_type == HEADTYPE)
			{
				cout << '(';
			}
			else if (cur->_type == VALUETYPE)
			{
				cout << cur->_value;
				if (cur->_next)
				{
					cout << ',';
				}
			}
			else if (cur->_type == SUBTYPE)
			{
				_Print(cur->_sublink);
				if (cur->_next)
					cout << ',';
			}
			cur = cur->_next;
		}
		cout << ')';
		return head;
	}
	Node* _CreatGL(const char* & str)
	{
		Node* head = new Node();
		head->_type = HEADTYPE;
		Node* cur = head;
		str++;
		while (*str)
		{
			if (*str == '(')
			{
				Node* tmp = new Node();
				tmp->_type = SUBTYPE;
				cur->_next = tmp;
				cur = cur->_next;
				tmp->_sublink = _CreatGL(str);
				str++;
			}
			else if (*str == ')')
			{
				cur->_next = NULL;
				str++;
				return head;
			}
			else if ((*str >= 'A'&&*str <= 'Z') || (*str >= 'a'&&*str <= 'z'))
			{
				Node* tmp=new Node();
				tmp->_type = VALUETYPE;
				tmp->_value = *str;
				cur->_next = tmp;
				cur = cur->_next;
				str++;
			}
			else
				str++;
		}
		return head;
	}

private:
	Node* _start;
};

void test()
{
	GeneralizedLink g1("(a, b, (c, d), (e, (f), h))");
	GeneralizedLink g2(g1);
	GeneralizedLink g3 = g1;
	//g2.Print();
	//g1.Print();
	g3.Print();
	cout << g3.Size() << endl;
	cout << g3.Depth() << endl;
}