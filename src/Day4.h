#pragma once

#include "AdventDay.h"
#include "Inputs/I_Day4.h"

#include <unordered_map>

class Day4 : public AdventDay
{
public:
	virtual void PrintAnswer() override
	{
		int part1 = Part1Answer();
		int part2 = Part2Answer();
		std::cout << "Day4:" << std::endl;
		std::cout << "  Part1 Answer: " << part1 << std::endl;
		std::cout << "  Part2 Answer: " << part2 << std::endl;
		std::cout << std::endl;
	}

private:
	int Part1Answer()
	{
		int answer = 0;

		for (auto& scratcher : Day4_Inputs)
		{
			// We set points to 1 so we can multiply it by 2
			int points = 1;
			std::vector<int> numbers = GetYourNumbers(scratcher);

			// We loop through winning numbers and check against ours
			for (auto& winners : GetWinningNumbers(scratcher))
			{
				for (auto& number : numbers)
				{
					if (winners == number)
					{
						// We multiply our points by two for every winner we have. This is a bitshift to the left, which doubles the number. It isn't as simple but faster then multiplication
						points = points << 1;
						break;
					}
				}
			}

			// We have to divide the number by 2 since we initialized points with a 1
			answer += points >> 1;
		}

		return answer;
	}

	// This answer is extremely slow and there may be some optimizations that could be made since there are a lot of For Loops
	// EDIT: I resolved the speed issues pretty easily and added a note with the solution below
	int Part2Answer()
	{
		int answer = 0;

		// We keep a record of the current card and all card counts
		int card = 0;
		std::unordered_map<int, int> cardCounts;
		for (auto& scratcher : Day4_Inputs)
		{
			// Increase the current card by 1 to account for the original card
			card++;
			cardCounts[card]++;
			int points = 0;
			std::vector<int> numbers = GetYourNumbers(scratcher);

			//for (int i = 0; i < cardCounts[card]; i++)
			//{
			//	for (auto& winners : GetWinningNumbers(scratcher))
			//	{
			//		for (auto& number : numbers)
			//		{
			//			if (winners == number)
			//			{
			//				points += 1;
			//				break;
			//			}
			//		}
			//	}

			//	while (points > 0)
			//	{
			//		cardCounts[card + points]++;
			//		points--;
			//	}
			//}

			// **This is an improved version that runs quicker by only looping over the point tallying instead of calculating the points multiple times

			// We loop through winning numbers and check against ours
			for (auto& winners : GetWinningNumbers(scratcher))
			{
				for (auto& number : numbers)
				{
					if (winners == number)
					{
						points += 1;
						break;
					}
				}
			}

			int tempPoints = points;
			// We need to loop through all copies of the card
			for (int i = 0; i < cardCounts[card]; i++)
			{
				points = tempPoints;

				// Add copies of subsequent cards
				while (points > 0)
				{
					cardCounts[card + points]++;
					points--;
				}
			}
		}

		for (auto& pair : cardCounts)
		{
			answer += pair.second;
		}

		return answer;
	}

	// Returns winning numbres from the scratcher
	std::vector<int> GetWinningNumbers(const std::string& scratcher)
	{
		std::vector<int> numbers;

		std::string parsed = "";
		bool started = false;
		for (auto& character : scratcher)
		{
			// We start parsing once we reach the starting character and break once we reach the end character
			if (character == '|') break;
			if (character == ':') started = true;
			if (!started) continue;

			if (std::isdigit(character))
			{
				parsed += character;
			}
			else
			{
				// We check if we have any numbers, spaces will read as empty so this check doesn't throw false positives
				if (!parsed.empty())
					numbers.push_back(atoi(parsed.c_str()));
				parsed = "";
			}
		}

		return numbers;
	}

	// Returns our numbers from the scratcher
	std::vector<int> GetYourNumbers(const std::string& scratcher)
	{
		std::vector<int> numbers;

		std::string parsed = "";
		bool started = false;
		for (auto& character : scratcher)
		{
			// We start parsing once we reach the starting character
			if (character == '|') started = true;
			if (!started) continue;

			if (std::isdigit(character))
			{
				parsed += character;
			}
			else
			{
				// We check if we have any numbers, spaces will read as empty so this check doesn't throw false positives
				if (!parsed.empty())
					numbers.push_back(atoi(parsed.c_str()));
				parsed = "";
			}
		}

		numbers.push_back(atoi(parsed.c_str()));

		return numbers;
	}
};