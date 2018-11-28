#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <cctype>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::unordered_map<char, std::vector<std::string>> Grammar;
    std::unordered_map<char, std::unordered_set<char>> FIRST;
    for (int i = 0; i < n; ++i)
    {
        std::string Str;
        std::cin >> Str;
        Grammar[Str[0]].push_back(Str.substr(3, Str.size()));
        FIRST[Str[0]] = {};
    }

    while (true)
    {
        bool Changed = false;
        for (const auto &r : Grammar)
        {
            auto Now = r.first;
            auto BeforeSize = FIRST[Now].size();
            for (const auto &X : r.second)
            {
                if (std::isupper(X.front()))
                {
                    for (const auto &t : FIRST[X.front()])
                    {
                        FIRST[Now].insert(t);
                    }
                    if (FIRST[X.front()].count('~') && X.size() > 1)
                    {
                        std::size_t i;
                        for (i = 1; i < X.size(); ++i)
                        {
                            for (const auto &t : FIRST[X[i]])
                            {
                                FIRST[Now].insert(t);
                            }
                            if (!FIRST[X[i]].count('~'))
                            {
                                break;
                            }
                        }
                        if (i != X.size())
                        {
                            FIRST[Now].erase('~');
                        }
                    }
                }
                else if (X.front() == '~')
                {
                    FIRST[Now].insert('~');
                    if (X.size() > 1)
                    {
                        for (std::size_t i = 1; i < X.size(); ++i)
                        {
                            for (const auto &t : FIRST[X[i]])
                            {
                                FIRST[Now].insert(t);
                            }
                            if (!FIRST[X[i]].count('~'))
                            {
                                break;
                            }
                        }
                    }
                }
                else if (std::islower(X.front()) || X.front() == '(' || X.front() == ')')
                {
                    FIRST[Now].insert(X.front());
                }
            }

            Changed |= BeforeSize != FIRST[Now].size();
        }

        if (!Changed)
        {
            break;
        }
    }

    for (char c = 'a'; c <= 'z'; ++c)
    {
        FIRST.erase(c);
    }

    for (const auto &rr : FIRST)
    {
        std::cout << rr.first << ":\n";
        for (const auto &r : rr.second)
        {
            std::cout << r << ' ';
        }
        std::cout << '\n' << std::endl;
    }

    return 0;
}