#include <stdio.h>

#define MAX_SIZE 10
int g_nSquare[MAX_SIZE][MAX_SIZE] = {0,};

/*
 * 함수 정의부
 */ 
bool IsInBlock(int n, int row, int col)
{
	int nQuater = 0, nHalf = 0;
	nHalf = n / 2;
	nQuater = nHalf / 2;

	if ( (row < nQuater) || (row >= nHalf + nQuater) )
	{
		if ( (col < nQuater) || (col >= nHalf + nQuater) )
			return true; 
	} 

	if ( (row >= nQuater) && (row < nHalf + nQuater) )
	{
		if ( (col >= nQuater) && (col < nHalf+nQuater) )
			return true;
	}

	return false;
}

void GetQuaterSquare(int n)
{
	int row = 0, col = 0;
	int nValue = 1;
	
	for (row=0; row<n; row++)
	{	
		for (col=0; col<n; col++)
		{
			if (IsInBlock(n, row, col) == true)
				g_nSquare[row][col] = nValue;
			nValue++;
		}
	}	

	nValue = 1;
	for (row=n-1; row>=0; row--)
	{
		for(col=n-1; col>=0; col--)
		{
			if (IsInBlock(n, row, col) == false)
				g_nSquare[row][col] = nValue;
			nValue++;
		}
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
	// 4 x 4 마방진
	InitSquare();
	GetQuaterSquare(4);
	ShowSquare(4);

	// 8 x 8 마방진
	InitSquare();
	GetQuaterSquare(8);
	ShowSquare(8);

	return 0;
}
