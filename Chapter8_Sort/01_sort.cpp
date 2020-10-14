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

//快速排序
//思想：分治递归。关键是每次取中枢元素后划分的步骤
int partition(ElemType A[], int low, int high)
{
	int pivot = A[low];    //每次取子列开头的元素作为中枢
	while (low < high)
	{
		while (low<high && A[high] >= pivot)--high;    
		A[low] = A[high];    //从右向左找到比中枢小的，移到左边
		while (low < high && A[low] <= pivot)++low;
		A[high] = A[low];    //从左向右找到比中枢大的，移到右边
	}
	A[low] = pivot;    //划分完成，中枢在中间，左边都比中枢小，右边都比中枢大
	return low;    //返回中枢的位置
}

void quickSort(ElemType A[], int low, int high)
{
	if (low < high)
	{
		int k = partition(A, low, high);    //子列整体划分
		quickSort(A, low, k - 1);    //继续划分左子列
		quickSort(A, k + 1, high);    //继续右子列
	}    //当子列只有一个元素时，什么也不做，划分到底，排序完成
}

//简单选择排序
void selectSort(ElemType A[],int n)
{
	for(int i = 0;i<n;++i)
	{
		min = i;
		for(j = i+1;j<n;++j)
		{
			if(A[j]<A[min])
				min = j;
		}
		int temp = A[i];
		A[i] = A[min];
		A[min] = temp;
	}
}

int main()
{
	
	
	
	
}