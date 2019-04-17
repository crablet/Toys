// Factory Method
#include <iostream>
#include <type_traits>
#include <memory>

class IFrult
{
public:
	virtual void Eat() = 0;
};

class Apple : public IFrult
{
public:
	virtual void Eat() override
	{
		std::cout << "Eat apple." << std::endl;
	}
};

class Banana : public IFrult
{
public:
	virtual void Eat() override
	{
		std::cout << "Eat banana." << std::endl;
	}
};

class Orange : public IFrult
{
public:
	virtual void Eat() override
	{
		std::cout << "Eat orange." << std::endl;
	}
};

class Eater
{
protected:
	virtual std::shared_ptr<IFrult> MakeSomething() = 0;

public:
	void EatSomething()
	{
		MakeSomething()->Eat();
	}
};

template <class Frult>
class FrultEater : public Eater
{
protected:
	virtual std::shared_ptr<IFrult> MakeSomething() override
	{
		static_assert(std::is_base_of_v<IFrult, Frult>, "Frult shoule be based of IFrult.");

		return std::make_shared<Frult>();
	}
};

int main()
{
	FrultEater<Apple>().EatSomething();
	FrultEater<Banana>().EatSomething();
	FrultEater<Orange>().EatSomething();

	return 0;
}