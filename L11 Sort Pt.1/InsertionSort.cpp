#include <stdio.h>

/*
 * 함수 정의부
 */
void InsertionSort(int data[], int n)
{
	for (int i=1; i<n; i++)
	{
		int temp = data[i];
		for (int j=i; j>0; j--)
		{ 
			if (temp < data[j-1])
				data[j] = data[j-1];
			else
				break;
		}

		data[j] = temp;
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
	int nArray[10] = {9, 10, 2, 5, 7, 3, 8, 6, 1, 4};
	
	PrintArray(nArray, 10);

	InsertionSort(nArray, 10);

	PrintArray(nArray, 10);

	return 0;
}