#include <iostream>

using namespace std;

typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode;

//insert rear
void createlistR(LNode *&C, int a[], int n)
{
	LNode* r, * s;
	C = (LNode*)malloc(sizeof(LNode));
	C->next = NULL;
	r = C;
	
	C->data = 0;    //head stores data quantities
	for (int i = 0; i < n; ++i)
	{
		s = (LNode*)malloc(sizeof(LNode));
		s->data = a[i];
		r->next = s;
		r = r->next;

		++(C->data);    //quantities+1
	}
	r->next = NULL;
}

//insert front
void createlistF(LNode*& C, int a[], int n)
{
	LNode* s;
	C = (LNode*)malloc(sizeof(LNode));
	C->next = NULL;

	C->data = 0;    //head stores data quantities
	for (int i = 0; i < n; ++i)
	{
		s = (LNode*)malloc(sizeof(LNode));
		s->data = a[i];
		s->next = C->next;
		C->next = s;

		++(C->data);    //quantities+1
	}
}

//show the list
void showlist(LNode* C)
{
	LNode* r;
	r = C->next;
	for (int i = 0; r != NULL; ++i)
	{
		cout << r->data << " ";
		r = r->next;
	}
	cout << endl;
	
}

//merge a new list with sequence
void mergeList(LNode* A, LNode* B, LNode*& C)
{
	LNode* p = A->next;    //use p&q to track A&B's first data
	LNode* q = B->next;
	LNode* r;
	C = A;    //use A's head
	C->next = NULL;
	free(B);    //free B's head
	r = C;    //use r to track C's rear

	while (p != NULL && q != NULL)
	{
		if (p->data <= q->data)
		{
			r->next = p;
			p = p->next;
			r = r->next;
		}
		else
		{
			r->next = q;
			q = q->next;
			r = r->next;
		}
	}

	if (p != NULL)
	{
		r->next = p;    
	}
	else if (q != NULL)
	{
		r->next = q;
	}
	else
	{
		//do nothing
	}
}

//find and delete int x
int findAndDelete(LNode* C, int x)
{
	LNode* p;
	LNode* q;
	p = C;
	while (p != NULL)
	{
		if (p->next->data == x)
		{
			break;
		}
		else
		{
			p = p->next;
		}
	}

	if (p == NULL)
	{
		return 0;    //false
	}
	else
	{
		q = p->next;
		p->next = p->next->next;
		free(q);
		return 1;    //true
	}
}

int main()
{
	int A[5] = { 1,2,3,4,5 };
	int B[6] = { 10,9,8,7,6,0 };

	LNode* nodeslistR; 
	LNode* nodeslistF;
	LNode* nodesMerged;

	createlistR(nodeslistR, A, 5);
	showlist(nodeslistR);

	//nodeslistF in reverse order
	createlistF(nodeslistF, B, 6);
	showlist(nodeslistF);

	mergeList(nodeslistR, nodeslistF, nodesMerged);
	showlist(nodesMerged);

	findAndDelete(nodesMerged, 6);
	showlist(nodesMerged);

	return 0;

}

