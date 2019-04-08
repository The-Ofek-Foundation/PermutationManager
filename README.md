# PermutationManager
Efficiently get distinct permutations of sets by index.

Assigns a unique index to each distinct permutation of a given list.
Can convert to and from a unique index to a distinct permutation.

If the list is originally passed in alphabetically, then the assigned indices will be generated in alphabetical order.

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
