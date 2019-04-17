// Abstract Factory
#include <iostream>
#include <memory>

class IProduct
{
public:
	virtual void Do() = 0;
};

class IProductA : public IProduct
{
public:
	virtual void Do() = 0;
};

class ProductA1 : public IProductA
{
public:
	virtual void Do() override
	{
		std::cout << "ProductA1" << std::endl;
	}
};

class ProductA2 : public IProductA
{
public:
	virtual void Do() override
	{
		std::cout << "ProductA2" << std::endl;
	}
};

class IProductB : public IProduct
{
public:
	virtual void Do() = 0;
};

class ProductB1 : public IProductB
{
public:
	virtual void Do() override
	{
		std::cout << "ProductB1" << std::endl;
	}
};

class ProductB2 : public IProductB
{
public:
	virtual void Do() override
	{
		std::cout << "ProductB2" << std::endl;
	}
};

class IFactory
{
public:
	virtual std::shared_ptr<IProduct> Create(int) = 0;
};

class FactoryA : public IFactory
{
public:
	std::shared_ptr<IProduct> Create(int Type) override
	{
		if (Type == 0)
		{
			return std::make_shared<ProductA1>();
		}
		else if (Type == 1)
		{
			return std::make_shared<ProductA2>();
		}
		else
		{
			return nullptr;
		}
	}
};

class FactoryB : public IFactory
{
public:
	std::shared_ptr<IProduct> Create(int Type) override
	{
		if (Type == 0)
		{
			return std::make_shared<ProductB1>();
		}
		else if (Type == 1)
		{
			return std::make_shared<ProductB2>();
		}
		else
		{
			return nullptr;
		}
	}
};

class Factory
{
public:
	static std::shared_ptr<IFactory> CreateFactory(int Type)
	{
		if (Type == 0)
		{
			return std::make_shared<FactoryA>();
		}
		else if (Type == 1)
		{
			return std::make_shared<FactoryB>();
		}
		else
		{
			return nullptr;
		}
	}
};

int main()
{
	Factory::CreateFactory(0)->Create(0)->Do();
	Factory::CreateFactory(0)->Create(1)->Do();
	Factory::CreateFactory(1)->Create(0)->Do();
	Factory::CreateFactory(1)->Create(1)->Do();

	return 0;
}