#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <vector>
#include <random>
#include <conio.h>
#include <utility>
#include <ctime>
#include <iomanip>
#include <chrono>

auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Coord;
int Col, Row;
bool IsAte = false;

void DrawWall()
{
    std::cout << " ";
    for (int i = 0; i < Col; ++i)
    {
        std::cout << "#";
    }
    std::cout << std::endl;
    for (int j = 0; j < Row - 1; ++j)
    {
        std::cout << ".";
        for (int q = 0; q < Col; ++q)
        {
            std::cout << " ";
        }
        std::cout << "." << std::endl;
    }
    std::cout << " ";
    for (int i = 0; i < Col; ++i)
    {
        std::cout << "#";
    }
    std::cout << std::endl;
}

void HideMouse(HANDLE &Handle, CONSOLE_CURSOR_INFO &CursorInfo)
{
    GetConsoleCursorInfo(Handle, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(Handle, &CursorInfo);
}

void ShowMouse(HANDLE &Handle, CONSOLE_CURSOR_INFO &CursorInfo)
{
    GetConsoleCursorInfo(Handle, &CursorInfo);
    CursorInfo.bVisible = true;
    SetConsoleCursorInfo(Handle, &CursorInfo);
}

int Random(int Range)
{
    std::random_device RD;
    std::mt19937 Gen(RD());
    std::uniform_int_distribution<> Dis(1, Range);

    return Dis(Gen);
}

inline void GotoXY(int x, int y)
{
    Coord.X = y;
    Coord.Y = x;
    SetConsoleCursorPosition(Handle, Coord);
}

class Snake_
{
public:
    int X, Y;

    Snake_() = default;

    Snake_(int x, int y) :
        X(x), Y(y)
    {
    }
    ~Snake_() = default;

    void MoveUp()
    {
        --X;
    }

    void MoveDown()
    {
        ++X;
    }

    void MoveLeft()
    {
        --Y;
    }

    void MoveRight()
    {
        ++Y;
    }
};

template <typename T>
void DrawSnake(const T &Snake)
{
    // Print the head of snake.
    GotoXY(Snake[0].X, Snake[0].Y);
    std::cout << '@';

    //Print the body of snake.
    for (auto iter = Snake.cbegin() + 1; iter != Snake.cend(); ++iter)
    {
        GotoXY(iter->X, iter->Y);
        std::cout << 'O';
    }
}

template <typename T>
bool IsAlive(const T &Snake)
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
        {
            return false;
        }
    }

    // Still alive.
    return true;
}

template <typename T>
inline void InitSnake(T &Snake)
{
    // I assume that you can got 16 points at least.
    Snake.reserve(16);

    // Be born in the middle of the field.
    Snake.emplace_back(Row / 2, (Col / 2) + 0);
    Snake.emplace_back(Row / 2, (Col / 2) + 1);
    Snake.emplace_back(Row / 2, (Col / 2) + 2);
    Snake.emplace_back(Row / 2, (Col / 2) + 3);
    Snake.emplace_back(Row / 2, (Col / 2) + 4);
}

struct Food_
{
    int X, Y;
};

template <typename F, typename S>
void DrawFood(F &Food, const S &Snake)
{
    while (true)
    {
        bool OK = true;

        // Initialize Food(x, y).
        Food.X = Random(Row - 1);
        Food.Y = Random(Col - 1);

        // Check if (Food(x, y) == Snake(x, y)).
        for (const auto &s : Snake)
        {
            if (s.X == Food.X && s.Y == Food.Y)
            {
                OK = false;

                break;
            }
        }

        // Check passed.
        if (OK)
        {
            break;
        }
    }

    // Draw the food.
    GotoXY(Food.X, Food.Y);
    std::cout << '8';
}

template <typename F, typename S>
bool ContinueToGo(S &Snake, F &Food, unsigned Where)
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
    std::cout << 'O';

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
        std::cout << ' ';
    }

    // Draw the head of snake.
    GotoXY(Snake.front().X, Snake.front().Y);
    std::cout << '@';

    if (!IsAlive(Snake))
    {
        return false;
    }

    return true;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    SetConsoleTitle("Gluttonous Snake");

    std::vector<std::pair<std::size_t, std::time_t>> Scores;

    while (true)
    {
        std::cout << "Please input col and row: ";
        std::cin >> Col >> Row;
        std::system("cls");

        CONSOLE_CURSOR_INFO CursorInfo;
        HideMouse(Handle, CursorInfo);

        std::vector<Snake_> Snake;
        InitSnake(Snake);

        struct Food_ Food;

        DrawWall();
        DrawSnake(Snake);
        DrawFood(Food, Snake);

        int Where = 2;
        int Difficulty = 500;

        char PreHit = 0;

        while (1)
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
            {
                Difficulty = static_cast<int>(Difficulty - Snake.size() * 0.3);
            }

            GotoXY(Row + 3, 0);
            std::cout << "Score: " << Snake.size() - 5 << std::endl;
            std::cout << "Speed: " << (500 - Difficulty) << std::endl;
        }
        GotoXY(Row + 3, 0);
        std::cout << "Your final score is " << Snake.size() - 5 << std::endl;

        const auto Now = std::chrono::system_clock::now();
        const auto Now_c = std::chrono::system_clock::to_time_t(Now);
        Scores.push_back({ Snake.size() - 5, Now_c });

        ShowMouse(Handle, CursorInfo);
        std::cout << "Continue? (Y/N)" << std::endl;
        char C;
        std::cin >> C;
        if (C == 'Y')
        {
            std::system("cls");
        }
        else if (C == 'N')
        {
            std::cout << "\n\n";
            std::cout << "NO.  Score          Time" << std::endl;
            if (!Scores.empty())
            {
                int i = 0;
                for (const auto &r : Scores)
                {
                    ++i;
                    std::cout << i << ":   " << r.first << "      "
                        << std::put_time(std::localtime(&r.second), "%F %T") << std::endl;
                }
            }

            std::cout << '\n';
            std::sort(Scores.begin(), Scores.end(), [](const auto &m, const auto &n)
            {
                return m.first > n.first;
            });
            std::cout << "The highest score is: " << Scores.front().first << std::endl;

            break;
        }
        else
        {
            std::cout << "Input error." << std::endl;

            break;
        }
    }

    std::system("pause");

    return 0;
}