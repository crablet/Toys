// Singelton
#include <iostream>

class Singelton
{
public:
	static Singelton& GetInstance()
	{
		static Singelton Singel;

		return Singel;
	}

	Singelton(const Singelton&) = delete;
	Singelton(Singelton&&) = delete;
	Singelton& operator=(const Singelton&) = delete;
	Singelton& operator=(Singelton&&) = delete;

private:
	Singelton() = default;
};

int main()
{
	auto &Instance1 = Singelton::GetInstance();
	auto &Instance2 = Singelton::GetInstance();
	if (&Instance1 == &Instance2)
	{
		std::cout << "OK the same instance" << std::endl;
	}
	else
	{
		std::cout << "NO not the same instance" << std::endl;
	}

	return 0;
}