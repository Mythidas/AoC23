#include "Inputs.h"

#include <iostream>

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

std::vector<size_t> GetSeeds(const std::string& str)
{
	std::vector<size_t> seeds;
	std::string parsed = "";
	bool initial = true;

	for (auto& character : str)
	{
		if (std::isdigit(character))
		{
			parsed += character;
		}
		else if (!initial)
		{
			initial = true;
			parsed = "";
		}
		else
		{
			if (!parsed.empty())
			{
				seeds.push_back(atoll(parsed.c_str()));
				initial = false;
			}

			parsed = "";
		}
	}

	return seeds;
}

// Storing indexes as names to avoid mistypes
const size_t DEST = 0;
const size_t SOURCE = 1;
const size_t RANGE = 2;

int Part1Answer()
{
	// Get seeds and set current seed states to track if seed was modified
	std::vector<size_t> seeds = GetNumbers(Inputs[0]);
	std::vector<int> seedStates(seeds.size(), 0);

	for (size_t i = 1; i < Inputs.size(); i++)
	{
		std::vector<size_t> line = GetNumbers(Inputs[i]);
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
			lowest = seed;
	}

	return lowest;
}

int Part2Answer()
{
	// Get seeds and set current seed states to track if seed was modified
	std::vector<size_t> seeds = GetSeeds(Inputs[0]);
	std::vector<int> seedStates(seeds.size(), 0);

	for (size_t i = 1; i < Inputs.size(); i++)
	{
		std::vector<size_t> line = GetNumbers(Inputs[i]);
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
			lowest = seed;
	}

	return lowest;
}

int main()
{
	int part1 = Part1Answer();
	int part2 = Part2Answer();
	std::cout << "Part1 Answer: " << part1 << std::endl;
	std::cout << "Part2 Answer: " << part2 << std::endl;

	return 0;
}