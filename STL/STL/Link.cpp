////#include"Link.h"
//#include"test_list.h"
////void TestLink()
////{
////	Link<int> l;
////	l.PushBack(1);     //²âÊÔÎ²²å£¬²åÈëº¯Êı
////	l.PushBack(2);
////	Link<int> l2;
////	l2.PushFront(1);    //²âÊÔÍ·²å
////	l2.PushFront(2);
////	Link<int>::Iterator it;
////	for (it = l.Begin(); it != l.End(); it++)      //²âÊÔµü´úÆ÷
////	{
////		cout << *it << " ";
////	}
////	cout << endl;
////	for (it = l2.Begin(); it != l2.End(); it++)
////	{
////		cout << *it << " ";
////	}
////	cout << endl;
////	l2.Insert(l2.Begin(), 4, 1);     //²âÊÔÖØÔØµÄ²åÈëº¯Êı
////	for (it = l2.Begin(); it != l2.End(); it++)
////	{
////		cout << *it << " ";
////	}
////	cout << endl;
////	l.Insert(l.Begin(), l2.Begin(), l2.End());  //²âÊÔÖØÔØµÄ²åÈëº¯Êı
////	for (it = l.Begin(); it != l.End(); it++)     
////	{
////		cout << *it << " ";
////	}
////	cout << endl;
////	l.Erase(--l.End());//²âÊÔÉ¾³ıº¯Êı
////	for (it = l.Begin(); it != l.End(); it++)
////	{
////		cout << *it << " ";
////	}
////	cout << endl;
////	cout << l.Front() << endl;  //²âÊÔ·ÃÍ·º¯Êı
////	cout << l.Back() << endl;  //²âÊÔ·ÃÎ²º¯Êı
////	cout << l.Size() << endl;  //²âÊÔÈİÆ÷´óĞ¡º¯Êı
////}
//
//int main()
//{
//	//TestLink();
//	TestList();
//	getchar();
//	return 0;
//}


#include <iostream>
#include <list>
#include <string>
#include <cctype>
using namespace std;

// comparison, not case sensitive.
bool compare_nocase(string first, string second)
{
	unsigned int i = 0;
	while ((i<first.length()) && (i<second.length()))
	{
		if (tolower(first[i])<tolower(second[i])) return true;
		else if (tolower(first[i])>tolower(second[i])) return false;
		++i;
	}
	if (first.length()<second.length()) return true;
	else return false;
}

int main()
{
	list<string> mylist;
	list<string>::iterator it;
	mylist.push_back("a");
	mylist.push_back("b");
	mylist.push_back("c");

	mylist.sort();

	cout << "mylist contains:";
	for (it = mylist.begin(); it != mylist.end(); ++it)
		cout << " " << *it;
	cout << endl;

	mylist.sort(compare_nocase);

	cout << "mylist contains:";
	for (it = mylist.begin(); it != mylist.end(); ++it)
		cout << " " << *it;
	cout << endl;
	getchar();
	return 0;
}