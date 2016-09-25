#include <stdio.h>

/*
 * �Լ� ���Ǻ�
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
 * ���� ���α׷� �����
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