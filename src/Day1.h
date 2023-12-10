#pragma once

#include "AdventDay.h"
#include "Inputs/I_Day1.h"

#include <string>

const std::vector<std::string> StringNumbers =
{
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine"
};

class Day1 : public AdventDay
{
public:
	virtual void PrintAnswer() override
	{
		std::cout << "Day1:" << std::endl;
		std::cout << "  Part 1 Answer: " << Part1Answer() << std::endl;
		std::cout << "  Part 2 Answer: " << Part2Answer() << std::endl;
		std::cout << std::endl;
	}

private:
	int Part1Answer()
	{
		int answer = 0;

		for (auto& line : Day1_Inputs)
		{
			answer += CaluclateCalibration_Part1(line);
		}

		return answer;
	}

	int Part2Answer()
	{
		int answer = 0;

		for (auto& line : Day1_Inputs)
		{
			answer += CaluclateCalibration_Part2(line);
		}

		return answer;
	}

	int CaluclateCalibration_Part1(const std::string& line)
	{
		int calibration = 0;

		// This loop handles finding the first digit from the left
		for (size_t i = 0; i < line.size(); i++)
		{
			// Using atoi returns 0 if the const char* isn't a number. This works because our input values will never be a 0
			// We use substring to avoid grouped numbers being referenced as a single char in memory
			int temp = atoi(&line.substr(i, 1)[0]);

			if (temp > 0)
			{
				// We save this number multiplied by 10 because it needs to occupy the left digit of our calibration
				calibration += temp * 10;
				break;
			}
		}

		// This loop handles finding the first digit from the right
		// Using Reverse Iterator loop to avoid initializing i with a .size() - 1 value that could return an invalid value
		for (auto character = line.crbegin(); character != line.crend(); character++)
		{
			int temp = atoi(&character[0]);

			if (temp > 0)
			{
				// This number occupys the right digit and gauranteed to be less than 10
				calibration += temp;
				break;
			}
		}

		return calibration;
	}

	int CaluclateCalibration_Part2(const std::string& line)
	{
		int calibration = 0;

		// We create a substring to keep track of parsed characters
		std::string substring = "";

		// This loop handles finding the first digit from the left
		for (size_t i = 0; i < line.size(); i++)
		{
			// Using atoi returns 0 if the const char* isn't a number. This works because our input values will never be a 0
			// We use substring to avoid grouped numbers being referenced as a single char in memory
			std::string character = line.substr(i, 1);
			int temp = atoi(&character[0]);
			substring += character;

			// We check if the parsed characters contains a Stringified number
			if (substring.size() >= 3)
			{
				for (size_t num = 1; num < 10; num++)
				{
					if (substring.contains(StringNumbers[num - 1]))
					{
						temp = static_cast<int>(num);
						break;
					}
				}
			}


			if (temp > 0)
			{
				// We save this number multiplied by 10 because it needs to occupy the left digit of our calibration
				calibration += temp * 10;
				substring = "";
				break;
			}
		}

		// This loop handles finding the first digit from the right
		// Using Reverse Iterator loop to avoid initializing i with a .size() - 1 value that could return an invalid value
		for (auto character = line.crbegin(); character != line.crend(); character++)
		{
			int temp = atoi(&character[0]);
			substring = *character + substring;

			// We check if the parsed characters contains a Stringified number
			if (substring.size() >= 3)
			{
				for (size_t num = 1; num < 10; num++)
				{
					if (substring.contains(StringNumbers[num - 1]))
					{
						temp = static_cast<int>(num);
						break;
					}
				}
			}

			if (temp > 0)
			{
				// This number occupys the right digit and gauranteed to be less than 10
				calibration += temp;
				break;
			}
		}

		return calibration;
	}
};