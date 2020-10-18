#include <iostream>
using namespace std;

#define ElemType     int 
#define maxsize    10

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
		int min = i;
		for(int j = i+1;j<n;++j)
		{
			if(A[j]<A[min])
				min = j;
		}
		int temp = A[i];
		A[i] = A[min];
		A[min] = temp;
	}
}

//建立大根堆
void headAdjust(ElemType A[], int k, int n)
{
	A[0] = A[k];    //A[0]暂存子树的根节点
	for (int i = 2 * k; i <= n; i *= 2)    //调整k节点的子树
	{
		if (i < n && A[i] < A[i + 1])    //k左右节点较大的下标
			++i;
		if (A[0] >= A[i])    //孩子与根节点的值比较，小的什么也不做，大的都移到上面
			break;    //筛选结束
		else
		{
			A[k] = A[i];    //孩子调整到双亲上
			k = i;    //k更新为孩子节点，向下调整被破坏的堆
		}
	}
	A[k] = A[0];    //筛选节点的值放入最终位置
}

void buildMaxHeap(ElemType A[], int n)
{
	for (int i = n / 2; i > 0; --i)    //从最远的有孩子的节点开始
		headAdjust(A, i, n);
}

void swap(int& x, int& y)
{
	cout << y << " ";
	y = x;
}

//堆排序（从大到小）
void heapSort(ElemType A[], int n)
{
	buildMaxHeap(A, n);
	for (int i = n; i > 1; --i)
	{
		swap(A[i], A[1]);    //输出顶部节点，底部节点移到顶部
		headAdjust(A, 1, i - 1);    //重新调整剩下的堆（所谓输出节点其实就是移到最下面，后续不再操作）
	}
}

//二路合并
ElemType *B = (ElemType*)malloc(maxsize*sizeof(ElemType));    //辅助空间，看表长
void merge(ElemType A[],int low,int mid,int high)
{
	int i,j,k;
	for(k = low;k<=high;++k)
	    B[k] = A[k];    //复制A到B
	for(i=low,j=mid+1,k=low;i<=mid&&j<=high;++k)
	{
		if(B[i]<=B[j])
			A[k] = B[i++];    //取两子表较小者并移动其上指针
		else
			A[k] = B[j++];
	}
	while(i<=mid)    //插入剩余元素
		A[k++] = B[i++];
	while(j<=high)
		A[k++] = B[j++];
}

//二路归并排序
void mergeSort(ElemType A[],int low,int high)
{
	if(low<high)
	{
		int mid = (low+high)/2;
		mergeSort(A,low,mid);    //排序左子表
		mergeSort(A,mid+1,high);    //排序右子表
		merge(A,low,mid,high);    //整体再合并一次
	}
}

int main()
{
	int data[9] = { 0,6,1,5,12,13,7,8,4 };

	//insertSort(data, 8);
	//quickSort(data, 0, 7);

	//cout << "Insert sort:";
	//for (int i = 1; i < 8; ++i)
		//cout << data[i]<<" ";
	//cout << endl;

	//cout << "Quick sort:";
	for (int i = 1; i < 9; ++i)
		cout << data[i] << " ";
	cout << endl;

	//heapSort(data, 9);
	mergeSort(data, 1, 8);
	for (int i = 1; i < 9; ++i)
		cout << data[i] << " ";
}