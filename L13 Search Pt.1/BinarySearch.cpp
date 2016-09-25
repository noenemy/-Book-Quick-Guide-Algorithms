#include <stdio.h>

/*
 * 함수 정의부
 */
int BinarySearch(int data[], int n, int find_key)
{
	int mid = 0;
	int left = 0;
	int right = n-1;

	while (right >= left)
	{
		mid = (right + left) / 2;
		if (find_key == data[mid])
			return mid;

		if (find_key < data[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}

	return -1;
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

	int nIndex = BinarySearch(nArray, 10, 8);
	if (nIndex > 0)
		printf("found 8 at %d\n", nIndex);
	else
		printf("not found.\n");

	return 0;
}