#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct StuInfo
{
    int StuID;
    char StuName[10];
    int Age;
} Elemtype;

typedef struct Node
{
    Elemtype Data;
    struct Node *Next;
} ListNode, *ListPtr;

ListPtr ListInit()
{
    ListPtr L = (ListPtr)malloc(sizeof(ListNode));
    L->Next = NULL;

    return L;
}

void ListDestroy(ListPtr h)
{
    ListPtr Pre = h, p = h->Next;
    while (p != NULL)
    {
        free(Pre);
        Pre = p;
        p = Pre->Next;
    }

    free(Pre);
}

void ListCheck(ListPtr L)
{
    ListPtr p = L->Next, q, Pre = L;
    while (p != NULL && p->Next != NULL)
    {
        bool Changed = false;
        if (p->Data.StuID == p->Next->Data.StuID)
        {
            if (p->Data.Age > p->Next->Data.Age)
            {
                q = p->Next;
                p->Next = q->Next;

                free(q);
            }
            else
            {
                q = p;
                Pre->Next = q->Next;
                p = p->Next;

                free(q);
            }

            Changed = true;
        }

        if (!Changed)
        {
            p = p->Next;
            Pre = Pre->Next;
        }
    }
}

void OutPut(ListPtr La)
{
    ListPtr p = La->Next;
    while (p != NULL)
    {
        printf("Name: %s\nNO: %d\nAge: %d\n\n", p->Data.StuName, p->Data.StuID, p->Data.Age);
        p = p->Next;
    }
}

void ListInsert(ListPtr L, Elemtype e)
{
    ListPtr Pre = L, p;
    while (Pre->Next != NULL && Pre->Next->Data.StuID < e.StuID)
    {
        Pre = Pre->Next;
    }

    p = (ListPtr)malloc(sizeof(ListNode));
    p->Data = e;
    p->Next = Pre->Next;
    Pre->Next = p;
}

ListPtr ListMergeNotReverse(ListPtr La, ListPtr Lb)
{
    ListPtr pa = La->Next, pb = Lb->Next, r, s;
    ListPtr Lc = (ListPtr)malloc(sizeof(ListNode));
    r = Lc;

    while (pa != NULL && pb != NULL)
    {
        if (pa->Data.StuID < pb->Data.StuID)
        {
            s = (ListPtr)malloc(sizeof(ListNode));
            s->Data = pa->Data;
            r->Next = s;
            r = s;
            pa = pa->Next;
        }
        else
        {
            s = (ListPtr)malloc(sizeof(ListNode));
            s->Data = pb->Data;
            r->Next = s;
            r = s;
            pb = pb->Next;
        }
    }

    while (pa != NULL)
    {
        s = (ListPtr)malloc(sizeof(ListNode));
        s->Data = pa->Data;
        r->Next = s;
        r = s;
        pa = pa->Next;
    }
    while (pb != NULL)
    {
        s = (ListPtr)malloc(sizeof(ListNode));
        s->Data = pb->Data;
        r->Next = s;
        r = s;
        pb = pb->Next;
    }

    r->Next = NULL;

    return Lc;
}

ListPtr ListMergeReverse(ListPtr La, ListPtr Lb)
{
    ListPtr T = ListMergeNotReverse(La, Lb)->Next;
    ListPtr s;
    ListPtr L = (ListPtr)malloc(sizeof(ListNode));
    L->Next = NULL;

    while (T != NULL)
    {
        s = (ListPtr)malloc(sizeof(ListNode));
        s->Data = T->Data;
        s->Next = L->Next;
        L->Next = s;

        T = T->Next;
    }

    return L;
}

int main(void)
{
    puts("Plaese input two groups:");

    Elemtype Temp;

    ListPtr L = ListInit();
    puts("Group1: (student numbers)");
    int T;
    scanf("%d", &T);
    while (T--)
    {
        puts("StuID:");
        int n;
        scanf("%d", &n);
        Temp.StuID = n;

        puts("StuAge:");
        scanf("%d", &n);
        Temp.Age = n;

        char s[10];
        puts("Name:");
        scanf("%s", s);
        strcpy(Temp.StuName, s);

        ListInsert(L, Temp);
    }

    puts("-----------------------------");

    ListPtr LL = ListInit();
    puts("Group2: (student numbers)");
    scanf("%d", &T);
    while (T--)
    {
        puts("StuID:");
        int n;
        scanf("%d", &n);
        Temp.StuID = n;

        puts("StuAge:");
        scanf("%d", &n);
        Temp.Age = n;

        char s[10];
        puts("Name:");
        scanf("%s", s);
        strcpy(Temp.StuName, s);

        ListInsert(L, Temp);
    }

    ListPtr M = ListMergeReverse(L, LL);

    OutPut(M);

    ListCheck(M);

    puts("-----------------------------");
    puts("Output:");
    OutPut(M);

    ListDestroy(L);
    ListDestroy(LL);
    ListDestroy(M);

    return 0;
}