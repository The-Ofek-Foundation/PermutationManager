#ifndef PM_CHARINFO
#define PM_CHARINFO

#include "InfInt.hxx"

#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace pm
{
	template <typename T>
	class PermutationRepresentation
	{
	public:
		struct ValueRepresentation
		{
			const T value;
			unsigned count = 1u;
		};

		PermutationRepresentation(const std::vector<T>& values); // Θ(num_values)
		PermutationRepresentation(const T* values, unsigned numValues); // Θ(num_values)
		PermutationRepresentation(const PermutationRepresentation<T>& pr); // Θ(num_unique_values)

		void addValue(const T& value); // Θ(1)
		void removeValue(const T& value); // Θ(1)

		InfInt getNumCombinations() const
		{
			return numCombinations;
		}

		unsigned getNumValues() const
		{
			return numValues;
		}

		InfInt getNumSubcombinations(const T& value) const;

		const std::vector<ValueRepresentation>& getValueRepresentations() const
		{
			return representations;
		}

	private:

		std::vector<ValueRepresentation> representations;
		std::unordered_map<T, unsigned> indices;
		unsigned numValues = 0u;
		InfInt numCombinations;
	};

	template <typename T>
	PermutationRepresentation<T>::PermutationRepresentation(const std::vector<T>& values)
		: representations({}), indices({}), numValues(0u), numCombinations(1)
	{
		for (const T& value : values)
		{
			addValue(value);
		}
	}

	template <typename T>
	PermutationRepresentation<T>::PermutationRepresentation(const T* values, unsigned numValues)
		: representations({}), indices({}), numValues(0u), numCombinations(1)
	{
		for (unsigned i = 0u; i < numValues; ++i)
		{
			addValue(values[i]);
		}
	}

	template <typename T>
	PermutationRepresentation<T>::PermutationRepresentation(const PermutationRepresentation<T>& pr)
		: representations(pr.representations), indices(pr.indices),
		  numValues(pr.numValues), numCombinations(pr.numCombinations)
	{
	}

	template <typename T>
	void PermutationRepresentation<T>::addValue(const T& value)
	{
		// assume it doesn't exist
		const auto& returnedPair = indices.emplace(value, representations.size());

		unsigned count;

		if (returnedPair.second)
		{
			// was successfully added, so it is a new item
			representations.push_back({ value });
			count = 1u;
		}
		else
		{
			// was not succesfully added, meaning it already exists
			count = ++representations[returnedPair.first->second].count;
		}

		++numValues;

		numCombinations = numCombinations * numValues / count;
	}

	template <typename T>
	void PermutationRepresentation<T>::removeValue(const T& value)
	{
		unsigned& count = representations[indices.at(value)].count;

		if (count == 0u)
		{
			throw std::runtime_error("Cannot remove value, already empty: " + value);
		}

		numCombinations = numCombinations * count / numValues;

		--count;
		--numValues;
	}

	template <typename T>
	InfInt PermutationRepresentation<T>::getNumSubcombinations(const T& value) const
	{
		unsigned count = representations[indices.at(value)].count;

		if (count == 0u)
		{
			return 0;
		}

		return numCombinations * count / numValues;
	}
}

#endif
