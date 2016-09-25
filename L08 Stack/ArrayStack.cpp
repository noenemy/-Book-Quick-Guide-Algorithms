#include <stdio.h>

#define MAX_STACK_SIZE	10

int g_nArray[MAX_STACK_SIZE] = {0,};
int g_nTop = -1;

/*
* 함수 정의부
*/ 
bool IsEmpty()
{
	if (g_nTop == -1)
		return true;

	return false;
}

bool IsFull()
{
	if (g_nTop >= MAX_STACK_SIZE - 1)
		return true;

	return false;
}

bool Push(int nValue)
{
	if (IsFull() == true)
	{
		printf("[error] stack overflow.\n");
		return false;
	}

	g_nTop++;
	g_nArray[g_nTop] = nValue;

	printf("Push(%d)\n", nValue);

	return true;
}

bool Pop(int *pnValue)
{
	if (pnValue == NULL)
	{
		printf("[error] invalid parameter.\n");
		return false;
	}
	
	if (IsEmpty() == true)
	{
		printf("[error] stack underflow.\n");
		return false;
	}

	*pnValue = g_nArray[g_nTop];
	g_nTop--;

	printf("Pop(%d)\n", *pnValue);

	return true;
}

int GetDataCount()
{
	return g_nTop + 1;
}

void PrintStack()
{
	printf("PrintStack() : ");

	for (int i=g_nTop; i >= 0; i--)
		printf("%d ", g_nArray[i]);

	printf("\n");	
}

/* 
 * 메인 프로그램 실행부
 */ 
int main()
{
	int nValue = 0;

	Push(19);
	Push(28);
	Push(74);
	Push(10);

	PrintStack();
	printf("Current data count = %d\n", GetDataCount());

	Pop(&nValue);
	Pop(&nValue);
	Pop(&nValue);
	Pop(&nValue);
	Pop(&nValue);

	return 0;
}
