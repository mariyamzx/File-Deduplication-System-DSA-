#include <iostream>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <vector>
#include <string>
#include <shlobj.h>    // Required for Shell API
#include <functional>  // For std::hash
#include "DeduplicationSystem.h"

using namespace std;

int main() {
     // Welcome message
    cout << "================================================================================" << endl;
    cout << "                           FILE DEDUPLICATION SYSTEM                         " << endl;
    cout << "================================================================================" << endl;

    // Specify the directory path where the files are located
    string directoryPath = "C:\\Users\\mary3\\OneDrive\\Desktop\\FileDeduplicationSystem\\Files";

    // Create a DeduplicationSystem instance with 1000 buckets for HashMap
    cout << "\n \t\t Initializing the File Deduplication System" << endl;
    DeduplicationSystem deduplicationSystem(directoryPath, 1000);

    // Process files in the directory
    cout << "\nStep 1: Scanning and processing files in the directory..." << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    deduplicationSystem.processFiles();
    cout << "\n\nFile scanning and processing completed successfully!" << endl;

    // Check for and handle duplicates
    cout << "\n\nStep 2: Identifying and Handling duplicates..." << endl;
    cout << "-------------------------------------------------------------------------------" << endl ;
    deduplicationSystem.printAndHandleDuplicates();

      // End of program message
    cout << "\n===============================================================================" << endl;
    cout << "                  File Deduplication Process Completed                      " << endl;
    cout << "===============================================================================\n" << endl;

    return 0;
}
