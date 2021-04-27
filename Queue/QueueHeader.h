#include<list>
using namespace std;

template<typename T>
class Queue {
private:
	// A queue contains a list and pointers to the first and last elements
	list<T> elements;
	T* first, last;
public:
	Queue() {
		first = nullptr;
		last = nullptr;
	}
	void enqueue(T value) {
		elements.push_front(value);
		first = &elements.front();
	}
	void dequeue() {
		elements.pop_back_back();
		last = &elements.back();
	}
	int size() const {
		unsigned int count = 0;

		//initializing iterators that point to the first element in the list and to one after the
		//end to iterate through the list
		list<T>::iterator begin, end;
		for (begin = first; end != elements.end(); begin++) {
			count++;
		}
		return count;
	}
};