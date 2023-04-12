#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm>
#include <map>
#include <set>
#include <deque>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// Add prototypes of helper functions here

//bool isValidWord(const string &word, const set<string> &dict);
//void wordle_helper(string temp_word, const string &letters_fix, const string &letters_floating, const set<string> &dict, set<string> &combinations);
//set<std::string> wordle(const std::string &in, const std::string &floating,const std::set<std::string> &dict);

// Definition of primary wordle function


bool isValidWord(const string &word, const set<string> &dict, string fixed )
{
    bool validity;
    auto pos = dict.find(word);
    cout << "validating..." << word << endl;
    if (pos != dict.end())
    {
        validity = true;
        for(size_t i = 0; i < fixed.size(); i ++)
        {
          char character = fixed[i];
          cout << "validating c" << character << endl; 
          cout << "word " << word << endl; 
          cout << "fixed " << word << endl; 
          if(word.find(character) == string::npos)
          {
            return false;
          } 
        }
        
        cout << "VALID" << endl;
        return true;

    }
    else
    {
        validity = false;
        cout << "INVALID" << endl;
    }
    return validity;
}
// Add your code here

void wordle_helper(string temp_word,  string &letters_fix, string &letters_floating, const set<string> &dict, set<string> &combinations)
{
    // Case #1 Characters in Word are Full
    if (temp_word.size() == letters_fix.size())
    {
        if (isValidWord(temp_word, dict, letters_floating))
        {
            cout << "inserting " << temp_word << endl;
            combinations.insert(temp_word);
        }
        return;
    }

    // Case #2 cuurent position is fixed, iterates to next character
    if (letters_fix.size() > temp_word.size() && letters_fix[temp_word.size()] != '-')
    {
        temp_word += letters_fix[temp_word.size()];
        cout << "Case 2... " << temp_word << endl;
        wordle_helper(temp_word, letters_fix, letters_floating, dict, combinations);
        temp_word.pop_back();
    }

    // Case #3 Try All Letter Combinations for Floating Character

    else
    {
        for (char c = 'a'; c <= 'z'; c++)
        {
            cout << "C first " << c << endl;
            if (letters_fix.size() <= temp_word.size() || letters_fix[temp_word.size()] == '-')
            {
                // Case #4 current position is empty, assigns a floating character
                if (letters_floating.find(c) != string::npos)
                {   cout << "Before Case 4... " << temp_word << endl;
                    temp_word += c;
                    cout << "C var: " << c << endl;
                    cout << "After Case 4... " << temp_word << endl;
                     cout << "Letter Fix Before: " << letters_floating << endl;
                    cout << "Letter Fix after: " << letters_floating << endl;
                    wordle_helper(temp_word, letters_fix, letters_floating, dict, combinations);
                    temp_word.pop_back();
                }
                // Case #5 curr not fixed, not float
                else
                {
                    cout << "Case 5 Before... " << temp_word << endl;
                    temp_word += c;
                    cout << "Case 5 After... " << temp_word << endl;
                    wordle_helper(temp_word, letters_fix, letters_floating, dict, combinations);
                    temp_word.pop_back();
                    //continue;
                }
            }
            else
            {   // Case #6 curr pos fixed, add letter
                cout << "Before Case 6... " << temp_word << endl;
                temp_word += letters_fix[temp_word.size()];
                cout << "After Case 6... " << temp_word << endl;
                wordle_helper(temp_word, letters_fix, letters_floating, dict, combinations);
                temp_word.pop_back();
            }
        }
    }
}



set<string> wordle(const string &in, const string &floating, const set<std::string> &dict)
{
    set<std::string> combinations;
    string letters_fix = in;
    string floating_copy = floating;
    cout << "wordle starting" << endl;
   /* for(size_t i = 0; i < in.length(); i++)
    {
        if(isalpha(in[i]))
        {
            in[i] = in[i].lower
        }
    }*/
    wordle_helper("", letters_fix, floating_copy, dict, combinations );
    return combinations;


}

/*
wordle_helper(-i--, dash_ct, float_ct, dictionaty)
Case #1 while  dash count < float

Case #2 while  dash count > float
    all permutations of float letters in remaining spaces

Case #3 dash count == 0 && float == 0
    return

// else index a dash
    abc helper script

// else letter, iterate next index
    next letter




*/

// dash count, float count

// dash count less than float count
// dash count greater than float,
// dash ==0, float == 0
// indexed past size of word
// else index a dash
// else letter, iterate next index

// iterating through entire dictionary
// set fixed_int_place
// delete words too long
// delete words too short
// check if second letter is i
// check if contains floating

// assignment: GENERATE all possible words
// -i--  nd
// 1. place floating letter (nid-)
// loop alphabet in free space
// ndia
// ndib
// ndic
// 2. shift floating letter(-ind)
// loop alphabet in free space

// 3. shift floating letter(di-n)
// loop alphabet in free space

// 4. shift floating letter(ni-d)
// loop alphabet in free space
//(-nd)

// get current permutation
// push into a word

// Define any helper functions here

// create permute function

// two m
/// loop options
// loop a-z
// not loop overlength og the input

// any spot not a floating letter, all of the letters

//

// in persions set of options in a deque, miss first one you use
