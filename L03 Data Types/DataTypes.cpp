#include <stdio.h>

// 구조체 MyStruct 선언
struct MyStruct
{
    char c; // 1 byte
    short int si; // 2 bytes
    int i; // 4 bytes
};

// 공용체 MyUnion 선언
union MyUnion
{
    char c; // 1 byte
    short int si; // 2 bytes
    int i; // 4 bytes
};

/*
 * 메인 프로그램 실행부
 */ 
int main()
{
	printf("int : %d\n", sizeof(int));
	printf("long : %d\n", sizeof(long));
	printf("char : %d\n", sizeof(char));
	printf("uint : %d\n", sizeof(unsigned int));
	printf("ulong : %d\n", sizeof(unsigned long));
	printf("float : %d\n", sizeof(float));
	printf("double : %d\n", sizeof(double));
	printf("MyStruct : %d\n", sizeof(MyStruct));
	printf("MyUnion : %d\n", sizeof(MyUnion));

	return 0;
}