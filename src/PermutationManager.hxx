#ifndef PM_PERMUTATION_MANAGER
#define PM_PERMUTATION_MANAGER

#include "PermutationRepresentation.hxx"

#include "InfInt.hxx"

#include <algorithm>
#include <random>
#include <stdexcept>
#include <vector>

namespace pm
{
	//
	// Many of these operations technically run in O(num_values²), but in practice
	// will run in linear time (O(num_values)). This is because they run in the worst
	// case proportional to num_values * num_distinct_values. If you are only dealing
	// with ASCII, for example, with 256 possible characters, then this will run in
	// text_length * 256, where the 256 does not affect the asymptotic running time.
	// Meaning that an essay with 10,000 characters will take twice as long as an essay
	// with 5,000 characters, not 4 times as long.
	//
	// The worst case of num_values² only occurs if all the values are distinct, and
	// you are looking for an unlucky permutation.
	//
	template <typename T>
	class PermutationManager
	{
	public:
		// Θ(num_values)
		PermutationManager(const std::vector<T>& values);
		PermutationManager(const T* values, unsigned numValues);
		template <typename InputIterator>
		PermutationManager(InputIterator first, InputIterator last);
		PermutationManager(const PermutationManager& pm);

		// O(num_values * num_distinct_values) = Ω(num_values), O(num_values²)
		std::vector<T> getPermutation(InfInt index) const;

		// Θ(num_values)
		template <typename RandomGenerator>
		std::vector<T> getRandomPermutation(RandomGenerator&& generator) const;

		// O(num_values * num_distinct_values) = Ω(num_values), O(num_values²)
		InfInt getPermutationIndex(const std::vector<T>& permutation) const;
		InfInt getPermutationIndex(const T* values, unsigned numValues) const;
		template <typename InputIterator>
		InfInt getPermutationIndex(InputIterator first, InputIterator last) const;

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
	template <typename InputIterator>
	PermutationManager<T>::PermutationManager(InputIterator first, InputIterator last)
		: valuesRepresentation(first, last)
	{
	}

	template <typename T>
	PermutationManager<T>::PermutationManager(const PermutationManager& pm)
		: valuesRepresentation(pm.valuesRepresentation)
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

	template <typename T>
	template <typename RandomGenerator>
	std::vector<T> PermutationManager<T>::getRandomPermutation(RandomGenerator&& generator) const
	{
		std::vector<T> permutation = getPermutation(0);
		std::shuffle(permutation.begin(), permutation.end(), generator);
		return permutation;
	}

	template <typename T>
	InfInt PermutationManager<T>::getPermutationIndex(const std::vector<T>& permutation) const
	{
		return getPermutationIndex(permutation.begin(), permutation.end());
	}

	template <typename T>
	InfInt PermutationManager<T>::getPermutationIndex(const T* values, unsigned numValues) const
	{
		return getPermutationIndex(&values[0u], &values[numValues]);
	}

	template <typename T>
	template <typename InputIterator>
	InfInt PermutationManager<T>::getPermutationIndex(InputIterator first, InputIterator last) const
	{
		PermutationRepresentation<T> tempRep(valuesRepresentation);
		InfInt permIndex = 0;

		for (; first != last; ++first)
		{
			const T& value = *first;

			for (const auto& representation : tempRep.getValueRepresentations())
			{
				if (representation.value == value)
				{
					break;
				}

				permIndex += tempRep.getNumSubcombinations(representation.value);
			}

			tempRep.removeValue(value);
		}

		return permIndex;
	}
}

#endif
