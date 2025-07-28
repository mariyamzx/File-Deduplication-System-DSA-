#include "List.h"
#include <iostream>

using namespace std;

// Node Constructor
Node::Node(const FileEntry& fileEntry) : data(fileEntry), next(nullptr) {}

// List Constructor
List::List() : head(nullptr) {}

// List Destructor
List::~List() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

// Add a new file to the list
void List::push_back(const FileEntry& fileEntry) {
    Node* newNode = new Node(fileEntry);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Get the head node
Node* List::begin() const {
    return head;
}

// Check if the list is empty
bool List::empty() const {
    return head == nullptr;
}

// Get all file paths in the list
vector<string> List::getAllFilePaths() const {
    vector<string> filePaths;
    Node* current = head;
    while (current != nullptr) {
        filePaths.push_back(current->data.filePath);
        current = current->next;
    }
    return filePaths;
}

// Print all file paths in the list
void List::print() const {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data.filePath << " ";
        current = current->next;
    }
}
