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
	printf("[1]New\t[2]Search\t[3]Print\t[4]Remove\t[0]Exit\n");
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
		case PRINT:
			PrintList();
			break;
		case REMOVE:
			break;
		default:
			break;
		}
	}
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