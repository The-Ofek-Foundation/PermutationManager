#include "PermutationManager.hxx"

#include "InfInt.hxx"

#include <cstring>
#include <iostream>
#include <vector>

using namespace pm;

template <typename T>
void printPermutation(const std::vector<T>& permutation)
{
	for (const auto& value : permutation)
	{
		std::cout << value << " ";
	}

	std::cout << "\n";
}

int main()
{
	PermutationManager<char> pm({'a', 'a', 'b', 'b', 'c'});

	std::cout << "Number of Unique Combinations: " << pm.getNumCombinations() << "\n";

	for (InfInt i = 0; i < pm.getNumCombinations(); ++i)
	{
		printPermutation(pm.getPermutation(i));
	}

	PermutationManager<int> pmInt({2, 1, 6, 7, 5, 9, 5, 0, 1, 4});

	std::cout << "Number of Unique Combinations: " << pmInt.getNumCombinations() << "\n";

	for (InfInt i = 0; i < 10u; ++i)
	{
		printPermutation(pmInt.getPermutation(i));
	}


	PermutationManager<char> pm2("my name is jeffrey, what's yours?", strlen("my name is jeffrey, what's yours?"));

	std::cout << "Number of Unique Combinations: " << pm2.getNumCombinations() << "\n";

	const auto& permutation = pm2.getPermutation(673498235uLL);

	printPermutation(permutation);

	std::cout << pm2.getPermutationIndex(permutation) << "\n";

	printPermutation(pm2.getRandomPermutation());

	return 0;
}
