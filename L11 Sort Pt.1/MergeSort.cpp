#include <stdio.h>

/*
 * 함수 정의부
 */
void MergeSort(int data1[], int data2[], int m, int n )
{
	int i = 1, k = 1;
	int j = m + 1;

	while (i<=m && j<=n)
	{
		if (data1[i] <= data1[j])
		{
			data2[k] = data1[i];
			i++;
		}
		else
		{
			data2[k] = data1[j];
			j++;
		}
		k++;
	}

	if (i > m)
	{
		for(int t=j; t<=n; t++)
			data2[k++] = data1[t];
	}
	else
	{
		for(int t=i; t<=m; t++)
			data2[k++] = data1[t];
	}
}

void PrintArray(int data[], int n)
{
	for (int i=1; i<n; i++)
		printf("%d ", data[i]);

	printf("\n");
}

/*
 * 메인 프로그램 실행부
 */ 
int main()
{
	int nArray1[11] = {0, 1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
	int nArray2[11] = {0,};
	
	PrintArray(nArray1, 11);

	MergeSort(nArray1, nArray2, 5, 10);

	PrintArray(nArray2, 11);

	return 0;
}