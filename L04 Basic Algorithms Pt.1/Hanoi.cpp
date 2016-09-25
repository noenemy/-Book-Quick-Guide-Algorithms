#include <stdio.h>

/*
 * 함수 정의부
 */ 
void Hanoi(int n, char from, char middle, char to)
{
	if (n == 1)
		printf("board #%02d %c -> %c\n", n, from, to);
	else
	{
		Hanoi(n-1, from, to, middle);

		printf("board #%02d %c -> %c\n", n, from, to);

		Hanoi(n-1, middle, from, to);
	}
}

/*
 * 메인 프로그램 실행부
 */ 
int main()
{
	int n = 0;
	
	printf("Input board number : ");
	scanf("%d", &n);

	printf("------------------------\n");
	Hanoi(n, 'A', 'B', 'C');

	return 0;
}