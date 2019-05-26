#include <iostream>

class Widget
{
public:
	virtual void Draw() = 0;
};

class TextField : public Widget
{
private:
	int Width, Height;

public:
	TextField() = default;
	TextField(int w, int h)
		: Width(w), Height(h)
	{
	}

	virtual void Draw() override
	{
		std::cout << "TextField: " << Width << ' ' << Height << std::endl;
	}
};

class Decorator : public Widget
{
private:
	Widget *w;

public:
	Decorator() = default;
	Decorator(Widget *w)
		: w(w)
	{
	}

	virtual void Draw() override
	{
		w->Draw();
	}
};

class BorderDecorator : public Decorator
{
public:
	BorderDecorator() = default;
	BorderDecorator(Widget *w)
		: Decorator(w)
	{
	}

	virtual void Draw() override
	{
		Decorator::Draw();
		std::cout << "BorderDecorator" << std::endl;
	}
};

class ScrollDecorator : public Decorator
{
public:
	ScrollDecorator() = default;
	ScrollDecorator(Widget *w)
		: Decorator(w)
	{
	}

	virtual void Draw() override
	{
		Decorator::Draw();
		std::cout << "ScrollDecorator" << std::endl;
	}
};

int main()
{
	(new BorderDecorator
		(new ScrollDecorator
			(new BorderDecorator
				(new BorderDecorator
					(new TextField(10, 20))))))
	->Draw();

	return 0;
}