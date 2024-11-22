//
// Created by Chinmay Agrawal on 11/19/24.
//
#include "hashNode.hpp"
#include <cstdlib>

hashNode::hashNode() {
    keyword = "";
    valuesSize = 0;
    currSize = 0;
    values = NULL;
}

hashNode::hashNode(string s) {
    keyword = s;
    valuesSize = 100;  // Initial size can be adjusted
    currSize = 0;
    values = new string[valuesSize];
}

hashNode::hashNode(string s, string v) {
    keyword = s;
    valuesSize = 100;
    currSize = 1;
    values = new string[valuesSize];
    values[0] = v;
}

void hashNode::addValue(string v) {
    if (currSize >= valuesSize) {
        dblArray();
    }
    values[currSize] = v;
    currSize++;
}

void hashNode::dblArray() {
    valuesSize *= 2;
    string *newValues = new string[valuesSize];
    for (int i = 0; i < currSize; i++) {
        newValues[i] = values[i];
    }
    delete[] values;
    values = newValues;
}

string hashNode::getRandValue() {
    if (currSize == 0) {
        return "";
    } else {
        int randIndex = rand() % currSize;
        return values[randIndex];
    }
}
