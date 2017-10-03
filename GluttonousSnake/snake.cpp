﻿#include <iostream>
#include <Windows.h>
#include <vector>
#include <random>
#include <conio.h>

auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Coord;
unsigned Col, Row;

using namespace std;

void DrawWall()
{
    cout << " ";
    for (unsigned i = 0; i < Col; ++i)
        cout << "#";
    cout << endl;
    for (unsigned j = 0; j < Row - 1; ++j)
    {
        cout << "|";
        for (unsigned q = 0; q < Col; ++q)
            cout << " ";
        cout << "|" << endl;
    }
    cout << " ";
    for (unsigned i = 0; i < Col; ++i)
        cout << "#";
    cout << endl;
}

inline void HideMouse(HANDLE &Handle, CONSOLE_CURSOR_INFO &CursorInfo)
{
    GetConsoleCursorInfo(Handle, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(Handle, &CursorInfo);
}

int Random(unsigned Range)
{
    random_device RD;
    mt19937 gen(RD());
    uniform_int_distribution<> dis(1, Range);
    return dis(gen);
}

inline void GotoXY(int x, int y)
{
    Coord.X = y;
    Coord.Y = x;
    SetConsoleCursorPosition(Handle, Coord);
}

class _Snake
{
public:
    unsigned X, Y;

    _Snake() = default;

    _Snake(unsigned x, unsigned y) :
        X(x), Y(y)
    {
    }
    ~_Snake() = default;

    inline void MoveUp()
    {
        --X;
    }
    inline void MoveDown()
    {
        ++X;
    }
    inline void MoveLeft()
    {
        --Y;
    }
    inline void MoveRight()
    {
        ++Y;
    }
};

void DrawSnake(const vector<_Snake> &Snake)
{
    GotoXY(Snake[0].X, Snake[0].Y);
    putchar('@');
    for (auto iter = Snake.cbegin() + 1; iter != Snake.cend(); ++iter)
    {
        GotoXY(iter->X, iter->Y);
        putchar('O');
    }
}

bool IsAlive(const vector<_Snake> &Snake)
{
    if (Snake.front().X == 0 || Snake.front().Y == 0
        || Snake.front().X == Row || Snake.front().Y == Col + 1)
    {
        return false;
    }

    for (auto iter = Snake.cbegin() + 1; iter != Snake.cend(); ++iter)
    {
        if (Snake.front().X == iter->X && Snake.front().Y == iter->Y)
            return false;
    }

    return true;
}

struct _Food
{
    unsigned X, Y;
};

void DrawFood(struct _Food &Food, const vector<_Snake> &Snake)
{
    while (true)
    {
        bool Flag = true;
        Food.X = Random(Row - 1);
        Food.Y = Random(Col - 1);
        for (const auto &S : Snake)
        {
            if (S.X == Food.X && S.Y == Food.Y)
            {
                Flag = false;
                break;
            }
        }
        if (Flag)
            break;
    }
    GotoXY(Food.X, Food.Y);
    putchar('8');
}

bool ContinueToGo(vector<_Snake> &Snake, struct _Food &Food, unsigned Where)
{
    const auto PreTail = Snake.back();
    bool IsAte = false;

    for (auto i = Snake.size() - 1; i >= 1; --i)
    {
        Snake[i] = Snake[i - 1];
    }

    switch (Where)
    {
    case 0:
        Snake.front().MoveUp();
        break;
    case 1:
        Snake.front().MoveDown();
        break;
    case 2:
        Snake.front().MoveLeft();
        break;
    case 3:
        Snake.front().MoveRight();
        break;
    default:
        break;
    }

    GotoXY(Snake[1].X, Snake[1].Y);
    putchar('O');

    if (Snake.front().X == Food.X && Snake.front().Y == Food.Y)
    {
        Snake.push_back(PreTail);
        IsAte = true;
    }

    if (IsAte)
    {
        DrawFood(Food, Snake);
    }
    else
    {
        GotoXY(PreTail.X, PreTail.Y);
        putchar(' ');
    }

    GotoXY(Snake.front().X, Snake.front().Y);
    putchar('@');

    if (!IsAlive(Snake))
    {
        system("cls");
        return false;
    }

    return true;
}

int main()
{
    SetConsoleTitle("贪吃蛇");

    cin >> Col >> Row;
    system("cls");

    CONSOLE_CURSOR_INFO CursorInfo;
    HideMouse(Handle, CursorInfo);

    vector<_Snake> Snake;
    Snake.reserve(16);
    Snake.emplace_back(Col / 2, (Row / 2) + 0);
    Snake.emplace_back(Col / 2, (Row / 2) + 1);
    Snake.emplace_back(Col / 2, (Row / 2) + 2);
    Snake.emplace_back(Col / 2, (Row / 2) + 3);
    Snake.emplace_back(Col / 2, (Row / 2) + 4);

    struct _Food Food;

    DrawWall();
    DrawSnake(Snake);
    DrawFood(Food, Snake);

    unsigned Where = 2;
    unsigned Difficulty = 500;

    while (1)
    {
        Sleep(Difficulty);

        char PreHit = 0;

        if (_kbhit())
        {
            char NowHit = _getch();

            if (NowHit == -32)
            {
                NowHit = _getch();
                switch (NowHit)
                {
                case 72:
                    if (Where == 2 || Where == 3)
                        Where = 0;
                    break;
                case 80:
                    if (Where == 2 || Where == 3)
                        Where = 1;
                    break;
                case 75:
                    if (Where == 0 || Where == 1)
                        Where = 2;
                    break;
                case 77:
                    if (Where == 0 || Where == 1)
                        Where = 3;
                    break;
                default:
                    break;
                }

                if (PreHit == NowHit)
                    Difficulty = Difficulty < 50 ? Difficulty : (Difficulty - 50);

                PreHit = NowHit;
            }
        }

        if (!ContinueToGo(Snake, Food, Where))
            break;

        GotoXY(Row + 3, 0);
        cout << "Score: " << Snake.size() - 5;
    }

    cout << "Your final score: " << Snake.size() - 5 << endl;
    system("pause");

    return 0;
}