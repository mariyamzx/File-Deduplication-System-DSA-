#ifndef LIST_H
#define LIST_H

#include <string>
#include <vector>

using namespace std;

// FileEntry Structure
struct FileEntry {
    string filePath; // Path of the file

    FileEntry(const string& path) : filePath(path) {}
};

// Node Structure for Linked List
struct Node {
    FileEntry data; // FileEntry data
    Node* next;     // Pointer to the next node

    Node(const FileEntry& fileEntry);
};

// List Class (Linked List)
class List {
private:
    Node* head; // Head of the linked list

public:
    List();  // Constructor
    ~List(); // Destructor

    void push_back(const FileEntry& fileEntry); // Add a new file to the list
    Node* begin() const;                        // Get the head node
    bool empty() const;                         // Check if the list is empty
    vector<string> getAllFilePaths() const;     // Get all file paths in the list
    void print() const;                         // Print all file paths
};

#endif // LIST_H
