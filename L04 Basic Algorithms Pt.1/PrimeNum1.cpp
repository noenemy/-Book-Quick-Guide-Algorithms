#include <stdio.h>

/*
 * 함수 정의부
 */ 
bool IsPrimeNumber(int n)
{
	int count = 0;

	for (int i=1; i<=n; i++)
	{
		if (n % i == 0)
			count++;
	}

	if (count == 2)
		return true;	

	return false;
}

/*
 * 메인 프로그램 실행부
 */ 
int main()
{
	int n = 0;
	
	printf("Input number : ");
	scanf("%d", &n);

	printf("------------------------\n");
	if (IsPrimeNumber(n) == true)
		printf("%d is a prime number.\n");
	else
		printf("%d is not a prime number.\n");

	return 0;
}