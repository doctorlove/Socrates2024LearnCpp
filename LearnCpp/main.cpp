#include <cassert>

#include <iostream>
#include <limits>
#include <optional>
#include <print>

#include <sstream> 
#include <stdexcept>

void show(std::ostream & os, const std::string & words)
{
	os << words;
}

int input(std::istream& is)
{
	int number{};
	is >> number;
	if (!is)
	{
		throw std::exception(); //or something else
	}
	return number;
}

std::optional<int> user_choice(std::istream & is)
{
	int number{};
	is >> number;
	if (is)
		return number;
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return {};
}

void tests()
{
	std::ostringstream oss;
	show(oss, "Hello, world!");
	assert(oss.str() == "Hello, world!");

	std::istringstream iss{ "42" };
	int value = input(iss);
	assert(value == 42);

	std::istringstream iss_invalid{ "Not a number" };
	try
	{
		input(iss);
		assert(false);
	}
	catch (const std::exception & )
	{

	}

	std::istringstream iss_again{ "42" };
	auto got = user_choice(iss_again);
	assert(got.has_value());
	std::istringstream iss_invalid_again{ "Not a number" };
	auto got_now = user_choice(iss_invalid_again);
	assert(!got_now.has_value());
}

int main()
{
	std::println("Hello, world!");
	std::print("Hello, world!");
	std::cout << "Hello, world!\n";

	show(std::cout, "Hello, world!");
	tests();
}

