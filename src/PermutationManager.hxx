#ifndef PM_PERMUTATION_MANAGER
#define PM_PERMUTATION_MANAGER

#include "CharInfo.hxx"

#include <string>
#include <vector>

namespace pm
{
	class PermutationManager
	{
	public:
		PermutationManager(const std::string& str);

		// O(str_len * NUM_POSSIBILITIES) = Θ(str_len)
		const std::string& getPermutation(uint64_t index) const;

		inline uint64_t getNumCombinations() const
		{
			return strInfo.getNumCombinations();
		}

	private:
		const CharInfo strInfo;
		mutable std::vector<std::string> permutations;
	};
}

#endif
