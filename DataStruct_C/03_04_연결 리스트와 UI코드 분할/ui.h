#pragma once

typedef enum MY_MENU
{
	EXIT,
	NEW,
	SEARCH,
	PRINT,
	REMOVE,
} MY_MENU;

MY_MENU PrintMenu(void);
void EventLoopRun(void);
void PrintList(void);
void PrintListReverse(void);
void Search(void);