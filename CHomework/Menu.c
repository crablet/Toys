#pragma warning(disable : 4996)

#include "Menu.h"

extern int Control = 0;
extern char Hit = -1;

void ShowMenu()
{
    //if (_kbhit())
    //{
        Hit = _getch();

        // If Up.
        if (Hit == 72)
            --Control;

        // If Down.
        else if (Hit == 80)
            ++Control;

        if (Control > 32766 || Control < -32766)
            Control %= 4;

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
    //}
}
