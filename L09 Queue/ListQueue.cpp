#include <stdio.h>
#include <malloc.h>

#define MAX_QUEUE_SIZE 100

struct Node
{
	int nValue;
	Node *pNext;
};

Node *g_pFront = NULL;
Node *g_pRear = NULL;
int g_nCount = 0;

/*
 * 함수 정의부
 */ 
bool IsFull()
{
	if (g_nCount >= MAX_QUEUE_SIZE)
		return true;
	
	return false;
}

bool IsEmpty()
{
	if (g_nCount == 0)
		return true;

	return false;
}

bool Put(int nValue)
{
	if (IsFull() == true)
	{
		printf("[error] queue overflow\n");
		return false;
	}

	Node *pNode = (Node *)malloc(sizeof(Node));
	if (pNode == NULL)
	{
		printf("[error] memory allocation failed.\n");
		return false;
	}

	pNode->nValue = nValue;
	pNode->pNext = NULL;

	if (g_nCount == 0)
	{
		g_pRear = pNode;
		g_pFront = pNode;
	}
	else
	{
		g_pRear->pNext = pNode;
		g_pRear = pNode;
	}

	g_nCount++;

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

	*pnValue = g_pFront->nValue;
	
	Node *pDelNode = g_pFront;
	g_pFront = g_pFront->pNext;
	free(pDelNode);

	g_nCount--;
	if (g_nCount == 0)
	{
		g_pFront = NULL;
		g_pRear = NULL;
	}

	printf("Pop(%d)\n", *pnValue);

	return true;
}

int GetDataCount()
{
	return g_nCount;
}

void PrintQueue()
{
	printf("PrintStack() : ");

	Node *pNode = g_pFront;
	while (pNode != NULL)
	{
		printf("%d ", pNode->nValue);
		pNode = pNode->pNext;
	}

	printf("\n");	
}

void RemoveQueue()
{
	Node *pNode = g_pFront;
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

	RemoveQueue();

	return 0;
}