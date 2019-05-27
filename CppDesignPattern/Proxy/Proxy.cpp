#include <iostream>
#include <string>

class Fruit
{
public:
	virtual void Eat() const = 0;
};

class Apple : public Fruit
{
public:
	virtual void Eat() const override
	{
		std::cout << "Eat apple." << std::endl;
	}
};

class BoomApple
{
public:
	BoomApple() = default;
	BoomApple(Fruit &SimpleApple)
		: SimpleApple{ SimpleApple }
	{
	}

	void Eat(const std::string &Password) const
	{
		if (Password == "Password")
		{
			SimpleApple.Eat();
		}
		else
		{
			std::cout << "Boom boom!" << std::endl;
		}
	}

private:
	Fruit& SimpleApple;
};

int main()
{
	Apple SimpleApple;
	BoomApple UnusualApple{ SimpleApple };
	UnusualApple.Eat("NoPassword");
	UnusualApple.Eat("Password");

	return 0;
}