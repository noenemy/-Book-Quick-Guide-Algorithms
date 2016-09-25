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
 * 함수 정의부
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
		g_nFreq[nValue]++;	// 빈도수 계산

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
	// Frequency를 이용해서 초기 노드를 생성
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
		// 현재 노드중에서 가장 작은 빈도수의 노드 찾기
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

	// 허프만 트리의 루트 노드
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

	// 8비트를 만들어서 저장
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
	// 문자별 빈도수 구하기
	CalcFrequency(fin);

	// 허프만 트리 구성하기
	MakeHuffTree();

	// 문자별 대체 코드 구하기
	MakeCode(g_pHead, 0u, 0);

	// 원본 파일 크기를 구해서 저장하기
	fseek(fin, 0, SEEK_END);
	long lFileSize = ftell(fin);
	rewind(fin);
	fwrite((void *)&lFileSize, sizeof(long), sizeof(long), fout);

	// 헤더 저장하기
	for (int i=0; i<256; i++)
	{
		putw(g_nLength[i], fout);
		putw(g_uCode[i], fout);
	}
	putc(NULL, fout);

	// 압축된 내용 저장하기
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

	// g_uCode와 g_nLength를 이용해서 허프만 트리 구성하기
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
	// 원본 파일 크기 읽기
	long lFileSize = 0;
	fread(&lFileSize, sizeof(long), sizeof(long), fin);
	
	// 헤더 읽기
	for (int i=0; i<256; i++)
	{
		g_nLength[i] = getw(fin);
		g_uCode[i] = getw(fin);
	}
	getc(fin);

	// 허프만 트리 재구성하기
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
	printf("[사용법] Huffman /C <압축하려는 파일명> <압축된 파일명>\n");
	printf("                 /X <압축된 파일명> <압축해제된 파일명>\n");
	printf("\n");
}

/*
 * 메인 프로그램 실행부
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
		printf("[err] 파일 열기 실패\n");

		if (fin != NULL) fclose(fin);
		if (fout != NULL) fclose(fout);
		
		return -1;
	}

	if (bCompressMode)
		Compress(fin, fout);	// 압축
	else
		Extract(fin, fout);		// 압축 해제

	DeleteHuffTree(g_pHead);

	if (fin != NULL) fclose(fin);
	if (fout != NULL) fclose(fout);

	return 0;
}