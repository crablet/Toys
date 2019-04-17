// Simple Factory
#include <iostream>
#include <memory>

class ICat
{
public:
	virtual void Mew() = 0;
};

class ACat : public ICat
{
public:
	virtual void Mew() override
	{
		std::cout << "ACat mews" << std::endl;
	}
};

class BCat : public ICat
{
public:
	virtual void Mew() override
	{
		std::cout << "BCat mews" << std::endl;
	}
};

class CCat : public ICat
{
public:
	virtual void Mew() override
	{
		std::cout << "CCat mews" << std::endl;
	}
};

class CatsFactory
{
public:
	static std::shared_ptr<ICat> CreateCat(int Type)
	{
		switch (Type)
		{
		case 0:
			return std::make_shared<ACat>();

			break;
		case 1:
			return std::make_shared<BCat>();

			break;

		case 2:
			return std::make_shared<CCat>();

			break;

		default:
			return nullptr;
		}
	}
};

int main()
{
	auto A = CatsFactory::CreateCat(0);
	A->Mew();

	auto B = CatsFactory::CreateCat(1);
	B->Mew();

	auto C = CatsFactory::CreateCat(2);
	C->Mew();

	return 0;
}