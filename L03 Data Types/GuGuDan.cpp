#include <stdio.h>

/*
 * 메인 프로그램 실행부
 */ 
int main()
{
	int n = 0;
	bool bLoop = true;	

	while (bLoop == true)
	{
		printf("몇 단을 출력할까요(1-9) :");
		scanf("%d", &n);

		if (n <= 0 || n > 9)
			printf("[에러]1-9 사이의 값을 입력하세요.\n");
		else
			bLoop = false;
	}

	printf("---------------\n");
	printf("%d단입니다.\n", n);
	printf("---------------\n");

	for (int i=1; i<=9; i++)
	{
		printf("%d * %d = %d\n", n, i, n*i);
	}

	return 0;
}