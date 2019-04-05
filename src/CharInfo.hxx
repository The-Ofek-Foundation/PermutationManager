#ifndef PM_CHARINFO
#define PM_CHARINFO

#include <cstdint>

class CharInfo
{
private:
	int counts[26u] = { 0 };
	unsigned numChars = 0u;
	uint64_t numPossiblePermutations;
};

#endif
