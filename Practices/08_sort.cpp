#include <iostream>
#define ElemType     int 

//01.找数组中第k小的元素，时间复杂度尽可能低
//思想：用快速排序。快排一轮后，中枢的元素就到了最终位置，然后根据k的大小判断接下来去左子列还是右子列找。
//平均时间复杂度可以达到O(n)。注意k从第0开始数。
int kthMin(ElemType A[],int low,int high,int k)
{
	//if(k>high||k<low)    //边界检查
	//{
		//cout<<"out of range.";
		//exit(1);
	//}
	int pivot = A[low];
	int low_temp = low;    //记录边界范围，给下面递归传递参数
	int high_temp = high;
	
	while(low<high)    //一轮快排
	{
		while(low<high&&A[high]>=pivot)--high;
		A[low] = A[high];
		while(low<high&&A[low]<=pivot)++low;
		A[high] = A[low];
	}
	A[low] = pivot;
	
	if(k == low)    
		return A[low];    //找到第k小的元素
	else if(k<low)
		return kthMin(A,low_temp,low-1,k);    //在左子列找
	else
		return kthMin(A,low+1,high_temp,k);    //在右子列找
}

//找出数组前k大/前k小的所有元素
//k较大时用堆排序最好

//02.数组A[1]...A[m]递增有序，A[m+1]...A[m+n]递增有序。编写算法排序。
//插入排序
void insertSort(ElemType A[],int m,int n)
{
	int i,j;
	for(i=m+1;i<=m+n;++i)    //前m个已经有序，将后n个作为待排序处理
	{
		A[0] = A[i];    //暂存待排序列的首元素
		for(j=i-1;A[j]>A[0];--j)
			A[j+1] = A[j];    //移动前面的元素
		A[j+1] = A[0];    //插入
	}
}

//03.无序序列K1,K2,...Kn,要求一次排序后Kn到最终位置，且比较次数不超过n
//思想：快排，取Kn为枢轴做一次划分即可
int partition(ElemType K[],int n)    //划分一次，返回枢轴的位置
{
	int i=1,j=n;
	ElemType pivot = K[n];    //取最后一个元素做枢轴
	while(i<j)
	{
		while(i<j&&K[i]<=pivot)    //比枢轴大的移到后面
			++i;
		if(i<j)
			K[j] = K[i];
		while(i<j&&K[j]>=pivot)    //比枢轴小的移到前面
			--j;
		if(i<j)
			K[i] = K[j];
	}
	K[i] = pivot;    //插入枢轴
	return i;    //返回枢轴最终位置
}

//测试主函数
int main()
{
	int data[8] = { 49,38,65,97,76,13,27,49 };
	
	for (int i = 0; i < 8; ++i)
		cout << data[i] << " ";
	cout << endl;

	int k;
	cout << "kth min:";
	cin >> k;
	kthMin(data, 0, 7, k);

	return 0;
}