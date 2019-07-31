#include <iostream>

class Doer
{
public:
	void Do()
	{
		Step1();
		Step2();
		Step3();
	}

private:
	virtual void Step1() = 0;
	virtual void Step2() = 0;
	virtual void Step3() = 0;
};

class NumberDoer : public Doer
{
private:
	virtual void Step1() override
	{
		std::cout << 1 << std::endl;
	}

	virtual void Step2() override
	{
		std::cout << 2 << std::endl;
	}

	virtual void Step3() override
	{
		std::cout << 3 << std::endl;
	}
};

class LetterDoer : public Doer
{
private:
	virtual void Step1() override
	{
		std::cout << 'A' << std::endl;
	}

	virtual void Step2() override
	{
		std::cout << 'B' << std::endl;
	}

	virtual void Step3() override
	{
		std::cout << 'C' << std::endl;
	}
};

int main()
{
	NumberDoer().Do();
	LetterDoer().Do();

	return 0;
}