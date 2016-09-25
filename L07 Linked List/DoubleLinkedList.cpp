#include <stdio.h>
#include <malloc.h>

struct Node
{
	Node *pPrev; // ���� ��忡 ���� ��ũ
	int nData;   // ������
	Node *pNext; // ���� ��忡 ���� ��ũ
};

/*
 * �Լ� ���Ǻ�
 */
void InsertNode(Node *pTarget, int nData)
{
	// ���ο� ��带 �����Ѵ�.
	Node *pNode = NULL;
	pNode = (Node *)malloc(sizeof(Node));
	pNode->nData = nData;

	// ���ο� ����� ��ũ�� �����Ѵ�.
	pNode->pNext = pTarget->pNext;
	pNode->pPrev = pTarget;

	// ���� ����� ��ũ�� ���ο� ��� ������ �����Ѵ�.
	if (pNode->pPrev != NULL)
		pNode->pPrev->pNext = pNode;

	if (pNode->pNext != NULL)
		pNode->pNext->pPrev = pNode;
}

void DeleteNode(Node *pTarget)
{
	// �� ����� ��ũ�� �����Ѵ�.
	if (pTarget->pPrev != NULL)
		pTarget->pPrev->pNext = pTarget->pNext;

	// �� ����� ��ũ�� �����Ѵ�.
	if (pTarget->pNext != NULL)
		pTarget->pNext->pPrev = pTarget->pPrev;

	// ��带 �����Ѵ�.
	free(pTarget);
}

void TraverseNodeForward(Node *pNode)
{
	Node *pPointer = pNode;

	// ����� �����͸� ����Ѵ�.	
	printf("%d ", pPointer->nData);

	// ���� ��� ������ ������ �ݺ��Ѵ�. (���ȣ��)
	if (pPointer->pNext != NULL)
		TraverseNodeForward(pPointer->pNext);	
}

void TraverseNodeReverse(Node *pNode)
{
	Node *pPointer = pNode;

	// ����� �����͸� ����Ѵ�.	
	printf("%d ", pPointer->nData);

	// ���� ��� ������ ������ �ݺ��Ѵ�. (���ȣ��)
	if (pPointer->pPrev != NULL)
		TraverseNodeReverse(pPointer->pPrev);	
}

/*
 * ���� ���α׷� �����
 */ 
int main()
{
	// ���� �Ӹ����� ������� ����
	Node head, tail;
	head.nData = 40;
	tail.nData = 50;
	head.pPrev = NULL;
	head.pNext = &tail;
	tail.pPrev = &head;
	tail.pNext = NULL;

	TraverseNodeForward(&head);
	printf("\n");
	
	InsertNode(&head, 20);
	InsertNode(&head, 10);
	InsertNode(&head, 1975);

	TraverseNodeForward(&head);
	printf("\n");

	TraverseNodeReverse(&tail);
	printf("\n");

	DeleteNode(head.pNext);
	DeleteNode(head.pNext);

	TraverseNodeForward(&head);
	printf("\n");

	return 0;
}

