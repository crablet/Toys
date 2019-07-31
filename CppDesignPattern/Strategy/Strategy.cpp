#include <iostream>
#include <memory>
#include <vector>

struct IPrintStrategy
{
	virtual void Print(const std::vector<int> &Vec) = 0;
};

struct NormalPrintStrategy : public IPrintStrategy
{
	virtual void Print(const std::vector<int> &Vec) override
	{
		for (const auto &r : Vec)
		{
			std::cout << r << ' ';
		}
		std::cout << std::endl;
	}
};

struct ReversePrintStrategy : public IPrintStrategy
{
	virtual void Print(const std::vector<int> &Vec) override
	{
		for (auto Iter = Vec.crbegin(); Iter != Vec.crend(); ++Iter)
		{
			std::cout << *Iter << ' ';
		}
		std::cout << std::endl;
	}
};

void Print(const std::vector<int> &Vec, const std::shared_ptr<IPrintStrategy> &Ptr)
{
	Ptr->Print(Vec);
}

int main()
{
	std::vector<int> Vec{ 1, 2, 3, 4, 5, 6 };
	Print(Vec, std::make_shared<NormalPrintStrategy>());
	Print(Vec, std::make_shared<ReversePrintStrategy>());

	return 0;
}