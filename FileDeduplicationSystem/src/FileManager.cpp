#include "FileManager.h"  // Include the header file for class definition
#include <iostream>       // For input/output operations
#include <shlobj.h>       // Required for Shell API (SHFileOperation)

using namespace std;

// FileManager method to move a file to the Recycle Bin
void FileManager::moveToRecycleBin(const string& filePath) {
    // Format the file path to make it compatible with SHFileOperation
    // Add an extra null character at the end of the file path for proper termination
    string formattedPath = filePath + '\0';

    // Initialize the SHFILEOPSTRUCT structure for file operations
    SHFILEOPSTRUCT fileOp = {0};
    fileOp.wFunc = FO_DELETE;                // Specify the operation as 'delete'
    fileOp.pFrom = formattedPath.c_str();   // File path to operate on (as C-string)
    fileOp.fFlags = FOF_ALLOWUNDO           // Enable undo (move to Recycle Bin)
                 | FOF_NOCONFIRMATION       // Skip confirmation dialogs
                 | FOF_SILENT;              // Suppress UI during the operation

    // Perform the file operation
    int result = SHFileOperation(&fileOp);

    // Check the result and provide feedback
    if (result == 0) {
        cout << "Moved file to Recycle Bin: " << filePath << endl;
    } else {
        cerr << "Failed to move file to Recycle Bin: " << filePath << endl;
    }
}
