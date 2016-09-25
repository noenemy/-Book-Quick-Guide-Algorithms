#include <stdio.h>

/*
 * 함수 정의부
 */ 
int GetGCD(int a, int b)
{
	printf("GCD(%d,%d)\n", a, b);

	while (b != 0)
	{
		int temp = b;
		b = a % b;
		a = temp;

		printf("GCD(%d,%d)\n", a, b);
	}
	return a;
}

/*
 * 메인 프로그램 실행부
 */ 
int main()
{
	int a = 0, b = 0;
	int gcd = 0;

	printf("input a : ");
	scanf("%d", &a);
	printf("input b : ");
	scanf("%d", &b);
	printf("-----------------\n");

	gcd = GetGCD(a, b);

	printf("-----------------\n");
	printf("result GCD : %d\n", gcd);

	return 0;
}