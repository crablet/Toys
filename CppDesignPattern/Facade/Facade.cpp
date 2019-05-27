#include <iostream>

class Go
{
public:
	void Up1()
	{
		std::cout << "Up1" << std::endl;
	}

	void Up2()
	{
		std::cout << "Up2" << std::endl;
	}

	void Up3()
	{
		std::cout << "Up3" << std::endl;
	}

	void Down1()
	{
		std::cout << "Down1" << std::endl;
	}

	void Down2()
	{
		std::cout << "Down2" << std::endl;
	}

	void Down3()
	{
		std::cout << "Down3" << std::endl;
	}
};

class GoFacede
{
private:
	Go TrueGo;

public:
	GoFacede() = default;
	GoFacede(const Go& rhs)
		: TrueGo(rhs)
	{
	}

	void Up()
	{
		TrueGo.Up1();
		TrueGo.Up2();
		TrueGo.Up3();
	}

	void Down()
	{
		TrueGo.Down1();
		TrueGo.Down2();
		TrueGo.Down3();
	}
};

int main()
{
	Go TrueGo;
	GoFacede FakeGo(TrueGo);
	FakeGo.Up();
	FakeGo.Down();

	return 0;
}