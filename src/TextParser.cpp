// TextParser.cpp
// CS 302 - Project 5: Word Frequency Analyzer
//
// Do not modify this file.

#include "TextParser.h"
#include <algorithm>
#include <stdexcept>

TextParser::TextParser(const std::string& filename, int maxWords)
    : maxWords_(maxWords), wordsReturned_(0)
{
    file_.open(filename);
    if (!file_.is_open())
    {
        throw std::runtime_error("TextParser: could not open file: " + filename);
    }
}

TextParser::~TextParser()
{
    if (file_.is_open())
    {
        file_.close();
    }
}

bool TextParser::nextWord(std::string& word)
{
    if (maxWords_ > 0 && wordsReturned_ >= maxWords_)
    {
        return false;
    }

    std::string raw;
    while (file_ >> raw)
    {
        std::string cleaned = cleanWord(raw);
        if (!cleaned.empty())
        {
            word = cleaned;
            wordsReturned_++;
            return true;
        }
    }
    return false;
}

std::string TextParser::cleanWord(const std::string& raw) const
{
    std::string result;
    for (char c : raw)
    {
        if (std::isalpha(static_cast<unsigned char>(c)))
        {
            result += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return result;
}
