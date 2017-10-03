#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <random>
#include <conio.h>

auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Coord;
unsigned Col, Row;
bool IsAte = false;

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
    // Print the head of snake.
    GotoXY(Snake[0].X, Snake[0].Y);
    putchar('@');

    //Print the body of snake.
    for (auto iter = Snake.cbegin() + 1; iter != Snake.cend(); ++iter)
    {
        GotoXY(iter->X, iter->Y);
        putchar('O');
    }
}

bool IsAlive(const vector<_Snake> &Snake)
{
    // The head of snake touches the wall.
    if (Snake.front().X == 0 || Snake.front().Y == 0
        || Snake.front().X == Row || Snake.front().Y == Col + 1)
    {
        return false;
    }

    // The head of snake touches itself.
    for (auto iter = Snake.cbegin() + 1; iter != Snake.cend(); ++iter)
    {
        if (Snake.front().X == iter->X && Snake.front().Y == iter->Y)
            return false;
    }

    // Still alive.
    return true;
}

inline void InitSnake(vector<_Snake> &Snake)
{
    // I assume that you can got 16 points at least.
    Snake.reserve(16);

    // Be born in the middle of the field.
    Snake.emplace_back(Col / 2, (Row / 2) + 0);
    Snake.emplace_back(Col / 2, (Row / 2) + 1);
    Snake.emplace_back(Col / 2, (Row / 2) + 2);
    Snake.emplace_back(Col / 2, (Row / 2) + 3);
    Snake.emplace_back(Col / 2, (Row / 2) + 4);
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

        // Initialize Food(x, y).
        Food.X = Random(Row - 1);
        Food.Y = Random(Col - 1);

        // Check if (Food(x, y) == Snake(x, y)).
        for (const auto &S : Snake)
        {
            if (S.X == Food.X && S.Y == Food.Y)
            {
                Flag = false;
                break;
            }
        }

        // Check passed.
        if (Flag)
            break;
    }

    // Draw the food.
    GotoXY(Food.X, Food.Y);
    putchar('8');
}

bool ContinueToGo(vector<_Snake> &Snake, struct _Food &Food, unsigned Where)
{
    // Backup for the extension of the snake.
    const auto PreTail = Snake.back();

    // Every part of the body moves to the previous one.
    for (auto i = Snake.size() - 1; i >= 1; --i)
    {
        Snake[i] = Snake[i - 1];
    }

    // The head of snake moves.
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

    // Cover the previous '@'(head of snake).
    GotoXY(Snake[1].X, Snake[1].Y);
    putchar('O');

    // If it eats.
    if (Snake.front().X == Food.X && Snake.front().Y == Food.Y)
    {
        // Head-Body-Tail => Head-Body-Tail-PreTail
        Snake.push_back(PreTail);
        IsAte = true;
    }

    if (IsAte)
    {
        DrawFood(Food, Snake);
    }
    else
    {
        // Cover the 'O'. ('O' => ' ')
        GotoXY(PreTail.X, PreTail.Y);
        putchar(' ');
    }

    // Draw the head of snake.
    GotoXY(Snake.front().X, Snake.front().Y);
    putchar('@');

    if (!IsAlive(Snake))
    {
        return false;
    }

    return true;
}

int main()
{
    SetConsoleTitle("Gluttonous Snake");

    cout << "Please input col and row: ";
    cin >> Col >> Row;
    system("cls");

    CONSOLE_CURSOR_INFO CursorInfo;
    HideMouse(Handle, CursorInfo);

    vector<_Snake> Snake;
    InitSnake(Snake);

    struct _Food Food;

    DrawWall();
    DrawSnake(Snake);
    DrawFood(Food, Snake);

    unsigned Where = 2;
    unsigned long Difficulty = 500;

    char PreHit = 0;

    while (true)
    {
        IsAte = false;

        Sleep(Difficulty);

        if (_kbhit())
        {
            char NowHit = _getch();

            if (NowHit == -32)
            {
                NowHit = _getch();
                switch (NowHit)
                {
                // Up
                case 72:
                    if (Where == 2 || Where == 3)
                        Where = 0;
                    break;

                // Down
                case 80:
                    if (Where == 2 || Where == 3)
                        Where = 1;
                    break;

                // Left
                case 75:
                    if (Where == 0 || Where == 1)
                        Where = 2;
                    break;

                // Right
                case 77:
                    if (Where == 0 || Where == 1)
                        Where = 3;
                    break;

                default:
                    break;
                }

                if (PreHit == NowHit)
                    Difficulty = Difficulty < 50 ? Difficulty : (Difficulty - 3);

                PreHit = NowHit;
            }
        }

        if (!ContinueToGo(Snake, Food, Where))
            break;

        if (IsAte)
            Difficulty = static_cast<unsigned long>(Difficulty - Snake.size() * 0.3);

        GotoXY(Row + 3, 0);
        cout << "Score: " << Snake.size() - 5 << endl;
        cout << "Speed: " << (500 - Difficulty) << endl;
    }

    GotoXY(Row + 3, 0);
    cout << "Your final score is " << Snake.size() - 5 << endl;
    system("pause");

    return 0;
}