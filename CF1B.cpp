#include <iostream>
#include <string>

constexpr char Base[] = "ZABCDEFGHIJKLMNOPQRSTUVWXY";

void ToExcel(const std::string &Str)
{
    int Row = 0;
    auto Beg = Str.cbegin() + 1;
    while (*Beg != 'C')
    {
        Row *= 10;
        Row += *Beg - '0';
        ++Beg;
    }

    ++Beg;
    int Col = 0;
    while (Beg != Str.cend())
    {
        Col *= 10;
        Col += *Beg - '0';
        ++Beg;
    }

    std::string StrCol;
    while (Col > 0)
    {
        StrCol.push_back(Base[Col % 26]);
        Col /= 26;
    }

    for (auto beg = StrCol.crbegin(); beg != StrCol.crend(); ++beg)
    {
        std::cout << *beg;
    }
    std::cout << Row << std::endl;
}

void ToRXCY(const std::string &Str)
{
    int Col = 0;
    auto beg = Str.cbegin();
    for ( ; !('0' <= *beg && *beg <= '9'); ++beg)
    {
        Col *= 26;
        Col += *beg - 'A' + 1;
    }

    int Row = 0;
    while (beg != Str.cend())
    {
        Row *= 10;
        Row += *beg - '0';
        ++beg;
    }

    std::cout << 'R' << Row << 'C' << Col << std::endl;
}

int main()
{
    int n;
    std::cin >> n;

    while (n--)
    {
        std::string Str;
        std::cin >> Str;
        if (Str[0] == 'R' && '0' <= Str[1] && Str[1] <= '9')
        {
            ToExcel(Str);
        }
        else
        {
            ToRXCY(Str);
        }
    }

    return 0;
}
