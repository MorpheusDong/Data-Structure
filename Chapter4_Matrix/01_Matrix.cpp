#include <iostream>

using namespace std;

typedef struct matrixType
{
	int** value;
	int rows;
	int columns;
}matrix;

//create a matrix
matrix createMatrix()
{
	matrix mtx;
	cout << "Enter rows and columns: ";
	cin >> mtx.rows >> mtx.columns;
	mtx.value = (int**)malloc(sizeof(int*) * mtx.rows);
	for (int i = 0; i < mtx.rows; ++i)
	{
		mtx.value[i] = (int*)malloc(sizeof(int) * mtx.columns);
	}
	cout << "Enter elements for matrix:\n";
	for (int i = 0; i < mtx.rows; ++i)
	{
		for (int j = 0; j < mtx.columns; ++j)
		{
			cin >> mtx.value[i][j];
		}
	}
	return mtx;
}

//initialize a matrix without elements
void initMatrix(matrix& mtx,int m,int n)
{
	mtx.rows = m;
	mtx.columns = n;
	mtx.value = (int**)malloc(sizeof(int*) * m);
	for (int i = 0; i < m; ++i)
	{
		mtx.value[i] = (int*)malloc(sizeof(int) * n);
	}
}

//transposition the matrix
matrix transposition(matrix oldmtx)
{
	matrix newmtx;
	initMatrix(newmtx, oldmtx.columns, oldmtx.rows);
	for (int i = 0; i < oldmtx.rows; ++i)
	{
		for (int j = 0; j < oldmtx.columns; ++j)
		{
			newmtx.value[j][i] = oldmtx.value[i][j];
		}
	}
	return newmtx;
}

//add two matrices
matrix addMatrix(matrix a,matrix b)
{
	matrix newmtx;
	initMatrix(newmtx, a.rows, a.columns);
	for (int i = 0; i < newmtx.rows; ++i)
	{
		for (int j = 0; j < newmtx.columns; ++j)
		{
			newmtx.value[i][j] = a.value[i][j] + b.value[i][j];
		}
	}
	return newmtx;
}

//multiple two matrices
matrix multiMatix(matrix a,matrix b)
{
	//A m*n, B must be n*k, and result matrix is m*k
	int m = a.rows;
	int n = a.columns;
	int k = b.columns;

	matrix newmtx;
	initMatrix(newmtx, m, k);

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			newmtx.value[i][j] = 0;
			for (int h = 0; h < n; ++h)
			{
				newmtx.value[i][j] += a.value[i][h] * b.value[h][j];    //row elements * column elements
			}
		}
	}
	return newmtx;
}

//show the elements
void showMatrix(matrix mtx)
{
	for (int i = 0; i < mtx.rows; ++i)
	{
		for (int j = 0; j < mtx.columns; ++j)
		{
			cout << mtx.value[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	matrix A = createMatrix();
	matrix B = createMatrix();
	matrix A_t = transposition(A);
	cout << "A's transposition:\n";
	showMatrix(A_t);
	matrix C = addMatrix(A, B);
	cout << "A+B:\n";
	showMatrix(C);
	matrix D = multiMatix(A, A_t);
	cout << "A*A_t:\n";
	showMatrix(D);
	
	return 0;
}

