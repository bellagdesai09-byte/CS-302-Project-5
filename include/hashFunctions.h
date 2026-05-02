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

// ---------------------------------------------------------
template<class K>
inline int modHash(const K& key, int tableSize)
{
    int sum = 0;

    for (char c : key)
    {
        sum += static_cast<int>(c);
    }
    return sum % tableSize;
}

// ---------------------------------------------------------
// hornerHash
//
// Treats the string as a polynomial evaluated at base 31.
// Applies mod tableSize at each step to prevent overflow.

// ---------------------------------------------------------
template<class K>
inline int hornerHash(const K& key, int tableSize)
{
// Use long long to safely contain (hash * 31) before the modulo
// prevents C++ signed integer undefined behavior
    long long hash = 0;
for (char c : key)
{
    if (c == ' ' || c == '\0') break;
    hash = (hash * 31 + static_cast<int>(c)) % tableSize;
}
    return static_cast<int>(hash);
}

#endif
