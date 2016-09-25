#include <stdio.h>

#define MAX_SIZE 5

/*
 * 함수 정의부
 */ 
void PrintArray(int nArray[][MAX_SIZE])
{
	for (int i=0; i<MAX_SIZE; i++)
	{
		for (int j=0; j<MAX_SIZE; j++)
			printf("%2d ", nArray[i][j]);

		printf("\n");
	}
}

/*
 * 메인 프로그램 실행부
 */ 
int main()
{
	int nValue = 1;
	int nArray[MAX_SIZE][MAX_SIZE] = {0,};

	for (int i=0; i<MAX_SIZE; i++)
	{
		if (i % 2 == 0)
		{
			for (int j=0; j<MAX_SIZE; j++)
				nArray[i][j] = nValue++;
		}
		else
		{
			for (int j=MAX_SIZE-1; j>=0; j--)
				nArray[i][j] = nValue++;
		}
	}

	PrintArray(nArray);

	return 0;
}