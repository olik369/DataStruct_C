#include <stdio.h>
#include <stdlib.h>

void AddNewData(void);

typedef enum MY_MENU
{
	EXIT,
	NEW,
	SEARCH,
	PRINT,
	REMOVE,
} MY_MENU;

MY_MENU PrintMenu(void)
{
	MY_MENU input = 0;

	system("cls"); // clear screen
	printf("[1]New\t[2]Search\t[3]Print\t[4]Remove\t[0]Exit\n");
	scanf_s("%d%*c", &input);
	return input;
}

int main(void)
{
	MY_MENU menu = 0;

	//기본적인 이벤트 루프의 형태
	while ((menu = PrintMenu()) != EXIT)
	{
		switch (menu)
		{
		case NEW:
			AddNewData();	// 특정 이벤트 - 특정 함수 1:1맵핑이 되면 이때의 함수를 이벤트 핸들러라고 함
			break;
		case SEARCH:
			break;
		case PRINT:
			break;
		case REMOVE:
			break;
		default:
			break;
		}
	}
	return 0;
}