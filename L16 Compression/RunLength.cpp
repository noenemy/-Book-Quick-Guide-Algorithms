#include <stdio.h>
#include <string.h>

#define ESCAPE_CHAR	0x21 // !	

/*
 * 함수 정의부
 */ 
bool Extract(FILE *fin, FILE *fout)
{
	bool bLoop = true;

	while (bLoop)
	{
		unsigned char uReadChar = fgetc(fin);

		// 파일의 끝이면 종료한다.
		if (feof(fin) != 0)
		{
			bLoop = false;
			continue;
		}

		// Escape 문자이면 반복개수만큼 문자를 출력한다.
		if (uReadChar == ESCAPE_CHAR)
		{
			unsigned char uRepeatChar = fgetc(fin);
			int nRepeatCount = fgetc(fin);

			for (int i=0; i < nRepeatCount; i++)
				fputc(uRepeatChar, fout);
		}
		// 일반문자이면 그냥 출력한다.
		else
			fputc(uReadChar, fout);
	}

	return true;
}

bool Compress(FILE *fin, FILE *fout)
{
	int nRepeatCount = 1;

	unsigned char uReadChar = fgetc(fin);
	unsigned char uLastChar = uReadChar;

	while (feof(fin) == 0)
	{
		uReadChar = fgetc(fin);

		// 최근에 읽은 문자와 같으면 카운터를 증가시킨다.
		if (uReadChar == uLastChar)
		{
			nRepeatCount++;
		}
		else
		{
			// 이전에 같은 문자가 2번 반복된 경우
			if (nRepeatCount == 2)
			{
				fputc(uLastChar, fout);
				fputc(uLastChar, fout);
			}
			// 3번이상 같은 문자가 반복된 경우
			else if (nRepeatCount > 2)
			{
				fputc(ESCAPE_CHAR, fout);
				fputc(uLastChar, fout);
				fputc(nRepeatCount, fout);
			}
			// 반복되지 않은 경우
			else
			{
				fputc(uLastChar, fout);
			}

			nRepeatCount = 1;
			uLastChar = uReadChar;
		}
	}

	return true;
}


void PrintUsage()
{
	printf("[사용법] RunLength /C <압축하려는 파일명> <압축된 파일명>\n");
	printf("                   /X <압축된 파일명> <압축해제된 파일명>\n");
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

	if (fin != NULL) fclose(fin);
	if (fout != NULL) fclose(fout);

	return 0;
}