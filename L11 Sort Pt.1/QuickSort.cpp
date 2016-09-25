#include <stdio.h>

/*
 * 함수 정의부
 */
void QuickSort (int data[], int n)
{
	if (n>1)
	{
		int x = data[n-1];
		int i = -1;
		int j = n-1;
		int temp = 0;

		while (true)
		{
			while (data[++i] < x);
			while (data[--j] > x);

			if (i>=j) 
				break;
			
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
		
		temp = data[i];
		data[i] = data[n-1];
		data[n-1] = temp;

		QuickSort(data, i);
		QuickSort(data+i+1, n-i-1);
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

	QuickSort(nArray, 10);

	PrintArray(nArray, 10);

	return 0;
}