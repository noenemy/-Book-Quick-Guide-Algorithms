#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_DIGIT 3
#define RADIX_SIZE 10

typedef struct stNode
{
	int nKey[MAX_DIGIT];
	struct stNode *pNext;
} NODE, *PNODE;

/*
 * 함수 정의부
 */
PNODE RadixSort(PNODE pNode)
{
	PNODE pFront[RADIX_SIZE] = {0,};
	PNODE pRear[RADIX_SIZE] = {0,};
	int nDigit = 0;	

	for (int i=MAX_DIGIT-1; i>=0; i--)
	{
		for (int j=0; j<RADIX_SIZE; j++)
			pFront[j] = pRear[j] = NULL;
		
		while (pNode)
		{
			nDigit = pNode->nKey[i];
			if (!pFront[nDigit])
				pFront[nDigit] = pNode;
			else
				pRear[nDigit]->pNext = pNode;
			pRear[nDigit] = pNode;
			pNode = pNode->pNext;
		}
		pNode = NULL;

		for (j=RADIX_SIZE-1; j>=0; j--)
		{
			if (pFront[j])
			{
				pRear[j]->pNext = pNode;
				pNode = pFront[j];
			}
		}
	}

	return pNode;
}

void PrintList(PNODE pNode)
{
	while (pNode)
	{
		for (int i=0; i<MAX_DIGIT; i++)
			printf("%d", pNode->nKey[i]);
		
		printf(" ");
		pNode = pNode->pNext;
	}
	printf("\n");
}

void AddToList(PNODE pHead, PNODE pNode)
{
	PNODE pTemp = NULL;
	pTemp = pHead->pNext;

	pHead->pNext = pNode;
	pNode->pNext = pTemp;
}

void DeleteList(PNODE pNode)
{
	while (pNode)
	{
		DeleteList(pNode->pNext);
		pNode = pNode->pNext;
	}
	if (pNode) 
		free(pNode);
}

/*
 * 메인 프로그램 실행부
 */ 
int main()
{
 	NODE head = {0,};

	for (int i=0; i < 10; i++)
	{
		PNODE pNode = (PNODE)malloc(sizeof(NODE));
		for (int j=0; j<MAX_DIGIT; j++)
			pNode->nKey[j] = (rand()%RADIX_SIZE);
		AddToList(&head, pNode);
	}
	
	PrintList(head.pNext);

	head.pNext = RadixSort(head.pNext);

	PrintList(head.pNext);

	DeleteList(head.pNext);

	return 0;
}