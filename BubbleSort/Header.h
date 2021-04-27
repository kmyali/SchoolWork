#include <iostream>
#include <cstdlib>
using namespace std;

template <typename T>
void flip(unsigned int pos, T* array); //declaration

template <typename T>
void bubbleSort(unsigned int size, T* array) {
	for (size_t i = 0; i < size - 1; i++) {
		for (size_t j = 0; j < size - i - 1; j++) {
			if (*(array + j) < *(array + j + 1)) {
				flip(j, array);
			}
		}
	}
}

//flip swaps the positions of the element in positions (pos) and (pos+1)
template <typename T>
void flip(unsigned int pos, T* array) {
	T temp = *(array + pos);
	*(array + pos) = *(array + pos + 1);
	*(array + pos + 1) = temp;
}
