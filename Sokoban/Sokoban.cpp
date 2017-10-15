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

//ǽ1  �յ�0  ����2 ��3 Ŀ�ĵ�4 ������Ŀ�ĵ���6 ��+Ŀ�ĵ�=��7
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
        if (Map[X][Y - 1] == 0 || Map[X][Y - 1] == 4) // ǰ���ǿյ�
        {
            // �޸ĵ�ͼ���˺Ϳյص�����
            Map[X][Y] = 0;
            Map[X][Y - 1] = 3;
            
            // �޸������ڴ��е�����
            this->MoveLeft();
        }
        else if (Map[X][Y - 1] == 2 && Map[X][Y - 2] == 0) // ǰ�������ӵ������ƶ�
        {
            // �޸ĵ�ͼ���ˡ����ӺͿյص�����
            Map[X][Y] = 0;
            Map[X][Y - 1] = 3;
            Map[X][Y - 2] = 2;

            // �޸������ڴ��е�����
            this->MoveLeft();
        }
    }
        break;

    case 1: // Right
    {
        if (Map[X][Y + 1] == 0 || Map[X][Y + 1] == 4) // ǰ���ǿյ�
        {
            // �޸ĵ�ͼ���˺Ϳյص�����
            Map[X][Y] = 0;
            Map[X][Y + 1] = 3;

            // �޸������ڴ��е�����
            this->MoveRight();
        }
        else if (Map[X][Y + 1] == 2 && Map[X][Y + 2] == 0) // ǰ�������ӵ������ƶ�
        {
            // �޸ĵ�ͼ���ˡ����ӺͿյص�����
            Map[X][Y] = 0;
            Map[X][Y + 1] = 3;
            Map[X][Y + 2] = 2;

            // �޸������ڴ��е�����
            this->MoveRight();
        }
    }
        break;

    case 2: // Up
    {
        if (Map[X - 1][Y] == 0 || Map[X - 1][Y] == 4) // ǰ���ǿյ�
        {
            // �޸ĵ�ͼ���˺Ϳյص�����
            Map[X][Y] = 0;
            Map[X - 1][Y] = 3;

            // �޸������ڴ��е�����
            this->MoveUp();
        }
        else if (Map[X - 1][Y] == 2 && Map[X - 2][Y] == 0) // ǰ�������ӵ������ƶ�
        {
            // �޸ĵ�ͼ���ˡ����ӺͿյص�����
            Map[X][Y] = 0;
            Map[X - 1][Y] = 3;
            Map[X - 2][Y] = 2;

            // �޸������ڴ��е�����
            this->MoveUp();
        }
    }
        break;

    case 3: // Down
    {
        if (Map[X + 1][Y] == 0 || Map[X + 1][Y] == 4) // ǰ���ǿյ�
        {
            // �޸ĵ�ͼ���˺Ϳյص�����
            Map[X][Y] = 0;
            Map[X + 1][Y] = 3;

            // �޸������ڴ��е�����
            this->MoveDown();
        }
        else if (Map[X + 1][Y] == 2 && Map[X + 2][Y] == 0) // ǰ�������ӵ������ƶ�
        {
            // �޸ĵ�ͼ���ˡ����ӺͿյص�����
            Map[X][Y] = 0;
            Map[X + 1][Y] = 3;
            Map[X + 2][Y] = 2;

            // �޸������ڴ��е�����
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
            case 0: cout << "  "; break;  //�յ�           0
            case 1: cout << "��"; break;   //ǽ             1
            case 2: cout << "��"; break;   //����           2
            case 3: cout << "��"; break;   //��             3
            case 4: cout << "��"; break;  //Ŀ�ĵ�         4
            case 6: cout << "��"; break;   //������Ŀ�ĵ��� 6
            case 7: cout << "��"; break;   //��+Ŀ�ĵ�=��   7
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
