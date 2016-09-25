#include <stdio.h>

/*
 * 함수 정의부
 */
void Reheap(int data[], int i, int n)
{
	bool bFlag = false;
	int j, k, m;
	
	m = k = data[i];
	j = 2 * i;

	while (j<=n && !bFlag)
	{
		if (j < n)
			if (data[j] < data[j+1]) j++;

		if (k >= data[j]) 
			bFlag = true;
		else
		{
			data[j/2] = data[j];
			j = j * 2;
		}
		
	}
	data[j/2] = m;
}

void HeapSort (int data[], int n)
{
	for (int i=n/2; i>=1; i--)
		Reheap(data, i, n);

	int temp = 0;

	for (i=n-1; i>=1; i--)
	{
		temp = data[i+1];
		data[i+1] = data[1];
		data[1] = temp;
	
		Reheap(data, 1, i);
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
	int nArray[11] = {0, 9, 10, 2, 5, 7, 3, 8, 6, 1, 4};
	
	PrintArray(nArray, 11);

	HeapSort(nArray, 11);

	PrintArray(nArray, 11);

	return 0;
}