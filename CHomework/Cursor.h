#ifndef CURSOR_H
#define CURSOR_H

#include <Windows.h>
#include <stdbool.h>
#include <conio.h>

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

inline unsigned GetDirection()
{
    if (GetKeyState(VK_LEFT) & 0b1000000000000000)
        return 0;
    else if (GetKeyState(VK_RIGHT) & 0b1000000000000000)
        return 1;
    else if (GetKeyState(VK_UP) & 0b1000000000000000)
        return 2;
    else if (GetKeyState(VK_DOWN) & 0b1000000000000000)
        return 3;
    else if (GetKeyState(VK_RETURN) & 0b1000000000000000)
        return 4;
    else
        return 5;
}

#endif // !CURSOR_H

