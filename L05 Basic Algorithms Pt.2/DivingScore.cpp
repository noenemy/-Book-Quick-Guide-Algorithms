#include <stdio.h>

/*
 * ���� ���α׷� �����
 */ 
int main()
{
	int n = 0;
	int nMax = 0, nMin = 10;
	int nScore = 0, nSum = 0;
	float fAvg = 0;

	printf("������ ���� �Է��ϼ��� : ");
	scanf("%d", &n);

	for (int i=1; i<=n; i++)
	{
		printf("%d��° ������ ����(0-10) : ", i);
		scanf("%d", &nScore);

		if (nScore > nMax)
			nMax = nScore;

		if (nScore < nMin)
			nMin = nScore;

		nSum = nSum + nScore;
	}

	nSum = nSum - nMax - nMin;
	fAvg = (float)nSum / (n-2);

	printf("-------------------\n");
	printf("�ְ����� : %d\n", nMax);
	printf("�������� : %d\n", nMin);
	printf("������� : %3.2f\n", fAvg);

	return 0;
}