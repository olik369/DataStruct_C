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
	USERDATA* pCmp = g_HeadNode.pNext;
	while (pCmp != NULL)
	{
		if (strcmp(pCmp->name, pszName) == 0)
		{
			return pCmp;
		}
		pCmp = pCmp->pNext;
	}
	return NULL;
}

void** SearchByAgeRange(const int min, const int max, int* pCount)
{
	// 정렬되어 있다는 가정하에 범위를 찾음
	if (IsEmpty())
		return NULL;

	USERDATA* pMin = NULL;
	USERDATA* pMax = NULL;
	USERDATA* pTemp = g_HeadNode.pNext;
	// 최초로 최소값인 지점을 찾음(단, 최대값 범위에도 만족해야함)
	while (pTemp != &g_TailNode)
	{
		if (pTemp->age >= min && pTemp->age <= max)
		{
			pMin = pTemp;
			pMax = pTemp;
			break;
		}
		pTemp = pTemp->pNext;
	}

	if (pMin != NULL)
	{
		pTemp = pMin->pNext;
	}
	else
	{
		// 다음 while문에서 터지는것 방지
		pTemp = g_HeadNode.pNext;
	}
	// 최대값을 벗어나는 순간까지 pMax 갱신
	while (pTemp != &g_TailNode)
	{
		if (pTemp->age >= min && pTemp->age <= max)
			pMax = pTemp;
		else if (pTemp->age > max)
			break;

		pTemp = pTemp->pNext;
	}

	// 범위를 찾음
	if (pMin != NULL && pMax != NULL)
	{
		pTemp = pMin;
		int cnt = 1;
		while (pTemp != pMax)
		{
			cnt++;
			pTemp = pTemp->pNext;
		}

		*pCount = cnt;
		void** pNodePtrList = malloc(sizeof(void*) * cnt);
		pTemp = pMin;
		for (int i = 0; i < cnt; ++i)
		{
			pNodePtrList[i] = pTemp;
			pTemp = pTemp->pNext;
		}
		return pNodePtrList;
	}

	return NULL;
}

void** SearchByAgeIndexRange(const int min, const int max, int* pCount)
{
	*pCount = 0;
	int cntTotal = 0;
	int idxMin = -1, idxMax = 0;
	USERDATA** aList = (USERDATA**)MakeIndexAge(&cntTotal);
	for (int i = 0; i < cntTotal; ++i)
	{
		if (aList[i]->age >= min && aList[i]->age <= max)
		{
			idxMin = i;
			idxMax = i;
			break;
		}
	}

	if (idxMin != -1)
	{
		for (int i = idxMax + 1; i < cntTotal; ++i)
		{
			if (aList[i]->age > max)
				break;
			idxMax = i;
		}

		int count = idxMax - idxMin + 1;
		void** aSelected = malloc(sizeof(void*) * count);
		memcpy(aSelected, aList + idxMin, sizeof(void*) * count);

		free(aList);
		*pCount = count;
		return aSelected;
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

int GetListCount(void)
{
	int count = 0;
	USERDATA* pTemp = g_HeadNode.pNext;
	while (pTemp != &g_TailNode)
	{
		count++;
		pTemp = pTemp->pNext;
	}
	return count;
}

void NodeDataCopy(USERDATA* pDest, USERDATA* pSource)
{
	pDest->age = pSource->age;
	strcpy_s(pDest->name, sizeof(pDest->name), pSource->name);
	strcpy_s(pDest->phone, sizeof(pDest->phone), pSource->phone);
}

void SwapNode(USERDATA* pLeft, USERDATA* pRight)
{
	USERDATA pCmp = *pLeft;
	NodeDataCopy(pLeft, pRight);
	NodeDataCopy(pRight, &pCmp);
}

// 선택 정렬 방식
void SortListByName(void)
{
	if (IsEmpty())
		return;

	USERDATA* pTemp = g_HeadNode.pNext;
	while (pTemp != &g_TailNode)
	{
		USERDATA* pSelected = pTemp;
		USERDATA* pCmp = pTemp->pNext;
		while (pCmp != &g_TailNode)
		{
			if (strcmp(pSelected->name, pCmp->name) > 0)
			{
				pSelected = pCmp;
			}
			pCmp = pCmp->pNext;
		}
		if (pTemp != pSelected)
		{
			SwapNode(pTemp, pSelected);
		}
		pTemp = pTemp->pNext;
	}
}

void SortListByAge(void)
{
	if (IsEmpty())
		return;

	USERDATA* pTemp = g_HeadNode.pNext;
	while (pTemp != &g_TailNode)
	{
		USERDATA* pSelected = pTemp;
		USERDATA* pCmp = pSelected->pNext;
		while (pCmp != &g_TailNode)
		{
			if (pSelected->age > pCmp->age)
			{
				pSelected = pCmp;
			}
			pCmp = pCmp->pNext;
		}
		if (pSelected != pTemp)
		{
			SwapNode(pTemp, pSelected);
		}
		pTemp = pTemp->pNext;
	}
}

void** MakeIndexAge(int* pCnt)
{
	*pCnt = 0;
	if (IsEmpty())
		return NULL;

	USERDATA** aList;
	aList = malloc(sizeof(USERDATA*) * GetListCount());
	memset(aList, 0, sizeof(USERDATA*) * GetListCount());
	*pCnt = GetListCount();

	USERDATA* pTemp = g_HeadNode.pNext;
	for (int i = 0; pTemp != &g_TailNode; ++i)
	{
		aList[i] = pTemp;
		pTemp = pTemp->pNext;
	}

	// 버블정렬
	for (int i = 0; i < GetListCount() - 1; ++i)
	{
		for (int j = i + 1; j < GetListCount(); ++j)
		{
			if (aList[i]->age > aList[j]->age)
			{
				USERDATA* pTemp = aList[i];
				aList[i] = aList[j];
				aList[j] = pTemp;
			}
		}
	}
	return aList;
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