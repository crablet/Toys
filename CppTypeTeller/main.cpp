#include <iostream>

template <typename ...T>
struct TellMeaningOf
{
	void operator()()
	{
		std::cout << "[unknown type]";
	}
};

template <>
struct TellMeaningOf<void>
{
	void operator()()
	{
		std::cout << "void";
	}
};

template <>
struct TellMeaningOf<>
{
	void operator()()
	{
		std::cout << "void";
	}
};

template <>
struct TellMeaningOf<int>
{
	void operator()()
	{
		std::cout << "int";
	}
};

template <>
struct TellMeaningOf<double>
{
	void operator()()
	{
		std::cout << "double";
	}
};

template <>
struct TellMeaningOf<float>
{
	void operator()()
	{
		std::cout << "float";
	}
};

template <>
struct TellMeaningOf<char>
{
	void operator()()
	{
		std::cout << "char";
	}
};

template <typename T>
struct TellMeaningOf<T*>
{
	void operator()()
	{
		std::cout << "pointer to ";
		TellMeaningOf<T>()();
	}
};

template <typename T>
struct TellMeaningOf<const T*>
{
	void operator()()
	{
		std::cout << "pointer to const ";
		TellMeaningOf<T>()();
	}
};

template <typename T>
struct TellMeaningOf<const T>
{
	void operator()()
	{
		std::cout << "const ";
		TellMeaningOf<T>()();
	}
};

template <typename T, std::size_t N>
struct TellMeaningOf<T[N]>
{
	void operator()()
	{
		std::cout << "array " << N << " of ";
		TellMeaningOf<T>()();
	}
};

template <typename ReturnT, typename ...ParaT>
struct TellMeaningOf<ReturnT(ParaT...)>
{
	void operator()()
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
	void operator()()
	{
		TellMeaningOf<First>()();
		std::cout << ", ";
		TellMeaningOf<Last...>()();
	}
};

int main()
{
	TellMeaningOf<char*(*(*)(void))[20]>()();
	std::cout << std::endl;

	return 0;
}