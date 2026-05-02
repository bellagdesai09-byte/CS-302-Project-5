// driver.cpp
// CS 302 – Project 5: Word Frequency Analyzer

#include "HashTable.h"
#include "TextParser.h"
#include "hashFunctions.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

const int TABLE_SIZE = 19997;

// -------------------------------------------------------
// Utility: prints a labeled section divider
// -------------------------------------------------------
void printSection(const std::string& label)
{
    std::cout << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "  " << label << std::endl;
    std::cout << "============================================" << std::endl;
}

// -------------------------------------------------------
// Utility: prints a labeled sub-divider
// -------------------------------------------------------
void printStep(const std::string& label)
{
    std::cout << std::endl << "--- " << label << " ---" << std::endl;
}

// -------------------------------------------------------
// Utility: verifyHash for Section 0
// -------------------------------------------------------
bool verifyHash(const string& funcName, const string& word, int tableSize, int expected, int actual)
{
    cout << left << setw(10) << funcName << "(\"" << setw(8) << word << "\", " 
         << tableSize << ") = " << setw(5) << actual << "    ";
    
    if (expected == actual) 
    {
        cout << "[PASS]" << endl;
        return true;
    }
    else 
    {
        cout << "[FAIL] (Expected: " << expected << ")" << endl;
        return false;
    }
}

// -------------------------------------------------------
// loadText
// -------------------------------------------------------
int loadText(const std::string& filename,
             HashTable<std::string, int>& table,
             int maxWords = 0)
{
    TextParser parser(filename, maxWords);
    std::string word;
    int count = 0;
    while (parser.nextWord(word))
    {
        table.insert(word);
        count++;
    }
    return count;
}

// -------------------------------------------------------
// Helper that prints table statistics
// -------------------------------------------------------
void printTableStats(const std::string& filename, const HashTable<std::string, int>& table, int totalCount)
{
    std::cout << "Text file:          " << filename << std::endl;
    std::cout << "Table size:         " << TABLE_SIZE << std::endl;
    std::cout << "Total unique words: " << table.getAllEntries().size() << std::endl;
    std::cout << "Total word count:   " << totalCount << std::endl;
    std::cout << "Load factor:        " << std::fixed << std::setprecision(4) << table.getLoadFactor() << std::endl;
    std::cout << "Longest chain:      " << table.getLongestChain() << std::endl;
    std::cout << "Shortest chain:     " << table.getShortestChain() << std::endl;
    std::cout << "Average chain:      " << table.getAverageChainLength() << std::endl;
}

// -------------------------------------------------------
// printTopBottom
// -------------------------------------------------------
bool compareDescending(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b)
{
    if (a.second != b.second)
        return a.second > b.second;
    return a.first < b.first;
}

bool compareAscending(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b)
{
    if (a.second != b.second)
        return a.second < b.second;
    return a.first < b.first;
}

void printTopBottom(HashTable<std::string, int>& table)
{
    std::vector<std::pair<std::string, int>> entries = table.getAllEntries();

    std::sort(entries.begin(), entries.end(), compareDescending);

    std::cout << "\n--- Top 20 Words by Frequency ---\n";
    for (int i = 0; i < 20 && i < (int)entries.size(); ++i)
        std::cout << std::left << std::setw(20) << entries[i].first << entries[i].second << "\n";

    std::sort(entries.begin(), entries.end(), compareAscending);

    std::cout << "\n--- Bottom 20 Words by Frequency ---\n";
    for (int i = 0; i < 20 && i < (int)entries.size(); ++i)
        std::cout << std::left << std::setw(20) << entries[i].first << entries[i].second << "\n";
}
int main()
{
    // ====================================================
    // Section 0: Hash Function Verification
    // ====================================================
    printSection("Section 0: Hash Function Verification");

    bool allPassed = true;

    // Verify modHash
    allPassed &= verifyHash("modHash", "hello",    TABLE_SIZE, 532,  modHash("hello", TABLE_SIZE));
    allPassed &= verifyHash("modHash", "world",    TABLE_SIZE, 552,  modHash("world", TABLE_SIZE));
    allPassed &= verifyHash("modHash", "hash",     TABLE_SIZE, 420,  modHash("hash", TABLE_SIZE));
    allPassed &= verifyHash("modHash", "computer", TABLE_SIZE, 879,  modHash("computer", TABLE_SIZE));
    allPassed &= verifyHash("modHash", "turing",   TABLE_SIZE, 665,  modHash("turing", TABLE_SIZE));
    allPassed &= verifyHash("modHash", "lambda",   TABLE_SIZE, 609,  modHash("lambda", TABLE_SIZE));

    cout << endl;

    // Verify hornerHash
    allPassed &= verifyHash("hornerHash", "hello",    TABLE_SIZE, 17196, hornerHash("hello", TABLE_SIZE));
    allPassed &= verifyHash("hornerHash", "world",    TABLE_SIZE, 15800, hornerHash("world", TABLE_SIZE));
    allPassed &= verifyHash("hornerHash", "hash",     TABLE_SIZE, 15627, hornerHash("hash", TABLE_SIZE));
    allPassed &= verifyHash("hornerHash", "computer", TABLE_SIZE, 4639,  hornerHash("computer", TABLE_SIZE));
    allPassed &= verifyHash("hornerHash", "turing",   TABLE_SIZE, 9021,  hornerHash("turing", TABLE_SIZE));
    allPassed &= verifyHash("hornerHash", "lambda",   TABLE_SIZE, 12240, hornerHash("lambda", TABLE_SIZE));

    if (!allPassed) 
    {
        cout << "\n[ERROR] One or more tests FAILED. Check your hash functions before proceeding." << endl;
        return 1; // Exit early if tests fail
    }

    cout << "\nAll hash function tests passed." << endl;
    const std::string filename = "texts/sicp.txt";
    const int WORD_LIMIT = 0;
    // ====================================================
    // Section A: Mod-Based Hash Analysis
    // ====================================================
    printSection("Section A: Mod-Based Hash Analysis");
    // Create the table using modHash
    HashTable<string, int> modTable(TABLE_SIZE, modHash<string>);    
    // Load the file (Use 500 for fast testing, 0 for final)
    int totalModWords = loadText("texts/sicp.txt", modTable, WORD_LIMIT);
    
    // Print stats and word lists
    printTableStats("texts/sicp.txt", modTable, totalModWords);
    printTopBottom(modTable);
    // ====================================================
    // Section B: Horner Hash Analysis
    // ====================================================
    printSection("Section B: Horner Hash Analysis");
    // Create the table using hornerHash
    HashTable<string, int> hornerTable(TABLE_SIZE, hornerHash<string>);    
    // Load the same file again
    int totalHornerWords = loadText("texts/sicp.txt", hornerTable, WORD_LIMIT);
    
    // Print stats and word lists
    printTableStats("texts/sicp.txt", hornerTable, totalHornerWords);
    printTopBottom(hornerTable);

    std::cout << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "  Analysis complete." << std::endl;
    std::cout << "============================================" << std::endl;

    return 0;
}