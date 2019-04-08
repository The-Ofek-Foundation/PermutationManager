#include "src/PermutationManager.hxx"

#include <cstring>
#include <iostream>
#include <random>
#include <string>
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
	// PermutationManager<char> pm({'a', 'a', 'b', 'c'});

	// std::cout << "Number of Unique Combinations: " << pm.getNumCombinations() << "\n";

	// for (InfInt i = 0; i < pm.getNumCombinations(); ++i)
	// {
	// 	printPermutation(pm.getPermutation(i));
	// }

	// PermutationManager<int> pmInt({2, 1, 6, 7, 5, 9, 5, 0, 1, 4});

	// std::cout << "Number of Unique Combinations: " << pmInt.getNumCombinations() << "\n";

	// for (InfInt i = 0; i < 10u; ++i)
	// {
	// 	printPermutation(pmInt.getPermutation(i));
	// }


	// PermutationManager<char> pm2("     ',?aaeeeffhiJmmnorrssstuwyyy", strlen("     ',?aaeeeffhijmmnorrssstuwyyy"));

	// std::cout << "Number of Unique Combinations: " << pm2.getNumCombinations() << "\n";

	// const auto& permutation = pm2.getPermutation(673498235uLL);

	// printPermutation(permutation);

	// std::cout << pm2.getPermutationIndex(permutation) << "\n";

	// InfInt spookyIndex = pm2.getPermutationIndex("my name is Jeffrey, what's yours?", strlen("     ',?aaeeeffhijmmnorrssstuwyyy"));

	// std::cout << spookyIndex << ": ";
	// printPermutation(pm2.getPermutation(spookyIndex));

	// std::random_device rd;
	// std::mt19937 g(rd());

	// printPermutation(pm2.getRandomPermutation(g));

	// std::vector<int> v = {-1, 2, -3, -3};
	// PermutationManager<int> pm3(v.begin(), v.end());

	// printPermutation(pm3.getPermutation(0u));
	// std::cout << pm3.getPermutationIndex({2, -1, -3, -3}) << "\n";

	std::string shamelessPlug = "Ofek Gila's website is theofekfoundation.org and you can contact him at webmaster@theofekfoundation.org.";
	std::string sortedPlug = shamelessPlug;
	std::sort(sortedPlug.begin(), sortedPlug.end());

	PermutationManager<char> pm(sortedPlug.begin(), sortedPlug.end());
	std::cout << "Number of Unique Combinations:\n\t" << pm.getNumCombinations() << "\n\n";

	InfInt shamelessPlugPermutationIndex = pm.getPermutationIndex(shamelessPlug.begin(), shamelessPlug.end());

	std::cout << "Index of Shameless Plug permutation:\n\t" << shamelessPlugPermutationIndex << "\n\n";

	std::cout << "Verify Permutation:\n\t";
	for (char c : pm.getPermutation(shamelessPlugPermutationIndex))
	{
		std::cout << c;
	}
	std::cout << "\n\n";

	return 0;
}
