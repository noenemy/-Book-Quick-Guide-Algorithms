#include <stdio.h>

/*
 * 함수 정의부
 */
int FibonacciSearch(int data[], int n, int find_key)
{
	int mid, f1, f2, t;

	f1 = data[n-2];
	f2 = data[n-3];
	mid = n - data[n-2] + 1;

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
			t = f1 - f2;
			f1 = f2;
			f2 = t;
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

	int nIndex = FibonacciSearch(nArray, 10, 8);
	if (nIndex > 0)
		printf("found 8 at %d\n", nIndex);
	else
		printf("not found.\n");

	return 0;
}