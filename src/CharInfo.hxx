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

		void addChar(char c); // Θ(1)
		void removeChar(char c);

	private:
		std::vector<unsigned> counts;
		unsigned numChars = 0u;
		uint64_t numCombinations;

		uint64_t calcNumCombinations() const;

		unsigned hash(char c) const;

		static bool isLegalChar(char c);
	};
}

#endif
