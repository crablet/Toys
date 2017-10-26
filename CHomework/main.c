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

int main(void)
{
    SetConsoleTitle("Items Management System");
    CONSOLE_CURSOR_INFO CursorInfo = { 1, 0 };
    HideTheCursor(GetStdHandle(STD_OUTPUT_HANDLE), CursorInfo);
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

    int Control = 0;
    while (1)
    {
        if (_kbhit())
        {
            char Hit = _getch();

            // If Up.
            if (Hit == 72)
                --Control;

            // If Down.
            else if (Hit == 80)
                ++Control;

            switch (Control % 4)
            {
            case 0:
                system("cls");
                system("mode con cols=45 lines=25");
                printf("\n\n\n\n\n\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("              --查询商品--\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
                printf("              --修改商品信息--\n\n");
                printf("              --删除商品--\n\n");
                printf("              --保存并退出--\n\n");
                break;
            case 1:
                system("cls");
                system("mode con cols=45 lines=25");
                printf("\n\n\n\n\n\n\n");
                printf("              --查询商品--\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("              --修改商品信息--\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
                printf("              --删除商品--\n\n");
                printf("              --保存并退出--\n\n");
                break;
            case 2:
                system("cls");
                system("mode con cols=45 lines=25");
                printf("\n\n\n\n\n\n\n");
                printf("              --查询商品--\n\n");
                printf("              --修改商品信息--\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("              --删除商品--\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
                printf("              --保存并退出--\n\n");
                break;
            case 3:
                system("cls");
                system("mode con cols=45 lines=25");
                printf("\n\n\n\n\n\n\n");
                printf("              --查询商品--\n\n");
                printf("              --修改商品信息--\n\n");
                printf("              --删除商品--\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("              --保存并退出--\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
                break;
            }

            // If Enter buttom is pressed.
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
                }
                break;

                case 1:
                {
                    system("cls");
                    printf("你想修改哪个商品的信息？\n");
                    char str[50];
                    scanf("%s", str);
                    InfoChange(Items, str);
                }
                break;

                case 2:
                {
                    system("cls");
                    printf("你想删除哪个商品？\n");
                    char str[50];
                    scanf("%s", str);
                    InfoDelete(Items, str);
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
        if (Control > 32766 || Control < -32766)
            Control %= 4;
    }

    //Item *Items[CAPACITY] = { NULL };

    //InfoInit(Items);
    //InfoInsert(Items, "qqqqqqqqqq", 700);
    //InfoDelete(Items, "bbbbbbbbbbbbbbb");
    //InfoChange(Items, "qqqqqqqqqq");
    //OutputAll(Items);
    //InfoFlush(Items);
    //ShowTheCursor(GetStdHandle(STD_OUTPUT_HANDLE), CursorInfo);
    return 0;
}