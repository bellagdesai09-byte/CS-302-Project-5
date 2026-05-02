# ADT Design: Dictionary and Hash Table

## Purpose
The primary purpose of this ADT is to act as a highly efficient, high-speed dictionary for counting word frequencies across a massive dataset. For this project, I need to take the 157,000 words in the SICP text and accurately count how many times each specific word appears. Because of the sheer volume of data, scanning through a standard array or even traversing a binary search tree takes too long. The Hash Table is designed to provide an average O(1) time complexity, allowing me to instantly drop a word into its designated "test tube" (bucket) or pull its current frequency without waiting around.
## Logical Data Model
At a conceptual level, this data model is a collection of strict key-value pairs.

* The Key is a unique string (a specific word parsed from the text).

* The Value is an integer representing the frequency count of that word.

A core rule of this data model is that every key must be entirely unique—no duplicate words are allowed as standalone entries. If a key that is already in the dictionary is processed again, the model dictates that we update its existing value (incrementing the count) rather than appending a new, redundant entry.
## Operations
The ADT guarantees the following core behaviors to interact with the data:

* insert(key): Computes the hash for the incoming word to instantly locate its bucket. If the word is already sitting in that collision chain, it increments the frequency value by 1. If it’s not there, it adds the word as a brand new entry with a count of 1.

* find(key): Takes a search word, hashes it to jump directly to its bucket, and searches the resulting chain. It returns the integer frequency if the word is found, or 0 if the word isn't in the table.

* getLoadFactor(): Returns a fractional metric showing how "full" the table is by dividing the total number of unique entries by the fixed table size.

* Diagnostic Checks (getLongestChain, getShortestChain, getAverageChainLength): These operations scan the underlying buckets to evaluate collision distribution. They are crucial for measuring how effectively the data is spread out across the table.

* getAllEntries(): Extracts every key-value pair from the table into a linear structure, allowing the data to be sorted and analyzed (such as finding the top 20 most frequent words)
## Hash Functions at the ADT Level
At the ADT level, a hash function is essentially a deterministic mapping protocol. It takes an arbitrary-length data input (the string key) and runs it through a mathematical formula to output a valid integer index strictly bounded by the size of the table (from 0 to tableSize - 1).

For the dictionary to maintain its O(1) efficiency, the hash function's job is to distribute the keys as uniformly as possible across the available buckets to prevent clustering. In this implementation, I am evaluating two specific mapping protocols: a basic modHash (which simply sums ASCII values) and hornerHash (a position-sensitive polynomial calculation using base 31), which acts as the optimized method to cleanly separate anagrams and reduce collisions.