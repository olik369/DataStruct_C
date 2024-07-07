#include <stdio.h>

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pNext;
} USERDATA;

void PrintUserData(USERDATA* const pUserData)
{
	USERDATA* pUser = pUserData;
	while (pUser != NULL)
	{
		printf("[%p] %d, %s, %s, [next: %p]\n",
			pUser,
			pUser->age, pUser->name, pUser->phone,
			pUser->pNext
			);

		pUser = pUser->pNext;
	}
}

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

	PrintUserData(aList);
	return 0;
}

/*
* 자료구조에 대한 가시성 확보
* 
* 자료구조는 이론으로 이해하는 것이며 눈으로 확인하기 어려움
* -> 논리적 오류를 인지하기 어려움
* -> 디버깅이 어려움
* 전체구조를 알 수 있는 출력 코드를 먼저 개발하는 것이 매우 유리
*/