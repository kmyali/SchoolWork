#include<vector>
#include<string>
#include<list>
#include<fstream>
#include<iostream>
using namespace std;

template<int size>
class hashT {

public:
	hashT() {

	}

	
	hashT& insert(string element) {
		int hashValue = getHash1(element);
		hashTable[hashValue].push_back(element); // Push to the corresponding list
		return *this;
	}

	void printStats() {
		cout << "Hash bucket\t" << "Number of elements\n";
		for (int i = 0; i < size; i++) {
			cout << i + 1 << "\t\t";
			cout<< hashTable[i].size()<<endl;
		}
	}

private:
	int getHash(string element) {
		int h = element[0] % size;
		return h;
	}
	int getHash1(string element) {
		int sum = 0;
		for (int i = 0; i < element.size(); i++) {
			sum += element[i];
		}
		int h = sum % size;
		return h;
	}

	list<string> hashTable[size]; // The hash table is an array of lists of strings
};



int main() {
	hashT<10> table;
	ifstream file;
	file.open("names.csv");
	string line; //to store every line
	
	// Store 200 names in the table
	if (file.is_open()) {
		for (int i = 0; i < 200; i++) {
			getline(file, line);
			int pos0= line.find(","); //Find the first "
			int pos1 = line.find(",", pos0 + 1); // and the second "
			line = line.substr(pos0 + 1, pos1 - pos0 - 1); // Extract the string between them
			table.insert(line); // Add that string to the table
		} // This will be repeated however long we want, initially 200
	}

	file.close();

	table.printStats();
}