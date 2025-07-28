#include "HashMap.h"
#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>
#include <cstring>

using namespace std;

// Constructor for HashMap
HashMap::HashMap(int size) : numBuckets(size), buckets(size) {}

// SHA-256 Hash Function
string HashMap::hashFile(const string& filePath) const {
    ifstream file(filePath, ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return "";
    }

    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_len;

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if (mdctx == nullptr) {
        cerr << "Failed to create context for file: " << filePath << endl;
        return "";
    }

    //EVP_DigestInit_ex is an OpenSSL function that initializes a cryptographic context (EVP_MD_CTX) for hashing.
    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr) != 1) {
        cerr << "Failed to initialize digest for file: " << filePath << endl;
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    char buffer[4096];
    while (file.read(buffer, sizeof(buffer))) {
        if (EVP_DigestUpdate(mdctx, buffer, file.gcount()) != 1) {
            cerr << "Failed to update digest for file: " << filePath << endl;
            EVP_MD_CTX_free(mdctx);
            return "";
        }
    }

    if (file.gcount() > 0) {
        if (EVP_DigestUpdate(mdctx, buffer, file.gcount()) != 1) {
            cerr << "Failed to update digest for file: " << filePath << endl;
            EVP_MD_CTX_free(mdctx);
            return "";
        }
    }

    if (EVP_DigestFinal_ex(mdctx, digest, &digest_len) != 1) {
        cerr << "Failed to finalize digest for file: " << filePath << endl;
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    ostringstream hashStream;
    for (unsigned int i = 0; i < digest_len; i++) {
        hashStream << hex << setw(2) << setfill('0') << (int)digest[i];
    }

    EVP_MD_CTX_free(mdctx);
    return hashStream.str();
}

// Insert file into HashMap
void HashMap::insert(const string& key, const FileEntry& value) {
    int bucketIndex = hashFunction(key);
    List& list = buckets[bucketIndex];

    //cout << "Inserting file with hash: " << key << " (" << value.filePath << ")" << endl;
    cout << "\nFile Path : "<<value.filePath << endl << "Hash Value: " <<key <<endl;
    list.push_back(value);
}

// Hash function to determine the bucket index
int HashMap::hashFunction(const string& key) const {
    // Using std::hash to generate a hash value from the string
    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(key);  // Generate a hash for the file path string
    return hash % numBuckets;  // Ensure it's mapped within bucket range
}

// Print all buckets and handle duplicates
void HashMap::printAndHandleDuplicates() const {
    for (int i = 0; i < numBuckets; ++i) {
        if (!buckets[i].empty()) {
            vector<string> filePaths = buckets[i].getAllFilePaths();
            if (filePaths.size() > 1) {
                cout << "\nPossible duplicates found in Bucket " << i << ":" << endl;
                for (size_t j = 0; j < filePaths.size(); ++j) {
                    cout << "- " << filePaths[j] << endl;
                }

                // Prompt user to confirm deletion
                char choice;
                cout << "Do you want to send duplicates to the Recycle Bin? (y/n): ";
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    for (size_t j = 1; j < filePaths.size(); ++j) {
                        // Call moveToRecycleBin or any equivalent function
                        FileManager::moveToRecycleBin(filePaths[j]);
                    }
                }
            }
        }
    }
}

// File Comparison for Collision Check
bool HashMap::compareFiles(const string& filePath1, const string& filePath2) const {
    // First check if hash values are identical before comparing file content
    string hash1 = hashFile(filePath1);
    string hash2 = hashFile(filePath2);

    if (hash1 != hash2) {
        return false;  // Files have different hashes, so they are not duplicates
    }

    // If hashes are the same, compare file contents byte by byte
    ifstream file1(filePath1, ios::binary);
    ifstream file2(filePath2, ios::binary);
    if (!file1.is_open() || !file2.is_open()) {
        cerr << "Error opening files for comparison" << endl;
        return false;
    }

    char buffer1[4096], buffer2[4096];
    while (file1.read(buffer1, sizeof(buffer1)) && file2.read(buffer2, sizeof(buffer2))) {
        if (memcmp(buffer1, buffer2, file1.gcount()) != 0) {
            return false;  // Files are not identical
        }
    }

    return true;  // Files are identical
}
