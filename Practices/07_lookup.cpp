
//01.二分查找的递归写法
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