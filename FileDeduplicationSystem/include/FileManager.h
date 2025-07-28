#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

using namespace std;

// FileManager Class for Recycle Bin Operations
class FileManager {
public:
    // Static method to move a file to the Recycle Bin
    static void moveToRecycleBin(const string& filePath);
};

#endif // FILEMANAGER_H
