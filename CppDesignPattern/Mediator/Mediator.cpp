#include <iostream>
#include <string>
#include <iomanip>

class User;

struct Room
{
	virtual void ShowMessage(const User &U, const std::string &Msg) = 0;
};

struct ChatRoom : public Room
{
	virtual void ShowMessage(const User &U, const std::string &Msg) override;
};

class User
{
public:
	User() = default;
	User(const std::string Name, Room &Room_)
		: Name{ Name }, Room_{ Room_ }
	{
	}

	const std::string& GetName() const noexcept
	{
		return Name;
	}

	void ShowMessage(const std::string &Message) const
	{
		Room_.ShowMessage(*this, Message);
	}

private:
	std::string Name;
	Room &Room_;
};

void ChatRoom::ShowMessage(const User &U, const std::string &Msg)
{
	std::cout << U.GetName() << " said:" << std::quoted(Msg) << std::endl;
}

int main()
{
	ChatRoom ChatRoom_;
	User A{ "A", ChatRoom_ }, B{ "B", ChatRoom_ };
	A.ShowMessage("Hello B");
	B.ShowMessage("Hello A");

	return 0;
}