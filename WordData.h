// Title: Lab 5 WordData class and implementation
// Author: Zack Pace
// Description: This file is used to create the class WordData, as well as defining
// member functions for the created class.

#ifndef WORDDATA
#define WORDDATA

#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class WordData {
public:

    WordData();
    WordData(const WordData & OtherWord);
    WordData(const string & InWord);
    ~WordData();
    WordData & operator = (const WordData & OtherWord);
    WordData operator + (const WordData & OtherWord) const;
    friend istream & operator >> (istream & ins, WordData & w);
    friend ostream & operator << (ostream & outs, const WordData & w);
    void SetWord(const string & InWord);
    void WriteData(ostream &outs) const;
    bool operator == (const WordData & OtherWord) const;
    bool operator < (const WordData & OtherWord) const;
    bool operator > (const WordData & OtherWord) const;
    string GetWord() const;
    int GetNumVowels () const;
    int GetNumConsonants () const;
    int GetNumDigits () const;
    int GetNumSpecialChars () const;

private:
    int length; // C++ string to hold the word
    char * word;
    int vowels; // vowel counter
    int consonants; // consonant counter
    int digits; // digit counter
    int specialchars; // special character counter
};

#endif
