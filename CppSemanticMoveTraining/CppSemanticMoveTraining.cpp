// CppSemanticMoveTraining.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MyList.h"
#include <iostream>
#include <ctime>
#include <vector>

template <unsigned N>
struct factorial { static constexpr int value = N * factorial<N - 1>::value; };
template <>
struct factorial<1u> { static int const value = 1u; };


class MyIntHolder
{
public:
	MyIntHolder(int value) noexcept : value(value) {}
	int getValue() noexcept { return value; }
	bool operator<(const MyIntHolder& ih) noexcept { return value < ih.value; }
	bool operator>(const MyIntHolder& ih) noexcept { return value > ih.value; }
	friend std::ostream& operator<<(std::ostream& os, const MyIntHolder& ih) noexcept { os << ih.value; return os; }
private:
	int value;
};

int main()
{
	std::srand(std::time(nullptr));
	auto constexpr nb_elem = factorial<3>::value;

	List<MyIntHolder> list;
	for (auto i = 0; i < nb_elem; i++)
	{
		int val = std::rand() % 1000;
		list.push(MyIntHolder(val));
	}
	
	std::cout << list << std::endl;

/*******************************************/

	List<MyIntHolder*> list2;
	for (auto i = 0; i < nb_elem; i++)
	{
		int val = std::rand() % 1000;
		list2.push(new MyIntHolder(val));
	}

	std::cout << list2 << std::endl;
}