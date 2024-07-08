#include "list.h"
#include "ui.h"
#include "test.h"

int main(void)
{
	InitList();

	InitDummyData();
	EventLoopRun();

	ReleaseList();
	return 0;
}