#include <iostream>
#include <string>
#include <vector>

struct Fruit
{
	Fruit(const std::string &Str)
		: Name(Str)
	{
	}

	auto GetName() const
	{
		return Name;
	}

	bool operator==(const Fruit &rhs) const noexcept
	{
		return Name == rhs.GetName();
	}

private:
	std::string Name;
};

class FruitDish
{
public:
	FruitDish() = default;

	void AddFruit(const Fruit &F)
	{
		Dish.push_back(F);
	}

	void RemoveFruit(const Fruit &F)
	{
		if (auto Iter = std::find(Dish.begin(), Dish.end(), F); Iter != Dish.end())
		{
			Dish.erase(Iter);
		}
	}

	auto begin()
	{
		return Dish.begin();
	}

	auto end()
	{
		return Dish.end();
	}

private:
	std::vector<Fruit> Dish;
};

int main()
{
	FruitDish FruitDish_;
	FruitDish_.AddFruit(Fruit("Apple"));
	FruitDish_.AddFruit(Fruit("Banana"));
	FruitDish_.AddFruit(Fruit("Cat"));
	for (const auto &r : FruitDish_)
	{
		std::cout << r.GetName() << std::endl;
	}

	return 0;
}