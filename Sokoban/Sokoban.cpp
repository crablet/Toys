#include <iostream>
#include <array>
#include <Windows.h>
#include <chrono>

using namespace std;

unsigned GetDirection();

inline void HideMouse(HANDLE &Handle, CONSOLE_CURSOR_INFO &CursorInfo)
{
    GetConsoleCursorInfo(Handle, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(Handle, &CursorInfo);
}

inline void ShowMouse(HANDLE &Handle, CONSOLE_CURSOR_INFO &CursorInfo)
{
    GetConsoleCursorInfo(Handle, &CursorInfo);
    CursorInfo.bVisible = true;
    SetConsoleCursorInfo(Handle, &CursorInfo);
}

//墙1  空地0  箱子2 人3 目的地4 箱子在目的地中6 人+目的地=人7
array<array<int, 19>, 10> Map =
{{
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
}};

unsigned There = 100;

class Player
{
public:
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
    bool CanMoveTo(unsigned There) const;
private:
    int X, Y;
};

bool Player::CanMoveTo(unsigned There) const
{
    if (There == 0 && (Map[X][Y - 1] == 1 || Map[X][Y - 1] == 4)) // Left
    {
        return false;
    }
    else if (There == 1 && (Map[X][Y + 1] == 1 || Map[X][Y + 1] == 4)) // Right
    {
        return false;
    }
    else if (There == 2 && (Map[X - 1][Y] == 1 || Map[X - 1][Y] == 4)) // Up
    {
        return false;
    }
    else if (There == 3 && (Map[X + 1][Y] == 1 || Map[X + 1][Y] == 4)) // Down
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
    case 0: // Left
    {
        if (Map[X][Y - 1] == 0 || Map[X][Y - 1] == 4) // 前面是空地
        {
            // 修改地图上人和空地的坐标
            Map[X][Y] = 0;
            Map[X][Y - 1] = 3;
            
            // 修改人在内存中的坐标
            this->MoveLeft();
        }
        else if (Map[X][Y - 1] == 2 && Map[X][Y - 2] == 0) // 前面是箱子但可以移动
        {
            // 修改地图上人、箱子和空地的坐标
            Map[X][Y] = 0;
            Map[X][Y - 1] = 3;
            Map[X][Y - 2] = 2;

            // 修改人在内存中的坐标
            this->MoveLeft();
        }
    }
        break;

    case 1: // Right
    {
        if (Map[X][Y + 1] == 0 || Map[X][Y + 1] == 4) // 前面是空地
        {
            // 修改地图上人和空地的坐标
            Map[X][Y] = 0;
            Map[X][Y + 1] = 3;

            // 修改人在内存中的坐标
            this->MoveRight();
        }
        else if (Map[X][Y + 1] == 2 && Map[X][Y + 2] == 0) // 前面是箱子但可以移动
        {
            // 修改地图上人、箱子和空地的坐标
            Map[X][Y] = 0;
            Map[X][Y + 1] = 3;
            Map[X][Y + 2] = 2;

            // 修改人在内存中的坐标
            this->MoveRight();
        }
    }
        break;

    case 2: // Up
    {
        if (Map[X - 1][Y] == 0 || Map[X - 1][Y] == 4) // 前面是空地
        {
            // 修改地图上人和空地的坐标
            Map[X][Y] = 0;
            Map[X - 1][Y] = 3;

            // 修改人在内存中的坐标
            this->MoveUp();
        }
        else if (Map[X - 1][Y] == 2 && Map[X - 2][Y] == 0) // 前面是箱子但可以移动
        {
            // 修改地图上人、箱子和空地的坐标
            Map[X][Y] = 0;
            Map[X - 1][Y] = 3;
            Map[X - 2][Y] = 2;

            // 修改人在内存中的坐标
            this->MoveUp();
        }
    }
        break;

    case 3: // Down
    {
        if (Map[X + 1][Y] == 0 || Map[X + 1][Y] == 4) // 前面是空地
        {
            // 修改地图上人和空地的坐标
            Map[X][Y] = 0;
            Map[X + 1][Y] = 3;

            // 修改人在内存中的坐标
            this->MoveDown();
        }
        else if (Map[X + 1][Y] == 2 && Map[X + 2][Y] == 0) // 前面是箱子但可以移动
        {
            // 修改地图上人、箱子和空地的坐标
            Map[X][Y] = 0;
            Map[X + 1][Y] = 3;
            Map[X + 2][Y] = 2;

            // 修改人在内存中的坐标
            this->MoveDown();
        }
    }
        break;

    default:
        break;
    }
}

void DrawMap()
{
    for (int i = 0; i < 10; ++i)
    {
        for (int p = 0; p < 19; ++p)
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
    if (GetKeyState(VK_LEFT) & 0b1000000000000000)
        return 0;
    else if (GetKeyState(VK_RIGHT) & 0b1000000000000000)
        return 1;
    else if (GetKeyState(VK_UP) & 0b1000000000000000)
        return 2;
    else if (GetKeyState(VK_DOWN) & 0b1000000000000000)
        return 3;
    else
        return 4;
}

int main()
{
    Player MyPlayer(1, 3);
    auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    HideMouse(Handle, CursorInfo);
    DrawMap();
    auto Now = std::chrono::system_clock::now();
    decltype(Now) Past = Now - 1s;

    while (1)
    {
        Now = std::chrono::system_clock::now();
        if (Now >= Past - 1s)
        {
            There = GetDirection();
            if (There != 4)
            {
                if (MyPlayer.CanMoveTo(There))
                {
                    system("cls");
                    MyPlayer.MoveTo(There);
                    DrawMap();
                }
            }
            Past = Now;
        }
    }

    return 0;
}
