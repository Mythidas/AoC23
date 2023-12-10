#pragma once

#include "AdventDay.h"
#include "Inputs/I_Day7.h"

#include <unordered_map>

// Using a struct to easily pack logic for sorting later
struct Hand
{
	std::string Cards;
	int Bid;
	bool UseJokers = false;
	enum class HandType : int
	{
		FiveOAK		= 7,
		FourOAK		= 6,
		FullHouse	= 5,
		ThreeOAK	= 4,
		TwoPair		= 3,
		OnePair		= 2,
		HighCard	= 1
	} Type;

	Hand(const std::string& cards, int bid, bool jokers)
		: Cards(cards), Bid(bid), UseJokers(jokers)
	{
		// We use a map to count cards and assign a hand type
		std::unordered_map<char, int> cardCounts;

		for (auto& card : cards)
		{
			cardCounts[card]++;
		}

		// If we use a deck with joker rules we rig use the jokers to best win the hand
		if (UseJokers)
		{
			// We keep track of the highest card count and strength
			int highCount = 0;
			char card = 'B';
			for (auto& count : cardCounts)
			{
				if (count.first == 'J') continue;

				// We set a card if its the highest cound or the same count but greater strength
				if (count.second > highCount || (count.second == highCount && GetCardStrength(count.first) > GetCardStrength(card)))
				{
					highCount = count.second;
					card = count.first;
				}
			}

			// Add the jokers to the best card and remove them from the cardCounts
			if (cardCounts.contains('J'))
			{
				cardCounts[card] += cardCounts['J'];
				cardCounts.erase('J');
			}
		}

		// Every hand type has somethig unique that identifies it
		if (cardCounts.size() == 5)
		{
			Type = HandType::HighCard;
		}
		else if (cardCounts.size() == 4)
		{
			Type = HandType::OnePair;
		}
		else if (cardCounts.size() == 1)
		{
			Type = HandType::FiveOAK;
		}
		else if (cardCounts.size() == 2)
		{
			int highCount = 0;
			for (auto& count : cardCounts)
			{
				if (count.second > highCount)
					highCount = count.second;
			}

			if (highCount == 4)
				Type = HandType::FourOAK;
			else
				Type = HandType::FullHouse;
		}
		else
		{
			int highCount = 0;
			for (auto& count : cardCounts)
			{
				if (count.second > highCount)
					highCount = count.second;
			}

			if (highCount == 3)
				Type = HandType::ThreeOAK;
			else
				Type = HandType::TwoPair;
		}
	}

	int GetCardStrength(char card) const
	{
		// We set jokers to the lowest strength when using joker rules
		switch (card)
		{
		case 'A': return 13;
		case 'K': return 12;
		case 'Q': return 11;
		case 'J': return UseJokers ? 0 : 10;
		case 'T': return 9;
		case '9': return 8;
		case '8': return 7;
		case '7': return 6;
		case '6': return 5;
		case '5': return 4;
		case '4': return 3;
		case '3': return 2;
		case '2': return 1;
		default: return 0;
		}
	}

	bool operator>(const Hand& rhs) const
	{
		if (Type > rhs.Type) return true;
		if (Type < rhs.Type) return false;

		for (size_t i = 0; i < 5; i++)
		{
			int lhsCard = GetCardStrength(Cards[i]);
			int rhsCard = GetCardStrength(rhs.Cards[i]);
			if (lhsCard > rhsCard) return true;
			if (lhsCard < rhsCard) return false;
		}

		return false;
	}

	bool operator<(const Hand& rhs) const
	{
		if (Type < rhs.Type) return true;
		if (Type > rhs.Type) return false;

		for (size_t i = 0; i < 5; i++)
		{
			int lhsCard = GetCardStrength(Cards[i]);
			int rhsCard = GetCardStrength(rhs.Cards[i]);
			if (lhsCard < rhsCard) return true;
			if (lhsCard > rhsCard) return false;
		}

		return false;
	}
};

class Day7 : public AdventDay
{
public:
	virtual void PrintAnswer() override
	{
		Timer timer;
		int part1 = Part1Answer();
		int part2 = Part2Answer();
		std::cout << "Day7: (Time to run: " << timer.Elapsed() << ")" << std::endl;
		std::cout << "  Part1 Answer: " << part1 << std::endl;
		std::cout << "  Part2 Answer: " << part2 << std::endl;
		std::cout << std::endl;
	}

private:
	int Part1Answer()
	{
		int answer = 0;

		m_Hands.clear();
		// We first create the hands for the inputs
		for (auto& line : Day7_Inputs)
		{
			std::string hand(line);
			Hand current(hand.substr(0, 5), atoi(hand.substr(5).c_str()), false);
			m_Hands.push_back(current);
		}

		// We use a quicksort algorithm to arrange the array in descending order
		QuickSort(m_Hands, 0, static_cast<int>(m_Hands.size() - 1));

		// We reverse iterate over the vector but it could be done the other direction by setting rank to 1 and using rank++
		int rank = static_cast<int>(m_Hands.size());
		for (auto hand = m_Hands.crbegin(); hand != m_Hands.crend(); hand++)
		{
			answer += hand->Bid * rank;
			rank--;
		}

		return answer;
	}

	int Part2Answer()
	{
		m_Hands.clear();
		// We first create the hands for the inputs
		for (auto& line : Day7_Inputs)
		{
			std::string hand(line);
			Hand current(hand.substr(0, 5), atoi(hand.substr(5).c_str()), true);
			m_Hands.push_back(current);
		}

		// We use a quicksort algorithm to arrange the array in descending order
		QuickSort(m_Hands, 0, static_cast<int>(m_Hands.size() - 1));

		int answer = 0;

		// We reverse iterate over the vector but it could be done the other direction by setting rank to 1 and using rank++
		int rank = static_cast<int>(m_Hands.size());
		for (auto hand = m_Hands.crbegin(); hand != m_Hands.crend(); hand++)
		{
			answer += hand->Bid * rank;
			rank--;
		}

		return answer;
	}

	void QuickSort(std::vector<Hand>& hands, int low, int high)
	{
		if (low < high)
		{
			int pi = Partition(hands, low, high);

			QuickSort(hands, low, pi - 1);
			QuickSort(hands, pi + 1, high);
		}
	}

	int Partition(std::vector<Hand>& hands, int low, int high)
	{
		Hand pivot = hands[high];
		int i = low - 1;

		for (int j = low; j <= high; j++)
		{
			if (hands[j] < pivot)
			{
				i++;
				std::swap(hands[i], hands[j]);
			}
		}
		std::swap(hands[static_cast<size_t>(i + 1)], hands[high]);
		return i + 1;
	}

private:
	std::vector<Hand> m_Hands;
};