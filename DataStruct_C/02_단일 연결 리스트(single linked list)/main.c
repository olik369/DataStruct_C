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
}

// 헤드 노드에 새노드 추가
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
	AddNewNodeToHead(10, "Hoon", "010-1111-1111");
	AddNewNodeToHead(11, "Choi", "010-2222-2222");
	AddNewNodeToHead(12, "Jang", "010-3333-3333");
}

int main(void)
{
	//Input
	InitDummyData();

	//Print List
	PrintList();

	ReleaseList();
	return 0;
}