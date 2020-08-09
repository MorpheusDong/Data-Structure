#include <iostream>

using namespace std;

typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode;

//头插法，数组建表
void insertF(LNode* &C,int A[],int n)
{
	C = (LNode*)malloc(sizeof(LNode));
	C->next = NULL;
	
	LNode* s;
	for(int i = 0;i<n;++i)
	{
		s = (LNode*)malloc(sizeof(LNode));
		s->data = A[i];
		s->next = C->next;
		C->next = s;
	}
}

//头插法，读数据建表
void insertF(LNode*& C)
{
	C = (LNode*)malloc(sizeof(LNode));
	C->next = NULL;

	LNode* s;
	int n = 0;
	cin >> n;
	while(n!= 9999)
	{
		s = (LNode*)malloc(sizeof(LNode));
		s->data = n;
		s->next = C->next;
		C->next = s;
		cin >> n;
	}
}

//尾插法，数组建表
void insertR(LNode* &C,int A[],int n)
{
	C = (LNode*)malloc(sizeof(LNode));
	C->next = NULL;
	
	LNode* r = C;
	LNode* s;
	
	for(int i = 0;i<n;++i)
	{
		s = (LNode*)malloc(sizeof(LNode));
		s->data = A[i];
		r->next = s;
		r = r->next;
	}
	r->next = NULL;
}

//尾插法，读数据建表
void insertR(LNode*& C)
{
	C = (LNode*)malloc(sizeof(LNode));
	C->next = NULL;

	LNode* r = C;
	int x;
	cin >> x;
	while (x != 9999)
	{
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = x;
		r->next = s;
		r = r->next;
		cin >> x;
	}
	r->next = NULL;
}

//打印链表
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

//按序号查找节点，设表头节点为0
LNode* getnode(LNode* C, int n)
{
	LNode* r = C;
	if (n == 0)
		return r;
	if (n < 0)
		return NULL;

	for (int i = 0; r != NULL && i < n; ++i)
	{
		r = r->next;
	}
	return r;
}

//按值查找节点
LNode* findElem(LNode* C,int x)
{
	LNode* r = C->next;
	while(r->data != x && r!=NULL)
	{
		r = r->next;
	}
	return r;
}

//在位置i处插入新元素（头插法）
int insertValue(LNode* C, int i, int x)
{
	if (i < 1)
		return 0;    //false

	LNode* p = getnode(C, i - 1);
	LNode* s = (LNode*)malloc(sizeof(LNode));
	s->data = x;
	s->next = p->next;
	p->next = s;

	return 1;    //true
}

//删除位置i处的节点
int eraseElem(LNode* C, int i)
{
	if (i < 1)
		return 0;    //false

	LNode* p = getnode(C, i-1);
	LNode* q = p->next;
	p->next = q->next;
	free(q);

	return 1;    //true
}

//01.用递归算法删除不带头节点的单链表中所有值为x的元素
void delAll_3(LNode *&c, int x)
{
	if (c == NULL)
	{
		return;
	}
	else if (c->data == x)
	{
		LNode* q;
		q = c;
		c = c->next;
		free(q);
		delAll_3(c, x);
	}
	else
	{
		delAll_3(c->next, x);
	}
}

//02.在带头节点的单链表中删除所有值为x的元素
void delAll_1(LNode *&c,int x)    //用两个指针遍历删除
{
	LNode *p,*pre,*q;
	p = c->next;
	pre = p;
	while(p!=NULL)
	{
		if(p->data == x)    //此处条件任意
		{
			q = p;
			p = p->next;
			pre->next = p;
			free(q);
		}
		else
		{
			pre = p;
			p = p->next;
		}
	}
}

void delAll_2(LNode* &c,int x)    //用尾插法删除
{
	LNode* p,*r,*q;
	r = c;    //r是表的尾指针
	p = c->next;    //p用来遍历表，做检查
	while(p != NULL)
	{
		if(p->data != x)
		{
			r->next = p;
			r = r->next;    //移动尾指针
			p = p->next;    //继续遍历
		}
		else
		{
			q = p;
			p = p->next;
			free(q);
		}
	}
	r->next = NULL;    //尾指针指向的空间可能被释放，所以最后置成NULL
}

//03.倒序输出带头节点的单链表的值
void showReverse(LNode* c)
{
	LNode* rlist;
	LNode* r, * p;    //r用来遍历原表，p用来遍历新表
	r = c->next;    
	rlist = (LNode*)malloc(sizeof(LNode));
	rlist->next = NULL;

	while (r != NULL)
	{
		p = r;
		r = r->next;    //移动尾指针，和上一步不能颠倒
		p->next = rlist->next;    //头插法建立逆置表
		rlist->next = p;
	}

	p = rlist->next;   
	while (p != NULL)    //遍历新表，打印元素
	{
		cout << p->data << " ";
		p = p->next;
	}
}

