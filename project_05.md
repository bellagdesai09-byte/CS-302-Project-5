# CS 302 – Project 5
## Word Frequency Analyzer (Dictionary and Hash Table)

**Assigned:** Thursday, April 17
**Due:** Wednesday, April 30

---

## Overview

In this project you will build a hash table-backed dictionary and use it to analyze the word frequency of a classic computer science text. You will implement two different hash functions, compare their behavior on real data, and reflect on what the numbers tell you about the design choices behind each one.

This is one of the most practical data structures you will encounter. Every major programming language ships a hash-based dictionary as a first-class type. By the end of this project you will understand exactly what is happening under the hood when you write `unordered_map` in C++ or `dict` in Python.

---

## How This Builds on Previous Projects

### From Projects 1 through 4

The structural expectations you have built up over the semester continue here:

- Multi-file C++ with `.h` and `.cpp` separation
- Interface-driven design
- Makefile builds
- Coding standards

### The New Idea

Every project this semester has been about finding things efficiently. BSTs gave us O(log n) by exploiting ordering. Heaps gave us O(1) access to the maximum by exploiting a structural invariant.

Hashing asks a completely different question: what if we could compute where something lives instead of searching for it? No comparisons. No traversal. Just a function that maps a key directly to a bucket. That gives us O(1) average-case lookup, which sounds like the end of the story.

It is not. The O(1) promise depends entirely on the hash function distributing keys evenly across buckets. A bad hash function clusters entries into a few buckets, and those buckets degrade to linked-list searches. The theoretical O(1) becomes practical O(n) in the worst case. The hash function is the design decision that makes or breaks the data structure.

This project makes that visible. You will run the same text through two different hash functions and compare the distributions they produce. One function ignores character position; the other accounts for it. The diagnostic numbers (longest chain, average chain length, load factor) are your evidence. Your job in `Design_Decisions.md` is to tell the story those numbers tell: not just that the distributions differ, but *why* they differ and what the difference means for lookup performance.

---

## The Text File

Your analysis text is **"Structure and Interpretation of Computer Programs"** by Abelson and Sussman, the foundational CS textbook used at MIT for decades, released under Creative Commons. Approximately 600 pages with a vocabulary heavy in terms like "procedure", "lambda", and "define". It is provided in the project ZIP as `sicp.txt`.

### Development Tip: Start Small

SICP is a large file (~157,000 words). While you are implementing and debugging, you do not want to wait for the full file on every test run. `TextParser` accepts an optional second parameter that limits how many words it returns:

```cpp
TextParser parser("texts/sicp.txt", 500);   // first 500 words only
TextParser parser("texts/sicp.txt");         // all words (for final run)
```

Use a small limit (e.g. 500) during development to keep iteration fast. Once your hash table and driver are working correctly, remove the limit and run the full analysis for your final submission. This is a common practice in real-world data work: test on a small slice, ship on the full dataset.

---

## The Hash Table ADT

A dictionary maps keys to values. You look up a word and get back its count. A hash table implements this by computing a bucket index directly from the key, giving O(1) average-case lookup without comparisons or traversal. For word frequency counting this is the natural fit: read each word, insert it, and let the table track how many times it has appeared.

`HashTable<K, V>` inherits from `HashTableInterface<K, V>` and implements all interface methods. The header files `HashTableInterface.h` and `HashTable.h` are the authoritative source for method signatures, parameter types, and expected behavior. Read them before you start coding.

Three notes that the headers alone do not make obvious:

**`V` is expected to be an integer type.** Although `HashTable<K, V>` is a template over both key and value types, the interface is specialized for counting. `insert` takes only a key; the table manages the value internally, starting new entries at 1 and incrementing by 1 on subsequent inserts. `find` returns 0 for missing keys. The caller never passes a value. For this project, `V` will always be `int`.

