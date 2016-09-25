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

		free(pNode);
	}
}

void TraversePreorder(Node *pNode)
{
	if (pNode != NULL)
	{
		printf("%c ", pNode->cValue);

		TraversePreorder(pNode->pLeft);

		TraversePreorder(pNode->pRight);		
	}
}

void TraverseInorder(Node *pNode)
{
	if (pNode != NULL)
	{
		TraverseInorder(pNode->pLeft);

		printf("%c ", pNode->cValue);

		TraverseInorder(pNode->pRight);	
	}
}

void TraversePostorder(Node *pNode)
{
	if (pNode != NULL)
	{
		TraversePostorder(pNode->pLeft);

		TraversePostorder(pNode->pRight);

		printf("%c ", pNode->cValue);
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

	printf("Preorder  : ");
	TraversePreorder(pRoot);
	printf("\n");

	printf("Inorder   : ");
	TraverseInorder(pRoot);
	printf("\n");

	printf("Postorder : ");
	TraversePostorder(pRoot);
	printf("\n");

	DeleteTree(pRoot);

	return 0;
} 