# PermutationManager

Efficiently get distinct permutations of sets by index.

Assigns a unique index to each distinct permutation of a given list.
Can convert to and from a unique index to a distinct permutation.

If the list is originally passed in alphabetically, then the assigned indices will be generated in alphabetical order.

#### Note: This project uses InfInt under the Mozilla Public License, v. 2.0. InfInt.hxx is a super user-friendly and fast arbitrarily-large integer type for C/C++. Check out the source code [here][InfInt Link].

#### Example:

Input list: 'a', 'a', 'b', 'c' has 12 distinct permutations:

0. a a b c
1. a a c b
2. a b a c
3. a b c a
4. a c a b
5. a c b a
6. b a a c
7. b a c a
8. b c a a
9. c a a b
10. c a b a
11. c b a a

Note that since the list was originally in alphabetical order, the indices are assigned in alphabetical order.

## Tutorial

### Creating a PermutationManager object
All the below methods create identical:

```c++

std::vector<int> valuesVector = { 1, 2, 2, 3, 5, 5 };
int * valuesArray  = new int[6] { 1, 2, 2, 3, 5, 5 };

PermutationManager<int> pm1({1, 2, 2, 3, 5, 5}); // implicitly converts {} to std::vector
PermutationManager<int> pm2(valuesVector); // accepts std::vector as argument
PermutationManager<int> pm3(valuesArray, 6); // accepts Type*, numValues as arguments
PermutationManager<int> pm4(valuesVector.begin(), valuesVector.end()); // accepts first, last iterators
PermutationManager<int> pm5(pm1); // accepts PermutationManager object

```

### Using PermutationManager object
The unique indicies assigned to permutations are given as InfInt types, which is an arbitrarily-large integer type. There are implicit conversions from basic integer types to InfInt types.

The following methods are at your disposal:

```c++
// get permutation given a unique permutation index
std::vector<Type> getPermutation(InfInt index);

// get permutation index given a permutation
InfInt getPermutationIndex(const std::vector<Type>& permutation);
InfInt getPermutationIndex(const Type* values, unsigned numValues);
InfInt getPermutationIndex(InputIterator first, InputIterator last);

// get a random unique permutation
std::vector<T> getRandomPermutation(RandomGenerator&& generator);

// get the total number of distinct permutations
InfInt getNumCombinations();
```

#### Example Usage:
Let's say you had the following question:

From all the distinct permutations of the string: "Ofek Gila's website is theofekfoundation.org and you can contact him at webmaster@theofekfoundation.org.", arranged in alphabetical order, what is the index of the original string.

In other words, if you had a list of all the distinct permutations of the characters of the above string, and sorted that (huge) list in alphabetical order, what index of that list would be exactly equal to the original text.

Here's an example of how our PermutationManager class can help answer that question:

```c++
std::string shamelessPlug = "Ofek Gila's website is theofekfoundation.org and you can contact him at webmaster@theofekfoundation.org.";
std::string sortedPlug = shamelessPlug;

// in order to index the permutations in sorted order, the PermutationManager
// input argument should be in sorted order
std::sort(sortedPlug.begin(), sortedPlug.end());
PermutationManager<char> pm(sortedPlug.begin(), sortedPlug.end());

std::cout << "Number of Unique Combinations:\n\t" << pm.getNumCombinations() << "\n\n";

InfInt shamelessPlugPermutationIndex = pm.getPermutationIndex(shamelessPlug.begin(), shamelessPlug.end());

std::cout << "Index of Shameless Plug permutation:\n\t" << shamelessPlugPermutationIndex << "\n\n";

std::cout << "Verify Permutation:\n\t";
for (char c : pm.getPermutation(shamelessPlugPermutationIndex))
{
	std::cout << c;
}
std::cout << "\n";
```

Which outputs the following:
```
Number of Unique Combinations:
	286085711893760574941932554490307792537822145936044875714756621975841562153542497906811500322138510013235200000000000000

Index of Shameless Plug permutation:
	47935447348857562352245753230908866438028901972133563623136599799234774696454727103578770017046189947569576549074289177

Verify Permutation:
	Ofek Gila's website is theofekfoundation.org and you can contact him at webmaster@theofekfoundation.org.
```

In other words, there are over two hundred eighty-six octotrigintillion (2.86 * 10^28) distinct combinations of those characters. The forty-seven octotrigintillion, nine hundred thirty-five septentrigintillion... th one of them, sorted in alphabetical order, is "Ofek Gila's website is theofek...". And this all **runs instantly**!

## Asymptotic Complexity
Here's where the heart of the matter is, how efficient is this really?

 - Initializing PermutationManager object: **Θ(# values)**
 - Getting a specific permutation given an index: **Ω(# values), O(# values * # distinct values)**
 - Getting an index given a specific permutation: **Ω(# values), O(# values * # distinct values)**
 - Get a random permutation: **Θ(# values)**
 - Get a number of distinct combinations: **Θ(1)**


Note that for many use cases, the number of distinct values might be fixed. For example, for an essay limited to ASCII, there are only 256 possible characters. This means that an essay with 10 thousand words will only run for twice as long as an essay with 5 thousand words.

In other words, for a fixed number of possible distinct values, both the latter permutations run in: **Θ(# values)**

In any case, the first permutation (index 0), runs in Θ(# values) time for both getting the permutation or reverse-getting the index due to the nature of this algorithm. This is how getting a random permutation is always **Θ(# values)**.

[InfInt Link]: https://github.com/sercantutar/infint/blob/master/InfInt.h "InfInt source code"
