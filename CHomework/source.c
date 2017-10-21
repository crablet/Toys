/**************************************
 *                                    *
 * Platform: Windows 10               *  
 * IDE: Visual Studio 2017 (15.4.0)   *
 * Compiler: MSVC 1911                *
 * Last Modified: 2017/10/21 10:24    *
 *                                    *
 **************************************/


#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>
#include "Items.h"

inline void HideTheCursor(HANDLE Handle, CONSOLE_CURSOR_INFO CursorInfo)
{
    GetConsoleCursorInfo(Handle, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(Handle, &CursorInfo);
}

inline void ShowTheCursor(HANDLE Handle, CONSOLE_CURSOR_INFO CursorInfo)
{
    GetConsoleCursorInfo(Handle, &CursorInfo);
    CursorInfo.bVisible = true;
    SetConsoleCursorInfo(Handle, &CursorInfo);
}

int main(void)
{
    SetConsoleTitle("Items Management System");
    CONSOLE_CURSOR_INFO CursorInfo = { 1, 0 };
    HideTheCursor(GetStdHandle(STD_OUTPUT_HANDLE), CursorInfo);

    Item *Items[CAPACITY] = { NULL };

    InfoInit(Items);
    InfoInsert(Items, "qqqqqqqqqq", 700);
    InfoDelete(Items, "bbbbbbbbbbbbbbb");
    InfoChange(Items, "qqqqqqqqqqqqq");
    OutputAll(Items);
    InfoFlush(Items);
    ShowTheCursor(GetStdHandle(STD_OUTPUT_HANDLE), CursorInfo);
    return 0;
}
