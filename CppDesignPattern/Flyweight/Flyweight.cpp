#include <iostream>
#include <unordered_map>
#include <string>

class Fruit
{
public:
	Fruit() = default;
	Fruit(const std::string &Name)
		: Name(Name)
	{
	}

	std::string GetName() const noexcept
	{
		return Name;
	}

private:
	std::string Name;
};

class FruitProvider
{
public:
	Fruit* Make(const std::string &Name)
	{
		if (FruitBucket.find(Name) != FruitBucket.end())
		{
			return FruitBucket[Name];
		}
		else
		{
			return FruitBucket[Name] = new Fruit(Name);
		}
	}

private:
	std::unordered_map<std::string, Fruit*> FruitBucket;
};

class FruitShop
{
public:
	FruitShop() = default;
	FruitShop(const FruitProvider &Provider)
		: Provider(Provider)
	{
	}

	void TakeOrder(const std::string &Name, int Customer)
	{
		Things[Customer] = Provider.Make(Name);
	}

	void Serve() const noexcept
	{
		for (const auto &r : Things)
		{
			std::cout << r.first << ' ' << r.second->GetName() << std::endl;
		}
	}

private:
	std::unordered_map<int, Fruit*> Things;

	FruitProvider Provider;
};

int main()
{
	FruitProvider Provider;
	FruitShop Shop(Provider);
	Shop.TakeOrder("Apple", 1);
	Shop.TakeOrder("Banana", 2);
	Shop.TakeOrder("Orange", 3);
	Shop.TakeOrder("Lemon", 4);
	Shop.Serve();

	return 0;
}