#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "burrows-wheeler-transform.hpp"

const int MAX_CHARACTER = 255;
const char MIN_CHARACTER = 0;

struct Suffix
{
	int index;
	int rank[2];
};

bool cmp(Suffix a, Suffix b)
{
	return a.rank[0] == b.rank[0] ? a.rank[1] < b.rank[1] : a.rank[0] < b.rank[0];
}

bool equal(Suffix a, Suffix b)
{
	return a.rank[0] == b.rank[0] && a.rank[1] == b.rank[1];
}

std::vector<Suffix> CreateSuffixes(std::string s)
{
	int n = s.length();

	std::vector<Suffix> suffixes(n);
	for (int i = 0; i < n; ++i)
	{
		suffixes[i].index = i;
		suffixes[i].rank[0] = s[i];
		if (i != n - 1)
			suffixes[i].rank[1] = s[i + 1];
		else
			suffixes[i].rank[1] = -1;
	}

	std::vector<int> index(n);
	for (int k = 2; k < n * 2; k *= 2)
	{
		sort(suffixes.begin(), suffixes.end(), cmp);

		int max_rank = 0;
		suffixes[0].rank[0] = max_rank;
		index[suffixes[0].index] = 0;

		for (int i = 1; i < n; ++i)
		{
			index[suffixes[i].index] = i;
			if (!equal(suffixes[i], suffixes[i - 1]))
			{
				++max_rank;
			}
			suffixes[i].rank[0] = max_rank;
		}
		for (int i = 0; i < n; ++i)
		{
			if (suffixes[i].index + k < n)
				suffixes[i].rank[1] = suffixes[index[suffixes[i].index + k]].rank[0];
			else
				suffixes[i].rank[1] = -1;
		}
		std::sort(suffixes.begin(), suffixes.end(), cmp);
	}
	return suffixes;
}

std::string Encode(std::string s)
{
	s += MIN_CHARACTER;
	std::vector<Suffix> suffixes = CreateSuffixes(s);
	std::string r = "";
	for (Suffix suffix : suffixes)
	{
		if (suffix.index == 0)
			r += MIN_CHARACTER;
		else
			r += s[suffix.index - 1];
	}
	return r;
}

std::string Decode(std::string s)
{
	// Init
	int amount[MAX_CHARACTER] = {0};
	int position[MAX_CHARACTER] = {0};

	int n = s.size();

	for (char c : s)
		++amount[(int)c];
	int x = 0;
	for (int i = 0; i < MAX_CHARACTER; ++i)
	{
		if (amount[i] > 0)
		{
			position[i] = x;
			x += amount[i];
			amount[i] = 0;
		}
	}

	std::vector<int> l;
	for (int i = 0; i < n; ++i)
		l.push_back(amount[(int)s[i]]++);

	std::string r = "";
	x = 0;
	while (1)
	{
		if (r.length() == s.length())
			break;
		if (s[x] == MIN_CHARACTER)
			break;
		r += s[x];
		x = position[(int)s[x]] + l[x];
	}
	reverse(r.begin(), r.end());
	return r;
}
