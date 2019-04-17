// Adapter
#include <iostream>

class Apple
{
public:
	virtual void EatApple() const
	{
		std::cout << "I eat an apple." << std::endl;
	}
};

class Banana
{
public:
	void EatBanana() const
	{
		std::cout << "I eat a banana." << std::endl;
	}
};

class BananaAdapter : public Apple
{
public:
	BananaAdapter() = default;
	BananaAdapter(const Banana &rhs)
		: FakeApple(rhs)
	{
	}

	virtual void EatApple() const override
	{
		FakeApple.EatBanana();
	}

private:
	Banana FakeApple;
};

class AppleEater
{
public:
	void EatApple(const Apple &AnApple)
	{
		AnApple.EatApple();
	}
};

int main()
{
	AppleEater().EatApple(BananaAdapter(Banana()));

	return 0;
}