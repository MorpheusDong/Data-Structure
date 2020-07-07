#include <iostream>

using namespace std;

void reverse(int a[], int left, int right, int k)
{
	for (int i = left, j = right;i < left+k && i < j; ++i, --j)
	{
		int temp;
		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
}

void moveToEnd(int a[],int n,int k)
{
	reverse(a, 0, k - 1, k);
	reverse(a, 0, n-1, k);
	reverse(a, 0, n - k - 1, n - k);
}

void rotateLeft(int a[], int n, int k)
{
	reverse(a, 0, k - 1, k);
	reverse(a, k, n - 1, n - k);
	reverse(a, 0, n - 1, n);
}

void showArray(int a[],int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

int main()
{
	cout << "original:";
	int A[7] = { 1,2,3,4,5,6,7 };
	showArray(A, 7);

	cout << "all reverse:";
	reverse(A, 0, 6, 7);
	showArray(A, 7);

	cout << "move three numbers to end:";
	moveToEnd(A, 7, 3);
	showArray(A, 7);

	cout << "rotate left 2 steps:";
	rotateLeft(A, 7, 2);
	showArray(A, 7);

	return 0;

}

