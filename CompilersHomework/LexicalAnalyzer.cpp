#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <cctype>

class Lexer
{
public:
    Lexer() = default;
    Lexer(const std::string &InFileName)
        : File(InFileName, std::ios::in), FirstRun(true), NowLine(0), LastLine(0)
    {
    }

public:
    static Lexer& Instance(const std::string &InFileName)
    {
        static Lexer MyLexer(InFileName);

        return MyLexer;
    }

    void Skip();
    void AddChar();
    void GetChar();
    void GetNonBlank();
    void CheckSymbol(char Ch, char NextCh);
    void CheckKeywords(const std::string &Str);
    void Run();
    auto GetNextToken()
    {
        return NextToken;
    }

private:
    enum class Lex : int
    {
        LETTER = 0,
        DIGIT = 1,
        WHILE = 258,
        IF,
        ELSE,
        FOR,
        RET,
        INT,
        ID,
        EQU,
        GEQU,
        LEQU,
        NEQU,
        OR,
        ORASSIGN,
        AND,
        ANDASSIGN,
        MOD,
        MODASSIGN,
        DIV,
        DIVASSIGN,
        SELFADD,
        SELFSUB,
        ERROR,
        UNKONWN = 999,
    };

    char NextChar, Next2Char;
    int NextToken;
    int CharClass;
    int NowLine, LastLine;
    bool FirstRun;

    std::fstream File;
    std::string Lexeme;
    std::unordered_map<std::string, int> Keywords =
    {
        {"while", 258},
        {"if", 259},
        {"else", 260},
        {"for", 261},
        {"return", 262}
    };
    std::unordered_map<int, int> ConstantCount;

public:
    Lexer(const Lexer&) = delete;
    Lexer(Lexer&&) = delete;
    Lexer& operator=(const Lexer&) = delete;
    Lexer& operator=(Lexer&&) = delete;
};

void Lexer::Skip()
{
    while (true)
    {
        if (auto Ch = File.get(); Ch == '#')
        {
            std::string Dummy;
            std::getline(File, Dummy);

            ++NowLine;
        }
        else
        {
            File.putback(Ch);

            break;
        }
    }
}

void Lexer::AddChar()
{
    Lexeme.push_back(NextChar);
}

void Lexer::GetChar()
{
    if (FirstRun)
    {
        NextChar = File.get();
        Next2Char = File.get();

        FirstRun = false;
    }
    else
    {
        NextChar = Next2Char;
        Next2Char = File.get();
    }

    if (NextChar == EOF)
    {
        CharClass = EOF;
    }
    else if (std::isalpha(NextChar))
    {
        CharClass = static_cast<int>(Lex::LETTER);
    }
    else if (std::isdigit(NextChar))
    {
        CharClass = static_cast<int>(Lex::DIGIT);
    }
    else
    {
        CharClass = static_cast<int>(Lex::UNKONWN);
    }
}

void Lexer::GetNonBlank()
{
    while (std::isspace(NextChar))
    {
        if (NextChar == '\n')
        {
            ++NowLine;
        }

        GetChar();
    }
}

