#include "PermutationManager.hxx"

#include <stdexcept>
#include <string>

using namespace pm;

PermutationManager::PermutationManager(const std::string& str)
	: strInfo(str)
{
	permutations.resize(getNumCombinations());
}

const std::string& PermutationManager::getPermutation(uint64_t index) const
{
	// verify permutation index is in range
	if (index > getNumCombinations())
	{
		throw std::runtime_error("Index out of range: " + index);
	}

	// return permutation if already calculated
	if (permutations[index].size() == strInfo.getNumCharacters())
	{
		return permutations[index];
	}

	// actually calculate the permutation
	std::string permutation = "";
	CharInfo tempInfo(strInfo);

	for (unsigned i = 0u; i < strInfo.getNumCharacters(); ++i)
	{
		unsigned charIndex;
		char c;

		for (charIndex = 0u, c = strInfo.unhash(charIndex); index >= tempInfo.getNumSubcombinations(c); ++charIndex, c = strInfo.unhash(charIndex))
		{
			index -= tempInfo.getNumSubcombinations(c);
		}

		tempInfo.removeChar(c);
		permutation += c;
	}

	return permutations[index] = permutation;
}
