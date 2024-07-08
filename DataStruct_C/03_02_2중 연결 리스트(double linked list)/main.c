#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pPrev;
	struct USERDATA* pNext;
} USERDATA;

//USERDATA* g_pHeadNode = NULL;
USERDATA g_HeadNode = { 0, "__Dummy Head__" };
USERDATA g_TailNode = { 0, "__Dummy Tail__" };

void InitList(void)
{
	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
}

void ReleaseList(void)
{
	USERDATA* pDelete = g_HeadNode.pNext;
	USERDATA* pNext = NULL;
	while (pDelete != &g_TailNode)
	{
		pNext = pDelete->pNext;
		printf("Delete : [%p] %d, %s, %s, [%p]\n",
			pDelete, pDelete->age, pDelete->name, pDelete->phone, pDelete->pNext);
		free(pDelete);
		pDelete = pNext;
	}
	InitList();
}

// 테일 노드에 새노드 추가(큐 구조)
void AddNewNode(const int age, const char* pszName, const char* pszPhone)
{
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	pNewNode->age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pszName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);
	pNewNode->pPrev = NULL;
	pNewNode->pNext = NULL;

	USERDATA* pLastNode = g_TailNode.pPrev;
	pNewNode->pPrev = pLastNode;
	pNewNode->pNext = &g_TailNode;
	g_TailNode.pPrev = pNewNode;
	pLastNode->pNext = pNewNode;
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
	putchar('\n');
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

// 좋은 코드는 아님("입력/리스트 검색" 을 따로 함수화 하는게 맞음)
USERDATA* SearchByName(const char* pszName)
{
	USERDATA* pTemp = g_HeadNode.pNext;
	while (pTemp != NULL)
	{
		if (strcmp(pTemp->name, pszName) == 0)
		{
			printf("\"%s\" : Found\n", pszName);
			return pTemp;
		}
		pTemp = pTemp->pNext;
	}
	printf("\"%s\" : Not Found\n", pszName);
	return NULL;
}

void RemoveNode(USERDATA* pRemove)
{
	pRemove->pPrev->pNext = pRemove->pNext;
	pRemove->pNext->pPrev = pRemove->pPrev;
	printf("RemoveNode(): %s\n", pRemove->name);
	free(pRemove);
}

void InitDummyData(void)
{
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(11, "Choi", "010-2222-2222");
	AddNewNode(12, "Jang", "010-3333-3333");
}

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

int IsEmpty(void)
{
	if (g_HeadNode.pNext == &g_TailNode)
		return 1;

	return 0;
}

void Push(USERDATA* pUser)
{
	// 오버플로우를 고려 안 한 코드!
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	memcpy(pNewNode, pUser, sizeof(USERDATA));
	pNewNode->pPrev = NULL;
	pNewNode->pNext = NULL;

	USERDATA* pNextNode = g_HeadNode.pNext;
	pNewNode->pPrev = &g_HeadNode;
	pNewNode->pNext = g_HeadNode.pNext;
	pNextNode->pPrev = pNewNode;
	g_HeadNode.pNext = pNewNode;
}

USERDATA* Pop(void)
{
	// 언더플로우를 고려 안 한 코드
	if (IsEmpty())
	{
		puts("Error: Stack underflow.");
		return NULL;
	}

	USERDATA* pPop = g_HeadNode.pNext;
	g_HeadNode.pNext = pPop->pNext;
	pPop->pNext->pPrev = &g_HeadNode;
	return pPop;
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

void Enqueue(USERDATA* pUser)
{
	// 큐는 테일로 들어감(즉, Enqueue의 경우 기존에 구현한 AddNewNode와 같음)
	AddNewNode(pUser->age, pUser->name, pUser->phone);
}

USERDATA* Dequeue(void)
{
	// 큐는 헤드에서 나감(즉, Dequeue의 경우 기존에 구현한 Pop과 같음)
	return Pop();
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

int main(void)
{
	InitList();
	TestQueue();
	ReleaseList();
	return 0;
}