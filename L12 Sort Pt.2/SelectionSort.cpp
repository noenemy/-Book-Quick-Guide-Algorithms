#include <stdio.h>

/*
 * 함수 정의부
 */
void SelectionSort(int data[], int n)
{
	for (int i=0; i<n-1; i++)
	{
		int min_index = i;
		for (int j=i+1; j<n; j++)
		{
			if (data[min_index] > data[j]) 
				min_index = j;
		}	
		
		if (min_index != i)
		{
			int temp = data[min_index];
			data[min_index] = data[i];
			data[i] = temp;
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
	int nArray[10] = {9, 10, 2, 5, 7, 3, 8, 6, 1, 4};
	
	PrintArray(nArray, 10);

	SelectionSort(nArray, 10);

	PrintArray(nArray, 10);

	return 0;
}