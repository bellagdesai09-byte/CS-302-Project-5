// hashFunctions.h
// CS 302 - Project 5: Word Frequency Analyzer
//
// Two standalone hash function templates for string-like keys.
// Both take the key and the table size as parameters and
// return a valid bucket index in [0, tableSize).
//
// See project_05.md for the formulas and verification values.

#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

#include <string>

// ---------------------------------------------------------
// modHash
//
// Sums the ASCII value of every character in the key,
// then returns the result mod tableSize.
//
// Formula: sum(ASCII value of each character) % tableSize
//
// Weakness: anagrams produce identical hash values because
// addition is commutative. "stop", "pots", "tops", "spot",
// and "opts" all map to the same bucket.
//
// Verification values for tableSize = 19997:
//   modHash("hello")    = 532
//   modHash("world")    = 552
//   modHash("hash")     = 420
//   modHash("computer") = 879
//   modHash("turing")   = 665
//   modHash("lambda")   = 609
// ---------------------------------------------------------
template<class K>
inline int modHash(const K& key, int tableSize)
{
    // TODO: Implement.
    //   Sum the ASCII value of each character in key.
    //   Return the sum mod tableSize.
    return 0;
}

// ---------------------------------------------------------
// hornerHash
//
// Treats the string as a polynomial evaluated at base 31.
// Applies mod tableSize at each step to prevent overflow.
//
// Formula: for each character c, left to right:
//   hash = (hash * 31 + ASCII(c)) % tableSize
// Start with hash = 0.
//
// IMPORTANT: apply % tableSize at EVERY step of the loop,
// not just once at the end. If you only mod at the end,
// `hash * 31` can overflow a signed int for even moderately
// long words. Signed integer overflow is undefined behavior
// in C++, which means the compiler is allowed to produce
// any result, including "correct" values on your machine
// and wrong ones on the grader's. Applying mod every step
// keeps `hash` small and the arithmetic safe.
//
// Strength: character position affects the result, so
// anagrams produce different hash values.
//
// Verification values for tableSize = 19997:
//   hornerHash("hello")    = 17196
//   hornerHash("world")    = 15800
//   hornerHash("hash")     = 15627
//   hornerHash("computer") = 4639
//   hornerHash("turing")   = 9021
//   hornerHash("lambda")   = 12240
// ---------------------------------------------------------
template<class K>
inline int hornerHash(const K& key, int tableSize)
{
    // TODO: Implement.
    //   Start with hash = 0.
    //   For each character c in key (left to right):
    //     hash = (hash * 31 + ASCII value of c) % tableSize
    //   Return hash.
    return 0;
}

#endif
