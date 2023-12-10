#pragma once

#include "AdventDay.h"
#include "Inputs/I_Day3.h"

struct Key
{
	size_t x, y;
	char Character;
};

struct Number
{
	size_t x, y;
	int Number;
	size_t Length;
};

class Day3 : public AdventDay
{
public:
	virtual void PrintAnswer() override
	{
		Timer timer;
		// Populate vectors for keys and numbers used as a map
		PopulateMaps(Day3_Inputs);

		int part1 = Part1Answer();
		int part2 = Part2Answer();
		std::cout << "Day3: (Time to run: " << timer.Elapsed() << ")" << std::endl;
		std::cout << "  Part1 Answer: " << part1 << std::endl;
		std::cout << "  Part2 Answer: " << part2 << std::endl;
		std::cout << std::endl;
	}

private:
	void PopulateMaps(const std::vector<std::string>& inputs)
	{
		size_t yWidth = inputs.size();
		size_t xWidth = inputs[0].size();

		for (size_t y = 0; y < yWidth; y++)
		{
			// Storing parsed characters of current number
			std::string parsed = "";
			// We only need to store numbers of parts
			bool isPartNumber = false;

			for (size_t x = 0; x < xWidth; x++)
			{
				char currrent = inputs[y][x];

				if (std::isdigit(currrent))
				{
					parsed += currrent;
					if (!isPartNumber)
						isPartNumber = IsSymbolAdjacent(inputs, x, y);
				}
				else
				{
					// We check if its a part and store anything thats in parsed
					if (isPartNumber)
						m_Numbers.push_back(Number(x - parsed.size(), y, atoi(parsed.c_str()), parsed.size()));

					// If we hit a key we store the type
					if (currrent != '.')
						m_Keys.push_back(Key(x, y, currrent));

					parsed = "";
					isPartNumber = false;
				}

				// Edge cases where a number is on the right edge
				if (x == xWidth - 1)
				{
					if (isPartNumber)
						m_Numbers.push_back(Number(x - parsed.size(), y, atoi(parsed.c_str()), parsed.size()));

					parsed = "";
					isPartNumber = false;
				}
			}
		}
	}

	int Part1Answer()
	{
		int answer = 0;

		for (auto& number : m_Numbers)
		{
			// Simply add all the parts found when populating the maps
			answer += number.Number;
		}

		return answer;
	}

	int Part2Answer()
	{
		int answer = 0;

		for (auto& key : m_Keys)
		{
			if (key.Character == '*')
			{
				// We get colliding numbers and if there are 2 add them to the answer
				std::vector<Number> adjacent = GetAdjacentNumbers(key);
				if (adjacent.size() == 2)
				{
					answer += adjacent[0].Number * adjacent[1].Number;
				}
			}
		}

		return answer;
	}

	std::vector<Number> GetAdjacentNumbers(Key key)
	{
		std::vector<Number> adjacent;

		for (auto& number : m_Numbers)
		{
			// We are using a bounding box collision to check if the keys box collides with a part number
			if (number.x <= key.x + 1 && number.x + number.Length - 1 >= key.x - 1)
			{
				if (number.y == key.y || number.y == key.y - 1 || number.y == key.y + 1)
					adjacent.push_back(number);
			}
		}

		return adjacent;
	}

	// Helper function to make sure coordinates are within vector bounds
	bool CheckPosition(const std::vector<std::string>& schematic, size_t x, size_t y)
	{
		if (x < 0 || y < 0) return false;
		if (y >= schematic.size() || x >= schematic[y].size()) return false;
		if (!std::isdigit(schematic[y][x]) && schematic[y][x] != '.') return true;

		return false;
	}

	// We check coordinates in a box around a given x and y
	bool IsSymbolAdjacent(const std::vector<std::string>& schematic, size_t x, size_t y)
	{
		if (CheckPosition(schematic, x - 1, y - 1)) return true;
		if (CheckPosition(schematic, x + 0, y - 1)) return true;
		if (CheckPosition(schematic, x + 1, y - 1)) return true;

		if (CheckPosition(schematic, x - 1, y + 0)) return true;
		if (CheckPosition(schematic, x + 1, y + 0)) return true;

		if (CheckPosition(schematic, x - 1, y + 1)) return true;
		if (CheckPosition(schematic, x + 0, y + 1)) return true;
		if (CheckPosition(schematic, x + 1, y + 1)) return true;

		return false;
	}

private:
	std::vector<Key> m_Keys;
	std::vector<Number> m_Numbers;
};