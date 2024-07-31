#include <cassert>

#include <array>
#include <iostream>
#include <limits>
#include <map> //extension
#include <optional>
#include <print> // might not work for you, so comment out
#include <random>
#include <ranges> //extension
#include <sstream> 
#include <stdexcept>
#include <vector>

void show(std::ostream& os, const std::string& words)
{
	os << words;
}

int input(std::istream& is)
{
	int number{};
	is >> number;
	if (!is)
	{
		is.clear(); // clear the fail flag (should mop up too)
		throw std::exception(); //or something else
	}
	return number;
}

std::optional<int> user_choice(std::istream& is)
{
	int number{};
	is >> number;
	if (is)
		return number;
	is.clear(); // clear the fail flag
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // mop up too
	return {};
}

std::optional<int> zero_one_or_two(std::istream& is)
{
	int number{};
	is >> number;
	if (is && 0 <= number && number < 3)
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

enum class Result {
	Draw,
	FirstWins,
	SecondWins,
};

std::ostream& operator<<(std::ostream& os, Choice choice)
{
	std::array choice_str{ "Rock", "Paper", "Scissors" };
	os << choice_str[std::to_underlying(choice)];
	return os;
}

Result outcome(Choice first, Choice second)
{
	if (first == second)
		return Result::Draw;
	else if ((first == Choice::Rock && second == Choice::Scissors)
		|| (first == Choice::Paper && second == Choice::Rock)
		|| (first == Choice::Scissors && second == Choice::Paper))
		return Result::FirstWins;
	return Result::SecondWins;
}

std::map<Choice, int> make_histogram(const std::vector<Choice>& data)
{
	std::map<Choice, int> histogram;

	for (const auto& e : data) ++histogram[e];
	return histogram;
}

Choice weighted_choice(const std::vector<Choice>& plays, std::default_random_engine& gen)
{
	auto hist = make_histogram(plays);
	auto probs = std::views::values(hist);
	std::discrete_distribution<int> weighted_dist(probs.begin(), probs.end());
	auto index = weighted_dist(gen);
	return std::ranges::to<std::vector>(std::views::keys(hist))[index];
}

Choice beats(Choice choice)
{
	if (choice == Choice::Rock)
		return Choice::Paper;
	else if (choice == Choice::Paper)
		return Choice::Scissors;
	else
		return Choice::Rock;
}

void game()
{
	// Extensions: Track winner?
	// Any patterns?
	//std::vector<Choice> plays;// extension
	std::default_random_engine gen{ std::random_device{}() };
	std::uniform_int_distribution dist{ 0, 2 };

	while (auto input = zero_one_or_two(std::cin))
	{
		auto human_choice = static_cast<Choice>(input.value());
		//plays.push_back(human_choice);// extension

		 auto computer_choice = static_cast<Choice>(dist(gen));
		// or extension
		//auto computer_choice = plays.size() > 2 ?
		//	beats(weighted_choice(plays, gen))  : static_cast<Choice>(dist(gen));

		std::cout << human_choice << " v. " << computer_choice << ": ";

		auto result = outcome(computer_choice, human_choice);
		if (result == Result::FirstWins)
			std::cout << "computer wins\n";
		else if (result == Result::SecondWins)
			std::cout << "human wins\n";
		else
			std::cout << "Draw\n";
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

	{
		assert(outcome(Choice::Rock, Choice::Rock) == Result::Draw); 
		assert(outcome(Choice::Paper, Choice::Paper) == Result::Draw);
		assert(outcome(Choice::Scissors, Choice::Scissors) == Result::Draw);

		assert(outcome(Choice::Rock, Choice::Paper) == Result::SecondWins);
		assert(outcome(Choice::Paper, Choice::Scissors) == Result::SecondWins);
		assert(outcome(Choice::Scissors, Choice::Rock) == Result::SecondWins);

		assert(outcome(Choice::Paper, Choice::Rock) == Result::FirstWins);
		assert(outcome(Choice::Scissors, Choice::Paper) == Result::FirstWins);
		assert(outcome(Choice::Rock, Choice::Scissors) == Result::FirstWins);
	}

	{
		assert(beats(Choice::Rock) == Choice::Paper);
		assert(beats(Choice::Paper) == Choice::Scissors);
		assert(beats(Choice::Scissors) == Choice::Rock);
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

