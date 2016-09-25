#include <stdio.h>
#include <malloc.h>

struct Node
{
	char cValue;
	struct Node *pLeft;
	struct Node *pRight;
};

/*
 * �Լ� ���Ǻ�
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

	printf("%c ��尡 �����Ǿ����ϴ�.\n", pNode->cValue);

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

		printf("%c ��带 �����մϴ�.\n", pNode->cValue);
		free(pNode);
	}
}

/*
 * ���� ���α׷� ����� 
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