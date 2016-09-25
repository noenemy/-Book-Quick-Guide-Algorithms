#include <stdio.h>
#include <malloc.h>

struct Node
{
	int nData;
	Node *pLeft;
	Node *pRight;
};

/*
 * 함수 정의부
 */
Node* InsertBTree(Node *pHead, int nValue)
{
	Node *pNode = pHead;
	Node *pPos = NULL;

	while (pNode != NULL)
	{
		pPos = pNode;

		if (nValue < pNode->nData)
			pNode = pNode->pLeft;
		else if (nValue > pNode->nData)
			pNode = pNode->pRight;
		else
			return NULL;
	}

	Node *pNewNode = (Node *)malloc(sizeof(Node));
	if (pNewNode == NULL)
		return NULL;

	pNewNode->nData = nValue;
	pNewNode->pLeft = NULL;
	pNewNode->pRight = NULL;

	if (pHead == NULL)
		return pNewNode;

	if (nValue < pPos->nData)
		pPos->pLeft = pNewNode;
	else
		pPos->pRight = pNewNode;

	return pNewNode;
}

void RemoveBTree(Node *pHead)
{
	if (pHead != NULL)
	{
		if (pHead->pLeft != NULL)
			RemoveBTree(pHead->pLeft);

		if (pHead->pRight != NULL)
			RemoveBTree(pHead->pRight);

		free(pHead);
	}
}

void PrintBTree(Node *pHead)
{
	Node *pNode = pHead;
	if (pNode != NULL)
	{
		if (pNode->pLeft != NULL)
			PrintBTree(pNode->pLeft);

		if (pNode->pRight != NULL)
			PrintBTree(pNode->pRight);

		printf("%d ", pNode->nData);
	}
}

Node* BTreeSearch(Node *pNode, int find_key)
{
	while (pNode != NULL)
	{
		if (find_key == pNode->nData)
			return pNode;
		else if (find_key < pNode->nData)
			pNode = pNode->pLeft;
		else
			pNode = pNode->pRight;
	}

	return NULL;
}

/*
 * 메인 프로그램 실행부
 */ 
int main()
{
	Node *pHead = NULL;
	pHead = InsertBTree(NULL, 60);

	InsertBTree(pHead, 40);
	InsertBTree(pHead, 20);
	InsertBTree(pHead, 44);
	InsertBTree(pHead, 95);
	InsertBTree(pHead, 80);

	PrintBTree(pHead);
	printf("\n");

	Node *pNode = BTreeSearch(pHead, 44);
	if (pNode != NULL)
		printf("found 44.\n");
	else
		printf("not found.\n");

	RemoveBTree(pHead);

	return 0;
}