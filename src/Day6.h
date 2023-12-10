#pragma once

#include "AdventDay.h"
#include "Inputs/I_Day6.h"

class Day6 : public AdventDay
{
public:
	virtual void PrintAnswer() override
	{
		int part1 = Part1Answer();
		int part2 = Part2Answer();
		std::cout << "Day6:" << std::endl;
		std::cout << "  Part1 Answer: " << part1 << std::endl;
		std::cout << "  Part2 Answer: " << part2 << std::endl;
		std::cout << std::endl;
	}

private:
	int Part1Answer()
	{
		// Obtain times and distances from input
		int answer = 1;
		std::vector<int> times = GetNumbers(Day6_Inputs[0]);
		std::vector<int> dists = GetNumbers(Day6_Inputs[1]);

		// Loop through separate races
		for (size_t i = 0; i < times.size(); i++)
		{
			// We can skip unnecessary numbers by getting the lowest possible number our time could multiply with to equal the distance
			int start = dists[i] / times[i];
			while (start < times[i])
			{
				// We use this formula to create a curve until the curve is greater than the distance
				if (start * (times[i] - start) > dists[i])
				{
					// Since we are using a curve we can get the last possible number with END - CURRENT and subtract CURRENT to get the length of the curve, we add 1 to make it inclusive
					answer *= (times[i] - start) - start + 1;
					break;
				}

				start++;
			}
		}

		return answer;
	}

	// Since we made the first problem easier using a curve we can paste the solution again and ignore large numbers
	int Part2Answer()
	{
		// We are using a size_t here to account for large numbers
		int answer = 0;
		size_t time = GetSingleNumber(Day6_Inputs[0]);
		size_t dist = GetSingleNumber(Day6_Inputs[1]);

		size_t start = dist / time;
		while (start < time)
		{
			if (start * (time - start) > dist)
			{
				answer = static_cast<int>((time - start) - start + 1);
				break;
			}

			start++;
		}

		return answer;
	}

	// Converts string into one number ignoring any additional characters (size_t to allow for large numbers)
	size_t GetSingleNumber(const std::string& str)
	{
		std::string parsed = "";

		for (auto& character : str)
		{
			if (std::isdigit(character))
			{
				parsed += character;
			}
		}

		return atoll(parsed.c_str());
	}

	// Simple function to parse all numbers in a string
	std::vector<int> GetNumbers(const std::string& str)
	{
		std::vector<int> numbers;
		std::string parsed = "";

		for (auto& character : str)
		{
			if (std::isdigit(character))
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