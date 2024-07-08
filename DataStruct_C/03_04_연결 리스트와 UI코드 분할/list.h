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

void InitList(void);
void ReleaseList(void);
void AddNewNode(const int age, const char* pszName, const char* pszPhone);
USERDATA* SearchByName(const char* pszName);
void RemoveNode(USERDATA* pRemove);
int IsEmpty(void);

void Push(USERDATA* pUser);
USERDATA* Pop(void);

void Enqueue(USERDATA* pUser);
USERDATA* Dequeue(void);