#pragma once

#include "AdventDay.h"
#include "Inputs/I_Day2.h"

class Day2 : public AdventDay
{
public:
	virtual void PrintAnswer() override
	{
		Timer timer;
		int part1 = Part1Answer();
		int part2 = Part2Answer();
		std::cout << "Day2: (Time to run: " << timer.Elapsed() << ")" << std::endl;
		std::cout << "  Part1 Answer: " << part1 << std::endl;
		std::cout << "  Part2 Answer: " << part2 << std::endl;
		std::cout << std::endl;
	}

private:
	int Part1Answer()
	{
		int answer = 0;

		for (auto& game : Day2_Inputs)
		{
			if (IsGamePossible(game, 12, 13, 14))
			{
				answer += ParseNumber(GetKey(":", game));
			}
		}

		return answer;
	}

	int Part2Answer()
	{
		int answer = 0;

		for (auto& game : Day2_Inputs)
		{
			answer += GetGamePower(game);
		}

		return answer;
	}

	// We check if the game is possible with cube counts
	bool IsGamePossible(const std::string& game, int redCube, int greenCube, int blueCube)
	{
		// We keep a temp string to parse with
		std::string parsed = "";

		// We start at index 7 to skip the Game: part of the line
		for (size_t i = 7; i < game.size(); i++)
		{
			parsed += game[i];

			// If a key is contained we know its unique because we always reset the parsed string
			if (parsed.contains("red"))
			{
				int count = ParseNumber(parsed);
				if (count > redCube)
					return false;

				parsed = "";
			}
			else if (parsed.contains("green"))
			{
				int count = ParseNumber(parsed);
				if (count > greenCube)
					return false;

				parsed = "";
			}
			else if (parsed.contains("blue"))
			{
				int count = ParseNumber(parsed);
				if (count > blueCube)
					return false;

				parsed = "";
			}
		}

		return true;
	}

	int GetGamePower(const std::string& game)
	{
		// We keep a temp string to parse with
		std::string parsed = "";

		// We store the lowest possible count of each color
		int redMin = 0;
		int greenMin = 0;
		int blueMin = 0;

		// We start at index 7 to skip the Game: part of the line
		for (size_t i = 7; i < game.size(); i++)
		{
			parsed += game[i];

			// If a key is contained we know its unique because we always reset the parsed string
			if (parsed.contains("red"))
			{
				int count = ParseNumber(parsed);
				if (count > redMin)
					redMin = count;

				parsed = "";
			}
			else if (parsed.contains("green"))
			{
				int count = ParseNumber(parsed);
				if (count > greenMin)
					greenMin = count;

				parsed = "";
			}
			else if (parsed.contains("blue"))
			{
				int count = ParseNumber(parsed);
				if (count > blueMin)
					blueMin = count;

				parsed = "";
			}
		}

		return redMin * greenMin * blueMin;
	}

	// Simple function to find a key and return the values before the key
	std::string GetKey(const char* key, const std::string& string)
	{
		size_t index = string.find_first_of(key);
		return string.substr(0, index);
	}

	// Simple function that keeps only numerical chars and returns them as an int
	int ParseNumber(const std::string& string)
	{
		std::string number = "";

		for (auto& character : string)
		{
			if (std::isdigit(character))
				number += character;
		}

		return atoi(number.c_str());
	}
};