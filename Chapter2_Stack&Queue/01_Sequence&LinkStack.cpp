#include <iostream>

#define maxSize 5

using namespace std;

//sequence stack
typedef struct SequenceStack
{
	int a[maxSize];
	int top;
}SqStack;

void initSqStack(SqStack& s)
{
	s.top = -1;
}

int isSequenceStackEmpty(SqStack s)
{
	if (s.top == -1)
	{
		return 1;    //true
	}
	else
	{
		return 0;    //false;
	}
}

int pushSqStack(SqStack &s, int x)
{
	if (s.top >= maxSize - 1)
	{
		return 0;    //false
	}
	else
	{
		++(s.top);
		s.a[s.top] = x;
		return 1;    //true;
	}
}

int popSqStack(SqStack& s, int &x)
{
	if (s.top <= -1)
	{
		return 0;    //false
	}
	else
	{
		x = s.top;
		--(s.top);
		return 1;    //true;
	}
}

void showSqStack(SqStack s)
{
	if (isSequenceStackEmpty(s) != 1)
	{
		for (int i = 0; i <= s.top;++i)
		{
			cout << s.a[i] << " ";
		}
		cout << endl;
	}
	else
	{
		cout << "This sequence stack is empty now.\n";
	}
	
}

//link stack
typedef struct LinkNode
{
	int data;
	struct LinkNode* next;
}LNode;

void initLinkStack(LNode* &lst)
{
	lst->next = NULL;
}

int isLinkStackEmpty(LNode* lst)
{
	if (lst->next == NULL)
		return 1;    //true
	else
		return 0;    //false
}

void pushLinkStack(LNode* &lst,int x)
{
	LNode* p = (LNode*)malloc(sizeof(LNode));
	p->data = x;
	p->next = NULL;

	p->next = lst->next;
	lst->next = p;    //insert front
}

int popLinkStack(LNode* &lst, int& x)
{
	if (isLinkStackEmpty(lst) == 1)
	{
		return 0;    //false
	}
	else
	{
		LNode* p = (LNode*)malloc(sizeof(LNode));
		p = lst->next;
		x = p->data;
		lst->next = p->next;
		free(p);
		return 1;    //true
	}
}

void showLinkStack(LNode* lst)
{
	LNode* p;
	p = lst->next;
	if (p == NULL)
	{
		cout << "This link stack is empty now.\n";
	}
	else
	{
		//the beginning node is the stack top
		while (p != NULL)
		{
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
}

int main()
{
	int tempPoped;
	
	SqStack SequenceStack_1;
	initSqStack(SequenceStack_1);
	showSqStack(SequenceStack_1);

	pushSqStack(SequenceStack_1, 1);pushSqStack(SequenceStack_1, 3);pushSqStack(SequenceStack_1, 5);
	showSqStack(SequenceStack_1);

	popSqStack(SequenceStack_1, tempPoped);
	showSqStack(SequenceStack_1);

	pushSqStack(SequenceStack_1, 7);pushSqStack(SequenceStack_1, 9);pushSqStack(SequenceStack_1, 11);
	pushSqStack(SequenceStack_1, 13);    //this should be ignored
	showSqStack(SequenceStack_1);
	
	//if maxSize is not concerned,there's another easy way
	//int Stack[maxSize];int top = -1;
	//Stack[++top] = x;    //push
	//x = Stack[top--];    //pop

	LNode* LinkStack_1 = (LNode*)malloc(sizeof(LNode));
	initLinkStack(LinkStack_1);
	showLinkStack(LinkStack_1);

	pushLinkStack(LinkStack_1, 2); pushLinkStack(LinkStack_1, 4); pushLinkStack(LinkStack_1, 6);
	showLinkStack(LinkStack_1);

	popLinkStack(LinkStack_1, tempPoped);
	showLinkStack(LinkStack_1);

	return 0;
}

