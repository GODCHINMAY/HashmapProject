#include "makeSeuss.hpp"
#include <fstream>
#include <iostream>

makeSeuss::makeSeuss(string f1, string f2, bool h1, bool c1) {
    ht = new hashMap(h1, c1);
    newfile = f2;
    fn = f1;
    readFile();
    writeFile();
}

void makeSeuss::readFile() {
    ifstream infile(fn.c_str(), ios::in);
    string key = "";
    string value = "";
    infile >> key;
    ht->first = key;
    while (infile >> value) {
        ht->addKeyValue(key, value);
        key = value;
        value = "";
    }
    ht->addKeyValue(key, value);
    infile.close();
}

void makeSeuss::writeFile() {
    ofstream outfile(newfile.c_str(), ios::out);
    outfile << ht->first << " ";
    int index = ht->getIndex(ht->first);
    if (index == -1 || ht->map[index] == NULL) {
        cerr << "Error: First keyword '" << ht->first << "' not found in hash map." << endl;
        outfile.close();
        return;
    }
    string key = ht->first;
    string value = ht->map[index]->getRandValue();
    int ct = 0;
    int len = 0;
    while (ct < 500 && value != "") {
        key = value;
        outfile << key << " ";
        if (len == 11) {
            outfile << "\n";
            len = 0;
        } else {
            len++;
        }
        index = ht->getIndex(key);
        if (index == -1 || ht->map[index] == NULL) {
            break;
        }
        value = ht->map[index]->getRandValue();
        ct++;
    }
    outfile.close();
}

void makeSeuss::printCollisionCounts() {
    cout << "Collision counts for " << newfile << ":" << endl;
    ht->printCollisionCounts();
    cout << endl;
}
