#include "DeduplicationSystem.h"
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

// Constructor for DeduplicationSystem
// Initializes the DeduplicationSystem with a directory path and a hash table with a specified number of buckets
DeduplicationSystem::DeduplicationSystem(const string& dirPath, int numBuckets)
    : directoryPath(dirPath), hashTable(numBuckets) {}

// Process files in the directory and add them to the HashMap
void DeduplicationSystem::processFiles() {
    // Create a search path to find all files in the directory using a (*)
    string searchPath = directoryPath + "\\*";

    WIN32_FIND_DATA findFileData; // Structure to hold file information
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &findFileData); // Begin search for files in the directory

    // Check if the directory can be opened
    if (hFind == INVALID_HANDLE_VALUE) {
        cerr << "Error opening directory: " << directoryPath << endl; // Output error if the directory cannot be opened
        return; // Exit the function as no further processing can be done
    }

    // Loop through each file found in the directory
    do {
        const string fileName = findFileData.cFileName; // Retrieve the name of the current file or directory

        // Check if the current item is a file (not a directory)
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            // Construct the full file path
            string filePath = directoryPath + "\\" + fileName;

            // Generate a hash for the file's content
            string fileHash = hashTable.hashFile(filePath);

            // If the hash is valid (non-empty), add the file's hash and path to the hash table
            if (!fileHash.empty()) {
                hashTable.insert(fileHash, FileEntry(filePath));
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0); // Continue to the next file in the directory

    // Close the search handle to release resources
    FindClose(hFind);
}

// Outputs duplicate files and processes them (e.g., removes or marks them)
void DeduplicationSystem::printAndHandleDuplicates() const {
    hashTable.printAndHandleDuplicates();
}
