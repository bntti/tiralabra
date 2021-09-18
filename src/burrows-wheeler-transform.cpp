/**
 * @file burrows-wheeler-transform.cpp
 * @author Juho Röyskö
 * @brief Burrows-Wheeler transform
 * @version 0.1.1
 * @date 2021-09-17
 */
#include <string>
#include <vector>
#include <algorithm>

const int ALPHABET_SIZE = 128;
const char MIN_CHARACTER = 0;

/**
 * @brief Suffix struct
 */
struct Suffix
{
	int index;
	int rank[2];
};

/**
 * @brief Comparison function for suffixes
 * 
 * @param a Suffix 1
 * @param b Suffix 2
 * @return true If the first suffixes ranks are smaller than the second one's
 * @return false Otherwise.
 */
bool Compare(Suffix a, Suffix b)
{
	return a.rank[0] == b.rank[0] ? a.rank[1] < b.rank[1] : a.rank[0] < b.rank[0];
}

/**
 * @brief Check if two suffixes have the same ranks
 * 
 * @param a Suffix 1
 * @param b Suffix 2
 * @return true If both suffixes have the same ranks
 * @return false Otherwise
 */
bool SameRanks(Suffix a, Suffix b)
{
	return a.rank[0] == b.rank[0] && a.rank[1] == b.rank[1];
}

/**
 * @brief Create suffix array in O(nlog(n)log(n))
 * 
 * @param input String to create suffix array form
 * @return std::vector<Suffix> Suffix array
 */
std::vector<Suffix> CreateSuffixes(std::string input)
{
	int len = input.length();

	// Rank according to first and second letter from i
	std::vector<Suffix> suffixes(len);
	for (int i = 0; i < len; ++i)
	{
		suffixes[i].index = i;
		suffixes[i].rank[0] = input[i];
		if (i != len - 1)
			suffixes[i].rank[1] = input[i + 1];
		else
			suffixes[i].rank[1] = -1;
	}

	std::sort(suffixes.begin(), suffixes.end(), Compare);

	// Rank according to place in sorted array and place of suffix starting from i + k
	std::vector<int> index(len);
	for (int k = 2; k < len * 2; k *= 2)
	{
		int max_rank = 0;
		suffixes[0].rank[0] = max_rank;
		index[suffixes[0].index] = 0;

		// Get Rank[0] for all suffixes
		for (int i = 1; i < len; ++i)
		{
			index[suffixes[i].index] = i;
			if (!SameRanks(suffixes[i], suffixes[i - 1]))
			{
				++max_rank;
			}
			suffixes[i].rank[0] = max_rank;
		}

		// Get Rank[1] for all suffixes
		for (int i = 0; i < len; ++i)
		{
			if (suffixes[i].index + k < len)
				suffixes[i].rank[1] = suffixes[index[suffixes[i].index + k]].rank[0];
			else
				suffixes[i].rank[1] = -1;
		}
		std::sort(suffixes.begin(), suffixes.end(), Compare);
	}
	return suffixes;
}

/**
 * @brief Encode string in O(nlog(n)log(n))
 * 
 * @param input String to encode
 * @return std::string Encoded string
 */
std::string BWTEncode(std::string input)
{
	// Get suffix array
	input += MIN_CHARACTER;
	std::vector<Suffix> suffixes = CreateSuffixes(input);

	// Encode using suffix array
	std::string encoded = "";
	for (Suffix suffix : suffixes)
	{
		if (suffix.index == 0)
			encoded += MIN_CHARACTER;
		else
			encoded += input[suffix.index - 1];
	}
	return encoded;
}

/**
 * @brief Decode string in O(n + alphabet size)
 * 
 * @param input String to decode
 * @return std::string Decoded string
 */
std::string BWTDecode(std::string input)
{
	// Init
	int amount[ALPHABET_SIZE] = {0};   // Amount of character
	int position[ALPHABET_SIZE] = {0}; // Starting position of char in sorted array

	int len = input.length();

	for (char c : input)
		++amount[(int)c];
	int pos = 0;
	for (int i = 0; i < ALPHABET_SIZE; ++i)
	{
		if (amount[i] > 0)
		{
			position[i] = pos;
			pos += amount[i];
			amount[i] = 0;
		}
	}

	std::vector<int> l;
	for (int i = 0; i < len; ++i)
		l.push_back(amount[(int)input[i]]++);

	// Decode
	std::string decoded = "";
	pos = 0;
	while (1)
	{
		if (input[pos] == MIN_CHARACTER)
			break;
		decoded += input[pos];
		pos = position[(int)input[pos]] + l[pos];
	}
	reverse(decoded.begin(), decoded.end());
	return decoded;
}
