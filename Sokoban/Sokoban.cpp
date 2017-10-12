#include <iostream>
#include <array>
#include <Windows.h>
#include <conio.h>

using namespace std;

unsigned GetDirection();

//墙1  空地0  箱子2 人3 目的地4
array<array<int, 19>, 6> Map
{{
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 4, 4, 4, 0, 0, 3, 0, 0, 4, 4, 4, 0, 0, 0, 1 },
    { 1, 0, 2, 2, 2, 0, 0, 1, 1, 1, 1, 1, 0, 0, 2, 2, 2, 0, 1 },
    { 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1 },
    { 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0 }
}};

unsigned There = 100;

class Player
{
public:
    int X, Y;
    Player() = default;
    Player(int x, int y) :
           X(x), Y(y)
    {
    }
    ~Player() = default;

    void MoveUp() { --X; }
    void MoveDown() { ++X; }
    void MoveLeft() { --Y; }
    void MoveRight() { ++Y; }

    void MoveTo(unsigned There);
    bool CanMoveTo(unsigned There);

};

bool Player::CanMoveTo(unsigned There)
{
    if (There == 0 && Map[X][Y - 1] == 1)
    {
        return false;
    }
    else if (There == 1 && Map[X][Y + 1] == 1)
    {
        return false;
    }
    else if (There == 2 && Map[X - 1][Y] == 1)
    {
        return false;
    }
    else if (There == 3 && Map[X + 1][Y] == 1)
    {
        return false;
    }
    else
        return true;
}

void Player::MoveTo(unsigned There)
{
    switch (There)
    {
    case 0:
        if (Map[X][Y - 1] == 0) // 前面是空地
        {
            --Y;
        }
        else if (Map[X][Y - 1] == 2 && Map[X][Y - 2] == 0) // 前面是箱子但可以移动
        {
            Map[X][Y - 1] = 0;
            Map[X][Y - 2] = 2;
            --Y;
        }
        break;

    case 1:
        if (Map[X][Y + 1] == 0) // 前面是空地
        {
            ++Y;
        }
        else if (Map[X][Y + 1] == 2 && Map[X][Y + 2] == 0) // 前面是箱子但可以移动
        {
            Map[X][Y + 1] = 0;
            Map[X][Y + 2] = 2;
            ++Y;
        }
        break;

    case 2:
        if (Map[X - 1][Y] == 0) // 前面是空地
        {
            --X;
        }
        else if (Map[X - 1][Y] == 2 && Map[X - 2][Y] == 0) // 前面是箱子但可以移动
        {
            Map[X - 1][Y] = 0;
            Map[X - 2][Y] = 2;
            --X;
        }
        break;

    case 3:
        if (Map[X + 1][Y] == 0) // 前面是空地
        {
            ++X;
        }
        else if (Map[X + 1][Y] == 2 && Map[X + 2][Y] == 0) // 前面是箱子但可以移动
        {
            Map[X + 1][Y] = 0;
            Map[X + 2][Y] = 2;
            ++X;
        }
        break;

    default:
        break;
    }
}

void DrawMap()
{
    for (int i = 0; i < 6; ++i)
    {
        for (int p = 0; p < 16; ++p)
        {
            switch (Map[i][p])
            {
            case 0: cout << "  "; break;  //空地           0
            case 1: cout << "■"; break;   //墙             1
            case 2: cout << "□"; break;   //箱子           2
            case 3: cout << "♂"; break;   //人             3
            case 4: cout << "☆"; break;  //目的地         4
            case 6: cout << "★"; break;   //箱子在目的地中 6
            case 7: cout << "♂"; break;   //人+目的地=人   7
            }
        }
        cout << endl;
    }
}



/*
Returns: 
0: LEFT  1: RIGHT  2: UP  3: DOWN  4 :NOINPUT
*/
inline unsigned GetDirection()
{
    if (GetKeyState(VK_LEFT) < 0)
        return 0;
    else if (GetKeyState(VK_RIGHT) < 0)
        return 1;
    else if (GetKeyState(VK_UP) < 0)
        return 2;
    else if (GetKeyState(VK_DOWN) < 0)
        return 3;
    else
        return 4;
}

int main()
{
    Player MyPlayer(1, 9);
    DrawMap();
    while (1)
    {
        if (_kbhit())
        {
            system("cls");
            There = GetDirection();
            if (MyPlayer.CanMoveTo(There))
            {
                MyPlayer.MoveTo(There);
                DrawMap();
            }
        }
    }

    return 0;
}
