#include <iostream>

using namespace std;

typedef struct QueueNode
{
	int data;
	QueueNode* next;
}Qnode;

typedef struct LinkQueue
{
	Qnode* front;
	Qnode* rear;
}LiQueue;

void initLiQueue(LiQueue* lq)
{
	lq->front = NULL;
	lq->rear = NULL;
}

int isLiQueueEmpty(LiQueue* lq)
{
	if (lq->front == NULL || lq->rear == NULL)
	{
		return 1;    //true
	}
	else
	{
		return 0;    //false
	}
}

void enQueueLq(LiQueue* &lq, int x)
{
	Qnode* p = (Qnode*)malloc(sizeof(Qnode));
	p->data = x;
	p->next = NULL;

	if (lq->rear == NULL)    //queue empty, p's both the front and rear
	{
		lq->front = p;
		lq->rear = p;
	}
	else
	{
		lq->rear->next = p;    //follow the last member
		lq->rear = p;
	}
}

int deQueueLq(LiQueue*& lq, int& x)
{
	Qnode* p;

	if (lq->rear == NULL)
	{
		return 0;    //false
	}
	else
	{
		p = lq->front;
	}

	if (lq->front == lq->rear)    //only one node 
	{
		lq->front == NULL;
		lq->rear = NULL;
	}
	else
	{
		x = p->data;
		lq->front = p->next;
		free(p);
	}
	return 1;
}

void showLiQueue(LiQueue* lq)
{
	if (isLiQueueEmpty(lq))
	{
		cout << "This link queue is empty now.\n";
	}
	else
	{
		Qnode* r;
		r = lq->front;
		while (r != NULL)
		{
			cout << r->data << " ";
			r = r->next;
		}
		cout << endl;
	}
}

int main()
{
	int tempDequeue;
	LiQueue* LinkQueue_1 = (LiQueue*)malloc(sizeof(LiQueue));
	initLiQueue(LinkQueue_1);
	showLiQueue(LinkQueue_1);

	enQueueLq(LinkQueue_1, 1);enQueueLq(LinkQueue_1, 2);enQueueLq(LinkQueue_1, 3);
	showLiQueue(LinkQueue_1);

	deQueueLq(LinkQueue_1, tempDequeue);
	showLiQueue(LinkQueue_1);

	deQueueLq(LinkQueue_1, tempDequeue); deQueueLq(LinkQueue_1, tempDequeue);
	showLiQueue(LinkQueue_1);
	
	return 0;
}

