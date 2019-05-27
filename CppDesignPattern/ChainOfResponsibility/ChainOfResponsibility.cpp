#include <iostream>
#include <string>
#include <memory>

class Amount
{
public:
	Amount() = default;
	Amount(double Money)
		: Money(Money)
	{
	}

	virtual std::string GetName() const noexcept = 0;

	std::shared_ptr<Amount> SetNext(const std::shared_ptr<Amount> &Next)
	{
		return Ptr = Next;
	}

	void Pay(double Price)
	{
		if (Money >= Price)
		{
			std::cout << "Paid " << Price << " using " << GetName() << std::endl;
		}
		else if (Ptr)
		{
			std::cout << "Can't pay using " << GetName() << ", using next." << std::endl;
			Ptr->Pay(Price);
		}
		else
		{
			std::cout << "Oh too expensive!" << std::endl;
		}
	}

private:
	double Money;
	std::shared_ptr<Amount> Ptr = nullptr;
};

class Taobao : public Amount
{
public:
	Taobao() = default;
	Taobao(double Money)
		: Amount(Money)
	{
	}

	virtual std::string GetName() const noexcept override
	{
		return "Taobao";
	}
};

class Alipay : public Amount
{
public:
	Alipay() = default;
	Alipay(double Money)
		: Amount(Money)
	{
	}

	virtual std::string GetName() const noexcept override
	{
		return "Alipay";
	}
};

class Bank : public Amount
{
public:
	Bank() = default;
	Bank(double Money)
		: Amount(Money)
	{
	}

	virtual std::string GetName() const noexcept override
	{
		return "Bank";
	}
};

int main()
{
	auto _Bank = std::make_shared<Bank>(100);
	_Bank->SetNext(std::make_shared<Taobao>(200))->SetNext(std::make_shared<Alipay>(300));
	_Bank->Pay(99);
	_Bank->Pay(199);
	_Bank->Pay(299);
	_Bank->Pay(399);

	return 0;
}