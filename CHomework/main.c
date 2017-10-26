/**************************************
*                                    *
* Platform: Windows 10               *
* IDE: Visual Studio 2017 (15.4.0)   *
* Compiler: MSVC 1911                *
* Last Modified: 2017/10/21 16:24    *
*                                    *
**************************************/

#include <stdio.h>
#include <Windows.h>
#include "Cursor.h"
#include "Items.h"
#include "Menu.h"

extern int Control;
extern char Hit;

#define DEBUG

int main(void)
{
    SetConsoleTitle("Items Management System");
    CONSOLE_CURSOR_INFO CursorInfo = { 1, 0 };
    //HideTheCursor(GetStdHandle(STD_OUTPUT_HANDLE), CursorInfo);
    system("mode con cols=45 lines=25");
    printf("\n\n\n\n\n\n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
    printf("              --查询商品--\n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
    printf("              --修改商品信息--\n\n");
    printf("              --删除商品--\n\n");
    printf("              --保存并退出--\n\n");

    Item *Items[CAPACITY] = { NULL };
    InfoInit(Items);

    while (1)
    {
        ShowMenu();

        if (Hit == 13)
        {
            switch (Control)
            {
            case 0:
            {
                system("cls");
                printf("你想查询哪个商品？\n");
                char str[50];
                scanf("%s", str);
                InfoSearch(Items, str, FIND_AND_PRINT);

#ifdef DEBUG
                printf("%s", str);
#endif

            }
            break;

            case 1:
            {
                system("cls");
                printf("你想修改哪个商品的信息？\n");
                char str[50];
                scanf("%s", str);
                InfoChange(Items, str);

#ifdef DEBUG
                printf("%s", str);
#endif

            }
            break;

            case 2:
            {
                system("cls");
                printf("你想删除哪个商品？\n");
                char str[50];
                scanf("%s", str);
                InfoDelete(Items, str);

#ifdef DEBUG
                printf("%s", str);
#endif

            }
            break;

            case 3:
                system("cls");
                printf("目前的商品如下\n");
                OutputAll(Items);
                InfoFlush(Items);

                break;

            default:
                break;
            }
        }
    }

    return 0;
}