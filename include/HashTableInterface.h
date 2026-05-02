// HashTableInterface.h
// CS 302 – Project 5: Word Frequency Analyzer
//
// Pure abstract interface for a hash table-backed dictionary.
// Do not modify this file.

#ifndef HASH_TABLE_INTERFACE_H
#define HASH_TABLE_INTERFACE_H

#include <vector>
#include <utility>

template<class K, class V>
class HashTableInterface
{
public:

    virtual ~HashTableInterface() {}

    // ---------------------------------------------------------
    // insert
    //   If key is not present, adds it with value 1.
    //   If key is already present, increments its value by 1.
    // ---------------------------------------------------------
    virtual void insert(const K& key) = 0;

    // ---------------------------------------------------------
    // find
    //   Returns the value associated with key.
    //   Returns 0 if the key is not in the table.
    // ---------------------------------------------------------
    virtual V find(const K& key) const = 0;

    // ---------------------------------------------------------
    // getLoadFactor
    //   Returns total number of entries divided by table size.
    // ---------------------------------------------------------
    virtual double getLoadFactor() const = 0;

    // ---------------------------------------------------------
    // getLongestChain
    //   Returns the length of the longest chain in the table.
    // ---------------------------------------------------------
    virtual int getLongestChain() const = 0;

    // ---------------------------------------------------------
    // getShortestChain
    //   Returns the length of the shortest non-empty chain.
    // ---------------------------------------------------------
    virtual int getShortestChain() const = 0;

    // ---------------------------------------------------------
    // getAverageChainLength
    //   Returns the average length of all non-empty chains.
    // ---------------------------------------------------------
    virtual double getAverageChainLength() const = 0;

    // ---------------------------------------------------------
    // getAllEntries
    //   Returns all key-value pairs as a vector of pairs.
    //   Used by the driver to sort and display top/bottom words.
    // ---------------------------------------------------------
    virtual std::vector<std::pair<K, V>> getAllEntries() const = 0;

}; // end HashTableInterface

#endif
