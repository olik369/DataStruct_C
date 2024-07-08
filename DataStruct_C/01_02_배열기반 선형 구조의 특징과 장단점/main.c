#include <stdio.h>

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pNext;
} USERDATA;

int main(void)
{
	USERDATA aList[4] =
	{
		{20, "Tester01", "010-1234-1111", NULL},
		{21, "Tester02", "010-1234-2222", NULL},
		{22, "Tester03", "010-1234-3333", NULL},
		{23, "Tester04", "010-1234-4444", NULL}
	};

	aList[0].pNext = &aList[1];
	aList[1].pNext = &aList[2];
	aList[2].pNext = &aList[3];
	aList[3].pNext = NULL;

	return 0;
}

/*
* 배열기반 선형 자료구조의 특징과 장/단점
* 
* - 장점
* 1. 가장 단순한 메모리 구조를 가지며 구현 및 대상 자료에 대한 접근이 용이
* 2. 짧고 간결한 코드 구성으로 쉬운 이해에 도움을 줌
* 
* - 단점
* 1. 컴파일 타임에 관리 가능한 자료개수를 코드로 기술해야 하며 변동에 대응하기가 어려움
*/