**Load factor and average chain length measure different things.** Load factor averages over **all** buckets (`totalEntries / tableSize`); average chain length averages only over **non-empty** buckets. Worked example: if the buckets have chain lengths `[3, 0, 5, 0, 2]`, then `getAverageChainLength()` returns `(3 + 5 + 2) / 3 = 3.33`, **not** `(3 + 0 + 5 + 0 + 2) / 5 = 2.0`. Empty buckets are excluded from both the numerator and the denominator. Comparing the two tells you how clustered the distribution is. With 19997 buckets and ~2,000 unique words, your load factor will be around 0.1. That is fine. What matters when comparing `modHash` and `hornerHash` is whether the longest chain is close to the average. If one function has longest = 15 and average = 2, its worst buckets are doing about 7x the work of a typical bucket, and lookups there approach linear search.

**`getAllEntries` returns entries in whatever order they happen to be stored.** The driver sorts the result by frequency after it gets the vector back. Let `getAllEntries` just collect; let the driver sort.

### Internal Structure

You decide how to represent the table internally. The interface does not dictate your member variables. Think about what a hash table with chaining needs: a fixed-size array of buckets, where each bucket holds a collection of entries that hashed to the same index. Explain your choice in `Design_Decisions.md`.

In Projects 3 and 4 you built linked lists and trees from scratch to understand what those structures do under the hood. You have earned the right to use the real tools. This project allows `std::vector` and `std::list` from the C++ standard library. Use them. They are fast, well-tested, and handle memory for you. Choosing which one belongs at which level of the hash table is the most important design decision in the project.

One restriction: do **not** use `std::unordered_map`, `std::map`, or any other standard library associative container as your table. Those types already *are* hash tables (or balanced trees); using them defeats the purpose of the assignment. You are building the hash table. `std::vector` and `std::list` give you the pieces; the assembly is yours.

### Constructor and Hash Function

The constructor takes the table size and the hash function to use for every `insert` and `find`:

```cpp
HashTable<std::string, int> modTable(TABLE_SIZE, modHash);
HashTable<std::string, int> hornerTable(TABLE_SIZE, hornerHash);
```

`std::function` lets you pass a function as a parameter, the same way you pass an `int` or a `string`. You'll store the function and call it later. The usage examples in `HashTable.h` and `driver.cpp` show exactly how it works. The table size is **19997**, a prime number. The hash functions section below explains why primes matter.

### Template Implementation Note

Because `HashTable<K, V>` is a class template, the implementation must be visible to the compiler at the point of use. Place all declarations and definitions in `HashTable.h`.

---

## Hash Functions

Implement both hash functions in `hashFunctions.h` as standalone template functions.

### Recommended Table Size: 19997

19997 is prime. Prime table sizes matter because they ensure every bucket is reachable regardless of the hash values produced. A non-prime table size can cause certain buckets to never receive entries, wasting space and increasing collisions elsewhere. Document this in `Design_Decisions.md`.

### Function 1: Mod-Based Hash

```cpp
template<class K>
inline int modHash(const K& key, int tableSize);
```

Sum the ASCII values of all characters in the key, then take the result mod `tableSize`.

**Formula:** `sum(ASCII value of each character) % tableSize`

This is simple and fast. Its weakness is that anagrams produce identical hash values, causing guaranteed collisions regardless of table size. The words "stop", "pots", "tops", "spot", and "opts" all hash to the same bucket.

### Function 2: Horner's Method

```cpp
template<class K>
inline int hornerHash(const K& key, int tableSize);
```

Treat the string as a polynomial evaluated at base 31, taking the result mod `tableSize` at each step to prevent integer overflow.

**Formula:** For each character c at position i:
`hash = (hash * 31 + ASCII(c)) % tableSize`

Start with `hash = 0` and process characters left to right. The position of each character affects the result, so anagrams hash differently.

See **Section 0** below for verification values you must check before moving on.

---

## Section 0: Hash Function Verification

Section 0 is your safety net. Before you analyze any text, verify both hash functions against six pre-computed values. Once all twelve checks pass, you can trust that every hash value in the rest of the project is correct. That confidence saves hours of debugging.

