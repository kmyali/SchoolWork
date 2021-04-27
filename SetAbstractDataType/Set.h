#include <iostream>
using namespace std;

#ifndef SET_H_
#define SET_H_

template<typename T>
class stack {

public:
	stack() {
		topNode = nullptr;
	}

	void push(T value) {
		stackNode* newNode = new stackNode(value); // Create a new stackNode with the value
		newNode->prev = topNode; // set its prev to the current top
		topNode = newNode; //Make this new stackNode the top of the stack
	}

	//Returns the element stored in the top element of the stack
	T top() {
		return topNode->value_;
	}

	//Deletes the top element of the stack
	void pop() {
		topNode = topNode->prev;
	}

	size_t size() const {
		stackNode* temp = topNode;
		size_t ret = 0;
		while (temp != nullptr) {
			ret++;
			temp = temp->prev;
		}
		return ret;
	}

private:
	struct stackNode {
		T value_; //This will be the set node pointer
		stackNode* prev; //Each element of the stack knows where the element preceding it is

		//constructor, initializes the value
		stackNode(T value) {
			value_ = value;
			prev = nullptr;
		}
	};
	stackNode* topNode; // The stack knows where its top element is

};

template<typename T>
class Set
{
private:
	class Iterator;
	class ConstIterator;
public:
	Set() {
		root_ = nullptr;
	}

	void insert(T value)
	{
		insert(std::move(value), root_); // Call to the internal insert 
	}

	bool contains(const T& value) const {
		ConstIterator it; // construct an iterator to walk through all nodes
		it.setPtr(root_);
		return it.contains(std::move(value), root_); //Call to the internal ConstIterator::contains method
	}

	//! How many values are in this set?
	size_t size() const {
		ConstIterator it = begin();
		ConstIterator endIt = end(); // for easier debugging
		size_t ret = 0;

		//Visit each node and increment by 1 each time
		for (it; it != endIt; ++it) {
			ret++;
		}
		return ret;
	}
	
	Iterator begin() {
		Iterator it; // Create an Iterator object

		//if no root exists, set to nullptr which is the same as end
		if (not root_) {
			it.setPtr(nullptr);
		}

		else {
			it.setPtr(root_);
			it.InOrderBegin(); //InOrderBegin was used to traverse the underlying BST.
							   // The choice of InOrder is arbitrary.
		}
		return it;
	}
	ConstIterator begin() const {
		ConstIterator it; 

		if (not root_) {
			it.setPtr(nullptr);
		}

		else {
			it.setPtr(root_);
			it.InOrderBegin();
		}
		return it;
	}

	//end iterator is always a nullptr
	Iterator end() {
		Iterator it;
		it.setPtr(nullptr);
		return it;
	}
	ConstIterator end() const {
		ConstIterator it;
		it.setPtr(nullptr);
		return it;
	}

	//Find an element and return an iterator pointing to it if found, or to nullptr otherwise
	Iterator find(const T& value) {
		Iterator it;
		it.setPtr(root_);
		it.find(value, root_); //call to the Iterator::find method
		return it;
	}
	ConstIterator find(const T& value) const{
		Iterator it;
		it.setPtr(root_);
		it.find(value, root_);
		return it;
	}


private:
	struct Node {
		T value_;
		Node* right_;
		Node* left_;

		//Node constructor, initializes the value
		Node(T value) {
			value_ = std::move(value);
			right_ = nullptr;
			left_ = nullptr;
		}


		//Node constructor, without initializing the value
		Node() {
			right_ = nullptr;
			left_ = nullptr;
		}

		void setValue(T value){
			value_ = std::move(value);
		}

	};
	Node* root_; // Every set has a Node pointer to its root

	void insert(T&& value, Node*& nodePtr) {

		//If no root, initialize the root
		if (nodePtr == nullptr)
		{
			Node* temp = new Node(std::move(value)); //initializing a Node struct and storing the pointer temporarily. 
			nodePtr = temp;
			temp = nullptr; //Reducing memory leakage
		}

		else if (value < nodePtr->value_)
		{
			insert(std::move(value), nodePtr->left_);
		}

		else if (value > nodePtr->value_)
		{
			insert(std::move(value), nodePtr->right_);
		}

		else
		{
			// If they are equal, nothing will happen, since no duplicates allowed
		}
	}

	class ConstIterator {
	public:

		//Empty constructor
		ConstIterator() {
		}

