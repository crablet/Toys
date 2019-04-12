#include <iostream>
#include <bitset>
#include <string>
#include <functional>

template <class ElemType, std::size_t Size>
class BloomFilter
{
private:
	std::bitset<Size> Bitmap;

	constexpr static std::size_t K = 3;

	std::size_t Hash(const ElemType &Elem, std::size_t k) const
	{
		k += 11210904;
		return (std::hash<ElemType>()(Elem) + 0x9e3779b9 + (k << 6) + (k >> 2)) % Size;
	}

public:
	BloomFilter() = default;

	bool Contains(const ElemType&) const noexcept;
	void Add(const ElemType&);
};

template <class ElemType, std::size_t Size>
bool BloomFilter<ElemType, Size>::Contains(const ElemType &Elem) const noexcept
{
	bool Found = true;
	for (std::size_t i = 0; i < K; ++i)
	{
		Found &= Bitmap.test(Hash(Elem, i));
	}

	return Found;
}

template <class ElemType, std::size_t Size>
void BloomFilter<ElemType, Size>::Add(const ElemType &Elem)
{
	for (std::size_t i = 0; i < K; ++i)
	{
		Bitmap.set(Hash(Elem, i));
	}
}

int main()
{
	BloomFilter<std::string, 32> BF;
	BF.Add("xiaozhaxie");
	BF.Add("damiantuo");
	std::cout << BF.Contains("xiaozhaxie") << std::endl;
	std::cout << BF.Contains("xiaomiantuo") << std::endl;
	std::cout << BF.Contains("damiantuo") << std::endl;

	return 0;
}