Your driver prints all twelve values (six per function) with a `[PASS]` or `[FAIL]` label for each. If any value shows `[FAIL]`, fix the hash function before moving on. Everything downstream depends on these being right.

| Word | modHash | hornerHash |
|------|--------:|----------:|
| "hello" | 532 | 17196 |
| "world" | 552 | 15800 |
| "hash" | 420 | 15627 |
| "computer" | 879 | 4639 |
| "turing" | 665 | 9021 |
| "lambda" | 609 | 12240 |

All values use table size **19997**.

The expected output format is shown in the Required Driver Sequence section below.

---

## TextParser (Provided)

`TextParser` handles all file I/O and text preprocessing. It reads a text file and returns a stream of cleaned, lowercase words with punctuation stripped. It is fully implemented and ready to use.

The `nextWord(std::string& word)` signature uses the **out-parameter pattern** you have already seen in C++ stream APIs like `std::getline` and `std::istream::operator>>`. The return value says whether a word was produced; the out-parameter carries the word itself. See the comment in `TextParser.h` for details.

```cpp
TextParser parser("texts/sicp.txt");
std::string word;
while (parser.nextWord(word))
{
    table.insert(word);
}
```

---

## Required Driver Sequence

Your driver must produce the following output for both hash functions against `sicp.txt`.

```
============================================
  Section 0: Hash Function Verification
============================================
modHash("hello",    19997) = 532    [PASS]
modHash("world",    19997) = 552    [PASS]
modHash("hash",     19997) = 420    [PASS]
modHash("computer", 19997) = 879    [PASS]
modHash("turing",   19997) = 665    [PASS]
modHash("lambda",   19997) = 609    [PASS]

hornerHash("hello",    19997) = 17196   [PASS]
hornerHash("world",    19997) = 15800   [PASS]
hornerHash("hash",     19997) = 15627   [PASS]
hornerHash("computer", 19997) = 4639    [PASS]
hornerHash("turing",   19997) = 9021    [PASS]
hornerHash("lambda",   19997) = 12240   [PASS]

All hash function tests passed.

============================================
  Section A: Mod-Based Hash Analysis
============================================

Text file:          [filename]
Table size:         19997
Total unique words: [N]  (distinct keys in the table)
Total word count:   [N]  (every word including repeats; much larger than unique)
Load factor:        [N]
Longest chain:      [N]
Shortest chain:     [N]
Average chain:      [N]

--- Top 20 Words by Frequency ---
[word]              [count]
...

--- Bottom 20 Words by Frequency ---
[word]              [count]
...
(Break ties alphabetically: when many words share the minimum frequency,
 list the first 20 in alphabetical order.)

============================================
  Section B: Horner Hash Analysis
============================================

[Same structure as Section A]
```

After both sections print, look at the two sets of diagnostics side by side. The story the numbers tell is about *why* position-sensitive hashing matters, not just *that* it produces different values. That comparison is what you will write up in `Design_Decisions.md`.

---

## Directory Structure

```
project_05/
├── include/
│   ├── HashTableInterface.h       (provided, do not modify)
│   ├── HashTableEntry.h                    (provided, do not modify)
│   ├── TextParser.h               (provided, do not modify)
│   ├── HashTable.h                (you implement)
│   └── hashFunctions.h            (you implement)
├── src/
│   ├── TextParser.cpp             (provided, do not modify)
│   └── driver.cpp                 (you implement)
├── texts/
│   └── sicp.txt                   (provided)
├── build/
├── Makefile
├── project_05.md                  (provided, this document)
├── project_05_rubric.md           (provided, do not modify)
├── coding_standards.md            (provided, do not modify)
├── ADT_Design.md
├── Design_Decisions.md
└── README.md
```

---

## Files and Build Requirements

**Provided, do not modify:**
- `include/HashTableInterface.h`
- `include/HashTableEntry.h`
- `include/TextParser.h`
- `src/TextParser.cpp`
- `Makefile`
- `coding_standards.md`
- `project_05_rubric.md`
- `texts/sicp.txt`

