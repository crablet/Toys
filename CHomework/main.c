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
    printf("              --��ѯ��Ʒ--\n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
    printf("              --�޸���Ʒ��Ϣ--\n\n");
    printf("              --ɾ����Ʒ--\n\n");
    printf("              --���沢�˳�--\n\n");

    int Control = 0;
    while (1)
    {
        if (_kbhit())
        {
            char Hit = _getch();
            if (Hit == 72)
                --Control;
            else if (Hit == 80)
                ++Control;
            switch (Control % 4)
            {
            case 0:
                system("cls");
                system("mode con cols=45 lines=25");
                printf("\n\n\n\n\n\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("              --��ѯ��Ʒ--\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
                printf("              --�޸���Ʒ��Ϣ--\n\n");
                printf("              --ɾ����Ʒ--\n\n");
                printf("              --���沢�˳�--\n\n");
                break;
            case 1:
                system("cls");
                system("mode con cols=45 lines=25");
                printf("\n\n\n\n\n\n\n");
                printf("              --��ѯ��Ʒ--\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("              --�޸���Ʒ��Ϣ--\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
                printf("              --ɾ����Ʒ--\n\n");
                printf("              --���沢�˳�--\n\n");
                break;
            case 2:
                system("cls");
                system("mode con cols=45 lines=25");
                printf("\n\n\n\n\n\n\n");
                printf("              --��ѯ��Ʒ--\n\n");
                printf("              --�޸���Ʒ��Ϣ--\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("              --ɾ����Ʒ--\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
                printf("              --���沢�˳�--\n\n");
                break;
            case 3:
                system("cls");
                system("mode con cols=45 lines=25");
                printf("\n\n\n\n\n\n\n");
                printf("              --��ѯ��Ʒ--\n\n");
                printf("              --�޸���Ʒ��Ϣ--\n\n");
                printf("              --ɾ����Ʒ--\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("              --���沢�˳�--\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
                break;
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
