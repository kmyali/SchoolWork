
#include<unordered_set>
#include <iostream>
#include <chrono>
using namespace std;

// Command line tool to time insertion in a hash table based on user-specified load factor
int main(int argc, char** argv) {
    unordered_set<int> hashTable;
    double   size = atof(argv[1]);
    hashTable.max_load_factor(size);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 9999; i++) {
        hashTable.insert(i);
    }
    auto end = std::chrono::high_resolution_clock::now();

    cout << "\nTime taken for load factor of " << size << " is: " << (end - start).count()/100000 <<" ms";
    return 0;
}