**Provided as scaffolds, fill in the TODOs:**
- `include/HashTable.h`
- `include/hashFunctions.h`
- `README.md`

**You create:**
- `src/driver.cpp`
- `ADT_Design.md`
- `Design_Decisions.md`

### Build Requirements

```bash
make        # Builds the executable
make clean  # Removes build artifacts
make run    # Builds and runs the program
make debug  # Rebuilds with -g -O0 -fsanitize=address,undefined
            # Use this if you hit a segfault or suspect UB.
```

Compiler flags must include:

```bash
-std=c++17 -Wall -Wextra -pedantic
```

---

## Written Documentation

### `ADT_Design.md`

Write this before you write any code. It must include:

1. **Purpose:** what problem the dictionary ADT solves and why a hash table is the right implementation for word frequency counting
2. **Logical data model:** describe the dictionary abstractly, focusing on what it stores and what operations it supports, not how it is implemented in memory
3. **Operations:** document the behavior and preconditions of `insert`, `find`, and the four diagnostic methods
4. **Key insight:** explain what a hash function does at the ADT level: what role does it play, and why does the dictionary need one?

### `Design_Decisions.md`

1. **Internal structure:** what containers you used for the table and for each bucket, and why you chose them
2. **Prime table size:** explain why 19997 was chosen over a nearby non-prime like 20000. Use the anagram example from the spec to ground your explanation
3. **Real collision:** find a real collision in your own `modHash` output and explain it (see the prompt in the scaffold)
4. **Hash function comparison:** tell the story your numbers tell. Include the actual diagnostic numbers from both Section A and Section B, then explain *why* the distributions differ: what does `modHash` ignore that `hornerHash` accounts for? What would happen to lookup performance in the worst bucket under each function? Use your actual longest chain and average chain length to make the argument
5. **Interesting observations:** what did you notice about the word frequencies? Were any results surprising?

### `README.md`

1. **Project title and author**
2. **Build instructions**
3. **Sample output snippet**
4. **Known issues, or confirmation that everything works**

---

## Standard Library Reference

Before you start, review the documentation for `std::vector` and `std::list` at cppreference.com. Understanding their performance characteristics will help you decide which one belongs at each level of your hash table:
- `std::vector`: https://en.cppreference.com/w/cpp/container/vector
- `std::list`: https://en.cppreference.com/w/cpp/container/list

---

## Coding Standards

The CS 302 Coding Standards apply to this project in full. See `coding_standards.md`.

One update for Project 5: both Allman style (opening brace on its own line) and K&R style (opening brace on the same line) are acceptable. Choose one and use it consistently throughout the entire project.

---

## File Submission Instructions

Submit one ZIP file named exactly:

```
project_05_lastname.zip
```

Include:
- `include/` directory with all `.h` files
- `src/` directory with all `.cpp` files
- `Makefile`
- `ADT_Design.md`
- `Design_Decisions.md`
- `README.md`

Leave out the `build/` directory, compiled files, and IDE artifacts.

Before submitting, confirm:
1. `make clean` followed by `make` builds successfully
2. Section 0 output shows all PASS
3. Full SICP analysis runs and output is clearly labeled
4. `Design_Decisions.md` includes your actual diagnostic numbers and analysis

---

## Final Notes

This project emphasizes practical design over structural complexity. The hash table itself is the most straightforward data structure you have built this semester. The interesting work is in the comparison: two functions, same data, different distributions.

The diagnostic numbers are your evidence. Your job in `Design_Decisions.md` is to explain what those numbers mean. Two students with identical output can write very different analyses. The difference is whether you can explain *why* one hash function outperforms the other, not just *that* it does. The numbers tell the story; your analysis brings it to life.

Read SICP's first chapter before you analyze it. It is 50 pages and will change how you think about programming.

Ask questions on Canvas so everyone benefits from the answers.

Have fun. Go Team.
