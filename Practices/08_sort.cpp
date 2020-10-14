#include <iostream>
#define ElemType     int 

//01.找数组中第k小的元素，时间复杂度尽可能低
//思想：用快速排序。快排一轮后，中枢的元素就到了最终位置，所以可以根据k的大小判断接下来去左子列还是右子列找。
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

//测试主函数
int main()
{
	int data[8] = { 49,38,65,97,76,13,27,49 };

	//insertSort(data, 8);
	//quickSort(data, 0, 7);

	//cout << "Insert sort:";
	//for (int i = 1; i < 8; ++i)
		//cout << data[i]<<" ";
	//cout << endl;

	//cout << "Quick sort:";
	for (int i = 0; i < 8; ++i)
		cout << data[i] << " ";
	cout << endl;

	int k;
	cout << "kth min:";
	cin >> k;
	kthMin(data, 0, 7, k);

	return 0;
}