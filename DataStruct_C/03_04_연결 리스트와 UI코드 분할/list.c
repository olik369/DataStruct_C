#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "list.h"

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

// 좋은 코드는 아님("입력/리스트 검색" 을 따로 함수화 하는게 맞음)
USERDATA* SearchByName(const char* pszName)
{
	USERDATA* pTemp = g_HeadNode.pNext;
	while (pTemp != NULL)
	{
		if (strcmp(pTemp->name, pszName) == 0)
		{
			return pTemp;
		}
		pTemp = pTemp->pNext;
	}
	return NULL;
}

void RemoveNode(USERDATA* pRemove)
{
	pRemove->pPrev->pNext = pRemove->pNext;
	pRemove->pNext->pPrev = pRemove->pPrev;
	free(pRemove);
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
	if (IsEmpty())
	{
		return NULL;
	}

	USERDATA* pPop = g_HeadNode.pNext;
	g_HeadNode.pNext = pPop->pNext;
	pPop->pNext->pPrev = &g_HeadNode;
	return pPop;
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