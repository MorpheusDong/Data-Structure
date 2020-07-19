#include <iostream>

#define MAXSIZE 10

using namespace std;

//review some recursive problems

//calculate factorial
int factorial(int n)
{
	if (n <= 2)
	{
		return n;
	}
	else
	{
		return n * factorial(n - 1);
	}
}

//fibonacci number
int fibonacci(int n)
{
	if (n <= 2)
	{
		return 1;
	}
	else
	{
		return fibonacci(n) * fibonacci(n - 1);
	}
}

int arr[MAXSIZE] = { -1 };
//jump stair problem
int jumpstair(int n)
{
	if (n <= 2)
	{
		return n;
	}
	else
	{
		if (arr[n] != -1)    //already calculated 
		{
			return arr[n];
		}
		else
		{
			arr[n] = jumpstair(n - 1) + jumpstair(n - 2);
			return arr[n];
		}
	}
}

//hanuota
void hanMove(int n, char from, char buffer, char to)
{
	if (n == 1)
	{
		cout << "move " << n << " from " << from << " to " << to << endl;
	}
	else
	{
		hanMove(n - 1, from, to, buffer);
		hanMove(1, from, buffer, to);
		hanMove(n - 1, buffer, from, to);
	}
}

int main()
{
	int n = 4;
	hanMove(5, 'A', 'B', 'C');
	
	return 0;
}

