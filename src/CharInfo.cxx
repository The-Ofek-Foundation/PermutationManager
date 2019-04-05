#include "CharInfo.hxx"

#include <stdexcept>

using namespace pm;

CharInfo::CharInfo(const std::string& str)
	: counts(NUM_POSSIBILITIES, 0u), numChars(0u), numCombinations(1uLL)
{
	for (char c : str)
	{
		addChar(c);
	}
}

CharInfo::CharInfo(const CharInfo& charInfo)
	: counts(charInfo.counts), numChars(charInfo.numChars),
	  numCombinations(charInfo.numCombinations)
{

}

void CharInfo::addChar(char c)
{
	unsigned count = ++counts[hash(c)];
	++numChars;

	numCombinations = numCombinations * numChars / count;
}

void CharInfo::removeChar(char c)
{
	unsigned& count = counts[hash(c)];

	if (count == 0u)
	{
		throw std::runtime_error("Cannot remove char, already empty: " + c);
	}

	numCombinations = numCombinations * count / numChars;

	--count;
	--numChars;
}

uint64_t CharInfo::getNumSubcombinations(char c) const
{
	return numCombinations * counts[hash(c)] / numChars;
}

char CharInfo::unhash(unsigned c) const
{
	return 'a' + c;
}

unsigned CharInfo::hash(char c) const
{
	if (!isLegalChar(c))
	{
		throw std::runtime_error("Illegal character: " + c);
	}

	return c - 'a';
}

bool CharInfo::isLegalChar(char c)
{
	return c >= 'a' && c <= 'z';
}
