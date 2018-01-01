#pragma warning(disable : 4996)

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "Items.h"
#include "Menu.h"

int Tail = 0;

void InfoInit(Item *Items[])
{
    FILE *fp = fopen("C:\\Users\\Crablet\\source\\repos\\CHomeWork\\Debug\\data", "rb");

    if (fp == NULL)
    {
        printf("Cannot open file.");
        return;
    }
    else
    {
        int Size;
        fscanf(fp, "%d", &Size);

        for (int i = 0; i < Size; ++i)
        {
            Items[i] = (Item*)malloc(sizeof(Item));
            fscanf(fp, "%s%lf", Items[i]->Name, &Items[i]->Price);
            ++Tail;
        }
    }
    fclose(fp);
}

int InfoSearch(Item *Items[], const char *str, unsigned Flag)
{
    for (int i = 0; i < Tail; ++i)
    {
        if (strcmp(Items[i]->Name, str) == 0)
        {
            if (Flag == FIND_AND_PRINT)
            {
                printf("商品""%s""的价格是：%lf。\n", Items[i]->Name, Items[i]->Price);
                return i;
            }
            else if (Flag == FIND_ONLY)
            {
                return i;
            }
            else
            {
                return -2;
            }
        }
    }

    if (Flag == FIND_AND_PRINT)
    {
        printf("对不起，找不到名为""%s""的商品。", str);
        return -1;
    }
    else if (Flag == FIND_ONLY)
    {
        return -1;
    }
    else
    {
        return -2;
    }

    _getch();
    ShowMenu();
}

void InfoInsert(Item *Items[], const char *str, double Price)
{

    for (int i = Tail + 1; i > HEAD; --i)
    {
        Items[i] = Items[i - 1];
    }

    Item *NewPtr = (Item*)malloc(sizeof(Item));
    NewPtr->Price = Price;
    strcpy(NewPtr->Name, str);
    Items[HEAD] = NewPtr;

    ++Tail;
}

inline void StrReplace(char *Destination, const char *Source)
{
    memset(Destination, 0, sizeof(Destination));
    strcpy(Destination, Source);
}

void InfoChange(Item *Items[], const char *str)
{
    int i;
    if ((i = InfoSearch(Items, str, FIND_ONLY)) == -1)
    {
        printf("对不起，找不到名为""%s""的商品。\n", str);
        printf("您想把它添加进去吗？（Y/N）\n");
        getchar();

        int Temp = getchar();
        if (Temp == 'Y')
        {
            printf("请问它的价格是：");
            double Price;
            scanf_s("%lf", &Price);

            InfoInsert(Items, str, Price);

            printf("商品%s已添加。\n", str);
        }
        else if (Temp == 'N')
        {
            printf("好的，马上返回\n");
        }
        else
        {
            printf("输入错误。\n");
        }

        return;
    }
    else
    {
        StrReplace(Items[i]->Name, str);

        printf("修改后的价格为：");
        double Price;
        scanf("%lf", &Price);
        Items[i]->Price = Price;
    }

    _getch();
    ShowMenu();
}

void InfoDelete(Item *Items[], const char *str)
{
    int i = InfoSearch(Items, str, FIND_ONLY);
    if (i == -1)
    {
        printf("对不起，找不到名为""%s""的商品。", str);
        return;
    }
    else
    {
        free(Items[i]);
        Items[i] = NULL;

        for (int p = i; p < Tail; ++p)
        {
            Items[p] = Items[p + 1];
        }

        Items[Tail] = NULL;
        --Tail;
    }

    _getch();
    ShowMenu();
}

void InfoFlush(Item *Items[])
{
    FILE *fp = fopen("C:\\Users\\Crablet\\source\\repos\\CHomework\\Debug\\data", "w+");
    if (fp == NULL)
    {
        printf("Cannot find the file.\n");
        return;
    }
    else
    {
        fprintf(fp, "%d\n", Tail);
        int i = HEAD;
        while (Items[i] != NULL)
        {
            fprintf(fp, "%s\n", Items[i]->Name);
            fprintf(fp, "%lf\n", Items[i]->Price);
            ++i;
        }
    }
    fclose(fp);
}

void OutputAll(Item *Items[])
{
    int i = HEAD;
    while (Items[i] != NULL)
    {
#ifdef DEBUG
        printf("%p\n", Items[i]);
#endif // DEBUG

        printf("商品名：%s\n", Items[i]->Name);
        printf("商品价格：%lf\n", Items[i]->Price);
        putchar('\n');
        ++i;
    }

    _getch();
    ShowMenu();
}
