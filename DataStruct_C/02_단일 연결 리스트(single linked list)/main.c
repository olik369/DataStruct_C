#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pNext;
} USERDATA;

USERDATA* g_pHeadNode = NULL;

void PrintList(void)
{
	USERDATA* pTemp = g_pHeadNode;
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
	USERDATA* pTemp = g_pHeadNode;
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
	pNewNode->pNext = NULL;

	if (g_pHeadNode == NULL)
	{
		g_pHeadNode = pNewNode;
	}
	else
	{
		pNewNode->pNext = g_pHeadNode;
		g_pHeadNode = pNewNode;
	}
}

// 테일 노드에 새노드 추가(큐 구조)
void AddNewNodeToTail(const int age, const char* pszName, const char* pszPhone)
{
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	pNewNode->age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pszName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);
	pNewNode->pNext = NULL;

	if (g_pHeadNode == NULL)
	{
		g_pHeadNode = pNewNode;
	}
	else
	{
		USERDATA* pTail = g_pHeadNode;
		while (pTail->pNext != NULL)
		{
			pTail = pTail->pNext;
		}
		pTail->pNext = pNewNode;
	}
}

USERDATA* SearchToRemove(USERDATA** ppPrev, const char* pszName)
{
	USERDATA* pPrev = NULL;
	USERDATA* pCurrent = g_pHeadNode;
	while (pCurrent != NULL)
	{
		if (strcmp(pCurrent->name, pszName) == 0)
		{
			*ppPrev = pPrev;
			return pCurrent;
		}

		pPrev = pCurrent;
		pCurrent = pCurrent->pNext;
	}

	return NULL;
}

void RemoveNode(USERDATA* pPrev)
{
	USERDATA* pRemove = NULL;
	// 지울 노드가 헤드노드
	if (pPrev == NULL)
	{
		if (g_pHeadNode == NULL)
			return;
		else
		{
			pRemove = g_pHeadNode;
			g_pHeadNode = pRemove->pNext;
			printf("RemoveNode(): %s\n", pRemove->name);
			free(pRemove);
		}
		return;
	}

	pRemove = pPrev->pNext;
	pPrev->pNext = pRemove->pNext;
	printf("RemoveNode(): %s\n", pRemove->name);
	free(pRemove);
}

void ReleaseList(void)
{
	USERDATA* pDelete = g_pHeadNode;
	USERDATA* pNext = NULL;
	while (pDelete != NULL)
	{
		pNext = pDelete->pNext;
		printf("Delete : [%p] %d, %s, %s, [%p]\n",
			pDelete, pDelete->age, pDelete->name, pDelete->phone, pDelete->pNext);
		free(pDelete);
		pDelete = pNext;
	}
	g_pHeadNode = NULL;
	printf("Head Node [%p]\n", g_pHeadNode);
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

void TestStep01(void)
{
	puts("TestStep01()--------------------------");
	AddNewNodeToTail(11, "Choi", "010-2222-2222");
	AddNewNodeToTail(10, "Hoon", "010-1111-1111");
	AddNewNodeToTail(12, "Jang", "010-3333-3333");
	PrintList();

	USERDATA* pPrev = NULL;
	if (SearchToRemove(&pPrev, "Choi") != NULL)
		RemoveNode(pPrev);
	PrintList();
	ReleaseList();
	putchar('\n');
}

void TestStep02(void)
{
	puts("TestStep02()--------------------------");
	AddNewNodeToTail(11, "Choi", "010-2222-2222");
	AddNewNodeToTail(10, "Hoon", "010-1111-1111");
	AddNewNodeToTail(12, "Jang", "010-3333-3333");
	PrintList();

	USERDATA* pPrev = NULL;
	if (SearchToRemove(&pPrev, "Hoon") != NULL)
		RemoveNode(pPrev);
	PrintList();
	ReleaseList();
	putchar('\n');
}

void TestStep03(void)
{
	puts("TestStep03()--------------------------");
	AddNewNodeToTail(11, "Choi", "010-2222-2222");
	AddNewNodeToTail(10, "Hoon", "010-1111-1111");
	AddNewNodeToTail(12, "Jang", "010-3333-3333");
	PrintList();

	USERDATA* pPrev = NULL;
	if (SearchToRemove(&pPrev, "Jang") != NULL)
		RemoveNode(pPrev);
	PrintList();
	ReleaseList();
	putchar('\n');
}

int main(void)
{
	TestStep01();
	TestStep02();
	TestStep03();
	return 0;
}