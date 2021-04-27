#include <iostream>
#include <list>
using namespace std;

template<typename T1>
list<T1>& quickSort(list<T1>& listq);
template<typename T>
T medianOf3(list<T>& listm);

int main() {
	list<int> list1 = { 3,4,2,5,1 };
	quickSort(list1);
	for (list<int>::iterator i = list1.begin(); i != list1.end(); i++) {
		cout << *i << " ";
	}
	return 0;
}


template<typename T>
T medianOf3(list<T>& listm){ //listm for list median
	unsigned int pos = listm.size() / 2;
	typename std::list<T>::iterator iter = listm.begin();
	advance(iter, pos); //advance iterator to point to element at the middle of the list
	T front = listm.front();
	T back = listm.back();
	if ((front > back) != (front > * iter)) {
		return front;
	}
	else if ((back > front) != (back > * iter)) {
		return back;
	}
	else {
		return *iter;
	}
}

template<typename T1>
list<T1>& quickSort(list<T1>& listq) { //listq for listquickSort
	list<T1> less, greater, equal;
	if (listq.size() == 1) {
		return listq;
	}
	else {
		T1 med = medianOf3(listq);
		//Loops through all elements and divides them into three containers: "less", "greater", or "equal" to the pivot
		for (typename list<T1>::iterator iter = listq.begin(); iter != listq.end(); iter++) {
			if (*iter > med) {
				greater.push_back(*iter);
			}
			else if (*iter < med) {
				less.push_back(*iter);
			}
			else {
				equal.push_back(*iter);
			}
		}
		listq.clear();//clears the original unsorted array to replace it with the sorted one
		typename list<T1>::iterator iter = listq.begin();
		listq.splice(iter, quickSort(less));
		listq.splice(iter, quickSort(equal));
		listq.splice(iter, quickSort(greater));
		return listq;
	}
}