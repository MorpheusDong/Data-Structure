#include <iostream>

using namespace std;

#define MAXSIZE    5

typedef struct SequenceQueue
{
	int data[MAXSIZE];
    int front;
	int rear;
}SqQueue;

void initSqQueue(SqQueue& sq)
{
	sq.front = 0;
	sq.rear = 0;
}

int isSqQueueEmpty(SqQueue sq)
{
	if (sq.front == sq.rear)
	{
		return 1;    //true
	}
	else
	{
		return 0;    //false
	}
}

int enQueueSq(SqQueue& sq,int x)
{
	if ((sq.rear + 1) % MAXSIZE == sq.front)    //the queue is full
	{
		return 0;    //false
	}
	else
	{
		sq.data[sq.rear] = x;     //store the data
		sq.rear = (sq.rear + 1) % MAXSIZE;    //then move the pointer
		return 1;    //true
	}
}

int deQueueSq(SqQueue& sq, int& x)
{
	if (isSqQueueEmpty(sq) == 1)
	{
		return 0;    //false
	}
	else
	{
		x = sq.data[sq.front];    //receive the data
		sq.front = (sq.front + 1) % MAXSIZE;    //then move the pointer
		return 1;    //true
	}
}

void showSqQueue(SqQueue sq)
{
	if (isSqQueueEmpty(sq) == 1)
	{
		cout << "This sequence queue is empty now.\n";
	}
	else
	{
		for (int i = sq.front; i != sq.rear; i = (i + 1) % MAXSIZE)    //watch out the traverse
		{
			cout << sq.data[i] << " ";
		}
		cout << endl;
	}
}

int main()
{
	int tempDequeue;

	SqQueue SequenceQueue_1;
	initSqQueue(SequenceQueue_1);
	showSqQueue(SequenceQueue_1);

	enQueueSq(SequenceQueue_1, 1);enQueueSq(SequenceQueue_1, 2);enQueueSq(SequenceQueue_1, 3);
	showSqQueue(SequenceQueue_1);

	enQueueSq(SequenceQueue_1, 4);
	enQueueSq(SequenceQueue_1, 5);    //igored, because sequence queue sacrifices one block
	showSqQueue(SequenceQueue_1);

	deQueueSq(SequenceQueue_1, tempDequeue);deQueueSq(SequenceQueue_1, tempDequeue); 
	deQueueSq(SequenceQueue_1, tempDequeue);
	showSqQueue(SequenceQueue_1);

	deQueueSq(SequenceQueue_1, tempDequeue);
	deQueueSq(SequenceQueue_1, tempDequeue);
	showSqQueue(SequenceQueue_1);

	return 0;
}

