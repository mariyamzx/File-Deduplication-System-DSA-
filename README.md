# 📂 File Deduplication System

## 📌 Overview
The **File Deduplication System** is a C++ application that scans directories to detect and manage duplicate files using cryptographic hashing and custom-built data structures. It is designed to optimize storage by identifying redundant files and safely moving them to the Recycle Bin upon user confirmation.

---

## 🚀 Features
- 📁 Scan a directory to list all files  
- 🔐 Use **SHA-256 hashing** to detect duplicate content  
- ⚙️ Employ custom **HashMap** and **Linked List** for efficient storage  
- 👀 Preview detected duplicates before deletion  
- 🗑 Move confirmed duplicates to the **Recycle Bin** (Windows API)  

---

## 🧱 Modules & Files

/FileDeduplicationSystem
│
├── main.cpp # Entry point
├── DeduplicationSystem.cpp # Main system control logic
├── DeduplicationSystem.h
├── FileManager.cpp # File scanning, hashing, and comparison logic
├── FileManager.h
├── HashMap.cpp # Hash map implementation (buckets using linked lists)
├── HashMap.h
├── List.cpp # Singly linked list for hash buckets
├── List.h
└── README.md



## 🧠 Algorithms Used
- **SHA-256 Hashing** (via OpenSSL) for content fingerprinting  
- **Hash Bucketing** using `std::hash % numBuckets` for file organization  
- **Byte-by-byte Comparison** to confirm file equality  

---

## 🧾 Data Structures
- `FileEntry`: Struct holding file path and metadata  
- `List`: Custom singly linked list class  
- `HashMap`: Buckets with chaining via linked lists  
- `DeduplicationSystem`: Orchestrates the entire process  
- `FileManager`: Handles scanning, hashing, and duplicate comparison  

---

## 📋 How It Works
1. The user specifies a directory path  
2. The system reads files and generates SHA-256 hashes  
3. Files are organized into buckets based on their hashes  
4. Files with the same hash are compared byte-by-byte  
5. Verified duplicates are shown to the user  
6. User decides which duplicates to delete (moved to Recycle Bin)  

---

## ⚙️ Requirements
- C++11 or higher  
- OpenSSL library  
- Windows OS (for Recycle Bin support)  



## 🧪 Build & Run (Windows + g++)

```bash
g++ -std=c++11 -lssl -lcrypto *.cpp -o deduper
./deduper
✅ Make sure OpenSSL is installed and linked properly.
