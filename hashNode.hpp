#ifndef HASHNODE_HPP
#define HASHNODE_HPP

#include <string>
using namespace std;

class hashNode {
    friend class hashMap;
    string keyword;      // The keyword (key) used for hashing
    string *values;      // Dynamically allocated array of words that follow the keyword
    int valuesSize;      // Size of the 'values' array
    int currSize;        // Current number of values in the 'values' array

public:
    hashNode();                       // Default constructor
    hashNode(string s);               // Constructor with keyword initialization
    hashNode(string s, string v);     // Constructor with keyword and initial value
    void addValue(string v);          // Adds a value to the 'values' array
    void dblArray();                  // Doubles the size of the 'values' array
    string getRandValue();            // Returns a random value from the 'values' array
};

#endif // HASHNODE_HPP