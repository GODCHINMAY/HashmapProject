#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "hashNode.hpp"
#include <string>
using namespace std;

class hashMap {
    friend class makeSeuss;
    hashNode **map;
    string first;
    int numKeys;
    int mapSize;
    bool h1;
    bool c1;
    int collisionct1;
    int collisionct2;

public:
    hashMap(bool hash1, bool coll1);
    void addKeyValue(string k, string v);
    int getIndex(string k);
    int calcHash(string k);
    int calcHash2(string k);
    void getClosestPrime();
    void reHash();
    int collHash1(int h, int i, string k);
    int collHash2(int h, int i, string k);
    int findKey(string k);
    void printMap();
    void printCollisionCounts(); // Added method
};

#endif // HASHMAP_HPP
