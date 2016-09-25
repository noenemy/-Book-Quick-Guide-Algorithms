#include <stdio.h>

#define MAX_SIZE 5

/*
 * 함수 정의부
 */ 
void PrintArray(char cArray[][MAX_SIZE])
{
	for (int i=0; i<MAX_SIZE; i++)
	{
		for (int j=0; j<MAX_SIZE; j++)
			printf("%c", cArray[i][j]);

		printf("\n");
	}
}

/*
 * 메인 프로그램 실행부
 */ 
int main()
{
	char cArray[MAX_SIZE][MAX_SIZE] = {0,};

	for (int i=0; i<MAX_SIZE; i++)
	{
		for (int j=0; j<MAX_SIZE; j++)
		{
			if ((i+j) % 2 == 0)
				cArray[i][j] = '*';
			else
				cArray[i][j] = ' ';
		}
	}

	PrintArray(cArray);

	return 0;
}