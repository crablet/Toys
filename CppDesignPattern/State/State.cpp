#include <iostream>
#include <execution>
#include <string>
#include <memory>
#include <algorithm>

struct IWrittingStrategy
{
	virtual void Write(std::string Str) = 0;
};

struct Uppercase : public IWrittingStrategy
{
	virtual void Write(std::string Str) override
	{
		std::transform(std::execution::par, Str.begin(), Str.end(), Str.begin(), std::toupper);
		std::cout << Str << std::endl;
	}
};

struct Lowercase : public IWrittingStrategy
{
	virtual void Write(std::string Str) override
	{
		std::transform(std::execution::par, Str.begin(), Str.end(), Str.begin(), std::tolower);
		std::cout << Str << std::endl;
	}
};

struct Normal : public IWrittingStrategy
{
	virtual void Write(std::string Str) override
	{
		std::cout << Str << std::endl;
	}
};

class TextEditor
{
public:
	TextEditor(const std::shared_ptr<IWrittingStrategy> &Ptr)
		: Ptr{ Ptr }
	{
	}

	void SetState(const std::shared_ptr<IWrittingStrategy> &rhs)
	{
		Ptr = rhs;
	}

	void Type(std::string Str)
	{
		Ptr->Write(Str);
	}

private:
	std::shared_ptr<IWrittingStrategy> Ptr;
};

int main()
{
	TextEditor Editor{ std::make_shared<Normal>() };
	Editor.Type("Hello World!");
	Editor.SetState(std::make_shared<Lowercase>());
	Editor.Type("Hello World!");
	Editor.SetState(std::make_shared<Uppercase>());
	Editor.Type("Hello World!");

	return 0;
}