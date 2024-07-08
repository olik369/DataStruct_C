#pragma once

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pPrev;
	struct USERDATA* pNext;
} USERDATA;

USERDATA g_HeadNode;
USERDATA g_TailNode;

// Linked List
void InitList(void);
void ReleaseList(void);
void AddNewNode(const int age, const char* pszName, const char* pszPhone);
USERDATA* SearchByName(const char* pszName);
void** SearchByAgeRange(const int min, const int max, int* cnt);
void** SearchByAgeIndexRange(const int min, const int max, int* pCount);
void RemoveNode(USERDATA* pRemove);
int IsEmpty(void);
int GetListCount(void);
void NodeDataCopy(USERDATA* pDest, USERDATA* pSource);
void SwapNode(USERDATA* pLeft, USERDATA* pRight);
void SortListByName(void);
void SortListByAge(void);
void** MakeIndexAge(int* cnt);

// Stack
void Push(USERDATA* pUser);
USERDATA* Pop(void);

// Queue
void Enqueue(USERDATA* pUser);
USERDATA* Dequeue(void);