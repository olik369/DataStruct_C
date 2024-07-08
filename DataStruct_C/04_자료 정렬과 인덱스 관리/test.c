#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "ui.h"
#include "test.h"

void TestStep01()
{
	puts("TestStep01()--------------------------");
	AddNewNode(11, "Choi", "010-2222-2222");
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(12, "Jang", "010-3333-3333");
	PrintList();

	USERDATA* pRemove = SearchByName("Choi");
	if (pRemove != NULL)
		RemoveNode(pRemove);
	PrintList();

	PrintListReverse();
	ReleaseList();
	putchar('\n');
}

void TestStep02()
{
	puts("TestStep02()--------------------------");
	AddNewNode(11, "Choi", "010-2222-2222");
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(12, "Jang", "010-3333-3333");
	PrintList();

	USERDATA* pRemove = SearchByName("Hoon");
	if (pRemove != NULL)
		RemoveNode(pRemove);
	PrintList();
	ReleaseList();
	putchar('\n');
}

void TestStep03()
{
	puts("TestStep03()--------------------------");
	AddNewNode(11, "Choi", "010-2222-2222");
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(12, "Jang", "010-3333-3333");
	PrintList();

	USERDATA* pRemove = SearchByName("Jang");
	if (pRemove != NULL)
		RemoveNode(pRemove);
	PrintList();
	ReleaseList();
	putchar('\n');
}

void TestStack()
{
	USERDATA user = { 10, "Test01", "0000" };
	Push(&user);
	user.age = 11;
	strcpy_s(user.name, sizeof(user.name), "Test02");
	Push(&user);
	user.age = 12;
	strcpy_s(user.name, sizeof(user.name), "Test03");
	Push(&user);
	PrintList();

	for (int i = 0; i < 3; ++i)
	{
		USERDATA* pPop = Pop();
		printf("Pop : [%p] %2d, %s, %s, [%p]\n",
			pPop, pPop->age, pPop->name, pPop->phone, pPop->pNext);
		free(pPop);
	}
	putchar('\n');
	PrintList();
}

void TestQueue()
{
	USERDATA user = { 10, "Test01", "0000" };
	Enqueue(&user);
	user.age = 11;
	strcpy_s(user.name, sizeof(user.name), "Test02");
	Enqueue(&user);
	user.age = 12;
	strcpy_s(user.name, sizeof(user.name), "Test03");
	Enqueue(&user);
	PrintList();

	for (int i = 0; i < 3; ++i)
	{
		USERDATA* pUser = Dequeue();
		printf("Dequeue : [%p] %2d, %s, %s, [%p]\n",
			pUser, pUser->age, pUser->name, pUser->phone, pUser->pNext);
		free(pUser);
	}
	putchar('\n');
	PrintList();
}

void TestCopyAndSwap(void)
{
	InitDummyData();

	puts("============Prev Swap============");
	PrintList();

	USERDATA* pLeft = SearchByName("Hoon");
	USERDATA* pRight = SearchByName("Jang");
	if (pLeft != NULL && pRight != NULL)
	{
		SwapNode(pLeft, pRight);
	}
	puts("============After Swap============");
	PrintList();
}

void TestSortName(void)
{
	//puts("============Prev Sort============");
	//AddNewNode(10, "Hoon", "010-1111-1111");
	//PrintList();
	//SortListByName();
	//puts("============After Sort============");
	//PrintList();
	//putchar('\n');

	puts("============Prev Sort============");
	AddNewNode(12, "Jang", "010-3333-3333");
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(12, "Kim", "010-4444-4444");
	AddNewNode(11, "Choi", "010-2222-2222");
	PrintList();
	SortListByName();
	puts("============After Sort============");
	PrintList();
	putchar('\n');
}

void TestSortAge(void)
{
	InitDummyData();
	puts("============Prev Sort============");
	PrintList();
	puts("============After Sort============");
	SortListByAge();
	PrintList();
}

void InitDummyData(void)
{
	AddNewNode(7, "Park", "010-1234-3333");
	AddNewNode(5, "Kim", "010-1234-1111");
	AddNewNode(8, "Chang", "010-1234-7777");
	AddNewNode(6, "Hoon", "010-1234-2222");
	AddNewNode(8, "Jang", "010-1234-6666");
	AddNewNode(8, "Jung", "010-1234-8888");
	AddNewNode(7, "Choi", "010-1234-4444");
	AddNewNode(7, "Chae", "010-1234-5555");
}