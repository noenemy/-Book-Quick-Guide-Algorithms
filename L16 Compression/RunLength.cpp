#include <stdio.h>
#include <string.h>

#define ESCAPE_CHAR	0x21 // !	

/*
 * �Լ� ���Ǻ�
 */ 
bool Extract(FILE *fin, FILE *fout)
{
	bool bLoop = true;

	while (bLoop)
	{
		unsigned char uReadChar = fgetc(fin);

		// ������ ���̸� �����Ѵ�.
		if (feof(fin) != 0)
		{
			bLoop = false;
			continue;
		}

		// Escape �����̸� �ݺ�������ŭ ���ڸ� ����Ѵ�.
		if (uReadChar == ESCAPE_CHAR)
		{
			unsigned char uRepeatChar = fgetc(fin);
			int nRepeatCount = fgetc(fin);

			for (int i=0; i < nRepeatCount; i++)
				fputc(uRepeatChar, fout);
		}
		// �Ϲݹ����̸� �׳� ����Ѵ�.
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

		// �ֱٿ� ���� ���ڿ� ������ ī���͸� ������Ų��.
		if (uReadChar == uLastChar)
		{
			nRepeatCount++;
		}
		else
		{
			// ������ ���� ���ڰ� 2�� �ݺ��� ���
			if (nRepeatCount == 2)
			{
				fputc(uLastChar, fout);
				fputc(uLastChar, fout);
			}
			// 3���̻� ���� ���ڰ� �ݺ��� ���
			else if (nRepeatCount > 2)
			{
				fputc(ESCAPE_CHAR, fout);
				fputc(uLastChar, fout);
				fputc(nRepeatCount, fout);
			}
			// �ݺ����� ���� ���
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
	printf("[����] RunLength /C <�����Ϸ��� ���ϸ�> <����� ���ϸ�>\n");
	printf("                   /X <����� ���ϸ�> <���������� ���ϸ�>\n");
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

	if (fin != NULL) fclose(fin);
	if (fout != NULL) fclose(fout);

	return 0;
}