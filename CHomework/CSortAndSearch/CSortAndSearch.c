#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void QuickSort(int Arr[], int l, int r)
{
    int p = l + rand() % (r - l + 1);
    int Mid = Arr[p];
    int i = l, j = r;
    do
    {
        while (Arr[i] < Mid)
        {
            ++i;
        }
        while (Arr[j] > Mid)
        {
            --j;
        }

        if (i <= j)
        {
            int t = Arr[i];
            Arr[i] = Arr[j];
            Arr[j] = t;

            ++i;
            --j;
        }
    } while (i <= j);

    if (l < j)
    {
        QuickSort(Arr, l, j);
    }
    if (i < r)
    {
        QuickSort(Arr, i, r);
    }
}

int* LowerBound(int *First, int *Last, const int Val)
{
    int Count = Last - First;

    while (Count > 0)
    {
        int *it = First;
        int Step = Count >> 1;
        it += Step;
        if (*it < Val)
        {
            First = ++it;
            Count -= Step + 1;
        }
        else
        {
            Count = Step;
        }
    }

    return First;
}

int* UpperBound(int *First, int *Last, const int Val)
{
    int Count = Last - First;

    while (Count > 0)
    {
        int *it = First;
        int Step = Count >> 1;
        it += Step;
        if (!(Val < *it))
        {
            First = ++it;
            Count -= Step + 1;
        }
        else
        {
            Count = Step;
        }
    }

    return First;
}

bool BinarySearch(int *First, int *Last, const int Val)
{
    First = LowerBound(First, Last, Val);

    return !(First == Last) && !(Val < *First);
}

int main()
{
    srand((unsigned)time(NULL));

    int Arr[100];

    printf("Please input the sequence\n");
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &Arr[i]);
    }

    QuickSort(Arr, 0, n - 1);

    printf("After sorting\n");
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", Arr[i]);
    }
    putchar('\n');

    printf("Please the number you want to find\n");
    int Val;
    scanf("%d", &Val);
    bool f = BinarySearch(Arr, Arr + n, Val);
    if (f)
    {
        int *beg = LowerBound(Arr, Arr + n, Val);
        int *end = UpperBound(Arr, Arr + n, Val);
        printf("I found there are %d.\n", end - beg);
    }
    else
    {
        printf("Sorry! Not found.\n");
    }

    return 0;
}