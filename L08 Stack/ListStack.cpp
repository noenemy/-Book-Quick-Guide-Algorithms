#include <stdio.h>
#include <malloc.h>

#define MAX_STACK_SIZE 100

struct Node
{
	int nValue;
	Node *pNext;
};

Node *g_pTop = NULL;
int g_nCount = 0;

/*
 * 함수 정의부
 */ 
bool IsFull()
{
	if (g_nCount >= MAX_STACK_SIZE)
		return true;
	
	return false;
}

bool IsEmpty()
{
	if (g_nCount == 0)
		return true;

	return false;
}

bool Push(int nValue)
{
	if (IsFull() == true)
	{
		printf("[error] stack overflow\n");
		return false;
	}

	Node *pNode = (Node *)malloc(sizeof(Node));
	if (pNode == NULL)
	{
		printf("[error] memory allocation failed.\n");
		return false;
	}

	pNode->nValue = nValue;
	pNode->pNext = g_pTop;

	g_pTop = pNode;
	g_nCount++;

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

	*pnValue = g_pTop->nValue;
	
	Node *pDelNode = g_pTop;
	g_pTop = g_pTop->pNext;
	free(pDelNode);

	g_nCount--;

	printf("Pop(%d)\n", *pnValue);

	return true;
}

int GetDataCount()
{
	return g_nCount;
}

void PrintStack()
{
	printf("PrintStack() : ");

	Node *pNode = g_pTop;
	while (pNode != NULL)
	{
		printf("%d ", pNode->nValue);
		pNode = pNode->pNext;
	}

	printf("\n");	
}

void RemoveStack()
{
	Node *pNode = g_pTop;
	while (pNode != NULL)
	{
		Node *pDelNode = pNode;
		pNode = pNode->pNext;

		free(pDelNode);
	}
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

	RemoveStack();

	return 0;
}