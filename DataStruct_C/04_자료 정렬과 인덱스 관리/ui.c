#pragma once
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "list.h"
#include "ui.h"

MY_MENU PrintMenu(void)
{
	MY_MENU input = 0;

	system("cls"); // clear screen
	printf("[1]New\t[2]Search\t[3]Search age\t[4]Print\t[5]Remove\t[0]Exit\n");
	scanf_s("%d%*c", &input);
	return input;
}

void EventLoopRun(void)
{
	MY_MENU menu = 0;

	//기본적인 이벤트 루프의 형태
	while ((menu = PrintMenu()) != EXIT)
	{
		switch (menu)
		{
		case NEW:
			break;
		case SEARCH:
			Search();
			break;
		case SEARCH_RANGE:
			//SearchByAge();
			SearchByAgeIndex();
			break;
		case PRINT:
			PrintList();
			break;
		case REMOVE:
			break;
		default:
			break;
		}
	}
	puts("Bye~!");
}

void PrintList(void)
{
	USERDATA* pTemp = &g_HeadNode;
	while (pTemp != NULL)
	{
		printf("[%p] %2d, %s, %s, Prev:[%p], Next:[%p]\n",
			pTemp, pTemp->age, pTemp->name, pTemp->phone, pTemp->pPrev, pTemp->pNext);
		pTemp = pTemp->pNext;
	}
	puts("[End of list]");
	_getch();
}

void PrintListReverse(void)
{
	USERDATA* pTemp = &g_TailNode;
	while (pTemp != NULL)
	{
		printf("[%p] %d, %s, %s, [%p]\n",
			pTemp, pTemp->age, pTemp->name, pTemp->phone, pTemp->pNext);
		pTemp = pTemp->pPrev;
	}
	putchar('\n');
}

void Search(void)
{
	char szName[32] = { 0 };
	gets_s(szName, sizeof(szName));

	USERDATA* pResult = SearchByName(szName);
	if (pResult != NULL)
	{
		printf("%d, %s, %s\n", pResult->age, pResult->name, pResult->phone);
	}
	else
		puts("Not found");

	_getch();
}

void SearchByAge(void)
{
	int min = 0, max = 1, cnt = 0;
	printf("MIN MAX age: ");
	scanf_s("%d%d%*c", &min, &max);

	SortListByAge();

	void** pResult = SearchByAgeRange(min, max, &cnt);
	if (cnt == 0)
		puts("Not found");
	else
	{
		for (int i = 0; i < cnt; ++i)
		{
			USERDATA* pTemp = (USERDATA*)pResult[i];
			printf("%d, %s, %s\n", pTemp->age, pTemp->name, pTemp->phone);
		}
		printf("Count : %d", cnt);
		free(pResult);
	}
	_getch();
}

void SearchByAgeIndex(void)
{
	int min = 0, max = 1;
	int cnt = 0;
	printf("[Index search] MIN MAX age: ");
	scanf_s("%d%d%*c", &min, &max);

	USERDATA** pResult = (USERDATA**)SearchByAgeIndexRange(min, max, &cnt);
	if (cnt == 0)
	{
		puts("Not found");
	}
	else
	{
		for (int i = 0; i < cnt; ++i)
		{
			USERDATA* pTemp = pResult[i];
			printf("%d, %s, %s\n", pTemp->age, pTemp->name, pTemp->phone);
		}
		free(pResult);
	}
	_getch();
}