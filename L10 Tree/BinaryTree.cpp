#include <stdio.h>
#include <malloc.h>

struct Node
{
	char cValue;
	struct Node *pLeft;
	struct Node *pRight;
};

/*
 * 함수 정의부
 */ 
Node * CreateNode(char cValue)
{
	Node *pNode = NULL;
	pNode = (Node *)malloc(sizeof(Node));
	if (pNode == NULL)
		return NULL;

	pNode->cValue = cValue;
	pNode->pLeft = NULL;
	pNode->pRight = NULL;

	printf("%c 노드가 생성되었습니다.\n", pNode->cValue);

	return pNode;
}

void DeleteTree(Node *pNode)
{
	if (pNode != NULL)
	{
		if (pNode->pLeft != NULL)
			DeleteTree(pNode->pLeft);
		if (pNode->pRight != NULL)
			DeleteTree(pNode->pRight);

		printf("%c 노드를 삭제합니다.\n", pNode->cValue);
		free(pNode);
	}
}

/*
 * 메인 프로그램 실행부 
 */
int main()
{
	Node *pRoot = NULL;
	pRoot = CreateNode('A');

	pRoot->pLeft = CreateNode('B');
	pRoot->pRight = CreateNode('C');

	pRoot->pLeft->pLeft = CreateNode('D');
	pRoot->pLeft->pRight = CreateNode('E');

	pRoot->pRight->pLeft = CreateNode('F');
	pRoot->pRight->pRight = CreateNode('G');

	pRoot->pLeft->pRight->pLeft = CreateNode('H');
	pRoot->pLeft->pRight->pRight = CreateNode('I');

	DeleteTree(pRoot);

	return 0;
} 