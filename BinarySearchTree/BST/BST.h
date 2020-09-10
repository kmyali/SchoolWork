#include <cassert>
#include <cstddef>      // for definition of size_t
#include <functional>   // std::function
#include <memory>       // std::unique_ptr
#include <iostream>

template<typename T, typename Comparator = std::less<T>>
class BinarySearchTree
{
public:
	//! Does this tree contain the given value?
	bool contains(const T& value)
	{
		return (not empty() and root_->contains(value));
	}

	size_t maxDepth() const
	{
		if (empty())
		{
			return 0;
		}

		return root_->maxDepth();
	}

	//! Is this tree empty?
	bool empty() const
	{
		return (not root_);
	}

	//! Insert a new value into the appropriate place in the tree.
	void insert(T value)
	{
		insert(std::move(value), root_);
	}

	const T& min() const
	{
		assert(root_);
		return root_->min().value();
	}

	const T& max() const
	{
		assert(root_);
		return root_->max().value();
	}

	bool remove(const T&& value)
	{
		return remove(value, root_);
	}

	void printDot(std::ostream& o) const {
		std::cout << "digraph G {\n";
		if (root_ != nullptr) {
			root_->printDot(o); //call the recursive Node::printDot on the tree's root
		}
		std::cout << "}\n";
	}
	
	void rotateLeft(){
		root_->rotateLeft(); //Apply Node::rotateLeft() to the root. This function is tested and working.
	}
	
	void rotateRight(){
		root_->rotateRight();
	}

protected:
	struct Node
	{
		// the modified node constructor that includes
		Node(T&& value, const Comparator& compare)
			: element_(value), count_(1), compare_(compare)
		{
		}

		const T& value() const {
			return element_; 
		}

		bool contains(const T& value) const {

			//if value<element_, look for value in left subtree
			if (compare_(value, element_)) {
				return left_->contains(value) and right_;
			}

			// if value>element_, look for value in right subtree
			else if (compare_(element_, value)) {
				return right_->contains(value) and right_;
			}

			//if the value==element, return true
			else {
				return true;
			}
		}
		
		Node& min() {
			
			//if a left pointer exists
			if (left_ != nullptr) {
				return left_->min();
			}
			else {
				return *this;
			}
		}
		
		Node& max() {

			//if a right pointer exists
			if (right_ != nullptr) {
				return right_->max();
			}
			else {
				return *this;
			}
		}
		
		//This function finds the minimum value in a subtree and moves its value
		T takeMin() {
			if (left_) {
				return left_->takeMin();
			}
			return std::move(element_);
		}
		
		size_t maxDepth() const {
			size_t depth=0;
			if (left_ or right_) {
				depth++;
			}
			if (left_) {
				depth += left_->maxDepth();
			}
			if (right_) {
				if (right_->maxDepth() > depth) {
					depth += right_->maxDepth();
				}
			}
			else if (not left_ and not right_) {
				return 0;
			}
			return depth;
		}

		void printDot(std::ostream& o) const {
			std::cout << std::endl<< element_ << " [ label = \"count " << count_ << ", value " << element_ << "\" ];\n"; //printing info about current node

			if (left_) {
				std::cout << element_ << " -> " << left_->value() << " [ label = \"L\" ];\n"; //print its left child if it exists
			}
			if (right_) {
				std::cout << element_ << " -> " << right_->value() << " [ label = \"R\" ];\n"; 
			}

			if(left_){ 
				left_->printDot(o);  //recursive call on left child if it exists
			}
			
			if (right_) {
				right_->printDot(o);
			}
		}

		// To be called on the parent of the subtree's root
		void rotateRight() {
			std::unique_ptr<Node> prevRoot = std::move(left_);
			left_ = std::move(prevRoot->left_);

			std::unique_ptr<Node> temp;
			if (left_->right_) {
				temp = std::move(left_->right_);
			}
			left_->right_ = std::move(prevRoot); 
			left_->right_->left_ = std::move(temp);
		}

		void rotateLeft() {
			std::unique_ptr<Node> prevRoot = std::move(right_);
			right_ = std::move(prevRoot->right_);

			std::unique_ptr<Node> temp;
			if (right_->left_) {
				temp = std::move(left_->right_);
			}
			right_->left_ = std::move(prevRoot); 
			right_->left_->right_ = std::move(temp);
		}
		
		const Comparator& compare_;
		T element_;
		size_t count_;
		std::unique_ptr<Node> left_;
		std::unique_ptr<Node> right_;
	};

	void insert(T&& value, std::unique_ptr<Node>& node) {
		if (node.get() == nullptr) {
			node = std::make_unique<Node>(std::move(value), compare_);
		}
		else if (compare_(node->value(), value)){
			insert(std::move(value), node->right_);
		}
		else if (compare_(value, node->value())) {
			insert(std::move(value), node->left_);
		}
		else if (value == node->value()) {
			(node->count_)++; // If the value already exists, increment the counter for the node with that value
		}
		else {
			throw "Unexpected state reached";
		}
	}

