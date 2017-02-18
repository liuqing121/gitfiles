#include<iostream>
#include<stack>
using namespace std;

struct Calcul
{
	int symbol;
	char num;	
};
enum A
{
	OP_NUM,
	ADD,
	SUB,
	MUL,
	DIV,
};

void Calculate()
{
	stack<int> s;
	Calcul arr[] = {
		{OP_NUM,12},
		{OP_NUM,3},
		{ OP_NUM, 4},
		{ ADD,'+'},
		{MUL,'*'},
		{ OP_NUM, 6 },
		{ SUB, '-' },
		{ OP_NUM, 8 },
		{ OP_NUM, 2 },
		{ DIV, '/' },
		{ ADD, '+' }
	};
	size_t size = sizeof(arr) / sizeof(arr[0]);
	for (size_t i = 0; i < size; i++)
	{
		int right = 0;
		int left = 0;
		switch (arr[i].symbol)
		{
		case OP_NUM:
			s.push(arr[i].num);
			break;
		case ADD:
			right = s.top();
			s.pop();
			left = s.top();
			s.pop();
			s.push(left + right);
			break;
			
		case SUB:
			right = s.top();
			s.pop();
			left = s.top();
			s.pop();
			s.push(left - right);
			break;
		case MUL:
			right = s.top();
			s.pop();
			left = s.top();
			s.pop();
			s.push(left * right);
			break;
		case DIV:
			right = s.top();
			s.pop();
			left = s.top();
			s.pop();
			s.push(left / right);
			break;
		default:
			break;
		}
	}
	cout << s.top();
}
int main()
{
	Calculate();
	getchar();
	return 0;
}