#include <stdio.h>

/*
 * 함수 정의부
 */
int Fibo(int n)
{
	if (n <= 0)
		return -1;
	else if (n == 1 || n == 2)
		return 1;

	int f1 = 1, f2 = 1;
	int fib = 0;
	
	for (int i=2; i<n; i++)
	{
		fib = f1 + f2;
		f1 = f2;
		f2 = fib;
	}

	return fib;
}

int GetInitValue(int n)
{
	if (n==0)
		return 0;
	if (n==1)
		return 1;

	int p = 0;
	int q = 1;
	for (int i=1; p+q<=n; i++)
	{
		int temp = q;
		q = q + p;
		p = temp;
	}

	return i;
}

int FibonacciSearch(int data[], int n, int find_key)
{
	int i = GetInitValue(n);
	int f1 = Fibo(i-2);
	int f2 = Fibo(i-3);
	int mid = n - Fibo(i-2) + 1;

	while (true)
	{
		if (find_key > data[mid])
		{
			if (f1 == 0) 
				return -1;

			mid = mid + f2;
			f1 = f1 - f2;
			f2 = f2 - f1;
			continue;
		}

		if (find_key == data[mid])
			return mid;

		if (find_key < data[mid])
		{
			if (f2 == 0)
				return -1;

			mid = mid - f2;

			int temp = f1 - f2;
			f1 = f2;
			f2 = temp;
		}
	}
}

void PrintArray(int data[], int n)
{
	for (int i=0; i<n; i++)
		printf("%d ", data[i]);

	printf("\n");
}

/*
 * 메인 프로그램 실행부
 */ 
int main()
{
	int nArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	
	PrintArray(nArray, 10);

	int nIndex = FibonacciSearch(nArray, 10, 6);
	if (nIndex > 0)
		printf("found 6 at %d\n", nIndex);
	else
		printf("not found.\n");

	return 0;
}