#ifndef PM_CHARINFO
#define PM_CHARINFO

#include <cstdint>
#include <string>
#include <vector>

namespace pm
{
	class CharInfo
	{
	public:
		static const unsigned NUM_POSSIBILITIES = 26u;

		CharInfo(const std::string& str); // Θ(str_length)
		CharInfo(const CharInfo& charInfo); // Θ(NUM_POSSIBILITIES) = Θ(1)

		void addChar(char c); // Θ(1)
		void removeChar(char c); // Θ(1)

		uint64_t getNumCombinations() const
		{
			return numCombinations;
		}

		unsigned getNumCharacters() const
		{
			return numChars;
		}

		uint64_t getNumSubcombinations(char c) const;

		char unhash(unsigned hash) const;

	private:
		std::vector<unsigned> counts;
		unsigned numChars = 0u;
		uint64_t numCombinations;

		unsigned hash(char c) const;
		static bool isLegalChar(char c);
	};
}

#endif