	bool remove(const T& value, std::unique_ptr<Node>& node) {
		
		//If tree is empty
		if (node == nullptr) { return false; }
		
		// Searching for the node with the passed in value
		else if (compare_(node->value(), value)) {
			remove(value, node->right_);
		}
		
		else if (compare_(value, node->value())) {
			remove(value, node->left_);
		}
		
		//if the value exists in a node with two children
		else if(node->left_ and node->right_){
			T minGreater = node->right_->takeMin(); //remove minimum value in right subtree 
			remove(minGreater, node->right_); //remove the replacing value from its original node
			node->element_ = std::move(minGreater); // replace value that should be deleted with minGreater 
		}
		
		//if the value exists in a node with zero or one child
		else
		{
			node.swap(node->left_ ? node->left_ : node->right_); // replace with the child pointer
			return true;
		}
	}

	Comparator compare_;
	std::unique_ptr<Node> root_;
};

template<typename T>
class AvlTree {

private:
	struct Node;

public:
	AvlTree(){} //empty constructor

	Node* insert(T&& value) {

		//perform normal insertion
		insert(std::move(T), root_);
		
		//if balanceFactor = -2, do left rotate
		if (root_->calcBalance() = -2) {
			root_->leftRotate();
		}

		//if balanceFactor =2, do left rotate
		if (root_->calcBalance() = 2) {
			root_->rightRotate();
		}
	}
	
private:
	struct Node
	{
		// the modified node constructor that includes
		Node(T&& value, const Comparator& compare)
			: element_(value), count_(1), compare_(compare)
		{
		}

		//returns the balance factor that is used to balance the tree
		int calcBalance{
			return (right_->height) - (left_->height);
		}

		const T& value() const {
			return element_;
		}

		bool contains(const T& value) const {

			//if value<element_, look for value in left subtree
			if (compare_(value, element_)) {
				return left_->contains(value) and right_;
			}

			// if value>element_, look for value in right subtree
			else if (compare_(element_, value)) {
				return right_->contains(value) and right_;
			}

			//if the value==element, return true
			else {
				return true;
			}
		}

		Node& min() {

			//if a left pointer exists
			if (left_ != nullptr) {
				return left_->min();
			}
			else {
				return *this;
			}
		}

		Node& max() {
			
			//if a right pointer exists
			if (right_ != nullptr) {
				return right_->max();
			}
			else {
				return *this;
			}
		}

		//This function finds the minimum value in a subtree and steals it
		T takeMin() {
			if (left_) {
				return left_->takeMin();
			}
			return std::move(element_);
		}

		size_t maxDepth() const {
			size_t depth = 0;
			if (left_ or right_) {
				depth++;
			}
			if (left_) {
				depth += left_->maxDepth();
			}
			if (right_) {
				if (right_->maxDepth() > depth) {
					depth += right_->maxDepth();
				}
			}
			else if (not left_ and not right_) {
				return 0;
			}
			return depth;
		}

		void printDot(std::ostream& o) const {
			std::cout << std::endl << element_ << " [ label = \"count " << count_ << ", value " << element_ << "\" ];\n"; //printing info about current node

			if (left_) {
				std::cout << element_ << " -> " << left_->value() << " [ label = \"L\" ];\n"; //print its left child if it exists
			}
			if (right_) {
				std::cout << element_ << " -> " << right_->value() << " [ label = \"R\" ];\n";
			}

			if (left_) {
				left_->printDot(o);  //recursive call on left child if it exists
			}

			if (right_) {
				right_->printDot(o);
			}
		}

		// To be called on the parent of the subtree's root
		void rotateRight() {
			std::unique_ptr<Node> prevRoot = std::move(left_);
			left_ = std::move(prevRoot->left_);

			std::unique_ptr<Node> temp;
			if (left_->right_) {
				temp = std::move(left_->right_);
			}
			left_->right_ = std::move(prevRoot);
			left_->right_->left_ = std::move(temp);
		}

		void rotateLeft() {
			std::unique_ptr<Node> prevRoot = std::move(right_);
			right_ = std::move(prevRoot->right_);

			std::unique_ptr<Node> temp;
			if (right_->left_) {
				temp = std::move(left_->right_);
			}
			right_->left_ = std::move(prevRoot);
			right_->left_->right_ = std::move(temp);
		}

		const Comparator& compare_;
		T element_;
		size_t count_;
		std::unique_ptr<Node> left_;
		std::unique_ptr<Node> right_;
	};
	std::unique_ptr<BinarySearchTree::Node> root_;
	int height;

};
