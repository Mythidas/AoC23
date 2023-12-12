#pragma once

#include "AdventDay.h"
#include "Timer.h"
#include "Inputs/I_Day10.h"

struct Tile
{
	// Adding the dir to the x and y gets the next tile
	int x, y;
	int xDir, yDir;
	int distance;

	Tile() = default;
	Tile(int x, int y, char tile, const Tile& previous)
		: xDir(0), yDir(0), distance(previous.distance + 1)
	{
		this->x = x;
		this->y = y;

		switch (tile)
		{
		case '|': xDir = 0; yDir = y - previous.y; break;
		case '-': yDir = 0; xDir = x - previous.x; break;
		case 'L': if (previous.y < y) { yDir = 0; xDir = 1; }
				else { yDir = -1; xDir = 0; }; break;
		case 'J': if (previous.y < y) { yDir = 0; xDir = -1; }
				else { yDir = -1; xDir = 0; }; break;
		case '7': if (previous.y > y) { yDir = 0; xDir = -1; }
				else { yDir = 1; xDir = 0; }; break;
		case 'F': if (previous.y > y) { yDir = 0; xDir = 1; }
				else { yDir = 1; xDir = 0; }; break;
		}
	}

	bool operator!=(const Tile& rhs) const
	{
		return x != rhs.x || y != rhs.y;
	}
};

class Day10 : public AdventDay
{
public:
	virtual void PrintAnswer() override
	{
		Timer timer;
		int part1 = Part1Answer();
		int part2 = Part2Answer();
		std::cout << "Day10: (Time to run: " << timer.Elapsed() << ")" << std::endl;
		std::cout << "  Part1 Answer: " << part1 << std::endl;
		std::cout << "  Part2 Answer: " << part2 << std::endl;
		std::cout << std::endl;
	}

private:
	int Part1Answer()
	{
		// We start by finding the start tile and get the two possible path tiles in the m_ValidTiles vector
		Tile start = FindStartTile(Day10_Inputs);
		AddStartingPaths(start, Day10_Inputs);

		// We loop through until we find the other starting tile
		while (m_ValidTiles.front() != m_ValidTiles.back())
		{
			Tile current = m_ValidTiles.back();
			char next = Day10_Inputs[static_cast<size_t>(current.y + current.yDir)][static_cast<size_t>(current.x + current.xDir)];
			m_ValidTiles.push_back(Tile(current.x + current.xDir, current.y + current.yDir, next, current));
		}

		// We just divide the distance by 2 for the farthest tile and ceil the answer to account for odd length paths 
		return static_cast<int>(ceil(m_ValidTiles.back().distance * 0.5f));
	}

	int Part2Answer()
	{
		// Haven't figured out a solution
		return 0;
	}

	Tile FindStartTile(const std::vector<std::string>& pipes)
	{
		Tile start{};

		for (size_t y = 0; y < pipes.size(); y++)
		{
			if (pipes[y].contains('S'))
			{
				start.y = static_cast<int>(y);
				start.x = static_cast<int>(pipes[y].find('S'));
				start.distance = 0;
				break;
			}
		}

		return start;
	}

	void AddStartingPaths(const Tile& start, const std::vector<std::string>& pipes)
	{
		// There are only 4 posible tiles, we safe gaurd against out of range errors
		char top = static_cast<size_t>(start.x + 1) < pipes.size() ? pipes[static_cast<size_t>(start.y - 1)][static_cast<size_t>(start.x)] : '.';
		char right = static_cast<size_t>(start.x + 1) < pipes[start.y].size() ? pipes[static_cast<size_t>(start.y)][static_cast<size_t>(start.x + 1)] : '.';
		char bot = start.y - 1 >= 0 ? pipes[static_cast<size_t>(start.y + 1)][static_cast<size_t>(start.x)] : '.';
		char left = start.x - 1 >= 0 ? pipes[static_cast<size_t>(start.y)][static_cast<size_t>(start.x - 1)] : '.';

		if (top != '.' && (top == '|' || top == '7' || top == 'F'))
			m_ValidTiles.push_back(Tile(start.x, start.y - 1, top, start));
		if (right != '.' && (right == '-' || right == '7' || right == 'J'))
			m_ValidTiles.push_back(Tile(start.x + 1, start.y, right, start));
		if (bot != '.' && (bot == '|' || bot == 'L' || bot == 'J'))
			m_ValidTiles.push_back(Tile(start.x, start.y + 1, bot, start));
		if (left != '.' && (left == '-' || left == 'L' || left == 'F'))
			m_ValidTiles.push_back(Tile(start.x - 1, start.y, left, start));
	}

private:
	std::vector<Tile> m_ValidTiles;
};