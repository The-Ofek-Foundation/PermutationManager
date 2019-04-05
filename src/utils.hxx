#ifndef PM_UTILS
#define PM_UTILS

#include "InfInt.h"
#include <vector>

namespace pm
{
	InfInt factorial(unsigned num)
	{
		static std::vector<InfInt> factorials{"1"};

		for (unsigned i = factorials.size(); i <= num; ++i)
		{
			factorials.emplace_back(factorials[i - 1u]);
			factorials[i] *= i;
		}

		return factorials[num];
	}
}

#endif
