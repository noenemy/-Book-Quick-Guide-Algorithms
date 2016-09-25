#include <stdio.h>

/*
 * 메인 프로그램 실행부
 */ 
int main()
{
	int n = 0;
	int nMax = 0, nMin = 10;
	int nScore = 0, nSum = 0;
	float fAvg = 0;

	printf("심판의 수를 입력하세요 : ");
	scanf("%d", &n);

	for (int i=1; i<=n; i++)
	{
		printf("%d번째 심판의 점수(0-10) : ", i);
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
	printf("최고점수 : %d\n", nMax);
	printf("최저점수 : %d\n", nMin);
	printf("평균점수 : %3.2f\n", fAvg);

	return 0;
}