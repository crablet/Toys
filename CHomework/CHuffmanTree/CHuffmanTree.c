#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define N 100

typedef struct
{
    char Data;
    int Weight;
    int Parent, LChild, RChild;
} HTNode;

typedef struct
{
    char cd[N];
    int Start;
} HCode;

void CreatHT(HTNode ht[], int n0)
{
    for (int i = 0; i < 2 * n0 - 1; ++i)
    {
        ht[i].Parent = ht[i].LChild = ht[i].RChild = -1;
    }

    for (int i = n0; i < 2 * n0 - 1; ++i)
    {
        int Min1 = 1 << 15, Min2 = 1 << 15;
        int LNode = -1, RNode = -1;
        for (int k = 0; k < i; ++k)
        {
            if (ht[k].Parent == -1)
            {
                if (ht[k].Weight < Min1)
                {
                    Min2 = Min1;
                    Min1 = ht[k].Weight;

                    RNode = LNode;
                    LNode = k;
                }
                else if (ht[k].Weight < Min2)
                {
                    Min2 = ht[k].Weight;
                    RNode = k;
                }
            }
        }

        ht[i].Weight = ht[LNode].Weight + ht[RNode].Weight;
        ht[i].LChild = LNode;
        ht[i].RChild = RNode;
        ht[LNode].Parent = ht[RNode].Parent = i;
    }
}

void CreateHCode(HTNode ht[], HCode hcd[], int n0)
{
    HCode hc;
    for (int i = 0; i < n0; ++i)
    {
        int c = i, f = ht[i].Parent;

        hc.Start = n0;
        while (f != -1)
        {
            if (ht[f].LChild == c)
            {
                hc.cd[hc.Start--] = '0';
            }
            else
            {
                hc.cd[hc.Start--] = '1';
            }

            c = f;
            f = ht[f].Parent;
        }

        ++hc.Start;
        hcd[i] = hc;
    }
}

int main()
{
    int Num[N] = { 0 };

    FILE *fp = fopen("test.txt", "r");
    if (fp)
    {
        char c;
        while (fscanf(fp, "%c", &c) != EOF)
        {
            ++Num[c - 'A'];
        }

        fclose(fp);
    }

    HTNode ht[N];
    int Tol = 0;
    for (int i = 0; i < N; ++i)
    {
        if (Num[i])
        {
            ht[Tol].Data = i + 'A';
            ht[Tol].Weight = Num[i];
            ++Tol;
        }
    }

    HCode hcd[N];
    CreatHT(ht, Tol);
    CreateHCode(ht, hcd, Tol);

    for (int i = 0; i < Tol; ++i)
    {
        for (int j = hcd[i].Start; j <= Tol; ++j)
        {
            printf("%c", hcd[i].cd[j]);
        }

        printf(" %c\n", ht[i].Data);
    }

    return 0;
}