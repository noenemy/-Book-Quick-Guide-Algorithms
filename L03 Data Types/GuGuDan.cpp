#include <stdio.h>

/*
 * ���� ���α׷� �����
 */ 
int main()
{
	int n = 0;
	bool bLoop = true;	

	while (bLoop == true)
	{
		printf("�� ���� ����ұ��(1-9) :");
		scanf("%d", &n);

		if (n <= 0 || n > 9)
			printf("[����]1-9 ������ ���� �Է��ϼ���.\n");
		else
			bLoop = false;
	}

	printf("---------------\n");
	printf("%d���Դϴ�.\n", n);
	printf("---------------\n");

	for (int i=1; i<=9; i++)
	{
		printf("%d * %d = %d\n", n, i, n*i);
	}

	return 0;
}