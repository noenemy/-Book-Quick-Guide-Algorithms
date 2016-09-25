#include <stdio.h>

/*
 * 함수 정의부
 */
int LinearSearch(int data[], int n, int find_key)
{
	int i = 0;
	while (i < n)
	{
		if (data[i] == find_key)
			return i;
		i++;
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
	int nArray[10] = {9, 10, 2, 5, 7, 3, 8, 6, 1, 4};
	
	PrintArray(nArray, 10);

	int nIndex = LinearSearch(nArray, 10, 8);
	if (nIndex > 0)
		printf("found 8 at %d\n", nIndex);
	else
		printf("not found.\n");

	return 0;
}