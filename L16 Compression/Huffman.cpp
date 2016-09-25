#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct HuffNode
{
	int nValue;
	int nFreq;
	HuffNode *pLeft;
	HuffNode *pRight;
};

int g_nFreq[256] = {0,};
int g_nNodeCount = 0;

unsigned int g_uCode[256] = {0,};
int g_nLength[256] = {0,};

HuffNode *g_nNodeArray[256] = {0,};
HuffNode *g_pHead;

/*
 * �Լ� ���Ǻ�
 */ 
void DeleteHuffTree(HuffNode *pNode)
{
	if (pNode != NULL)
	{
		DeleteHuffTree(pNode->pLeft);
		DeleteHuffTree(pNode->pRight);

		free(pNode);
	}
}

void CalcFrequency(FILE *fin)
{
	int nValue = fgetc(fin);

	while (feof(fin) == 0)
	{
		g_nFreq[nValue]++;	// �󵵼� ���

		nValue = fgetc(fin);
	}

	rewind(fin);
}

int FindMinFrequency(int nIndex)
{
	int nMinIndex = 0;
	for (int i=0; i<nIndex; i++)
	{
		if (g_nNodeArray[i]->nFreq < g_nNodeArray[nMinIndex]->nFreq)
			nMinIndex = i; 
	}

	return nMinIndex;
}	

void MakeHuffTree()
{
	// Frequency�� �̿��ؼ� �ʱ� ��带 ����
	for (int i=0; i<256; i++)
	{
		if (g_nFreq[i] > 0)
		{
			HuffNode *pNode = (HuffNode *)malloc(sizeof(HuffNode));
			pNode->nValue = i;
			pNode->nFreq = g_nFreq[i];
			pNode->pLeft = NULL;
			pNode->pRight = NULL;

			g_nNodeCount++;
			g_nNodeArray[g_nNodeCount-1] = pNode;
		}
	}

	int nHead = g_nNodeCount;

	while (nHead > 1)
	{
		// ���� ����߿��� ���� ���� �󵵼��� ��� ã��
		int nMin = FindMinFrequency(nHead);
		HuffNode *pNode1 = g_nNodeArray[nMin];

		nHead--;
		g_nNodeArray[nMin] = g_nNodeArray[nHead];

		nMin = FindMinFrequency(nHead);
		HuffNode *pNode2 = g_nNodeArray[nMin];

		HuffNode *pNode = (HuffNode *)malloc(sizeof(HuffNode));

		pNode->nFreq = pNode1->nFreq + pNode2->nFreq;
		pNode->nValue = 0;
		pNode->pLeft = pNode1;
		pNode->pRight = pNode2;

		g_nNodeArray[nMin] = pNode;
	}

	// ������ Ʈ���� ��Ʈ ���
	g_pHead = g_nNodeArray[0];
}

void MakeCode(HuffNode *pNode, unsigned int uCode, int nLength)
{
	if (pNode->pLeft == NULL && pNode->pRight == NULL)
	{
		g_uCode[pNode->nValue] = uCode;
		g_nLength[pNode->nValue] = nLength;
	}
	else
	{
		uCode = uCode << 1;
		nLength++;
		MakeCode(pNode->pLeft, uCode, nLength);

		uCode = uCode | 1u;
		MakeCode(pNode->pRight, uCode, nLength);
		uCode = uCode >> 1;
		nLength--;
	}
}

void WriteByteFromBit(FILE* fout, unsigned int bCode, bool bFlush)
{
	static unsigned int s_nByte = 0;
	static int s_nBit = 7;

	// 8��Ʈ�� ���� ����
	if (s_nBit < 0 || bFlush == true) 
	{
        	putc(s_nByte, fout);
	        s_nBit = 7;
        	s_nByte = 0;
	}
	s_nByte = s_nByte | bCode << (s_nBit--);
}

bool Compress(FILE *fin, FILE *fout)
{
	// ���ں� �󵵼� ���ϱ�
	CalcFrequency(fin);

	// ������ Ʈ�� �����ϱ�
	MakeHuffTree();

	// ���ں� ��ü �ڵ� ���ϱ�
	MakeCode(g_pHead, 0u, 0);

	// ���� ���� ũ�⸦ ���ؼ� �����ϱ�
	fseek(fin, 0, SEEK_END);
	long lFileSize = ftell(fin);
	rewind(fin);
	fwrite((void *)&lFileSize, sizeof(long), sizeof(long), fout);

	// ��� �����ϱ�
	for (int i=0; i<256; i++)
	{
		putw(g_nLength[i], fout);
		putw(g_uCode[i], fout);
	}
	putc(NULL, fout);

	// ����� ���� �����ϱ�
	while (true)
	{
		int nIndex = getc(fin);
		if (feof(fin) != 0)
			break;
	
		for (i=g_nLength[nIndex]-1; i>=0; i--)
		{
			unsigned int uBit = 0;
			uBit = (g_uCode[nIndex] >> i) & ~ (~0 << 1);
			WriteByteFromBit(fout, uBit, false);
		}
	}
	WriteByteFromBit(fout, 0, true);

	return true;
}

