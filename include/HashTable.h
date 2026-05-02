// HashTable.h
// CS 302 - Project 5: Word Frequency Analyzer
//
// Hash table implementation using chaining for collision resolution.
// Inherits from HashTableInterface<K, V>.


#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "HashTableInterface.h"
#include "HashTableEntry.h"
#include <vector>
#include <list>
#include <utility>
#include <functional>

template<class K, class V>
class HashTable : public HashTableInterface<K, V>
{
private:
    std::vector<std::list<HashTableEntry<K, V>>> table_;
    int tableSize_;
    int numEntries_;
    std::function<int(const K&, int)> hashFn_;

public:

    // ---------------------------------------------------------
    HashTable(int tableSize,
              std::function<int(const K&, int)> hashFn)
    {
        tableSize_ = tableSize;
        hashFn_ = hashFn;
        numEntries_ = 0;
        table_.resize(tableSize_);
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
    int index = hashFn_(key, tableSize_);

    //Search the chain for an existing entry
    for (auto& entry : table_[index])
    {
        if (entry.key == key)
        {
            // If found, increment its value by 1.
            entry.value++;
            return;
        }
    }

    // Add a new entry with value 1
    table_[index].push_back(HashTableEntry<K, V>(key, 1));
    numEntries_++;
}

    // ---------------------------------------------------------
    // find
    //   Hash the key to find its bucket.
    //   Search the bucket's chain for a matching entry.
    //   Return its value if found, or 0 if not found.
    // ---------------------------------------------------------
    V find(const K& key) const override
    {
    int index = hashFn_(key, tableSize_);

    for (const auto& entry : table_[index])
    {
        if (entry.key == key)
        {return entry.value;
        }
    }
        return 0;
    }

    // ---------------------------------------------------------
    // getLoadFactor
    //   Total number of entries divided by table size.
    //   A load factor near 1.0 means the table is well utilized.
    // ---------------------------------------------------------
    double getLoadFactor() const override
    {
       return static_cast<double>(numEntries_) / tableSize_;
    }

    // ---------------------------------------------------------
    // getLongestChain
    //   Iterate all buckets. Return the maximum chain length.
    // ---------------------------------------------------------
    int getLongestChain() const override
    {
    int maxChain = 0;
    for (const auto& bucket : table_)
    {
        if (static_cast<int>(bucket.size()) > maxChain)
        {
            maxChain = bucket.size();
        }
    }
    return maxChain;    
    }

    // ---------------------------------------------------------
    // getShortestChain
    //   Iterate all buckets. Return the minimum non-empty chain length.
    //   Only consider buckets that have at least one entry.
    // ---------------------------------------------------------
    int getShortestChain() const override
    {
    int minChain = -1; // -1 indicates no non-empty buckets found yet
    for (const auto& bucket : table_)
    {
        if (!bucket.empty())
        {
            int currentSize = bucket.size();
            if (minChain == -1 || currentSize < minChain)
            {
                minChain = currentSize;
            }
        }
    }
    return (minChain == -1) ? 0 : minChain;
    }

    // ---------------------------------------------------------
    // getAverageChainLength
    //   Sum the lengths of all non-empty chains.
    //   Divide by the number of non-empty buckets.
    // ---------------------------------------------------------
    double getAverageChainLength() const override
    {
    if (numEntries_==0) return 0.0;
    double totalChainLength = 0;
    int nonEmptyBuckets = 0;

    for (const auto& bucket : table_)
    {
        if (!bucket.empty())
        {
            totalChainLength += bucket.size();
            nonEmptyBuckets++;
        }
    }
    return totalChainLength / nonEmptyBuckets;
    }

    // ---------------------------------------------------------
    // getAllEntries
    //   Collect all key-value pairs from every bucket into a
    //   single vector of pairs. The driver will sort this vector
    //   to produce the top 20 and bottom 20 frequency lists.
    // ---------------------------------------------------------
    std::vector<std::pair<K, V>> getAllEntries() const override
    {
    std::vector<std::pair<K, V>> allEntries;

    for (const auto& bucket : table_)
    {
        for (const auto& entry: bucket)
        {
            allEntries.push_back(std::make_pair(entry.key, entry.value));
        }
    }
    return allEntries;
    }

}; // end HashTable

#endif
