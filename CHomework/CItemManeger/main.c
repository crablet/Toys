/**************************************
*                                    *
* Platform: Windows 10               *
* IDE: Visual Studio 2017 (15.5.2)   *
* Compiler: MSVC 1911                *
* Last Modified: 2017/12/25 11:34    *
*                                    *
**************************************/

#pragma warning(disable : 4996)
#include <stdio.h>
#include <Windows.h>
#include "Cursor.h"
#include "Items.h"
#include "Menu.h"

extern int Control;
extern char Hit;

int main(void)
{
    SetConsoleTitle("��Ʒ����ϵͳ");
    CONSOLE_CURSOR_INFO CursorInfo = { 1, 0 };
    HideTheCursor(GetStdHandle(STD_OUTPUT_HANDLE), CursorInfo);
    system("mode con cols=45 lines=25");
    printf("\n\n\n\n\n\n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
    printf("              --��ѯ��Ʒ--\n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
    printf("              --�޸���Ʒ��Ϣ--\n\n");
    printf("              --ɾ����Ʒ--\n\n");
    printf("              --���沢�˳�--\n\n");

    Item *Items[CAPACITY] = { NULL };
    InfoInit(Items);

    while (1)
    {
        HideTheCursor(GetStdHandle(STD_OUTPUT_HANDLE), CursorInfo);
        if (_kbhit())
        {
            ShowMenu();

            if (Hit == 13)
            {
                switch (Control)
                {
                case 0:
                {
                    system("cls");
                    ShowTheCursor(GetStdHandle(STD_OUTPUT_HANDLE), CursorInfo);
                    printf("�����ѯ�ĸ���Ʒ��\n");
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
                    ShowTheCursor(GetStdHandle(STD_OUTPUT_HANDLE), CursorInfo);
                    printf("�����޸��ĸ���Ʒ����Ϣ��\n");
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
                    ShowTheCursor(GetStdHandle(STD_OUTPUT_HANDLE), CursorInfo);
                    printf("����ɾ���ĸ���Ʒ��\n");
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
                    ShowTheCursor(GetStdHandle(STD_OUTPUT_HANDLE), CursorInfo);
                    printf("Ŀǰ����Ʒ����\n");
                    OutputAll(Items);
                    InfoFlush(Items);

                    _getch();
                    return 0;

                default:
                    break;
                }
            }
        }    
    }

    return 0;
}