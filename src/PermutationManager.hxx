#ifndef PM_PERMUTATION_MANAGER
#define PM_PERMUTATION_MANAGER

#include "PermutationRepresentation.hxx"

#include "InfInt.hxx"

#include <stdexcept>
#include <vector>

namespace pm
{
	template <typename T>
	class PermutationManager
	{
	public:
		PermutationManager(const std::vector<T>& values);
		PermutationManager(const T* values, unsigned numValues);

		// O(str_len * NUM_POSSIBILITIES) = Θ(str_len)
		// Θ(1) if previously calculated
		std::vector<T> getPermutation(InfInt index) const;

		inline InfInt getNumCombinations() const
		{
			return valuesRepresentation.getNumCombinations();
		}

	private:
		const PermutationRepresentation<T> valuesRepresentation;
	};

	template <typename T>
	PermutationManager<T>::PermutationManager(const std::vector<T>& values)
		: valuesRepresentation(values)
	{
	}

	template <typename T>
	PermutationManager<T>::PermutationManager(const T* values, unsigned numValues)
		: valuesRepresentation(values, numValues)
	{
	}

	template <typename T>
	std::vector<T> PermutationManager<T>::getPermutation(InfInt permIndex) const
	{
		// verify permutation index is in range
		if (permIndex < 0 || permIndex >= getNumCombinations())
		{
			throw std::runtime_error("Index out of range: " + permIndex.toString());
		}

		// actually calculate the permutation
		PermutationRepresentation<T> tempRep(valuesRepresentation);

		std::vector<T> permutation;
		permutation.resize(tempRep.getNumValues());

		for (unsigned i = 0u; i < valuesRepresentation.getNumValues(); ++i)
		{
			for (const auto& representation : tempRep.getValueRepresentations())
			{
				if (permIndex < tempRep.getNumSubcombinations(representation.value))
				{
					tempRep.removeValue(representation.value);
					permutation[i] = representation.value;
					break;
				}

				permIndex -= tempRep.getNumSubcombinations(representation.value);
			}
		}

		return permutation;
	}
}

#endif
