#define maxsize 50
//栈ADT，简化写法
int stack[maxsize],top = -1;    //顺序实现 
stack[++top] = x;    //入栈
x = stack[top--];    //出栈

//链式实现用一个头插的链表即可。
//入栈用头插法逐个插到头节点后面，出栈依次删除首节点，实现后进先出。

//01.假定有字符串序列，I和O分别表示入栈和出栈操作，栈的初态和终态都为栈空。编写算法判断一串操作是否合法。
bool judgeStackOp(char A[])
{
	int pushCount = 0;
	int popCount = 0;
	int i = 0;
	
	while(A[i] != '\0')
	{
		if(A[i] == 'I')
		{
			++pushCount;
		}
		else if(A[i] == 'O')
		{
			++popCount;
		}
		
		if(popCount > pushCount)    //出栈次数大于入栈次数，不合法
			return false;
		
		++i;
	}
	
	if(pushCount == popCount)    //终态栈空，所以入栈次数应等于出栈次数
		return true;
	else    
		return false;
}

typedef struct LNode
{
	char data;
	struct LNode* next;
}LNode;

//02.假定单链表节点的值域是字符型，用一个单链表存储字符串。编写算法判断长度为n的字符串是否是中心对称。（如xyx和xyyx）
int checkSymmetry(LNode* C, int n)
{
	char* s = (char*)malloc(sizeof(char) * (n/2));    //数组栈，用来存前一半的字符
	LNode* p;
	int i = 0;
	p = C->next;

	for (i = 0; i < n/2; ++i)    //前半段字符入栈
	{
		*(s + i) = p->data;
		p = p->next;
	}                       //循环退出时，如果字符数是奇数，则i和p停在正中间；为偶数，则停在中间右边一格。
	--i;                    //i回退一格，让其停在栈顶
	if (n % 2 == 1)         //如果字符数是计数，p再往前走一格，停在后半段的首字符。
		p = p->next;

	while (p != NULL && p->data == *(s+i))    //前半段按出栈顺序与后半段依次比较
	{
		p = p->next;
		--i;
	}
	if (p == NULL)
		return 1;    //true
	else
		return 0;    //false
}

//03.为了使用循环队列的所有空间，假定循环队列类型增加一个tag值域，用0和1区分front == rear时是队空和队满。
//给出入队和出队的函数。
typedef struct LoopQueue
{
	int data[maxsize];
	int front;
	int rear;
	int tag;
}lq;

int enQueue(lq &lq, int x)
{
	if (lq.front == lq.rear && lq.tag == 1)    //入队时才有可能队满
		return 0;    //false

	lq.data[lq.rear] = x;
	lq.rear = (lq.rear + 1) % maxsize;
	lq.tag = 1;    //入队时tag置1
	return 1;    //true
}

int deQueue(lq & lq, int& x)
{
	if (lq.front == lq.rear && lq.tag == 0)    //出队时才有可能队空
		return 0;

	x = lq.data[lq.front];
	lq.front = (lq.front + 1) % maxsize;
	lq.tag = 0;    //出队时tag置0
	return 1;    //true
}

//04.用一个栈把一个队列中的所有成员逆置（用了上题的结构）
int stack[maxsize],top = -1;

bool isEmpty(lq lq)
{
	if (lq.front == lq.rear && lq.tag == 0)    
		return true;
	else
		return false;
}

void reverseQueue(lq & lq)
{
	int x;
	while(!isEmpty(lq))
	{
		deQueue(lq,x);
		stack[++top] = x;
	}
	while(top!= -1)
	{
		x = stack[top--];
		enQueue(lq,x);
	}
}