//04.删除带头节点的单链表中的最小值节点（假设最小值节点唯一）
void delMin(LNode* &c)
{
	if (c->next == NULL)
		return;

	LNode* r, * min, * minp, *pre;
	min = c->next;    //min指向当前最小值节点
	minp = c;    //minp指向最小值节点的前驱，用于删除min
	r = min->next;    //遍历指针
	pre = min;    //pre指向遍历节点的前驱

	while (r != NULL)
	{
		if (r->data < min->data)
		{
			min = r;    //更新最小值节点和其前驱
			minp = pre;
		}
		pre = r;    //pre和r一起移动
		r = r->next;
	}

	minp->next = min->next;
	free(min);
}

//05.将带头节点的单链表就地逆置（”就地“指不用辅助空间）
void reverse_1(LNode *&c)    //方法1，头插法逆置
{
	LNode *p, *r;
	p = c->next;
	c->next = NULL;    //摘下头节点

	while (p != NULL)
	{
		r = p->next;    //保存后继节点，防止断链
		p->next = c->next;    
		c->next = p;    //头插法建新表
		p = r;
	}
}

void reverse_2(LNode *C)    //方法2，改变指针转向
{
	if(C->next == NULL)    //空表不处理
		return;
	
	LNode *pre,*p,*r;
	p = C->next;
	pre = C;
	r = p->next;
	
	p->next = NULL;    //处理第一个节点，逆置后是最后一个节点，所以next为NULL
	while(r!=NULL)
	{
		pre = p;
		p = r;
		r = r->next;
		p->next = pre;
	}
	C->next = p;    //处理最后一个节点，逆置后是第一个节点，接到头上
}

