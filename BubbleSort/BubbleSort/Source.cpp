#include<chrono>
#include<fstream>
#include<vector>
#include "Header.h"
using namespace std;


int main() {
	std::vector<int> sizes = { 10, 100, 200, 500, 1000, 5000, 10000, 20000, 100000 }; //The sizes for which the bubble sorting algorithm will be tested
	ofstream f;
	f.open("bubbleSort.csv", ios_base::app); //opening the csv file to save results
	f << "Size,Time\n";
	if (!f.is_open()) {
		cout << "Not open\n";
	}

	//Executing the bubble sort for each size in the vector sizes
	for (auto size : sizes) {
		int* array = new int[size];
		f << size << ",";
		cout << size << ",";
		srand(time(NULL));
		for (size_t i = 0; i < size; i++) {
			*(array + i) = rand() % 1000; //assigns values from 0 to 999 in all n array elements
		}

		auto start = std::chrono::high_resolution_clock::now(); //start time
		bubbleSort(size, array);
		auto end = std::chrono::high_resolution_clock::now(); //end time
		f << (end - start).count()<<"\n"; //Writing the time to the file
		cout<< (end - start).count() << "\n";
	}
}

