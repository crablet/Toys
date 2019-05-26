#include <iostream>
#include <string>
#include <vector>

class Person
{
private:
	std::string Name;

public:
	Person() = default;
	Person(const std::string &Name)
		: Name(Name)
	{
	}

	void TellName() const
	{
		std::cout << Name << std::endl;
	}
};

class Man : public Person
{
public:
	Man() = default;
	Man(const std::string &Name)
		: Person(Name)
	{
	}
};

class Woman : public Person
{
public:
	Woman() = default;
	Woman(const std::string &Name)
		: Person(Name)
	{
	}
};

int main()
{
	std::vector<Person*> Persons;
	Persons.push_back(new Man("Man"));
	Persons.push_back(new Woman("Woman"));
	Persons.push_back(new Person("Person"));

	for (const auto &r : Persons)
	{
		r->TellName();
	}

	return 0;
}