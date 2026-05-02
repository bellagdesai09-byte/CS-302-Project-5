// driver.cpp
// CS 302 – Project 5: Word Frequency Analyzer
//
// INSTRUCTIONS:
//   1. Implement Section 0: verify both hash functions against
//      the expected values in project_05.md. Print PASS or FAIL
//      for each. If any FAIL, stop and fix before continuing.
//
//   2. Implement Section A: load texts/sicp.txt into a
//      HashTable using modHash. Print all statistics and the
//      top 20 and bottom 20 words by frequency.
//
//   3. Implement Section B: repeat Section A using hornerHash.
//
//   4. Your output must be clearly labeled. See project_05.md
//      for the required output format.
//
// The structure of main() is yours to write. Use printSection()
// and printStep() to keep your output organized.

#include "HashTable.h"
#include "TextParser.h"
#include <iostream>
#include <string>

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
// loadText
//   Reads words from the given file and inserts each one
//   into the table. Returns the total number of words
//   processed (including repeats).
//
//   Pass maxWords = 0 (the default) to process the entire
//   file. During development, use a small value to keep
//   iteration fast:
//
//     int n = loadText("texts/sicp.txt", table, 500);
//     int n = loadText("texts/sicp.txt", table);  // all
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
// TODO: Implement a helper that prints table statistics:
//       total unique words, total word count, load factor,
//       longest chain, shortest chain, average chain length.
// -------------------------------------------------------

// -------------------------------------------------------
// TODO: Implement a helper that prints the top N and
//       bottom N words by frequency from a HashTable.
//       Use getAllEntries() and std::sort with a lambda.
// -------------------------------------------------------

int main()
{
    // ====================================================
    // Section 0: Hash Function Verification
    // ====================================================
    // TODO: For each test word, call modHash and hornerHash
    //       with TABLE_SIZE. Compare to the expected values
    //       in project_05.md. Print the result and PASS/FAIL.
    //       If any test fails, print a message and return 1.

    printSection("Section 0: Hash Function Verification");

    // TODO: Verify modHash for all 6 test words

    // TODO: Verify hornerHash for all 6 test words

    // TODO: Print "All hash function tests passed." if all pass


    // ====================================================
    // Section A: Mod-Based Hash Analysis
    // ====================================================
    // TODO: Construct a HashTable using modHash and load sicp.txt.
    //       Print statistics and top/bottom 20 words.
    //
    // Construct one table per hash function:
    //   HashTable<std::string, int> modTable(TABLE_SIZE, modHash);
    //   HashTable<std::string, int> hornerTable(TABLE_SIZE, hornerHash);
    // Then load the same text file into each.
    //
    // During development, limit words to keep iteration fast:
    //   TextParser parser("texts/sicp.txt", 500);
    // For the final submission, use the full file:
    //   TextParser parser("texts/sicp.txt");

    printSection("Section A: Mod-Based Hash Analysis");

    // TODO


    // ====================================================
    // Section B: Horner Hash Analysis
    // ====================================================
    // TODO: Construct a HashTable using hornerHash.
    //       Load sicp.txt again.
    //       Print statistics and top/bottom 20 words.

    printSection("Section B: Horner Hash Analysis");

    // TODO


    std::cout << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "  Analysis complete." << std::endl;
    std::cout << "============================================" << std::endl;

    return 0;
}
