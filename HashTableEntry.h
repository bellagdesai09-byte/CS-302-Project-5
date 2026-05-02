// HashTableEntry.h
// CS 302 - Project 5: Word Frequency Analyzer
//
// A key-value pair stored in the hash table.
// Do not modify this file.

#ifndef HASH_TABLE_ENTRY_H
#define HASH_TABLE_ENTRY_H

template<class K, class V>
struct HashTableEntry
{
    K key;
    V value;

    HashTableEntry(const K& k, const V& v) : key(k), value(v) {}
};

#endif
