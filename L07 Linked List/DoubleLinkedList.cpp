#include <stdio.h>
#include <malloc.h>

struct Node
{
	Node *pPrev; // 이전 노드에 대한 링크
	int nData;   // 데이터
	Node *pNext; // 다음 노드에 대한 링크
};

/*
 * 함수 정의부
 */
void InsertNode(Node *pTarget, int nData)
{
	// 새로운 노드를 생성한다.
	Node *pNode = NULL;
	pNode = (Node *)malloc(sizeof(Node));
	pNode->nData = nData;

	// 새로운 노드의 링크를 구성한다.
	pNode->pNext = pTarget->pNext;
	pNode->pPrev = pTarget;

	// 기존 노드의 링크에 새로운 노드 정보를 저장한다.
	if (pNode->pPrev != NULL)
		pNode->pPrev->pNext = pNode;

	if (pNode->pNext != NULL)
		pNode->pNext->pPrev = pNode;
}

void DeleteNode(Node *pTarget)
{
	// 앞 노드의 링크를 수정한다.
	if (pTarget->pPrev != NULL)
		pTarget->pPrev->pNext = pTarget->pNext;

	// 뒤 노드의 링크를 수정한다.
	if (pTarget->pNext != NULL)
		pTarget->pNext->pPrev = pTarget->pPrev;

	// 노드를 삭제한다.
	free(pTarget);
}

void TraverseNodeForward(Node *pNode)
{
	Node *pPointer = pNode;

	// 노드의 데이터를 출력한다.	
	printf("%d ", pPointer->nData);

	// 다음 노드 정보가 있으면 반복한다. (재귀호출)
	if (pPointer->pNext != NULL)
		TraverseNodeForward(pPointer->pNext);	
}

void TraverseNodeReverse(Node *pNode)
{
	Node *pPointer = pNode;

	// 노드의 데이터를 출력한다.	
	printf("%d ", pPointer->nData);

	// 이전 노드 정보가 있으면 반복한다. (재귀호출)
	if (pPointer->pPrev != NULL)
		TraverseNodeReverse(pPointer->pPrev);	
}

/*
 * 메인 프로그램 실행부
 */ 
int main()
{
	// 최초 머리노드와 꼬리노드 구성
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

