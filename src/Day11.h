#pragma once

#include "AdventDay.h"
#include "Timer.h"
#include "Inputs/I_Day11.h"

#include <unordered_map>

struct Galaxy
{
	int x, y;
};

class Day11 : public AdventDay
{
public:
	virtual void PrintAnswer() override
	{
		Timer timer;

		// We preload the galaxies and which lines are empty
		InitGalaxies(Day11_Inputs);
		// We calculate the distance between galaxies
		LoadDistanceValues(Day11_Inputs);

		int part1 = Part1Answer();
		size_t part2 = Part2Answer();
		std::cout << "Day11: (Time to run: " << timer.Elapsed() << ")" << std::endl;
		std::cout << "  Part1 Answer: " << part1 << std::endl;
		std::cout << "  Part2 Answer: " << part2 << std::endl;
		std::cout << std::endl;
	}

private:
	int Part1Answer()
	{
		// We adjust the answer based on how many steps should be counted as multiple instead of increasing the array size
		return m_NormalSteps + (m_ExpandedSteps * 2);
	}

	size_t Part2Answer()
	{
		return static_cast<size_t>(m_NormalSteps) + (static_cast<size_t>(m_ExpandedSteps)* 1000000);
	}

	void InitGalaxies(const std::vector<std::string>& universe)
	{
		for (int y = 0; y < universe.size(); y++)
		{
			m_EmptyLines[y] = true;
		}

		for (int x = 0; x < universe[0].size(); x++)
		{
			m_EmptyLines[x + static_cast<int>(universe.size())] = true;
		}

		// We get all of the galaxies and mark lines as not empty
		for (int y = 0; y < universe.size(); y++)
		{
			for (int x = 0; x < universe[0].size(); x++)
			{
				if (universe[y][x] == '#')
				{
					m_Galaxies.push_back(Galaxy(x, y));
					m_EmptyLines[x + static_cast<int>(universe.size())] = false;
					m_EmptyLines[y] = false;
				}
			}
		}
	}

	void LoadDistanceValues(const std::vector<std::string>& universe)
	{
		for (size_t i = 0; i < m_Galaxies.size() - 1; i++)
		{
			for (size_t j = i + 1; j < m_Galaxies.size(); j++)
			{
				int distance = 0;
				int yStart = m_Galaxies[i].y <= m_Galaxies[j].y ? m_Galaxies[i].y : m_Galaxies[j].y;
				int xStart = m_Galaxies[i].x <= m_Galaxies[j].x ? m_Galaxies[i].x : m_Galaxies[j].x;
				int yEnd = m_Galaxies[i].y <= m_Galaxies[j].y ? m_Galaxies[j].y : m_Galaxies[i].y;
				int xEnd = m_Galaxies[i].x <= m_Galaxies[j].x ? m_Galaxies[j].x : m_Galaxies[i].x;

				for (int y = yStart; y < yEnd; y++)
				{
					if (m_EmptyLines[y])
						m_ExpandedSteps += 1;
					else
						m_NormalSteps += 1;
				}

				for (int x = xStart; x < xEnd; x++)
				{
					if (m_EmptyLines[x + static_cast<int>(universe.size())])
						m_ExpandedSteps += 1;
					else
						m_NormalSteps += 1;
				}
			}
		}
	}

private:
	std::unordered_map<int, bool> m_EmptyLines;
	std::vector<Galaxy> m_Galaxies;

	int m_NormalSteps;
	int m_ExpandedSteps;
};