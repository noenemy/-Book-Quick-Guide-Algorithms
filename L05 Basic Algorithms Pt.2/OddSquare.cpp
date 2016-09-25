#include <stdio.h>

#define MAX_SIZE 10
int g_nSquare[MAX_SIZE][MAX_SIZE] = {0,};

/*
 * 함수 정의부
 */ 
void GetOddSquare(int n)
{
	int row = 0, col = 0;
	int nValue = 1;

	row = 0;
	col = n/2;

	while (nValue <= n*n)
	{
		g_nSquare[row][col] = nValue;

		if (nValue % n == 0)
			row++;
		else
		{
			row--;
			col++;
		}

		if (row < 0) 
			row = n-1;

		if (row >= n) 
			row = 0;

		if (col < 0) 
			col = n-1;

		if (col >= n) 
			col = 0;

		nValue++;
	}	
}


void InitSquare()
{
	for (int i=0; i<MAX_SIZE; i++)
	{
		for (int j=0; j<MAX_SIZE; j++)
			g_nSquare[i][j] = 0;
	}
}

void ShowSquare(int n)
{
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
			printf("%02d ", g_nSquare[i][j]);
		printf("\n");
	}
	
	printf("\n");
}


/*
 * 메인 프로그램 실행부
 */ 
int main()
{
	// 3 x 3 마방진
	InitSquare();
	GetOddSquare(3);
	ShowSquare(3);

	// 5 x 5 마방진
	InitSquare();
	GetOddSquare(5);
	ShowSquare(5);

	// 7 x 7 마방진
	InitSquare();
	GetOddSquare(7);
	ShowSquare(7);

	return 0;
}