#pragma once

#include "AdventDay.h"
#include "Inputs/I_Day5.h"

class Day5 : public AdventDay
{
	// Storing indexes as names to avoid mistypes
	const size_t DEST = 0;
	const size_t SOURCE = 1;
	const size_t RANGE = 2;

public:
	virtual void PrintAnswer() override
	{
		Timer timer;
		int part1 = Part1Answer();
		int part2 = Part2Answer();
		std::cout << "Day5: (Time to run: " << timer.Elapsed() << ")" << std::endl;
		std::cout << "  Part1 Answer: " << part1 << std::endl;
		std::cout << "  Part2 Answer: " << part2 << std::endl;
		std::cout << std::endl;
	}

private:
	int Part1Answer()
	{
		// Get seeds and set current seed states to track if seed was modified
		std::vector<size_t> seeds = GetNumbers(Day5_Inputs[0]);
		std::vector<int> seedStates(seeds.size(), 0);

		for (size_t i = 1; i < Day5_Inputs.size(); i++)
		{
			std::vector<size_t> line = GetNumbers(Day5_Inputs[i]);
			if (!line.empty())
			{
				for (size_t j = 0; j < seeds.size(); j++)
				{
					// If seed state is set we skip this seed until the next Almanac Entry
					if (seedStates[j]) continue;

					// We check if the seed false inside of the source range
					if (seeds[j] >= line[SOURCE] && seeds[j] < line[SOURCE] + line[RANGE])
					{
						// Convert the seed to the DEST range and set its state to 1 (true)
						seeds[j] = (seeds[j] - line[SOURCE]) + line[DEST];
						seedStates[j] = 1;
					}
				}
			}
			else
			{
				// We reset seed states as we enter a new part of the Almanac
				seedStates = std::vector<int>(seeds.size(), 0);
			}
		}

		// We look through the seeds for the lowest value
		int lowest = INT_MAX;
		for (auto& seed : seeds)
		{
			if (seed < lowest)
				lowest = static_cast<int>(seed);
		}

		return lowest;
	}

	int Part2Answer()
	{
		// Still needs to be solved
		return 0;
	}

	// Simple function to parse all numbers in a string
	std::vector<size_t> GetNumbers(const std::string& str)
	{
		std::vector<size_t> numbers;
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
					numbers.push_back(atoll(parsed.c_str()));

				parsed = "";
			}
		}

		if (!parsed.empty())
			numbers.push_back(atoll(parsed.c_str()));

		return numbers;
	}
};