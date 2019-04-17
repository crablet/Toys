#include <iostream>
#include <memory>

class Frult
{
public:
	virtual std::shared_ptr<Frult> Clone() = 0;
	virtual void Eat() = 0;
};

class Apple : public Frult
{
public:
	Apple() = default;
	Apple(int Type)
		: Type(Type)
	{
	}
	Apple(const Apple &rhs)
	{
		Type = rhs.Type;
	}

	virtual std::shared_ptr<Frult> Clone()
	{
		return std::make_shared<Apple>(*this);
	}

	virtual void Eat() override
	{
		std::cout << Type << std::endl;
	}

private:
	int Type;
};

int main()
{
	Apple MyApple(10);
	auto YourApple = MyApple.Clone();
	YourApple->Eat();

	auto HisApple = MyApple.Clone();
	HisApple->Eat();

	auto HerApple = MyApple.Clone();
	HerApple->Eat();

	return 0;
}