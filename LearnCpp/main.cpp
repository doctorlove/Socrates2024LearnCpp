#include <cassert>

#include <array>
#include <iostream>
#include <limits>
#include <optional>
#include <print> // might not work for you, so comment out
#include <random>
#include <sstream> 
#include <stdexcept>
#include <vector>

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

std::optional<int> zero_one_or_two(std::istream& is)
{
	int number{};
	is >> number;
	if (is && 0<= number && number<3)
		return number;
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return {};
}

std::vector<int> store_input(std::istream& is)
{
	std::vector<int> values;
	while (auto choice = zero_one_or_two(is))
	{
		values.push_back(choice.value());
	}
	return values;
}

enum class Choice
{
	Rock,
	Paper,
	Scissors,
};

std::ostream& operator<<(std::ostream& os, Choice choice)
{
	std::array choice_str{ "Rock", "Paper", "Scissors" };
	os << choice_str[std::to_underlying(choice)];
	return os;
}

//constexpr 
bool first_player_wins(Choice first, Choice second)
{
	// Rock beats scissors (and nothing else)
	// Paper beats rock (and nothing else)
	// Scissors beats paper (and nothing else)
	return (first == Choice::Rock && second == Choice::Scissors)
		|| (first == Choice::Paper && second == Choice::Rock)
		|| (first == Choice::Scissors && second == Choice::Paper);
}

void game()
{
	std::default_random_engine gen{ std::random_device{}() };
	std::uniform_int_distribution dist{ 0, 2 };

	while (auto input = zero_one_or_two(std::cin))
	{
		auto human_choice = static_cast<Choice>(input.value());
		auto computer_choice = static_cast<Choice>(dist(gen));

		if (first_player_wins(computer_choice, human_choice))
			std::cout << "computer wins: ";
		else if (first_player_wins(human_choice, computer_choice))
			std::cout << "human wins: ";
		else
			std::cout << "Draw\n";

		std::cout << human_choice << " v. " << computer_choice << '\n';
	}
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

	{
		std::istringstream iss{ "Not a number" };
		auto got = zero_one_or_two(iss);
		assert(!got.has_value());
	}
	{
		std::istringstream iss{ "-1" };
		auto got = zero_one_or_two(iss);
		assert(!got.has_value());
	}
	{
		std::istringstream iss{ "0" };
		auto got = zero_one_or_two(iss);
		assert(got.has_value());
		assert(got.value()==0);
	}
	{
		std::istringstream iss{ "1" };
		auto got = zero_one_or_two(iss);
		assert(got.has_value());
		assert(got.value() == 1);
	}
	{
		std::istringstream iss{ "2" };
		auto got = zero_one_or_two(iss);
		assert(got.has_value());
		assert(got.value() == 2);
	}
	{
		std::istringstream iss{ "3" };
		auto got = zero_one_or_two(iss);
		assert(!got.has_value());
	}

	{
		std::istringstream iss{ "2 1 0" };
		auto got = store_input(iss);
		assert(got.size() == 3);
	}

	{
		std::istringstream iss{ "no" };
		auto got = store_input(iss);
		assert(got.size() == 0);
	}

	{
		std::istringstream iss{ "2 1 0 1 four" };
		auto got = store_input(iss);
		assert(got.size() == 4);
	}
}

int main()
{
	std::println("Hello, world!");// might not work for you, so comment out
	std::print("Hello, world!");// might not work for you, so comment out
	std::cout << "Hello, world!\n";

	show(std::cout, "Hello, world!\n");
	tests();

	std::cout << "Type in some numbers\n";
	auto got = store_input(std::cin);

	//Displaying - various ways to do this
	std::cout << "You typed\n";
	for (const auto& value : got)
	{
		std::cout << value << '\n';
	}

	////Why the const?
	//for (auto& value : got)
	//{
	//	value += 5;
	//}

	//for (const auto& value : got)
	//{
	//	std::cout << value << '\n';
	//}

	std::cout << "Rock (0), paper (1) or scissors (2)?\n";
	game();
}

