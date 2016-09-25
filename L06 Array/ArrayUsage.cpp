#include <stdio.h>

#define MAX_SIZE 10

/*
 * 함수 정의부
 */ 
void Insert(int nArray[], int nIndex, int nValue)
{
	if (nIndex < 0 || nIndex >= MAX_SIZE)
	{
		printf("Invalid Parameter.\n");
		return;
	}

	for (int i=MAX_SIZE-1; i>nIndex; i--)
		nArray[i] = nArray[i-1];

	nArray[nIndex] = nValue;
}

void Delete(int nArray[], int nIndex)
{
	if (nIndex < 0 || nIndex >= MAX_SIZE)
	{
		printf("Invalid Parameter.\n");
		return;
	}

	for (int i=nIndex; i<MAX_SIZE-1; i++)
		nArray[i] = nArray[i+1];

	nArray[MAX_SIZE-1] = 0;
}

int Find(int nArray[], int nValue)
{
	int i = 0;
	int nIndex = -1;

	while (i < MAX_SIZE)
	{
		if (nArray[i] == nValue)
		{
			nIndex = i;
			break;
		}
		i++;
	}

	return nIndex;
}

void Print(int nArray[])
{
	printf("->");

	for (int i=0; i<MAX_SIZE; i++)
		printf("%02d ", nArray[i]);
	printf("\n");
}

/*
 * 메인 프로그램 실행부
 */ 
int main()
{
	int nArray[MAX_SIZE] = {0,};
	Print(nArray);

	printf("set values\n");
	for (int i=0; i<MAX_SIZE; i++)
		nArray[i] = i+1;
	Print(nArray);

	printf("insert 10 at 3\n");
	Insert(nArray, 3, 10);
	Print(nArray);

	printf("delete at 5\n");
	Delete(nArray, 5);
	Print(nArray);

	int nIndex = Find(nArray, 6);
	if (nIndex > 0)
		printf("found 6 at %d\n", nIndex);

	return 0;
}