#include <iostream>
#include <chrono>

using namespace std;


template <typename X>
X flip(X data[], int i, int j)
{
	X temp = data(i);
	data(i) = data(j);
	data(j) = temp;
}
/*flip(int data[], int i, int j)
{
	temp = data(i);
	data(i) = data(j);
	data(j) = tmp;
}
*/
/*
template <typename T2>
T2 BubbleSort(T2 list, unsigned int size) {
	for (int i = 0; i <= size; i++) {
		cout << "HI";
	}
}
/*