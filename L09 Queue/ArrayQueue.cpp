#include <stdio.h>

#define MAX_QUEUE_SIZE	10

int g_nArray[MAX_QUEUE_SIZE] = {0,};
int g_nFront = 0;
int g_nRear = -1;

/*
 * 함수 정의부
 */ 
bool IsEmpty()
{
	if (g_nFront > g_nRear)
		return true;

	return false;
}

bool IsFull()
{
	if (g_nRear >= MAX_QUEUE_SIZE - 1)
		return true;

	return false;
}

bool Put(int nValue)
{
	if (IsFull() == true)
	{
		printf("[error] queue overflow.\n");
		return false;
	}

	g_nRear++;
	g_nArray[g_nRear] = nValue;

	printf("Push(%d)\n", nValue);

	return true;
}

bool Get(int *pnValue)
{
	if (pnValue == NULL)
	{
		printf("[error] invalid parameter.\n");
		return false;
	}
	
	if (IsEmpty() == true)
	{
		printf("[error] queue underflow.\n");
		return false;
	}

	*pnValue = g_nArray[g_nFront];
	g_nFront++;

	printf("Pop(%d)\n", *pnValue);

	return true;
}

int GetDataCount()
{
	return (g_nRear - g_nFront + 1);
}

void PrintQueue()
{
	printf("PrintQueue() : ");

	for (int i=g_nFront; i <= g_nRear; i++)
		printf("%d ", g_nArray[i]);

	printf("\n");	
}

/* 
 * 메인 프로그램 실행부
 */ 
int main()
{
	int nValue = 0;

	Put(19);
	Put(28);
	Put(74);
	Put(10);

	PrintQueue();
	printf("Current data count = %d\n", GetDataCount());

	Get(&nValue);
	Get(&nValue);
	Get(&nValue);
	Get(&nValue);
	Get(&nValue);

	return 0;
}