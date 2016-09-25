#include <stdio.h>

/*
 * 함수 정의부
 */
void BubbleSort(int data[], int n)
{
	bool bFlag = true;
	int final_position, limit, bubble_key;

	limit = n;

	while (bFlag == true)
	{
		bFlag = false;
		for (int j=0; j<limit; j++)
		{ 
			if (data[j] > data[j+1])
			{
				bubble_key = data[j];
				data[j] = data[j+1];
				data[j+1] = bubble_key;
       
				bFlag = true;
				final_position = j;
			}
		}
		limit = final_position;
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

	BubbleSort(nArray, 10);

	PrintArray(nArray, 10);

	return 0;
}