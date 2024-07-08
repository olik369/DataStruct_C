#pragma once

typedef enum MY_MENU
{
	EXIT,
	NEW,
	SEARCH,
	SEARCH_RANGE,
	PRINT,
	REMOVE,
} MY_MENU;

MY_MENU PrintMenu(void);
void EventLoopRun(void);
void PrintList(void);
void PrintListReverse(void);
void Search(void);
void SearchByAge(void);
void SearchByAgeIndex(void);