//06.对有头节点的单链表排序
void sortList(LNode*& C)
{
	if (C->next == NULL)
		return;

	LNode* r, * pre, * p;
	p = C->next;
	r = p->next;
	p->next = NULL;

	p = r;
	while (p != NULL)
	{
		r = r->next;
		pre = C;
		while (pre->next != NULL && pre->next->data < p->data)
		{
			pre = pre->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = r;
	}
}

//07.带头节点的单链表，删除所有值范围在s~t之间的节点
void RangeDelete(LNode *&C,int s,int t)
{
	LNode *pre,*p;
	p = C->next;
	pre = C;
	
	while(p!= NULL)
	{
		if(p->data >=s && p->data <= t)
		{
            pre->next = p->next;
			free(p);
			p = pre->next;
		}
		else
		{
			pre = p;
			p = p->next;
		}
	}
}

//求表长
int getLength(LNode *C)
{
	LNode *p;
	p = C->next;
	int len = 0;
	while(p!=NULL)
	{
		++len;
		p = p->next;
	}
	return len;
}

//08.找两个链表的公共节点（即从某节点开始，后面所有节点是共用的）
//思想：如长度一致，有公共节点，则同时遍历应该同时到达公共节点，所以先比较长短，长的表先遍历长度之差个节点，再同步遍历。
LNode* publicLink(LNode *C1,LNode *C2)
{
	int dist = 0;
	LNode *s,*l;    //用s遍历长的链表，l遍历短的链表
	int len1 = getLength(C1);
	int len2 = getLength(C2);
	if(len1>len2)    //比较表长
	{
		l = C1->next;
		s = C2->next;
		dist = len1 - len2;
	}
	else
	{
		l = C2->next;
		s = C1->next;
		dist = len2 - len1;
	}
	
	while(dist != 0)    //长表先遍历
	{
		l = l->next;
		--dist;
	}
	while(l != NULL)
	{
		if(l == s)
		{
			return l;    //找到公共节点
		}
		else
		{
			l = l->next;    //同步遍历
			s = s->next;
		}
	}
}

//09.按递增顺序输出单链表中的所有元素，并释放其空间
void delByMin(LNode *&C)
{
	LNode *p,*minp,*q;    //p为工作指针，minp指向最小值节点的前驱
	LNode *head = C;
	
	while(head->next != NULL)    //输出到表空为止
	{
		minp = head;
		p = minp->next;
		
		while(p->next != NULL)
		{
			if(p->next->data < minp->next->data)
				minp = p;    
			
			p = p->next;
		}
		cout<<minp->next->data;    //输出节点
		q = minp->next;
		minp->next = q->next;
		free(q);	
	}
}

//10.将一个单链表拆成两个表，前者的元素是原表序号为奇数的元素，后者的元素是原表序号为偶数的元素
void split_1(LNode *C, LNode *&A, LNode *&B)
{
	LNode *r;
	r = C->next;    //r是工作指针，遍历C
	A = (LNode*)malloc(sizeof(LNode));
	B = (LNode*)malloc(sizeof(LNode));
	A->next = NULL;
	B->next = NULL;
	LNode* Ar = A, * Br = B;    //Ar，Br分别是A和B的尾指针
	int count = 0;    //计数器

	while (r != NULL)
	{
		++count;
		if (count % 2 == 0)    //判别奇偶性，然后用尾插法建表
		{
			Br->next = r;   
			Br = Br->next;
			r = r->next;
		}
		else
		{
			Ar->next = r;
			Ar = Ar->next;
			r = r->next;
		}
	}
	Ar->next = NULL;    //尾插法的表最后节点置空
	Br->next = NULL;
}

//11.与上题类似，拆分一个单链表，A的顺序不变，但B为倒序
void split_2(LNode *C, LNode *&A, LNode *&B)
{
	LNode *r,*q;
	r = C->next;    //r是工作指针，遍历C
	q = r->next;    //q是r的后继，防止头插法建B时断链
	A = (LNode*)malloc(sizeof(LNode));
	B = (LNode*)malloc(sizeof(LNode));
	A->next = NULL;
	B->next = NULL;
	LNode* Ar = A;    //Ar是A的尾指针

	while (q != NULL)
	{
		Ar->next = r;    //尾插法建表A
		Ar = Ar->next;	
		r = q;    //移动工作指针
		q = q->next;
		
		if(q != NULL)    //插完A后，如果r走到最后一个节点，此时q为空，需要判断
		{
		    r->next = B->next;    //头插法建表B
		    B->next = r; 
			r = q;
		    q = q->next;
		}
		else
		{
			r->next = B->next;    //头插法建表B，此时是最后一个节点，不再遍历
		    B->next = r; 
		}
	}
	Ar->next = NULL;    //表A最后节点置空
}

//12.删除有序单链表中的重复元素
void delSame(LNode *&C)
{
	if (C->next == NULL)
		return;
	
	LNode *r,*p,*q;
	p = C->next;    //p指向不重复的元素
	r = p->next;    //r遍历链表
	
	while(r != NULL)
	{
	    if(r->data != p->data)
		{
			p->next = r;
			p = r;
			r = r->next;
		}
		else
		{
			q = r;
			p->next = r->next;
			r = r->next;
			free(q);
		}
	}
}

//13.合并两个递增的链表A和B，合并后变为递减，结果保存到其中一个表
void reverseMerge(LNode *&A,LNode *&B)
{
	LNode *pa,*pb,*r;
	pa = A->next;
	pb = B->next;
	A->next = NULL;    //使用A保存结果
	
	while(pa&&pb)
	{
		if(pa->data<pb->data)
		{
			r = pa->next;    //r保存后继节点以防头插法断链
			pa->next = A->next;
			A->next = pa;
			pa = r;
		}
		else
		{
			r = pb->next;
			pb->next = A->next;
			A->next = pb;
			pb = r;
		}
	}
	
	if(pa)    
		pb = pa;    //若A更短，则pb指针给A用    
	
	while(pb)    //将剩余的节点用头插法插入A
	{
		r = pb->next;
		pb->next = A->next;
		A->next = pb;
		pb = r;
	}
	free(B);
}

//14.使用两个有序的单链表中的公共元素建一个新表（不破坏两张表）
void getCommon(LNode *A,LNode *B,LNode *&C)
{
	LNode *pa,*pb,*s,*r;
	pa = A->next;
	pb = B->next;
	C = (LNode*)malloc(sizeof(LNode));    //空表初始化
	C->next = NULL;
	r = C;
	
	while(pa&&pb)
	{
		if(pa->data < pb->data)    //较小的节点指针后移
		{
			pa = pa->next;
		}
		else if(pa->data > pb->data)
		{
			pb = pb->next;
		}
		else
		{
			s = (LNode*)malloc(sizeof(LNode));    
			s->data = pa->data;    
			r->next = s;    //尾插法插入公共节点
			r = r->next;
			pa = pa->next;
			pb = pb->next;
		}
	}
	r->next = NULL;
}

//15.求两个有序链表的交集
//（和上题没啥区别，只要释放无用节点，结果保存到其中一个表）
void getUnion(LNode *A, LNode *B)
{
	LNode *pa,*pb,*r,*u;
	pa = A->next;
	pb = B->next;
	A->next = NULL;    //结果保存到A
	r = A;

	while (pa && pb)
	{
		if (pa->data < pb->data)    //较小的节点指针后移
		{
			u = pa;
			pa = pa->next;
			free(u);
		}
		else if (pa->data > pb->data)
		{
			u = pb;
			pb = pb->next;
			free(u);
		}
		else
		{
			r->next = pa;    //尾插法插入公共节点，采用A的节点
			r = r->next;
			pa = pa->next;
			u = pb;    //释放B的节点
			pb = pb->next;
			free(u);
		}
	}
	r->next = NULL;    //表A尾指针置空
	
	if(pa)    //比较长短
		pb =pa;
	
	while(pb)    //释放剩余节点
	{
		u = pb;
		pb = pb->next;
		free(u);
	}
	free(B);    
}

//16.检查单链表B是否为A的连续子序列
//（即串匹配算法，这里不用KMP）
bool isPattern(LNode *A, LNode *B)
{
	LNode *pa,*pb,*pre;
	pa = A->next;
	pb = B->next;
	pre = A;    //pre记住A比较前的前一位置

	while (pa && pb)
	{
		if (pa->data == pb->data)    //继续向后比较
		{
			pa = pa->next;    
			pb = pb->next;
		}
		else
		{
			pre = pre->next;    
			pa = pre;    //A回到比较前的后继
			pb = B->next;    //B回到开头重新比较
		}
	}
	if (pb)
		return false;
	else
		return true;
}


int main()
{
	
	
	
	
	
}