bool ReadBitFromFile(FILE* fin, unsigned int *puBit)
{
	static unsigned int s_uCur = 0;
	static int s_nBit = -1;
	if (s_nBit < 0)
	{
		s_uCur = getc(fin);
		s_nBit = 7;
	}

	if (feof(fin) != 0)
		return false;

	unsigned int uBit = 0;
	uBit = (s_uCur >> s_nBit) & ~ (~0 << 1);
	s_nBit--;

	*puBit = uBit;
	
	return true;
}

void InsertIntoHuffTree(int nValue)
{
	if (g_pHead == NULL)
		g_pHead = (HuffNode *)calloc(1, sizeof(HuffNode));

	// g_uCode�� g_nLength�� �̿��ؼ� ������ Ʈ�� �����ϱ�
	HuffNode *pNode = NULL;
	HuffNode *pTemp = NULL;
	pNode = pTemp = g_pHead;

	int nLength = g_nLength[nValue];
	unsigned int uCode = g_uCode[nValue];

	while (nLength > 0)
	{
		int nBit = (uCode >> nLength-1) & ~(~0 << 1);
		if (nBit == 0)
		{
			pTemp = pTemp->pLeft;
			if (pTemp == NULL)
			{
				pTemp = (HuffNode *)calloc(1, sizeof(HuffNode));
				pNode->pLeft = pTemp;
			}
		}
		else
		{
			pTemp = pTemp->pRight;
			if (pTemp == NULL)
			{
				pTemp = (HuffNode *)calloc(1, sizeof(HuffNode));
				pNode->pRight = pTemp;
			}
		}
		pNode = pTemp;
		nLength--;
	}
	pTemp->nValue = nValue;
}

bool Extract(FILE *fin, FILE *fout)
{
	// ���� ���� ũ�� �б�
	long lFileSize = 0;
	fread(&lFileSize, sizeof(long), sizeof(long), fin);
	
	// ��� �б�
	for (int i=0; i<256; i++)
	{
		g_nLength[i] = getw(fin);
		g_uCode[i] = getw(fin);
	}
	getc(fin);

	// ������ Ʈ�� �籸���ϱ�
	for (i=0; i<256; i++)
	{
		if (g_nLength[i] > 0)
			InsertIntoHuffTree(i);
	}

	unsigned int uBit = 0;
	unsigned int nValue = 0;
	long lWrittenSize = 0;
	HuffNode *pNode = g_pHead;

	ReadBitFromFile(fin, &uBit);

	while (lWrittenSize < lFileSize)
	{	
		while (pNode->pLeft && pNode->pRight)
		{
			if (uBit == 0)
				pNode = pNode->pLeft;
			else
				pNode = pNode->pRight;

			ReadBitFromFile(fin, &uBit);
		}
		putc(pNode->nValue, fout);
		pNode = g_pHead;

		lWrittenSize++;
	}

	return true;
}

void PrintUsage()
{
	printf("[����] Huffman /C <�����Ϸ��� ���ϸ�> <����� ���ϸ�>\n");
	printf("                 /X <����� ���ϸ�> <���������� ���ϸ�>\n");
	printf("\n");
}

/*
 * ���� ���α׷� �����
 */
int main(int argc, char **argv)
{
	FILE *fin = NULL;
	FILE *fout = NULL;

	if (argc < 4)
	{
		PrintUsage();
		return -1;
	}

	int bCompressMode = true;

	if (strcmp(argv[1], "/C") == 0)
		bCompressMode = true;
	else if (strcmp(argv[1], "/X") == 0)
		bCompressMode = false;
	else
	{
		PrintUsage();
		return -1;
	}

	fin = fopen(argv[2], "rb");
	fout = fopen(argv[3], "wb");

	if (fin == NULL || fout == NULL)
	{
		printf("[err] ���� ���� ����\n");

		if (fin != NULL) fclose(fin);
		if (fout != NULL) fclose(fout);
		
		return -1;
	}

	if (bCompressMode)
		Compress(fin, fout);	// ����
	else
		Extract(fin, fout);		// ���� ����

	DeleteHuffTree(g_pHead);

	if (fin != NULL) fclose(fin);
	if (fout != NULL) fclose(fout);

	return 0;
}