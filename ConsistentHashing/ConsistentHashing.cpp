// Reference:
// http://www.martinbroadhurst.com/Consistent-Hash-Ring.html
// http://www.zsythink.net/archives/1182
// https://blog.csdn.net/cywosp/article/details/23397179
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <exception>

class EmptyRingException : public std::exception
{
public:
	EmptyRingException() = default;

	virtual const char* what() const noexcept override
	{
		return "The HashRing is EMPTY now!";
	}
};

template <class Node, class Data, class Hash = std::hash<std::string>>
class HashRing
{
public:
	using NodeMap = std::map<std::size_t, Node>;

	HashRing(int Replicas)
		: Replicas(Replicas)
	{
	}

	void AddNode(const Node &node)
	{
		for (int i = 0; i < Replicas; ++i)
		{
			auto Hash_ = hash(node + std::to_string(i));
			Ring[Hash_] = node;
		}
	}

	void RemoveNode(const Node &node)
	{
		for (int i = 0; i < Replicas; ++i)
		{
			auto Hash_ = hash(node + std::to_string(i));
			Ring.erase(Hash_);
		}
	}

	const Node& GetNode(const Data &data) const
	{
		if (!Ring.empty())
		{
			auto Hash_ = hash(data);
			auto Iter = Ring.lower_bound(Hash_);
			if (Iter == Ring.end())
			{
				Iter = Ring.begin();
			}

			return Iter->second;
		}
		else
		{
			throw EmptyRingException();
		}
	}

private:
	const int Replicas;
	NodeMap Ring;
	Hash hash;
};

int main()
{
	HashRing<std::string, std::string> MyHashRing(5);
	MyHashRing.AddNode("123456");
	MyHashRing.AddNode("234567");
	std::cout << MyHashRing.GetNode("MyHash") << std::endl;

	return 0;
}