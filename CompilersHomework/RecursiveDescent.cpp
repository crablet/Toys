/*
BEFORE:
Expr   -> Expr + Term | Term | Expr - Term
Term   -> Term * Factor | Factor | Term / Factor
Factor -> (Expr) | i

AFTER:
Expr   -> TermExpr_
Expr_  -> +TermExpr_ | -TermExpr_ | \epsilon
Term   -> FactorTerm_
Term_  -> *FactorTerm_ | /FactorTerm_ | \epsilon
Factor -> (Expr) | i
*/
#include <iostream>
#include <fstream>
#include <cctype>

class RecursiveDescent
{
public:
    RecursiveDescent()
        : First(true), NextToken('q'), Num(0), File("In.txt")
    {
    }

    RecursiveDescent(const RecursiveDescent&) = delete;
    RecursiveDescent(RecursiveDescent&&) = delete;
    RecursiveDescent& operator=(const RecursiveDescent&) = delete;
    RecursiveDescent& operator=(RecursiveDescent&&) = delete;

private:
    bool First;
    char NextToken;
    int Num;
    std::ifstream File;

public:
    void Error()
    {
        std::cout << "Error!" << std::endl;
    }

    void Advance()
    {
        char Now = File.get();  // int is not suitable for debug.

        if (Now == EOF) // Finished.
        {
            std::cout << "\nDone!" << std::endl;

            std::exit(0);
        }
        while (std::isspace(Now))
        {
            Now = File.get();   // Skip the white space.
        }

        if (First)  // No \n before the first line.
        {
            First = false;
        }
        else
        {
            std::cout << std::endl;
        }
        std::cout << "Processing ";

        bool IsNum = false;
        Num = std::isdigit(Now) ? 0 : -1;   // No negative numbers to be processed.
        while (std::isdigit(Now))
        {
            IsNum = true;

            Num += Now - '0';
            Num *= 10;
            Now = File.get();
        }
        if (IsNum)  // An extra char has been used. Must putback.
        {
            Num /= 10;  // An extra 10 is muled to Num.
            File.putback(Now);
            NextToken = 'p'; // Skip '(' or it will fail when processing "(Expr)".

            std::cout << Num << std::endl;
        }
        else
        {
            NextToken = Now;

            std::cout << NextToken << std::endl;
        }
    }

    void Factor()
    {
        if (NextToken == '(')
        {
            std::cout << "Using: Factor -> (Expr)" << std::endl;

            Advance();
            Expr();
            if (NextToken == ')')
            {
                std::cout << "Using: Factor -> (Expr)" << std::endl;

                Advance();
            }
            else
            {
                Error();
            }
        }
        else if (std::isalpha(NextToken))
        {
            std::cout << "Using: Factor -> i" << std::endl;

            Advance();
        }
        else if (Num >= 0)
        {
            std::cout << "Using: Factor -> i" << std::endl;

            Advance();
        }
        else
        {
            Error();
        }
    }

    void Term_()
    {
        if (NextToken == '*')
        {
            std::cout << "Using: Term_ -> *FactorTerm_" << std::endl;

            Advance();
            Factor();
            Term_();
        }
        else if (NextToken == '/')
        {
            std::cout << "Using: Term_ -> /FactorTerm_" << std::endl;

            Advance();
            Factor();
            Term_();
        }
    }

    void Term()
    {
        std::cout << "Using: Term -> FactorTerm_" << std::endl;

        Factor();
        Term_();
    }

    void Expr_()
    {
        if (NextToken == '+')
        {
            std::cout << "Using: Expr_ -> +TermExpr_" << std::endl;

            Advance();
            Term();
            Expr_();
        }
        else if (NextToken == '-')
        {
            std::cout << "Using: Expr_ -> -TermExpr_" << std::endl;

            Advance();
            Term();
            Expr_();
        }
    }

    void Expr()
    {
        std::cout << "Using: Expr -> TermExpr_" << std::endl;

        Term();
        Expr_();
    }

    static RecursiveDescent& Instance()
    {
        static RecursiveDescent MyParser;

        return MyParser;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    auto MyParser = &RecursiveDescent::Instance();
    MyParser->Advance();
    MyParser->Expr();

    return 0;
}