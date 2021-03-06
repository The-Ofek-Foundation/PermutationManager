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
		template <typename InputIterator>
		PermutationRepresentation(InputIterator first, InputIterator last); // Θ(num_values)
		PermutationRepresentation(const PermutationRepresentation<T>& pr); // Θ(num_distinct_values)

		bool operator == (const PermutationRepresentation<T>& pr) const;
		bool operator != (const PermutationRepresentation<T>& pr) const;

		void addValue(const T& value); // Θ(1)
		void removeValue(const T& value); // Θ(1)

		InfInt getNumPermutations() const
		{
			return numPermutations;
		}

		unsigned getNumValues() const
		{
			return numValues;
		}

		InfInt getNumSubpermutations(const T& value) const; // Θ(1)

		const std::vector<ValueRepresentation>& getValueRepresentations() const
		{
			return representations;
		}

	private:
		std::vector<ValueRepresentation> representations;
		std::unordered_map<T, unsigned> indices;
		unsigned numValues = 0u;
		InfInt numPermutations;
	};

	template <typename T>
	PermutationRepresentation<T>::PermutationRepresentation(const std::vector<T>& values)
	    : PermutationRepresentation(values.begin(), values.end())
	{
	}

	template <typename T>
	PermutationRepresentation<T>::PermutationRepresentation(const T* values, unsigned numValues)
	    : PermutationRepresentation(&values[0u], &values[numValues])
	{
	}

	template <typename T>
	template <typename InputIterator>
	PermutationRepresentation<T>::PermutationRepresentation(InputIterator first, InputIterator last)
		: representations({}), indices({}), numValues(0u), numPermutations(1)
	{
		for (; first != last; ++first)
		{
			addValue(*first);
		}
	}

	template <typename T>
	PermutationRepresentation<T>::PermutationRepresentation(const PermutationRepresentation<T>& pr)
		: representations(pr.representations), indices(pr.indices),
		  numValues(pr.numValues), numPermutations(pr.numPermutations)
	{
	}

	template <typename T>
	bool PermutationRepresentation<T>::operator == (const PermutationRepresentation<T>& pr) const
	{
		if (representations.size() != pr.representations.size()
		 || numValues != pr.numValues)
		{
			return false;
		}

		for (const auto& representation : representations)
		{
			const auto& iterator = pr.indices.find(representation.value);

			if (iterator == pr.indices.end())
			{
				return false;
			}

			if (representation.count != pr.representations[iterator->second].count)
			{
				return false;
			}
		}

		return true;
	}

	template <typename T>
	bool PermutationRepresentation<T>::operator != (const PermutationRepresentation<T>& pr) const
	{
		return !(*this == pr);
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

		numPermutations = numPermutations * numValues / count;
	}

	template <typename T>
	void PermutationRepresentation<T>::removeValue(const T& value)
	{
		unsigned& count = representations[indices.at(value)].count;

		if (count == 0u)
		{
			throw std::runtime_error("Cannot remove value, already empty: " + value);
		}

		numPermutations = numPermutations * count / numValues;

		--count;
		--numValues;
	}

	template <typename T>
	InfInt PermutationRepresentation<T>::getNumSubpermutations(const T& value) const
	{
		unsigned count = representations[indices.at(value)].count;

		if (count == 0u)
		{
			return 0;
		}

		return numPermutations * count / numValues;
	}
}

#endif
