#include "CharInfo.hxx"

#include "utils.hxx"

#include "InfInt.hxx"

#include <cstring>
#include <stdexcept>

using namespace pm;

CharInfo::CharInfo(const std::string& str)
	: counts(NUM_POSSIBILITIES, 0u), numChars(str.size()), numCombinations(0uLL)
{
	for (char c : str)
	{
		addChar(c);
	}
}

void addChar(char c)
{
	unsigned count = ++counts[hash(c)];
	++numChars;

	numCombinations = numCombinations * numChars / count;
}

uint64_t CharInfo::calcNumCombinations() const
{
	InfInt numCombinations = factorial(numChars);

	for (unsigned count : counts)
	{
		numCombinations /= factorial(count);
	}

	return numCombinations.toUnsignedLongLong();
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
