#include <iostream>

struct Bulb
{
	void TurnOn()
	{
		std::cout << "On!" << std::endl;
	}

	void TurnOff()
	{
		std::cout << "Off!" << std::endl;
	}
};

struct ICommand
{
	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
};

class TurnOn : public ICommand
{
public:
	TurnOn(Bulb &rhs)
		: ABulb{ rhs }
	{
	}

	virtual void Execute() override
	{
		ABulb.TurnOn();
	}

	virtual void Undo() override
	{
		ABulb.TurnOff();
	}

	virtual void Redo() override
	{
		Execute();
	}

private:
	Bulb &ABulb;
};

class TurnOff : public ICommand
{
public:
	TurnOff(Bulb &rhs)
		: ABulb{ rhs }
	{
	}

	virtual void Execute() override
	{
		ABulb.TurnOff();
	}

	virtual void Undo() override
	{
		ABulb.TurnOn();
	}

	virtual void Redo() override
	{
		Execute();
	}

private:
	Bulb &ABulb;
};

struct Control
{
	void Summit(ICommand &Command)
	{
		Command.Execute();
	}
};

int main()
{
	Bulb Bulb_;
	TurnOn TurnOn_{ Bulb_ };
	TurnOff TurnOff_{ Bulb_ };

	Control Controler;
	Controler.Summit(TurnOn_);
	Controler.Summit(TurnOff_);

	return 0;
}