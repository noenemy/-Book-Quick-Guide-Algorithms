#include <stdio.h>

/*
 * 함수 정의부
 */
int InterpolationSearch(int data[], int n, int find_key)
{
	int low = 1;
	int high = n;

	while ((high > low))
	{
		int i = low + (find_key-data[low]) / (data[high]-data[low]) * (high-low);
		
		if (find_key == data[i])
			return i;
		else if (find_key < data[i])
			high = i - 1;
		else
			low = i + 1;	
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

	int nIndex = InterpolationSearch(nArray, 10, 7);
	if (nIndex > 0)
		printf("found 7 at %d\n", nIndex);
	else
		printf("not found.\n");

	return 0;
}