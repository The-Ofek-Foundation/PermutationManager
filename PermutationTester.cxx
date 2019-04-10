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

	std::string myStr = "            !'Raaaaaaaaccddeeeeeeegghhiiijkmmnnnoooprssssstttuuvvw";

	PermutationManager<char> pm(myStr.begin(), myStr.end());


	printPermutation(pm.getPermutation("60777544677604899641470067442790386864247604236308303175748360083677"));

	// std::cout << "Number of distinct permutations:\n\t" << pm.getNumPermutations() << "\n";

	// InfInt index = pm.getPermutationIndex("Raghav is awesome and just gave me a cookie and that's super nice!", myStr.size());

	// std::cout << "Specific Permutation #:\n\t" << index << "\n";

	return 0;
}
