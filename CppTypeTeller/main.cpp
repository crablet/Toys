#include <iostream>
#include <type_traits>
#include <typeinfo>

template <typename ...T>
struct TellMeaningOf;

template <typename T>
struct TellMeaningOf<T>
{
	void operator()() noexcept
	{
		if constexpr (!std::is_const_v<T> && std::is_fundamental_v<T>)
		{
			std::cout << typeid(T).name();
		}
		else
		{
			std::cout << "[unknown]";
		}
	}
};

template <>
struct TellMeaningOf<>
{
	void operator()() noexcept
	{
		std::cout << "void";
	}
};

template <typename ReturnT, typename ...ParaT>
struct TellMeaningOf<ReturnT(ParaT...)>
{
	void operator()() noexcept
	{
		std::cout << "function (";
		TellMeaningOf<ParaT...>()();
		std::cout << ") returning ";
		TellMeaningOf<ReturnT>()();
	}
};

template <typename First, typename ...Last>
struct TellMeaningOf<First, Last...>
{
	void operator()() noexcept
	{
		TellMeaningOf<First>()();
		std::cout << ", ";
		TellMeaningOf<Last...>()();
	}
};

template <typename T>
struct TellMeaningOf<T*>
{
	void operator()() noexcept
	{
		std::cout << "pointer to ";
		TellMeaningOf<T>()();
	}
};

template <typename T>
struct TellMeaningOf<const T*>
{
	void operator()() noexcept
	{
		std::cout << "pointer to const ";
		TellMeaningOf<T>()();
	}
};

template <typename T>
struct TellMeaningOf<const T>
{
	void operator()() noexcept
	{
		std::cout << "const ";
		TellMeaningOf<T>()();
	}
};

template <typename T, std::size_t N>
struct TellMeaningOf<T[N]>
{
	void operator()() noexcept
	{
		std::cout << "array " << N << " of ";
		TellMeaningOf<T>()();
	}
};

int main()
{
	TellMeaningOf<char*(*(*)(void))[20]>()();

	return 0;
}