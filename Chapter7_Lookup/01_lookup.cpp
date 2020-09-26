#include <iostream>
using namespace std;

//二分查找（假定顺序表A升序排列）
int binarySearch(int A[],int len,int key)
{
    int low = 0,high = len-1;
    int mid;
	while(low <= high)
	{
		mid = (low+high)/2;    //选取中间位置 
		if(A[mid] == key)
			return A[mid];    //找到值
		else if(A[mid] > key)
			high = mid-1;    //在前半部分找
		else
			low = mid+1;    //在后半部分找
	}
	return -1;    //查找失败
}

//二分查找的递归写法
int binarySearch_re(int A[], int low, int high, int key)
{
	int mid = (low + high) / 2;
	if (low > high)
		return -1;

	if (A[mid] == key)
		return A[mid];
	else if (A[mid] > key)
		return binarySearch_re(A, low, mid - 1, key);
	else
		return binarySearch_re(A, mid + 1, high, key);
}




int main()
{
	
	return 0;
}