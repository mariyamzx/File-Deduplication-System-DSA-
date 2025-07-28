#ifndef DEDUPLICATIONSYSTEM_H
#define DEDUPLICATIONSYSTEM_H

#include <string>
#include "HashMap.h" // Include HashMap class for deduplication

using namespace std;

class DeduplicationSystem {
private:
    string directoryPath;
    HashMap hashTable;

public:
    // Constructor
    DeduplicationSystem(const string& dirPath, int numBuckets);

    // Process files in the directory and add to HashMap
    void processFiles();

    // Print and handle duplicates
    void printAndHandleDuplicates() const;
};

#endif // DEDUPLICATIONSYSTEM_H