		void setPtr(Node* other) {
			currentPtr = other;
		}

		ConstIterator operator ++ () {

			//The end condition for iteration is pointing to maximum.
			if (not currentPtr->right_ and nodeStack.size() == 0) {
				currentPtr = nullptr;
			}

			//If we are at a leaf node, take from the stack
			else if (not currentPtr->left_ and not currentPtr->right_) {
				currentPtr = nodeStack.top();
				nodeStack.pop();
			}

			//Having either (left and right) or (right only) follows the same logic
			else if (currentPtr->right_) {
				currentPtr = currentPtr->right_;
				this->InOrderBegin();
			}

			//Having only a left, visit parent
			else if (currentPtr->left_) {
				currentPtr = nodeStack.top();
				nodeStack.pop();
			}
			//The above should cover all cases.
			return *this;

		}

		const T& operator * () {
			return currentPtr->value_;
		}

		bool operator != (ConstIterator other) {
			return (currentPtr != other.currentPtr);
		}

		bool operator == (ConstIterator other) {
			return (currentPtr == other.currentPtr);
		}

		//Used internally to stack the right nodes when needed
		void InOrderBegin() {
			if (currentPtr->left_) {
				nodeStack.push(currentPtr);
				currentPtr = currentPtr->left_;
				InOrderBegin();
			}

			else {
				// When the iterator reaches the minimum, do nothing. The recursion terminates.
			}
		}

		void find(T&& value, Node* nodePtr) {

			//If no root or element not found, return nullptr
			if (not nodePtr)
			{
				setPtr(nullptr);
			}

			else if (value < nodePtr->value_)
			{
				find(value, nodePtr->left_); //if value is less than the one in node, search in left subtree
			}

			else if (value > nodePtr->value_)
			{
				find(value, nodePtr->right_);
			}

			else
			{
				setPtr(nodePtr); //If the element is found, set the iterator's pointer to point to it
			}
		}

		bool contains(const T&& value, Node* nodePtr) const {
			//If no root or element not found, return false
			if (not nodePtr)
			{
				return false;
			}

			else if (value < nodePtr->value_)
			{
				contains(std::move(value), nodePtr->left_); 
			}

			else if (value > nodePtr->value_)
			{
				contains(std::move(value), nodePtr->right_);
			}

			else
			{
				return true; //If the element is found, return true
			}
		}

	private:
		Node* currentPtr;
		stack<Node*> nodeStack;
	};

	class Iterator {
	public:
		Iterator() {}

		void setPtr(Node* other) {
			currentPtr = other;
		}

		Iterator& operator ++ () {

			if (not currentPtr->right_ and nodeStack.size() == 0) {
				currentPtr= nullptr;
			}

			else if (not currentPtr->left_ and not currentPtr->right_) {
				currentPtr = nodeStack.top();
				nodeStack.pop();
			}

			else if (currentPtr->right_) {
				currentPtr = currentPtr->right_;
				this->InOrderBegin();
			}

			else if (currentPtr->left_) {
				currentPtr = nodeStack.top();
				nodeStack.pop();
			}
			
			return *this;

		}
		
		T& operator * () {
			return currentPtr->value_;
		}

		bool operator != (Iterator other) {
			return (currentPtr != other.currentPtr);
		}

		bool operator == (Iterator other) {
			return (currentPtr == other.currentPtr);
		}

		void InOrderBegin() {
			if (currentPtr->left_) {
				nodeStack.push(currentPtr);
				currentPtr = currentPtr->left_;
				InOrderBegin();
			}

			else {}
		}

		void find(const T& value, Node* nodePtr) {

			if (not nodePtr)
			{
				setPtr(nullptr);
			}

			else if (value < nodePtr->value_)
			{
				find(std::move(value), nodePtr->left_); 
			}

			else if (value > nodePtr->value_)
			{
				find(std::move(value), nodePtr->right_);
			}

			else
			{
				setPtr(nodePtr);
			}
		}

		bool contains(const T&& value, Node* nodePtr)  {
			if (not nodePtr)
			{
				return false;
			}

			else if (value < nodePtr->value_)
			{
				contains(std::move(value), nodePtr->left_); 
			}

			else if (value > nodePtr->value_)
			{
				contains(std::move(value), nodePtr->right_);
			}

			else
			{
				return true;
			}
		}
	private:
		Node* currentPtr;
		stack<Node*> nodeStack;

	};

};

#endif