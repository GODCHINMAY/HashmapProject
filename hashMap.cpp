#include "hashMap.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>

hashMap::hashMap(bool hash1, bool coll1) {
    h1 = hash1;
    c1 = coll1;
    mapSize = 101; // Starting with a prime number
    map = new hashNode*[mapSize];
    for (int i = 0; i < mapSize; i++) {
        map[i] = NULL;
    }
    numKeys = 0;
    collisionct1 = 0;
    collisionct2 = 0;
}

void hashMap::addKeyValue(string k, string v) {
    int index = getIndex(k);

    if (index == -1) {
        // Map is full or cannot find a spot due to collision resolution issues
        reHash();
        index = getIndex(k);
        if (index == -1) {
            std::cerr << "Error: Cannot insert key '" << k << "' after rehashing." << std::endl;
            return;
        }
    }

    if (map[index] == NULL) {
        // No collision, insert new node
        map[index] = new hashNode(k, v);
        numKeys++;
    } else if (map[index]->keyword == k) {
        // Key exists, add value to values array
        map[index]->addValue(v);
    }

    // Check load factor and rehash if necessary
    if ((float)numKeys / mapSize > 0.7) {
        reHash();
    }
}

int hashMap::getIndex(string k) {
    int index;
    if (h1) {
        index = calcHash(k);
    } else {
        index = calcHash2(k);
    }
    if (index < 0) index += mapSize;

    int i = 0;
    int originalIndex = index;

    if (map[index] == NULL || map[index]->keyword == k) {
        // No collision
        return index;
    } else {
        // Collision at initial index
        collisionct1++; // Increment original collision count once
        i = 1; // Start probing
        while (true) {
            if (c1) {
                index = collHash1(originalIndex, i, k);
            } else {
                index = collHash2(originalIndex, i, k);
            }
            if (index < 0) index += mapSize;

            if (map[index] == NULL || map[index]->keyword == k) {
                // Found an empty slot or the same key
                return index;
            }
            collisionct2++; // Increment secondary collision count
            i++;
            if (i >= mapSize) {
                // Map is full or probing failed
                return -1;
            }
        }
    }
}


int hashMap::calcHash(string k) {
    unsigned long hash = 5381;
    for (unsigned int i = 0; i < k.length(); i++) {
        hash = ((hash << 5) + hash) + (int)k[i]; // hash * 33 + c
    }
    hash = hash % mapSize;
    if (hash < 0) hash += mapSize;
    return (int)hash;
}


int hashMap::calcHash2(string k) {
    unsigned long long hash = 0;
    int prime = 31;
    for (unsigned int i = 0; i < k.length(); i++) {
        hash = (hash * prime + (int)k[i]) % mapSize;
    }
    hash = hash % mapSize;
    if (hash < 0) hash += mapSize;
    return (int)hash;
}

void hashMap::getClosestPrime() {
    int num = mapSize;
    bool found = false;
    while (!found) {
        num++;
        found = true;
        for (int i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) {
                found = false;
                break;
            }
        }
    }
    mapSize = num;
}

void hashMap::reHash() {
    int oldMapSize = mapSize;
    hashNode **oldMap = map;

    mapSize *= 2;
    getClosestPrime();

    map = new hashNode*[mapSize];
    for (int i = 0; i < mapSize; i++) {
        map[i] = NULL;
    }

    numKeys = 0;
    collisionct1 = 0;
    collisionct2 = 0;

    for (int i = 0; i < oldMapSize; i++) {
        if (oldMap[i] != NULL) {
            hashNode *node = oldMap[i];
            int index = getIndex(node->keyword);
            if (index != -1) {
                map[index] = node;
                numKeys++;
            } else {
                cerr << "Error: Cannot rehash key '" << node->keyword << "'." << endl;
            }
        }
    }

    delete[] oldMap;
}

int hashMap::collHash1(int h, int i, string k) {
    int index = (h + i) % mapSize;
    if (index < 0) index += mapSize;
    return index;
}

int hashMap::collHash2(int h, int i, string k) {
    int hash2 = calcHash(k);
    hash2 = hash2 % (mapSize - 1) + 1;
    int index = (h + i * hash2) % mapSize;
    if (index < 0) index += mapSize;
    return index;
}

int hashMap::findKey(string k) {
    int index;
    if (h1) {
        index = calcHash(k);
    } else {
        index = calcHash2(k);
    }
    if (index < 0) index += mapSize;

    int i = 0;
    int originalIndex = index;
    while (true) {
        if (map[index] == NULL) {
            return -1;
        } else if (map[index]->keyword == k) {
            return index;
        } else {
            i++;
            if (i >= mapSize) {
                return -1;
            }
            if (c1) {
                index = collHash1(originalIndex, i, k);
            } else {
                index = collHash2(originalIndex, i, k);
            }
            if (index < 0) index += mapSize;
        }
    }
}

void hashMap::printCollisionCounts() {
    cout << "Original collisions (collisionct1): " << collisionct1 << endl;
    cout << "Secondary collisions (collisionct2): " << collisionct2 << endl;
}
