#include <iostream>

struct Monkey;
struct Lion;
struct Dolphin;

struct Operation
{
	void MonkeySpeak(Monkey *M);
	void LionSpeak(Lion *L);
	void DolphinSpeak(Dolphin *D);
};

struct Animal
{
	virtual void Accept(Operation &) = 0;
};

struct Monkey : public Animal
{
	void Shout()
	{
		std::cout << "Monkey!" << std::endl;
	}

	void Accept(Operation &Op) override
	{
		Op.MonkeySpeak(this);
	}
};

struct Lion : public Animal
{
	void Roar()
	{
		std::cout << "Lion!" << std::endl;
	}

	void Accept(Operation &Op) override
	{
		Op.LionSpeak(this);
	}
};

struct Dolphin : public Animal
{
	void Speak()
	{
		std::cout << "Dolphin!" << std::endl;
	}

	void Accept(Operation &Op) override
	{
		Op.DolphinSpeak(this);
	}
};

void Operation::MonkeySpeak(Monkey *M)
{
	M->Shout();
}

void Operation::LionSpeak(Lion *L)
{
	L->Roar();
}
void Operation::DolphinSpeak(Dolphin *D)
{
	D->Speak();
}

int main()
{
	Operation Op;

	Monkey().Accept(Op);
	Lion().Accept(Op);
	Dolphin().Accept(Op);

	return 0;
}