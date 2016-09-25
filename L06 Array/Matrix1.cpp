#include <stdio.h>

#define MAX_SIZE 5

/*
 * �Լ� ���Ǻ�
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
 * ���� ���α׷� �����
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