//05.用两个栈S1和S2实现一个队列，写出入队，出队函数
//思想：入队正常压栈，想出队必须保证一个栈的元素已经压进了另一个栈，这样才可以倒序输出。所以设S1只输入，S2只输出。
//想要输出，如果S2是空的，就应该把S1所有元素压入S2，以输出S1底端的元素。如果S2非空，则继续输出S2的序列。
//队满状态：S2非空，S1已满。（这时把S1压到S2会打乱顺序）
//队空状态：S1和S2都为空。
typedef struct SqStack    
{
	int data[5];
	int top;
}stack;

void init(stack &st)
{
	st.top = -1;
}

void push(stack &st,int x)
{
	if(st.top == 4)
	{
		return;
	}
	else
	{
		++st.top;
		st.data[st.top] = x;
	}
}

void pop(stack &st,int &x)
{
	if(st.top == -1)
	{
		return;
	}
	else
	{
		x = st.data[st.top];
		--st.top;
	}
}

bool stackFull(stack st)
{
	if(st.top == 4)
		return true;
	else
		return false;
}

bool stackEmpty(stack st)
{
	if(st.top == -1)
		return true;
	else
		return false;
}

stack S1,S2;
init(S1,S2);

int enQueue(stack& s1, stack& s2, int x)
{
	if (!stackFull(s1))
	{
		push(s1, x);
		return 1;    //true
	}
	if (stackFull(s1) && !stackEmpty(s2))
	{
		cout << "The queue is full now.\n";
		return 0;    //false
	}
	if (stackFull(s1) && stackEmpty(s2))
	{
		int v;
		while (!stackEmpty(s1))
		{
			pop(s1, v);
			push(s2, v);
		}
		push(s1, x);
		return 1;    //true
	}
}

int deQueue(stack& s1, stack& s2, int& x)
{
	if (!stackEmpty(s2))
	{
		pop(s2, x);
		return 1;    //true
	}
	if (stackEmpty(s2) && !stackEmpty(s1))
	{
		int v;
		while (!stackEmpty(s1))
		{
			pop(s1, v);
			push(s2, v);
		}
		pop(s2, x);
		return 1;    //true
	}
	if (stackEmpty(s1) && stackEmpty(s2))
	{
		cout << "Unable to dequeue because it's empty.\n";
		return 0;    //false
	}
}

//06.检测一串字符串中的括号是否匹配
bool checkBracket(string c)
{
	stack s;
	init(s);
	char t;
	for(int i = 0;c[i]!='\0';++i)
	{
		switch(c[i])
		{
			case '(':push(s,c[i]);break;    //左括号都入栈
			case '[':push(s,c[i]);break;
			case '{':push(s,c[i]);break;
			case ')':    //右括号与栈顶的括号对比
			{
			    if(s.data[s.top] == '(')
					pop(s,t);
				else
					return 0;    //false   括号都一一配对，有一个不配整体就不匹配
				break;
			}
			case ']':
			{
				if(s.data[s.top] == '[')
					pop(s,t);
				else
					return 0;    //false
				break;
			}
			case '}':
			{
				if(s.data[s.top] == '{')
					pop(s,t);
				else
					return 0;    //false
				break;
			}	
			default:break;
		}
	}
	if(s.top == -1)    //栈空则匹配
		return 1;    //true
	else
		return 0;    //false
}

//07.利用栈实现递归函数的非递归计算。
//n = 0,P(n,x) = 1
//n = 1,P(n,x) = 2*x;
//n > 1,P(n,x) = 2*x*P(n-1,x) - 2*(n-1)*P(n-2,x)
int calcP(int n,int x)
{
	int p[maxsize],top = -1;
	if(n == 0)
		return 1;    //n = 0的值
	p[++top] = 1;
	if(n == 1)
		return 2*x;    //n = 1的值
	p[++top] = 2*x;
	if(n > 1)
	{
		for(int i = 3;i<=n && top<maxsize;++i)   //逐层向上计算，栈顶保存Pn(x)的结果
		{
			p[++top] = 2*x*p[top-1] - 2*(i-1)*p[top-2];    //递推公式
		}
	}
	return p[top];
}
		
		
	

	
	



