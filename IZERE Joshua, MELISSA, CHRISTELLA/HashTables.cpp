#include <bits/stdc++.h>

using namespace std;

// Array size for the Hash Table
const int TABLE_SIZE = 50;

// ==========================================
// 1. DIVISION METHOD
// ==========================================
int divisionHash(const string& key) {
    int sum = 0;
    for (char c : key) {
        sum += c;
    }
    return sum % TABLE_SIZE;
}

// ==========================================
// 2. FOLDING METHOD
// ==========================================
// Breaks the string into 2-character chunks and adds them
int foldingHash(const string& key) {
    int sum = 0;
    for (size_t i = 0; i < key.length(); i += 2) {
        int chunkVal = key[i];
        if (i + 1 < key.length()) {
            // Shift the first char and add the second to create a unique chunk value
            chunkVal = (chunkVal * 256) + key[i+1];
        }
        sum += chunkVal;
    }
    // Handle negative numbers just in case of overflow
    if (sum < 0) sum = -sum;
    return sum % TABLE_SIZE;
}

// ==========================================
// 3. MID-SQUARE METHOD
// ==========================================
int midSquareHash(const string& key) {
    long long sum = 0;
    for (char c : key) {
        sum += c;
    }

    // Square the sum
    long long square = sum * sum;
    string sqStr = to_string(square);

    // Extract the middle 2 digits
    int midIndex = sqStr.length() / 2 - 1;
    if (midIndex < 0) midIndex = 0;

    int midVal = 0;
    if (sqStr.length() >= 2) {
        midVal = stoi(sqStr.substr(midIndex, 2));
    } else {
        midVal = stoi(sqStr);
    }

    return midVal % TABLE_SIZE;
}

// ==========================================
// BENCHMARKING FUNCTION
// ==========================================
int countCollisions(const vector<string>& dataset, int (*hashFunc)(const string&)) {
    // A temporary array to act as our hash table buckets
    vector<int> buckets(TABLE_SIZE, 0);
    int collisions = 0;

    for (const string& name : dataset) {
        int index = hashFunc(name);

        // If the bucket already has something in it, that's a collision
        if (buckets[index] > 0) {
            collisions++;
        }
        // Place the item in the bucket
        buckets[index]++;
    }

    return collisions;
}

int main() {
    // Dataset of 50 Names
    vector<string> names = {
        "Aline", "Kwizera", "Mukamana", "Niyonkuru", "Iradukunda",
        "Uwase", "Hirwa", "Ishimwe", "Divine", "Mugisha",
        "Mugabo", "Charlie", "Chance", "Mike", "Kevine",
        "Davine", "Joy", "Alice", "Tom", "Jane",
        "John", "Chael", "Michael", "Ange", "Peter",
        "Sarah", "David", "Chris", "Emma", "Luke",
        "Paul", "Mark", "Mary", "Anna", "Ruth",
        "Joel", "Amos", "Ezra", "Levi", "Silas",
        "Titus", "Felix", "Jason", "Rufus", "Simon",
        "Jude", "Eli", "Noah", "Seth", "Abel"
    };

    cout << "======================================\n";
    cout << "   HASH FUNCTION BENCHMARK TEST       \n";
    cout << "======================================\n";
    cout << "Dataset Size: " << names.size() << " elements\n";
    cout << "Hash Table Size: " << TABLE_SIZE << " buckets\n\n";

    // Run tests
    int divCollisions = countCollisions(names, divisionHash);
    int foldCollisions = countCollisions(names, foldingHash);
    int midSqCollisions = countCollisions(names, midSquareHash);

    // Output Results
    cout << "1. Division Method Collisions  : " << divCollisions << "\n";
    cout << "2. Folding Method Collisions   : " << foldCollisions << "\n";
    cout << "3. Mid-Square Method Collisions: " << midSqCollisions << "\n";
    cout << "======================================\n";

    return 0;
}
