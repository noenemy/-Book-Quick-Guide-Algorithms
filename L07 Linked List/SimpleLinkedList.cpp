#include <stdio.h>
#include <malloc.h>

struct Node
{
	int nData; // 데이터
	Node *pNext; // 다음 노드에 대한 링크
};

/*
 * 함수 정의부
 */ 
void InsertNode(Node *pPrev, int nData)
{
	// 새로운 노드를 생성한다.
	Node *pNode = NULL;
	pNode = (Node *)malloc(sizeof(Node));
	pNode->nData = nData;

	// 이전 노드의 링크를 저장한다.
	pNode->pNext = pPrev->pNext;

	// 이전 노드의 링크에 새로운 노드 주소를 저장한다. 
	pPrev->pNext = pNode;
}

void DeleteNode(Node *pPrev)
{
	// 삭제할 노드
	Node *pDelNode = pPrev->pNext;

	// 삭제할 노드 링크 정보를 저장한다.
	pPrev->pNext = pDelNode->pNext;

	// 노드를 삭제한다.
	free(pDelNode);
}

void TraverseNode(Node *pNode)
{
	Node *pPointer = pNode;

	// 노드의 데이터를 출력한다.	
	printf("%d ", pPointer->nData);

	// 다음 노드 정보가 있으면 반복한다. (재귀호출)
	if (pPointer->pNext != NULL)
		TraverseNode(pPointer->pNext);		

}

/*
 * 메인 프로그램 실행부
 */ 
int main()
{
	// 최초 머리노드와 꼬리노드 구성
	Node head, tail;
	head.nData = 10;
	tail.nData = 20;
	head.pNext = &tail;
	tail.pNext = NULL;

	TraverseNode(&head);
	printf("\n");
	
	InsertNode(&head, 2);
	InsertNode(&head, 4);
	InsertNode(&head, 1978);

	TraverseNode(&head);
	printf("\n");

	DeleteNode(&head);
	DeleteNode(&head);
	DeleteNode(&head);

	TraverseNode(&head);
	printf("\n");

	return 0;
}

