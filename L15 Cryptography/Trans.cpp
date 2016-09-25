#include <stdio.h>
#include <memory.h>

#define BUFFER_SIZE 	512

/*
 * 함수 정의부
 */
void TransCipher(unsigned char *pBuffer, int nLength)
{
	for (int i=0; i<nLength; i=i+4)
	{
		unsigned char unTemp = 0;
	
		unTemp = pBuffer[i];
		pBuffer[i] = pBuffer[i+3];
		pBuffer[i+3] = unTemp;
	
		unTemp = pBuffer[i+1];
		pBuffer[i+1] = pBuffer[i+2];
		pBuffer[i+2] = unTemp;
	}
}

bool Encrypt(char *szInputFile, char *szOutputFile)
{
	FILE *fin = NULL;
	FILE *fout = NULL;

	unsigned char buffer[BUFFER_SIZE] = {0,};
	int nCount = 0;

	fin = fopen(szInputFile, "rb");
	fout = fopen(szOutputFile, "wb");

	if (fin == NULL || fout == NULL)
	{
		printf("파일 열기 실패\n");
		return false;
	}

	while (feof(fin) == NULL)
	{
		nCount = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, fin);
		TransCipher(buffer, nCount);

		nCount = fwrite(buffer, sizeof(unsigned char), nCount, fout);
		memset(buffer, 0, BUFFER_SIZE);
	}

	if (fin != NULL) 
		fclose(fin);
	if (fout != NULL)
		fclose(fout);

	return true;
}

/*
 * 메인 프로그램 실행부
 */
int main(int argc, char **argv)
{


	if (argc < 3)
	{
		printf("[사용법] Trans <inputfile> <outputfile>\n");
		return 0;
	}
	
	Encrypt(argv[1], argv[2]);

	return 0;
}