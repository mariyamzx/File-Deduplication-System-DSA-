#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <vector>
#include "List.h" // Include List class for linked lists used in the hashmap

using namespace std;

// HashMap Class for Deduplication
class HashMap {
private:
    vector<List> buckets; // Array of linked lists (buckets)
    int numBuckets;

public:
    // Constructor
    HashMap(int size);

    // SHA-256 Hash Function
    string hashFile(const string& filePath) const;

    // Insert file into HashMap
    void insert(const string& key, const FileEntry& value);

    // Hash function to determine the bucket index
    int hashFunction(const string& key) const;

    // Print all buckets and handle duplicates
    void printAndHandleDuplicates() const;

    // File Comparison for Collision Check
    bool compareFiles(const string& filePath1, const string& filePath2) const;
};

#endif // HASHMAP_H
