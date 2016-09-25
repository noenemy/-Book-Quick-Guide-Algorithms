#include <stdio.h>
#include <memory.h>

#define BUFFER_SIZE 	512
#define ENC_KEY_SIZE 	16

unsigned char XORKey[] = {0x20, 0x30, 0xEB, 0x90, 
			  0xB1, 0xE0, 0xF2, 0x3E, 
			  0x93, 0x4A, 0xF3, 0x41, 
			  0x5A, 0x3F, 0x32, 0xC9};

/*
 * 함수 정의부
 */
void XORCrypt(unsigned char *pBuffer, int nLength)
{
	for (int i=0; i<nLength; i++)
	{
		pBuffer[i] ^= XORKey[i % ENC_KEY_SIZE];
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
		XORCrypt(buffer, nCount);

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
		printf("[사용법] XOR.exe inputfile outputfile\n");
		return 0;
	}

	Encrypt(argv[1], argv[2]);


	return 0;
}