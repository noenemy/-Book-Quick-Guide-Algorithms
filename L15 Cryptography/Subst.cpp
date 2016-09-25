#include <stdio.h>
#include <memory.h>
#include <string.h>

#define BUFFER_SIZE 	512
#define SUBST_VALUE	5

/*
 * �Լ� ���Ǻ�
 */
void SubstEncrypt(unsigned char *pBuffer, int nLength)
{
	for (int i=0; i<nLength; i++)
	{
		pBuffer[i] = pBuffer[i] + SUBST_VALUE;
		if (pBuffer[i] > 255)
			pBuffer[i] = pBuffer[i] - 255;
	}
}

void SubstDecrypt(unsigned char *pBuffer, int nLength)
{
	for (int i=0; i<nLength; i++)
	{
		pBuffer[i] = pBuffer[i] - SUBST_VALUE;
		if (pBuffer[i] < 0)
			pBuffer[i] = pBuffer[i] + 255;
	}
}


bool Encrypt(char *szInputFile, char *szOutputFile, bool bEncrypt)
{
	FILE *fin = NULL;
	FILE *fout = NULL;

	unsigned char buffer[BUFFER_SIZE] = {0,};
	int nCount = 0;

	fin = fopen(szInputFile, "rb");
	fout = fopen(szOutputFile, "wb");

	if (fin == NULL || fout == NULL)
	{
		printf("���� ���� ����\n");
		return false;
	}

	while (feof(fin) == NULL)
	{
		nCount = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, fin);
		
		if (bEncrypt == true)
			SubstEncrypt(buffer, nCount);
		else
			SubstDecrypt(buffer, nCount);

		nCount = fwrite(buffer, sizeof(unsigned char), nCount, fout);
		memset(buffer, 0, BUFFER_SIZE);
	}

	if (fin != NULL) 
		fclose(fin);
	if (fout != NULL)
		fclose(fout);

	return true;
}

void ShowHelpMsg()
{
	printf("[����] Subst [/E] [/D] <inputfile> <outputfile>\n");
	printf("         /E : ��ȣȭ\n");
	printf("         /D : ��ȣȭ\n");
	printf("\n");
}


/*
 * ���� ���α׷� �����
 */
int main(int argc, char **argv)
{


	if (argc < 4)
	{
		ShowHelpMsg();
		return 0;
	}
	
	if (strcmp(argv[1], "/E") == 0)
		Encrypt(argv[2], argv[3], true);
	else if (strcmp(argv[1], "/D") == 0)
		Encrypt(argv[2], argv[3], false);
	else
		ShowHelpMsg();

	return 0;
}