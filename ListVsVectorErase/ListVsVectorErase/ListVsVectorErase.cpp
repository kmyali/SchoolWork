#include<iostream>
#include <list>
#include <vector>
#include <time.h>
#include <chrono>
#include <fstream>
#include"erase.h"
using namespace std;

void eraseTensList(list<int>& list1);
void eraseTensVector(vector<int>& v1);

int main() {
	vector<int> v1;
	list<int> list1;

	//Opening a file to write results to
	ofstream f;
	
	//Opening the file stream in append mode to a csv file where the time taken for each function for each value will be saved
	f.open("eraseTime.csv", ios_base::app);
	
	//Tells the user if the file was not opened successfully
	if (!f.is_open()) {
		cout << "Not open\n";
	}
	f << "Size,Vector Time,List time\n";
	
	vector<int> sizes = { 50, 100, 500, 1000, 3000, 10000, 50000, 100000 };
	for (int size : sizes) {
		srand(time(NULL));
	
		//initialize the vector and list with the same set of random numbers from 1-10
		int value;
		for (int i = 0; i < size; i++) {
			value = (rand() % 10) + 1;
			v1.push_back(value);
			list1.push_back(value);
		}

		/*cout << "Vector elements: ";
		for (int x = 0; x < size; x++) {
			cout << v1[x]<<" ";
		}*/
		auto start = std::chrono::high_resolution_clock::now();
		eraseTensVector(v1);
		auto end = std::chrono::high_resolution_clock::now();
		/*cout << "\nVector elements after: ";
		for (int x = 0; x < v1.size(); x++) {
			cout << v1[x] << " ";
		}*/
		cout << "\nTime taken for vector: " << (end - start).count();
		//Writing time to csv
		f << size << "," << (end - start).count() << ",";


		/*	cout << "\nList elements before: ";
			for (list<int>::iterator i=list1.begin(); i!=list1.end(); i++){
				cout << *i << " ";
			}*/
		start = std::chrono::high_resolution_clock::now();
		eraseTensList(list1);
		end = std::chrono::high_resolution_clock::now();
		/*cout << "\nList elements after: ";
		for (list<int>::iterator i = list1.begin(); i != list1.end(); i++) {
			cout << *i << " ";
		}*/
		cout << "\nTime taken for list: " << (end - start).count();
		f << (end - start).count() << "\n";
	}
	f.close();
}

void eraseTensList(list<int>& list1) {
	for (list<int>::iterator iter=list1.begin(); iter != list1.end(); iter++) {
		if (*iter % 10 == 0) {
			iter=list1.erase(iter);
			iter--;

		}
	}
}

void eraseTensVector(vector<int>& v1) {
	for (size_t j =0; j <v1.size(); j++) {
		if (v1[j] % 10 == 0) {
			//shifting (every element after the element that is divisible by 10) one
			//position to the left, therefore erasing said element.
			for (size_t k = j; k <v1.size()-1; k++) {
				v1[k] = v1[k + 1];
			}
			v1.resize(v1.size() - 1); //resizing the vector
			j--;//decrementing pointer to point to avoid skipping an element
		}
	}
}