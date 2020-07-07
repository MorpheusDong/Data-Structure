#include <iostream>

using namespace std;
#define maxSize 100

typedef struct SequenceList
{
	int data[maxSize];
	int length;
}Sqlist;

void initSqlist(Sqlist& l)
{
	l.length = 0;
}

int findElem(Sqlist l, int x)
{
	int i = 0;
	for (i = 0; i < l.length; ++i)
	{
		if (l.data[i] == x)
			return i;
	}
	return i;
}

int insertElem(Sqlist& l, int p, int x)
{
	if (p<0 || p>l.length || l.length == maxSize)
		return 0;    //false		

	for (int i = l.length - 1; i >= p; --i)
	{
		l.data[i+1] = l.data[i];
	}

	l.data[p] = x;
	++(l.length);

	return 1;    //true
}

int eraseElem(Sqlist& l, int p)
{
	if (p<0 || p>l.length - 1)
		return 0;    //false

	for (int i = p; i < l.length - 1; ++i)
	{
		l.data[i] = l.data[i + 1];
	}

	--(l.length);
	return 1;    //true
}

void showElem(Sqlist l)
{
	for (int i = 0; i < l.length; ++i)
	{
		cout << l.data[i] << " ";
	}
	cout << "\tcurrent length: " << l.length;
	cout << endl;
}

int main()
{
	//tests
	Sqlist list1;
	initSqlist(list1);

	insertElem(list1, 0, 1);
	showElem(list1);

	insertElem(list1, 0, 2);
	insertElem(list1, 0, 3);
	insertElem(list1, 0, 4);
	showElem(list1);
	
	insertElem(list1, 99, 99);
	showElem(list1);

	insertElem(list1, 4, 18);
	showElem(list1);

	eraseElem(list1, 2);
	showElem(list1);

	int n = 2;int r = 0;
	r = findElem(list1, n);
	cout << n << " found at ";
	if (r > list1.length - 1)
	{
		cout << "no where.";
	}
	else
	{
		cout << "index " << r;
	}
	cout << endl;

	return 0;
}

