// HashTable.h
// CS 302 - Project 5: Word Frequency Analyzer
//
// Hash table implementation using chaining for collision resolution.
// Inherits from HashTableInterface<K, V>.
//
// TODO: Implement all methods below.
//       Decide on your internal structure and declare your member
//       variables. Think carefully about which standard library
//       container belongs at each level and document your choice
//       in Design_Decisions.md.
//
// See project_05.md for full requirements.

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "HashTableInterface.h"
#include <vector>
#include <utility>
#include <functional>

template<class K, class V>
class HashTable : public HashTableInterface<K, V>
{
private:

    // TODO: Declare your member variables here.
    //
    // You need at minimum:
    //   - A structure to hold the buckets and their chains
    //   - A way to track the table size
    //   - A way to track the total number of entries
    //   - A hash function to use when hashing keys
    //
    // Think about what containers make sense at each level.
    // Your choice here is the most important design decision
    // in the project. Document it in Design_Decisions.md.

public:

    // ---------------------------------------------------------
    // Constructor
    //   Initializes the hash table with the given number of
    //   buckets and a hash function to use for all insert and
    //   find operations. Use a prime number for tableSize
    //   (recommended: 19997).
    //
    //   Example usage:
    //     HashTable<std::string, int> table(19997, modHash);
    //     HashTable<std::string, int> table(19997, hornerHash);
    //
    //   std::function lets you pass a function as a parameter.
    //   Store it and call it like any other function:
    //     hashFn_(key, tableSize_)
    // ---------------------------------------------------------
    HashTable(int tableSize,
              std::function<int(const K&, int)> hashFn)
    {
        // TODO: Initialize your internal structure and store the
        //       hash function for later use by insert() and find().
    }

    // ---------------------------------------------------------
    // Destructor
    // ---------------------------------------------------------
    ~HashTable()
    {
        // TODO: Free any dynamically allocated memory.
        //       If you used only standard library containers
        //       with no raw pointers, this may be empty.
        //       Explain why in Design_Decisions.md.
    }

    // ---------------------------------------------------------
    // insert
    //   Hash the key to find its bucket.
    //   Search the bucket's chain for an existing entry.
    //   If found, increment its value by 1.
    //   If not found, add a new HashTableEntry with value 1.
    // ---------------------------------------------------------
    void insert(const K& key) override
    {
        // TODO: Implement.
    }

    // ---------------------------------------------------------
    // find
    //   Hash the key to find its bucket.
    //   Search the bucket's chain for a matching entry.
    //   Return its value if found, or 0 if not found.
    // ---------------------------------------------------------
    V find(const K& key) const override
    {
        // TODO: Implement.
        return V();
    }

    // ---------------------------------------------------------
    // getLoadFactor
    //   Total number of entries divided by table size.
    //   A load factor near 1.0 means the table is well utilized.
    // ---------------------------------------------------------
    double getLoadFactor() const override
    {
        // TODO: Implement.
        return 0.0;
    }

    // ---------------------------------------------------------
    // getLongestChain
    //   Iterate all buckets. Return the maximum chain length.
    // ---------------------------------------------------------
    int getLongestChain() const override
    {
        // TODO: Implement.
        return 0;
    }

    // ---------------------------------------------------------
    // getShortestChain
    //   Iterate all buckets. Return the minimum non-empty chain length.
    //   Only consider buckets that have at least one entry.
    // ---------------------------------------------------------
    int getShortestChain() const override
    {
        // TODO: Implement.
        return 0;
    }

    // ---------------------------------------------------------
    // getAverageChainLength
    //   Sum the lengths of all non-empty chains.
    //   Divide by the number of non-empty buckets.
    // ---------------------------------------------------------
    double getAverageChainLength() const override
    {
        // TODO: Implement.
        return 0.0;
    }

    // ---------------------------------------------------------
    // getAllEntries
    //   Collect all key-value pairs from every bucket into a
    //   single vector of pairs. The driver will sort this vector
    //   to produce the top 20 and bottom 20 frequency lists.
    // ---------------------------------------------------------
    std::vector<std::pair<K, V>> getAllEntries() const override
    {
        // TODO: Implement.
        //   Iterate every bucket, iterate every entry in each chain,
        //   and push each key-value pair into the result vector.
        return {};
    }

}; // end HashTable

#endif
