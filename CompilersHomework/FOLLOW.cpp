#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <cctype>

int main()
{
    int n;
    std::cin >> n;
    std::unordered_map<char, std::vector<std::string>> Grammar;
    std::unordered_map<char, std::unordered_set<char>> FOLLOW;
    char S;
    for (int i = 0; i < n; ++i)
    {
        std::string Str;
        std::cin >> Str;
        if (i == 0)
        {
            S = Str.front();
        }
        auto Temp = Str.substr(3, Str.size());
        std::reverse(Temp.begin(), Temp.end());
        Grammar[Str[0]].push_back(Temp);
        FOLLOW[Str[0]] = {};
    }

    while (true)
    {
        bool Changed = false;
        for (const auto &r : Grammar)
        {
            auto Now = r.first;
            auto BeforeSize = FOLLOW[Now].size();
            for (const auto &X : r.second)
            {
                if (std::isupper(X.front()))
                {
                    for (const auto &t : FOLLOW[X.front()])
                    {
                        FOLLOW[Now].insert(t);
                    }
                    if (FOLLOW[X.front()].count('~') && X.size() > 1)
                    {
                        std::size_t i;
                        for (i = 1; i < X.size(); ++i)
                        {
                            if (FOLLOW[X[i]].count('~'))
                            {
                                for (const auto &t : FOLLOW[X[i]])
                                {
                                    FOLLOW[Now].insert(t);
                                }
                            }
                            else
                            {
                                for (const auto &t : FOLLOW[X[i]])
                                {
                                    FOLLOW[Now].insert(t);
                                }

                                break;
                            }
                        }
                        if (i != X.size())
                        {
                            FOLLOW[Now].erase('~');
                        }
                    }
                }
                else if (X.front() == '~')
                {
                    FOLLOW[Now].insert('~');
                    if (X.size() > 1)
                    {
                        for (const auto &t : FOLLOW[X[1]])
                        {
                            FOLLOW[Now].insert(t);
                        }
                        if (X.size() > 2 && FOLLOW[X[1]].count('~'))
                        {
                            for (std::size_t i = 1; i < X.size(); ++i)
                            {
                                if (FOLLOW[X[i]].count('~'))
                                {
                                    for (const auto &t : FOLLOW[X[i]])
                                    {
                                        FOLLOW[Now].insert(t);
                                    }
                                }
                                else
                                {
                                    for (const auto &t : FOLLOW[X[i]])
                                    {
                                        FOLLOW[Now].insert(t);
                                    }

                                    break;
                                }
                            }
                        }
                    }
                }
                else if (std::islower(X.front()) || X.front() == '(' || X.front() == ')')
                {
                    FOLLOW[Now].insert(X.front());
                }
            }

            Changed |= BeforeSize != FOLLOW[Now].size();
        }

        if (!Changed)
        {
            break;
        }
    }
    FOLLOW[S].insert('~');

    for (const auto &rr : FOLLOW)
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