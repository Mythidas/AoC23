#pragma once

#include "AdventDay.h"
#include "Timer.h"
#include "Inputs/I_Day9.h"

class Day9 : public AdventDay
{
public:
	virtual void PrintAnswer() override
	{
		Timer timer;
		int part1 = Part1Answer();
		int part2 = Part2Answer();
		std::cout << "Day9: (Time to run: " << timer.Elapsed() << ")" << std::endl;
		std::cout << "  Part1 Answer: " << part1 << std::endl;
		std::cout << "  Part2 Answer: " << part2 << std::endl;
		std::cout << std::endl;
	}

private:
	int Part1Answer()
	{
		int answer = 0;

		// This day was simple, a algorithm for finding the pattern of change was provided and implemented
		for (auto& line : Day9_Inputs)
		{
			std::vector<int> numbers = GetNumbers(line);

			// We get the factor of change to estimate the next number in the sequence
			answer += GetFactor(numbers) + numbers.back();
		}

		return answer;
	}

	int Part2Answer()
	{
		int answer = 0;

		for (auto& line : Day9_Inputs)
		{
			std::vector<int> numbers = GetNumbers(line);
			answer += numbers[0] - GetReverseFactor(numbers);
		}

		return answer;
	}

	// Recursively finds the difference in the sequence until the difference is 0, then reverses the tree addding all the results
	int GetFactor(const std::vector<int>& numbers)
	{
		std::vector<int> sequence;

		bool zeroed = true;
		for (size_t i = 1; i < numbers.size(); i++)
		{
			sequence.push_back(numbers[i] - numbers[i - 1]);
			if (sequence.back() != 0)
				zeroed = false;
		}

		if (zeroed) return 0;

		return GetFactor(sequence) + sequence.back();
	}

	// This does the reverse of GetFactor and subtracts from the beginning of the sequence
	int GetReverseFactor(const std::vector<int>& numbers)
	{
		std::vector<int> sequence;

		bool zeroed = true;
		for (size_t i = 1; i < numbers.size(); i++)
		{
			sequence.push_back(numbers[i] - numbers[i - 1]);
			if (sequence.back() != 0)
				zeroed = false;
		}

		if (zeroed) return 0;

		return sequence[0] - GetReverseFactor(sequence);
	}

	// Simple function to parse all numbers in a string
	std::vector<int> GetNumbers(const std::string& str)
	{
		std::vector<int> numbers;
		std::string parsed = "";

		for (auto& character : str)
		{
			if (std::isdigit(character) || character == '-')
			{
				parsed += character;
			}
			else
			{
				if (!parsed.empty())
					numbers.push_back(atoi(parsed.c_str()));

				parsed = "";
			}
		}

		if (!parsed.empty())
			numbers.push_back(atoi(parsed.c_str()));

		return numbers;
	}
};