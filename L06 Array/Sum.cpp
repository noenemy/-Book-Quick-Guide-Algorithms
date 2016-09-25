#include <stdio.h>

/*
 * 메인 프로그램 실행부
 */ 
int main()
{
	int nArray[10] = {0,};
	int nSum = 0;

	for (int i=0; i<10; i++)
		nArray[i] = i+1;

	for (int i=0; i<10; i++)
		nSum = nSum + nArray[i];

	printf("Sum = %d\n", nSum);

	return 0;
}