void Lexer::CheckSymbol(char Ch, char NextCh)
{
    switch (Ch)
    {
    case '(':
    case ')':
    case ';':
    case '{':
    case '}':
    case '"':
    case ',':
        AddChar();
        NextToken = Ch;

        break;

    case '+':
        AddChar();
        NextToken = Ch;

        if (NextCh == '+')
        {
            GetChar();
            AddChar();

            NextToken = static_cast<int>(Lex::SELFADD);
        }

        break;

    case '-':
        AddChar();
        NextToken = Ch;

        if (NextCh == '-')
        {
            GetChar();
            AddChar();

            NextToken = static_cast<int>(Lex::SELFSUB);
        }

        break;

    case '=':
        AddChar();
        NextToken = Ch;

        if (NextCh == '=')
        {
            GetChar();
            AddChar();

            NextToken = static_cast<int>(Lex::EQU);
        }

        break;

    case '|':
        AddChar();
        NextToken = Ch;

        if (NextCh == '|')
        {
            GetChar();
            AddChar();

            NextToken = static_cast<int>(Lex::OR);
        }
        else if (NextCh == '=')
        {
            GetChar();
            AddChar();

            NextToken = static_cast<int>(Lex::ORASSIGN);
        }

        break;

    case '\\':
        AddChar();
        NextToken = Ch;

        if (NextCh == '=')
        {
            GetChar();
            AddChar();

            NextToken = static_cast<int>(Lex::DIVASSIGN);
        }

        break;

    case '!':
        AddChar();
        NextToken = Ch;

        if (NextCh == '=')
        {
            GetChar();
            AddChar();

            NextToken = static_cast<int>(Lex::NEQU);
        }

        break;

    case '&':
        AddChar();
        NextToken = Ch;

        if (NextCh == '=')
        {
            GetChar();
            AddChar();

            NextToken = static_cast<int>(Lex::MODASSIGN);
        }
        else if (NextCh == '&')
        {
            GetChar();
            AddChar();

            NextToken = static_cast<int>(Lex::AND);
        }

        break;

    case '%':
        AddChar();
        NextToken = Ch;

        if (NextCh == '=')
        {
            GetChar();
            AddChar();

            NextToken = static_cast<int>(Lex::MODASSIGN);
        }

        break;

    case '<':
        AddChar();
        NextToken = Ch;

        if (NextCh == '=')
        {
            GetChar();
            AddChar();

            NextToken = static_cast<int>(Lex::LEQU);
        }

        break;

    case '>':
        AddChar();
        NextToken = Ch;

        if (NextCh == '=')
        {
            GetChar();
            AddChar();

            NextToken = static_cast<int>(Lex::GEQU);
        }

        break;

    case EOF:
        AddChar();
        NextToken = EOF;

        break;

    default:
        std::cout << "ERROR: unkown character '" << Ch << "'." << std::endl;
    }
}

void Lexer::CheckKeywords(const std::string &Str)
{
    if (Keywords.count(Str))
    {
        NextToken = Keywords[Str];
    }
}

void Lexer::Run()
{
    Lexeme.clear();
    GetNonBlank();

    switch (CharClass)
    {
    case (static_cast<int>(Lex::LETTER)):
        AddChar();
        GetChar();

        while (CharClass == static_cast<int>(Lex::LETTER)
            || CharClass == static_cast<int>(Lex::DIGIT))
        {
            AddChar();
            GetChar();
        }

        NextToken = static_cast<int>(Lex::ID);

        CheckKeywords(Lexeme);

        break;

    case (static_cast<int>(Lex::DIGIT)):
        AddChar();
        GetChar();

        while (CharClass == static_cast<int>(Lex::DIGIT))
        {
            AddChar();
            GetChar();
        }

        NextToken = static_cast<int>(Lex::INT);

        ++ConstantCount[std::stoi(Lexeme)];

        break;

    case (static_cast<int>(Lex::UNKONWN)):
        CheckSymbol(NextChar, Next2Char);

        GetChar();

        break;

    case EOF:
        NextToken = EOF;
        Lexeme = "EOF";

        break;

    default:
        break;
    }

    if (LastLine != NowLine)
    {
        if (LastLine)   // Skip the first line.
        {
            std::cout << std::endl; // Set a new line between each bars.
        }
        LastLine = NowLine;
    }

    std::cout << "line " << std::setfill('0') << std::setw(2) << NowLine << ": ("
              << std::setfill('0') << std::setw(3) << NextToken << ", "
              << (NextToken == static_cast<int>(Lex::INT) ? ConstantCount[std::stoi(Lexeme)] : 0) << ") "
              << Lexeme << std::endl;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    auto MyLexer = &Lexer::Instance("In.txt");
    MyLexer->Skip();
    MyLexer->GetChar();
    while (MyLexer->GetNextToken() != EOF)
    {
        MyLexer->Run();
    }

    return 0;
}