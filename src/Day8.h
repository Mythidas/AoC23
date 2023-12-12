#pragma once

#include "AdventDay.h"
#include "Timer.h"
#include "Inputs/I_Day8.h"

#include <unordered_map>

struct Node
{
	std::string Left;
	std::string Right;
};

class Day8 : public AdventDay
{
public:
	virtual void PrintAnswer() override
	{
		Timer timer;

		// We start by creating a map of nodes
		PopulateNodes();

		int part1 = Part1Answer();
		size_t part2 = Part2Answer();
		std::cout << "Day8: (Time to run: " << timer.Elapsed() << ")" << std::endl;
		std::cout << "  Part1 Answer: " << part1 << std::endl;
		std::cout << "  Part2 Answer: " << part2 << std::endl;
		std::cout << std::endl;
	}

private:
	int Part1Answer()
	{
		std::string key = Day8_Inputs[0];

		// We start at AAA with 0 steps
		int steps = 0;
		std::string current = "AAA";

		while (true)
		{
			if (current == "ZZZ") break;

			// We simply step through the key with our steps modulo key size to stay in bounds of the array
			if (key[steps % key.size()] == 'L')
			{
				current = m_Nodes[current].Left;
			}
			else
			{
				current = m_Nodes[current].Right;
			}

			steps++;
		}

		return steps;
	}

	// Part two was tricky and couldn't be brute forced, so I used a trick since the data set for this problem has a continuous loop for the nodes
	size_t Part2Answer()
	{
		std::string key = Day8_Inputs[0];

		int steps = 0;
		
		// We keep track of when we reach our destination for each start for use later
		std::vector<int> stepCounts;

		while (true)
		{
			int index = -1;
			for (auto& current : m_StartNodes)
			{
				index++;

				// We only need to process paths that haven't found an end
				if (current[2] == 'Z') continue;

				if (key[steps % key.size()] == 'L')
				{
					current = m_Nodes[current].Left;
				}
				else
				{
					current = m_Nodes[current].Right;
				}

				// We need to keep track of when we find our destination and store the steps count
				if (current[2] == 'Z')
					stepCounts.push_back(steps + 1);
			}

			// We have found all the ends to our paths
			if (stepCounts.size() == m_StartNodes.size()) break;

			steps++;
		}

		// We need to sort the array to make it simpler for our GCF calculation
		QuickSort(stepCounts, 0, static_cast<int>(stepCounts.size() - 1));

		// We are using GCF method of getting our LCM
		// This is a trick that can be used with this specific dataset because the destinations always loop
		// The loop means we only need to find the point where paths converge, which can be found with the Least Common Multiple
		size_t lcm = stepCounts[0];
		for (size_t i = 1; i < stepCounts.size(); i++)
		{
			steps++;
			lcm = lcm * stepCounts[i] / GreatestCommonFactor(lcm, stepCounts[i]);
		}

		return lcm;
	}

	// Finds the GCF of two numbers using the Euclidean method
	size_t GreatestCommonFactor(size_t low, size_t high)
	{
		size_t temp = low < high ? low : high;
		high = low < high ? high : low;
		low = low < high ? low : temp;

		size_t factor = static_cast<size_t>(floor(high / low));

		size_t gcf = high - low * factor;
		if (gcf <= 0) return low;
		
		if (gcf <= low)
			return GreatestCommonFactor(gcf, low);
		else
			return GreatestCommonFactor(gcf, high);
	}

	void PopulateNodes()
	{
		for (size_t i = 2; i < Day8_Inputs.size(); i++)
		{
			// We parse the line for the node information
			std::string input = Day8_Inputs[i];
			size_t first = input.find('(') + 1;
			size_t second = input.find(',') + 2;
			std::string node = input.substr(0, 3);

			// Store nodes with their key, storing nodes that end with A for part 2
			if (node[2] == 'A')
				m_StartNodes.push_back(node);
			m_Nodes[node] = Node(input.substr(first, 3), input.substr(second, 3));
		}
	}

	void QuickSort(std::vector<int>& list, int low, int high)
	{
		if (low < high)
		{
			int pi = Partition(list, low, high);

			QuickSort(list, low, pi - 1);
			QuickSort(list, pi + 1, high);
		}
	}

	int Partition(std::vector<int>& list, int low, int high)
	{
		int pivot = list[high];
		int i = low - 1;

		for (int j = low; j <= high; j++)
		{
			if (list[j] < pivot)
			{
				i++;
				std::swap(list[i], list[j]);
			}
		}
		std::swap(list[static_cast<size_t>(i + 1)], list[high]);
		return i + 1;
	}

private:
	std::unordered_map<std::string, Node> m_Nodes;
	std::vector<std::string> m_StartNodes;
};