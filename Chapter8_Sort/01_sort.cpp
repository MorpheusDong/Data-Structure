#include <iostream>
using namespace std;

#define ElemType     int 

//直接插入排序
//算法中的数组第一个元素作为哨兵，暂存每次要插入的元素，并用于移动元素时的比较
void insertSort(ElemType A[],int n)
{
	int i,j;
	for(i=2;i<=n;++i)    //依次将A[2]到A[n-1]插入到已排序序列
	{
		if(A[i]<A[i-1])
		{
			A[0] = A[i];
		    for(j=i-1;A[0]<A[j];--j)    //从右向左比较
			    A[j+1] = A[j];    //边比较边移动，把比A[i]大的都移到后面
		    A[j+1] = A[0];    //插入A[i]	
		}
	}
}


int main()
{
	
	
	
	
}