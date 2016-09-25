#include <stdio.h>

// ����ü MyStruct ����
struct MyStruct
{
    char c; // 1 byte
    short int si; // 2 bytes
    int i; // 4 bytes
};

// ����ü MyUnion ����
union MyUnion
{
    char c; // 1 byte
    short int si; // 2 bytes
    int i; // 4 bytes
};

/*
 * ���� ���α׷� �����
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