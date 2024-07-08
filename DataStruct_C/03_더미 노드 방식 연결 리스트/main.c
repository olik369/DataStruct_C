#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pNext;
} USERDATA;

//USERDATA* g_pHeadNode = NULL;
USERDATA g_HeadNode = { 0, "__Dummy Node__", "", NULL};

void PrintList(void)
{
	USERDATA* pTemp = &g_HeadNode;
	while (pTemp != NULL)
	{
		printf("[%p] %d, %s, %s, [%p]\n",
			pTemp, pTemp->age, pTemp->name, pTemp->phone, pTemp->pNext);
		pTemp = pTemp->pNext;
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

// 헤드 노드에 새노드 추가(스택 구조)
void AddNewNodeToHead(const int age, const char* pszName, const char* pszPhone)
{
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	//memset();
	pNewNode->age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pszName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);
	pNewNode->pNext = g_HeadNode.pNext;
	g_HeadNode.pNext = pNewNode;
}

// 테일 노드에 새노드 추가(큐 구조)
void AddNewNodeToTail(const int age, const char* pszName, const char* pszPhone)
{
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	pNewNode->age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pszName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);
	pNewNode->pNext = NULL;

	USERDATA* pTail = &g_HeadNode;
	while (pTail->pNext != NULL)
	{
		pTail = pTail->pNext;
	}
	pTail->pNext = pNewNode;
}

USERDATA* SearchToRemove(const char* pszName)
{
	USERDATA* pPrev = &g_HeadNode;
	while (pPrev->pNext != NULL)
	{
		if (strcmp(pPrev->pNext->name, pszName) == 0)
		{
			return pPrev;
		}

		pPrev = pPrev->pNext;
	}
	return NULL;
}

void RemoveNode(USERDATA* pPrev)
{
	USERDATA* pRemove = NULL;
	// 지울 노드가 헤드노드
	pRemove = pPrev->pNext;
	pPrev->pNext = pRemove->pNext;
	printf("RemoveNode(): %s\n", pRemove->name);
	free(pRemove);
}

void ReleaseList(void)
{
	USERDATA* pDelete = g_HeadNode.pNext;
	USERDATA* pNext = NULL;
	while (pDelete != NULL)
	{
		pNext = pDelete->pNext;
		printf("Delete : [%p] %d, %s, %s, [%p]\n",
			pDelete, pDelete->age, pDelete->name, pDelete->phone, pDelete->pNext);
		free(pDelete);
		pDelete = pNext;
	}
	g_HeadNode.pNext = NULL;
	printf("Head Node [%p]\n", &g_HeadNode);
}

void InitDummyData(void)
{
	//AddNewNodeToHead(10, "Hoon", "010-1111-1111");
	//AddNewNodeToHead(11, "Choi", "010-2222-2222");
	//AddNewNodeToHead(12, "Jang", "010-3333-3333");

	AddNewNodeToTail(10, "Hoon", "010-1111-1111");
	AddNewNodeToTail(11, "Choi", "010-2222-2222");
	AddNewNodeToTail(12, "Jang", "010-3333-3333");
}

void TestStep01(bool bStack)
{
	puts("TestStep01()--------------------------");
	if (bStack)
	{
		AddNewNodeToHead(11, "Choi", "010-2222-2222");
		AddNewNodeToHead(10, "Hoon", "010-1111-1111");
		AddNewNodeToHead(12, "Jang", "010-3333-3333");
	}
	else
	{
		AddNewNodeToTail(11, "Choi", "010-2222-2222");
		AddNewNodeToTail(10, "Hoon", "010-1111-1111");
		AddNewNodeToTail(12, "Jang", "010-3333-3333");
	}
	PrintList();

	USERDATA* pPrev = SearchToRemove("Choi");
	if (pPrev != NULL)
		RemoveNode(pPrev);
	PrintList();
	ReleaseList();
	putchar('\n');
}

void TestStep02(bool bStack)
{
	puts("TestStep02()--------------------------");
	if (bStack)
	{
		AddNewNodeToHead(11, "Choi", "010-2222-2222");
		AddNewNodeToHead(10, "Hoon", "010-1111-1111");
		AddNewNodeToHead(12, "Jang", "010-3333-3333");
	}
	else
	{
		AddNewNodeToTail(11, "Choi", "010-2222-2222");
		AddNewNodeToTail(10, "Hoon", "010-1111-1111");
		AddNewNodeToTail(12, "Jang", "010-3333-3333");
	}
	PrintList();

	USERDATA* pPrev = SearchToRemove("Hoon");
	if (pPrev != NULL)
		RemoveNode(pPrev);
	PrintList();
	ReleaseList();
	putchar('\n');
}

void TestStep03(bool bStack)
{
	puts("TestStep03()--------------------------");
	if (bStack)
	{
		AddNewNodeToHead(11, "Choi", "010-2222-2222");
		AddNewNodeToHead(10, "Hoon", "010-1111-1111");
		AddNewNodeToHead(12, "Jang", "010-3333-3333");
	}
	else
	{
		AddNewNodeToTail(11, "Choi", "010-2222-2222");
		AddNewNodeToTail(10, "Hoon", "010-1111-1111");
		AddNewNodeToTail(12, "Jang", "010-3333-3333");
	}
	PrintList();

	USERDATA* pPrev = SearchToRemove("Jang");
	if (pPrev != NULL)
		RemoveNode(pPrev);
	PrintList();
	ReleaseList();
	putchar('\n');
}

int main(void)
{
	bool bStack = true;
	TestStep01(bStack);
	TestStep02(bStack);
	TestStep03(bStack);
	return 0;
}