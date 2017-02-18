#pragma warning(disable:4996)
#pragma once;
#include<iostream>
#include<stack>
#include<cassert>
using namespace std;
const int rows = 10;
const int cols = 10;
void InitMaze(int*arr)
{
	FILE *f = fopen("MazeMap.txt", "r");
	assert(f);

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols;)
		{
			char tmp = fgetc(f);
			if (tmp =='0'||tmp =='1')
			{
				arr[i*cols + j] = tmp-'0';
				j++;
			}
		}
	}
	fclose(f);
}

void PrintMaze(int *arr)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols;j++)
		{
			cout << arr[i*cols + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

struct Pos
{
	Pos(int x = 0, int y = 0)
	:_x(x), _y(y)
	{}
	int _x, _y;
};

bool CheckGo(int*arr,Pos next)
{
	if ((next._x >= 0) && (next._x < rows) && (next._y >= 0) && (next._y < cols)
		&& (arr[next._x*cols + next._y] == 0))
		return true;
	else
		return false;
}

bool GetWay(int*arr, Pos pos,stack<Pos>& s)
{
	Pos cur = pos;
	Pos next = pos;
	s.push(pos);
	arr[pos._x*cols + pos._y] = 2;
	while (!s.empty())
	{ 
		
		next = s.top();
		cur = next;
		if ((next._x == rows - 1) || next._y == cols - 1 || next._x == 0)
		{
			return true;
		}
		//上
		next._x -= 1;
		if (CheckGo(arr,next))
		{
			s.push(next);
			arr[next._x*cols + next._y] = 2;
			continue;
		}
		//右
		next = cur;
		next._y += 1;
		if (CheckGo(arr, next))
		{
			s.push(next);
			arr[next._x*cols + next._y] = 2;
			continue;
		}
		//下
		next = cur;
		next._x += 1;
		if (CheckGo(arr, next))
		{
			s.push(next);
			arr[next._x*cols + next._y] = 2;
			continue;
		}
		//左
		next = cur;
		next._y -= 1;
		if (CheckGo(arr, next))
		{
			s.push(next);
			arr[next._x*cols + next._y] = 2;
			continue;
		}
		
		next = cur;
		
		arr[cur._x*cols + cur._y] = 3;  //不通的路置成3
		s.pop();
		
	}
	return false;
}

void GetShortPath(int* tmp,int *arr)
{
	stack<Pos> minPath;
	stack<Pos> path;

	while (!path.empty())
	{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			tmp[i*cols + j] = arr[i*cols + j];
		}
	}
	
		GetWay(tmp, Pos(2, 0), path);
		size_t size1 = path.size();
		size_t size2 = minPath.size();
		if (size1>size2)
		{
			minPath = path;
		}
	}
	cout << minPath.size() << endl;
}