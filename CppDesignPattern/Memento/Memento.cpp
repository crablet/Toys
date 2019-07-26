#include <iostream>
#include <string>

class Editor
{
public:
	void Type(const std::string &Word)
	{
		Content += Word;
	}

	const std::string &GetContent() const
	{
		return Content;
	}

	std::string Save() const
	{
		return Content;
	}

	void Restore(const std::string &Memento)
	{
		Content = Memento;
	}

private:
	std::string Content;
};

int main()
{
	Editor Editor_;
	Editor_.Type("Hello ");
	std::cout << Editor_.GetContent() << std::endl;

	auto Memento = Editor_.Save();

	Editor_.Type("World!");
	std::cout << Editor_.GetContent() << std::endl;

	Editor_.Restore(Memento);
	std::cout << Editor_.GetContent() << std::endl;

	return 0;
}