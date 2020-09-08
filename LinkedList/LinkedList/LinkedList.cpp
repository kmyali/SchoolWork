#include <iostream>

template <typename T>
class Node {
public:
	T value;
	Node* next;
	Node* prev;
	Node() {
		next = nullptr;
		prev = nullptr;
	}
	Node(T value) {
		this->value = value;
		next = nullptr;
		prev = nullptr;
	}
};

template <typename T>
class List {
public:
	Node* head = new Node();
	Node* tail = new Node();
	head->next = tail;
	tail->prev = head;
	Node* currentN = new Node();
	Node* prevN = new Node();
	void add_node(T value, int pos) {
		Node* addee = new Node(value);
		currentN = head;
		for (int i = 0; i < pos; i++ ) {
			prevN = currentN;
			currentN = currentN->next;
		}
		currentN->prev = addee;
		prevN->next = addee;
		addee->next = currentN;
		addee->prev = prevN;
	}
	//deletes the first instance of the node with passed-in value
	void delete_node(T input) {
		currentN = head;
		prevN = currentN;
		while (currentN != tail) {
			if (currentN->value == input) {
				currentN->next->prev = prevN;
				prevN->next = currentN->next;
				break;
			}
			prevN = currentN;
			currentN = currentN->next;
		}
	}
};