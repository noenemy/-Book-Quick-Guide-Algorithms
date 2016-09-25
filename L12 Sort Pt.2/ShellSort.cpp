#include <stdio.h>

/*
 * 함수 정의부
 */
void ShellSort(int data[], int n)
{
	for (int h=1; h<n; h=3*h+1);

	for (h/=3; h>0; h/=3)
	{
		for (int i=0; i<h; i++)
		{
			for (int j=i+h; j<n; j+=h)
			{
				int temp = data[j];
				int k = j;
				while (k>h-1 && data[k-h] > temp)
				{
					data[k] = data[k-h];
					k = k-h;
				}
				data[k] = temp;
			}
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

	ShellSort(nArray, 10);

	PrintArray(nArray, 10);

	return 0;
}