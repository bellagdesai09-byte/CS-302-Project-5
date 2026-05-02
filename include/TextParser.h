// TextParser.h
// CS 302 - Project 5: Word Frequency Analyzer
//
// Reads a text file and returns a stream of cleaned, lowercase
// words with punctuation stripped. Do not modify this file.

#ifndef TEXT_PARSER_H
#define TEXT_PARSER_H

#include <string>
#include <fstream>

class TextParser
{
public:

    // Opens the file at the given path.
    // Throws std::runtime_error if the file cannot be opened.
    //
    // maxWords controls how many words nextWord() will return
    // before reporting end-of-input. Pass 0 (the default) to
    // process the entire file. During development, use a small
    // value (e.g. 500) to keep iteration fast:
    //
    //   TextParser parser("texts/sicp.txt");        // all words
    //   TextParser parser("texts/sicp.txt", 500);   // first 500 only
    TextParser(const std::string& filename, int maxWords = 0);

    ~TextParser();

    // Returns the next cleaned word in the stream via the
    // out parameter. Returns true if a word was found,
    // false if the end of file (or maxWords limit) was reached.
    //
    // Uses an out-parameter to avoid constructing a string
    // when at EOF. This is a common pattern in C++ stream
    // APIs: std::getline and std::istream::operator>> use
    // the same shape. The return value says whether a word
    // was produced; the out-parameter carries the word.
    //
    // Usage:
    //   std::string word;
    //   while (parser.nextWord(word)) { /* use word */ }
    bool nextWord(std::string& word);

private:

    std::ifstream file_;
    int maxWords_;
    int wordsReturned_;

    std::string cleanWord(const std::string& raw) const;

}; // end TextParser

#endif
