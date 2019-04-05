#include "PermutationManager.hxx"

#include <iostream>

using namespace pm;

int main()
{
	PermutationManager pm("aabbc");

	std::cout << "Number of Unique Combinations: " << pm.getNumCombinations() << "\n";

	for (unsigned i = 0u; i < pm.getNumCombinations(); ++i)
	{
		std::cout << i << ":\t" << pm.getPermutation(i) << "\n";
	}


	return 0;
}