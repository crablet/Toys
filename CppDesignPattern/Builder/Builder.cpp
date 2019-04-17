// Builder
#include <iostream>
#include <memory>

class FrultEater
{
public:
	class Builder;

	void ShowHowMuchIEat()
	{
		std::cout << Apple << ' ' << Orange << ' ' << Banana << std::endl;
	}

private:
	int Apple, Orange, Banana;
};

class FrultEater::Builder
{
public:
	Builder()
	{
		EaterPtr = std::make_shared<FrultEater>();
	}

	Builder& Apple(int i)
	{
		EaterPtr->Apple = i;

		return *this;
	}

	Builder& Banana(int i)
	{
		EaterPtr->Banana = i;

		return *this;
	}

	Builder& Orange(int i)
	{
		EaterPtr->Orange = i;

		return *this;
	}

	std::shared_ptr<FrultEater> Build()
	{
		return EaterPtr;
	}

private:
	std::shared_ptr<FrultEater> EaterPtr;
};

int main()
{
	FrultEater::Builder().Apple(10).Banana(100).Orange(1000).Build()->ShowHowMuchIEat();

	return 0;
}