#include <iostream>

template <typename ...T>
struct TellMeaningOf
{
	void operator()() noexcept
	{
		std::cout << "[unknown type]";
	}
};

template <>
struct TellMeaningOf<void>
{
	void operator()() noexcept
	{
		std::cout << "void";
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

template <>
struct TellMeaningOf<int>
{
	void operator()() noexcept
	{
		std::cout << "int";
	}
};

template <>
struct TellMeaningOf<double>
{
	void operator()() noexcept
	{
		std::cout << "double";
	}
};

template <>
struct TellMeaningOf<float>
{
	void operator()() noexcept
	{
		std::cout << "float";
	}
};

template <>
struct TellMeaningOf<char>
{
	void operator()() noexcept
	{
		std::cout << "char";
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

int main()
{
	TellMeaningOf<char*(*(*)(void))[20]>()();

	return 0;
}