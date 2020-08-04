#include <iostream>
using namespace std;

#define maxsize 100

//typedef
typedef struct Sequencelist
{
	int data[maxsize];
	int length;
}Sqlist;

//Basic methods begin//
void initSqlist(Sqlist &l)
{
	l.length = 0;
}

int findElem(Sqlist l,int e)
{
	int i = 0;
	for(i = 0;i<l.length;++i)
	{
		if(e == l.data[i])
		{
			return i;    //found
		}
	}
	return i;    //not found
	
}

int insertElem(Sqlist &l,int e,int p)
{
	if(p<0 || p>l.length || l.length == maxsize)
	{
		return 0;    //false
	}
	
	for(int i = l.length - 1;i>= p;--i)
	{
		l.data[i+1] = l.data[i];
	}
	l.data[p] = e;
	++(l.length);
	return 1;    //true
}

int eraseElem(Sqlist &l,int p,int &x)
{
	if(p<0 || p>l.length - 1)
    {
		return 0;    //false
	}
	
	x = l.data[p];
	for(int i = p;i<l.length - 1;++i)
	{
		l.data[i] = l.data[i+1];
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
//Basic methods end//


//01.从一个顺序表中删除最小元素，将值返回，顺序表空出的位置用最后一个元素填补
int eraseMinElem(Sqlist &l,int &x)
{
	if(l.length == 0)
	{
		return 0;    //false
	}
	
	int min = l.data[0];
	int i;
	int p;
	for(i = 0;i<l.length;++i)
	{
		if(l.data[i]<min)
		{
			min = l.data[i];    //更新最小值
			p = i;    //更新位置
		}
	}
	x = min;
	l.data[p] = l.data[l.length - 1];
	--(l.length);
}

//02.将顺序表中所有元素逆置
void reverse(Sqlist &l)
{
	int temp;
	for(int i = 0;i<(l.length/2);++i)
	{
		temp = l.data[i];
		l.data[i] = l.data[l.length - i - 1];
		l.data[l.length - i - 1] = temp;
	}
	
}

//03.删除线性表中所有值为x的元素
void delAll(Sqlist &l,int x)
{
	int k = 0;    //k指向要保存到的位置
	for(int i = 0;i < l.length - 1;++i)
	{
		if(l.data[i] != x)
		{
			l.data[k] = l.data[i];    //保存所有不需要删除的元素
			++k;
		}
	}
	l.length = k;
}

//04.从有序的线性表中删除值在s到t的之间的所有元素
int delS2T_seq(Sqlist &l,int s,int t)
{
	if(s>=t || l.length == 0 || s>l.data[l.length - 1] || t<l.data[0])
		return 0;    //false
	
	int i = 0;
	while(l.data[i] < s && i < l.length)
	{
		++i;    //i保存第一个大于s的元素的位置
	}
	
	int j = i;
	while(l.data[j] <= t && j < l.length)
	{
		++j;    //j保存第一个大于t的元素的位置
	}
	
	for(;j<l.length;++j,++i)
	{
		l.data[i] = l.data[j];    //元素前移
	}
	l.length = i;
	return 1;    //true
}

//05.从顺序表中删除值在s到t的之间的所有元素(也可以用3的方法)
int delS2T(Sqlist &l,int s,int t)
{
	if(s>=t || l.length == 0)
		return 0;    //false
	
	int k = 0;
	for(int i = 0;i<l.length;++i)
	{
		if(l.data[i] >= s && l.data[i] <= t)
		{
			++k;
		}
		else
		{
			l.data[i-k] = l.data[i];    //当前元素前移k个位置
		}
	}
	
	l.length -= k;
	return 1;    //true
}
	
//06.从有序表中删除所有重复的元素，使所有元素值唯一
int delSame(Sqlist &l)
{
	if(l.length == 0)
		return 0;    //false
	
	int k = 0;
	for(int i = 1;i<l.length;++i)    //用i遍历顺序表，k指向不重复的元素的末尾
	{
		if(l.data[i] != l.data[k])
		{
			++k;
			l.data[k] = l.data[i];
		}
	}
	l.length = k+1;    //循环结束时k指向最后一位元素
	return 1;    //true
}

//07.有序表合并，函数返回合并后的有序表
int merge(Sqlist a, Sqlist b, Sqlist& c)
{
	if (a.length + b.length > maxsize)
		return 0;    //false

	int i = 0, j = 0, k = 0;
	while (i < a.length && j < b.length)    //用i遍历a，j遍历b
	{
		if (a.data[i] <= b.data[j])    //依次比较头部元素
		{
			c.data[k++] = a.data[i++];
		}
		else
		{
			c.data[k++] = b.data[j++];
		}
	}

	while (j < b.length)    //a先结束
	{
		c.data[k++] = b.data[j++];
	}
	while (i < a.length)    //b先结束
	{
		c.data[k++] = a.data[i++];
	}

	c.length = k;
	return 1;    //true
}

//数组的逆置算法
int reverse(int A[], int l, int r)
{
	if (l >= r)
		return 0;    //false

	int i, j;
	int temp;
	for (i = l, j = r; i < j; ++i, --j)
	{
		temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}
	return 1;    //true
}

//08.数组由m+n个元素构成，交换这两组元素的位置
void exchange(int A[],int m,int n)
{
	reverse(A,0,m+n-1);    //逆置整个数组
	reverse(A,0,n-1);    //逆置前面n个元素
	reverse(A,n,m+n-1);    //逆置后面m个元素
}

//二分查找，若找到x返回其位置
int binarySearch(Sqlist l, int x)
{
	int left, right, mid;
	left = 0;
	right = l.length - 1;
	
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (x == l.data[mid])
		{
			return mid;    //found
		}
		else if (x < l.data[mid])
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}

	return -1;    //not found
}

//09.用最快速度在有序表中查找x，找到则将其与后继元素交换，找不到则将x插入表，使线性表仍有序
void FindExchangeInsert(Sqlist& l, int x)
{
	int p = binarySearch(l, x);
	if (p >= 0 && p < l.length - 1)    //表中找到了x，且不是最后一个元素
	{
		int temp;
		temp = l.data[p];
		l.data[p] = l.data[p + 1];
		l.data[p + 1] = temp;
	}
	else if(p == -1)    //没找到x
	{
		int k = 0;
		while (x > l.data[k] && k < l.length)    //寻找插入位置
		{
			++k;
		}
		for (int j = l.length - 1; j >= k; --j)    //后移元素
		{
			l.data[j + 1] = l.data[j];
		}
		l.data[k] = x;
		++(l.length);
	}
}
	
//10.用尽可能高效的方法，将数组循环左移p个位置
//思想：循环左移p位，相当于前p个元素和后n-p个元素交换位置，顺序不变。和题8一样。
//如果循环右移p位，相当于循环左移n-p位。
void rollLeft(int A[], int n, int p)
{
	reverse(A, 0, n - 1);
	reverse(A, 0, n - p - 1);
	reverse(A, n - p, n - 1);
}

//11.给定两个升序序列A和B，找出A和B两个序列的中位数。设A和B总长度L，中位数是两个序列一起数第L/2个数（向上取整）。
int findMiddle(Sqlist a, Sqlist b)
{
	int i = 0, j = 0;
	int k = 0;
	int m = 0;    //m保存中位数
	int count = (int)((a.length + b.length) / 2.0 + 0.5);    //向上取整

	while(k < count)    //k用于计数，取到第L/2个停止
	{
		if (i == a.length)    //b先遍历完，在a继续取m
		{
			m = b.data[j];
			++j;
		}
		else if (j == b.length)    //a先遍历完，在b继续取m
		{
			m = a.data[i];
			++i;
		}
		else
		{
			if (a.data[i] <= b.data[j])    //依次比较a和b的头部元素，从小到大计数
			{
				m = a.data[i];
				++i;
			}
			else
			{
				m = b.data[j];
				++j;
			}
		}

		++k;
	}

	return m;
}

//12.找数组A中的主元素。主元素的定义是数组中重复的元素，其重复个数超过总量一半。
//思想：遍历数组，更新候选元素，对其计数。后继元素重复则+1，不重复则-1。
//因为主元素会占据超过一半的数量，所以如果有主元素，最后的count应会>0。
int findMajority(int A[],int n)
{
	int i = 0;
	int count = 0;    //计数器
	int c = A[0];    //候选元素，初始默认A[0]
	
	for(i = 1;i<n;++i)
	{
		if(c == A[i])
		{
			++count;    //后继元素重复，计数+1
		}
		else
		{
			if(count > 0)
			{
				--count;    //后继元素不重复，计数-1
			}
			else
			{
				c = A[i];    //重置候选元素
				count = 1;    //重置计数
			}
		}
	}
	
	if(count > 0)
	{
		for(i = 0,count = 0;i<n;++i)    //检验是否为主元素
		{
			if(c == A[i])
			{
				++count;
			}
		}
	}
	if(count > n/2)
	{
		return c;
	}
	else
	{
        return -1;
	}
}

//13.用时间尽可能快的方法，找出数组中未出现的最小正整数。
//思想：空间换时间，用长度为n的数组标记1~n的正整数是否出现。
int findMissMinInt(int A[],int n)
{
	int i = 0;
	int *B = (int*)malloc(sizeof(int)*n);    
	memset(B,0,sizeof(int)*n);
	for(i = 0;i<n;++i)
	{
		if(A[i]>0 && A[i]<=n)
		{
		    B[A[i]-1] = 1;    //标记出现过的正整数
		}
	}
	for(i = 0;i<n;++i)
	{
		if(B[i] == 0)
		{
			break;    //找到第一个没出现过的正整数即可
		}
	}
	return i+1;    //B数组实际表示的数是下标+1
}


