#include <stdio.h>

/*
 * ���� ���α׷� �����
 */ 
int main()
{
	int nArr[10] = {0,};

	for (int i=0; i<10; i++)
		nArr[i] = i * i;

	for (int j=0; j<10; j++)
		printf("nArr[%d] = %d\n", j, nArr[j]);

	return 0;
}