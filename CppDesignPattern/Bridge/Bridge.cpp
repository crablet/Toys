// Bridge
#include <iostream>
#include <string>
#include <memory>

class ITheme
{
public:
	virtual std::string GetColor() const = 0;
};

class YellowTheme : public ITheme
{
public:
	virtual std::string GetColor() const override
	{
		return "Yellow";
	}
};

class OrangeTheme : public ITheme
{
public:
	virtual std::string GetColor() const override
	{
		return "Orange";
	}
};

class IPage
{
public:
	virtual void TellColor() const = 0;
};

class PageA : public IPage
{
public:
	PageA(const std::shared_ptr<ITheme> &Theme)
		: Theme(Theme)
	{
	}

	void TellColor() const override
	{
		std::cout << "PageA is " << Theme->GetColor() << std::endl;
	}

private:
	std::shared_ptr<ITheme> Theme;
};

class PageB : public IPage
{
public:
	PageB(const std::shared_ptr<ITheme> &Theme)
		: Theme(Theme)
	{
	}

	void TellColor() const override
	{
		std::cout << "PageB is " << Theme->GetColor() << std::endl;
	}

private:
	std::shared_ptr<ITheme> Theme;
};

int main()
{
	auto Yellow = std::make_shared<YellowTheme>();
	auto Orange = std::make_shared<OrangeTheme>();

	PageA(Yellow).TellColor();
	PageB(Orange).TellColor();

	return 0;
}