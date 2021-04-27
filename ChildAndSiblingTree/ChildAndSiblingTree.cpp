#include <iostream>
#include <memory>

template <typename T>
class Tree {
private:

	class Node {
	private:

		T value_;
		std::unique_ptr<Node> child_;
		std::unique_ptr<Node> sibling_;

	public:
		Node() {
		}
		Node(T value) {
			value_ = std::move(value); //the value is moved to the value_ field of the node
		}
		void setValue(T value) {
			value_ = std::move(value);
		}
		void addChild(T value) {
			child_ = std::make_unique<Node>(std::move(value)); //constructing a child node using unique pointer
		}
		void addSibling(T value) {
			Node* n = new Node();
			n = root_.get()->child_.get(); //access the first child pointer

			//traverse across all siblings until sibling pointer is null
			while (n->sibling_.get() != nullptr) {
				n = n->sibling_.get();
			}
			n->sibling_ = std::make_unique<Node>(std::move(value)); //constructing a sibling node using unique pointer
		}
		void addTree(std::unique_ptr<Node> otherRoot) {
			Node* n = new Node();
			n= root_.get()->child_.get(); //access the first child pointer

			//traverse across all siblings until sibling pointer is null
			while(n->sibling_.get() != nullptr) {
				n = n->sibling_.get();
			}
			n->sibling_ = std::make_unique<Node>();
			n->sibling_ = std::move(otherRoot); //move other tree's root into the sibling with the nullptr
		}
	};
	std::unique_ptr<Node> root_; // a Tree has a unique_ptr to its root Node

public:
	Tree() {
		root_ = std::make_unique<Node>(); //initializing the Tree with an empty root
	}
	Tree& setRoot(T value) {
		root_.get()->setValue(std::move(value)); //calling setValue method on the root and moving the value
		return *this;
	}
	Tree& addChild(T value) {
		root_.get()->addChild(std::move(value)); //.get() gets the pointer of the node, so that the addChild node method can be called
		return *this;
	}
	Tree& addSibling(T value) {
		root_.get()->addSibling(std::move(value));
		return *this;
	}
	Tree& addSubtree(Tree<T>&& otherTree) {
		//change the unique_ptr to other tree's root node into rvalue reference so that it can be stolen/moved
		root_.get()->addTree(std::move(otherTree.root_)); //calling addTree method in Node class on this tree's root node
		return *this;
	}
	void print() {
		root_.get()->print();
	}

};


//Testing
int main() {
	Tree<int> users;

	/*  creating a tree with the following structure
	*	 3
	*    |
	*    5 -> 7 -> 9
	*/
	users.setRoot(3);
	users.addChild(5);
	users.addSibling(7);
	users.addSibling(9);

	/*  creating a tree with the following structure
	*	 11
	*    |
	*    13
	*/
	Tree<int> admins;
	admins.setRoot(11);
	admins.addChild(13);

	/*  After addition, the final structure should look like
	*	 3
	*    |
	*    5 -> 7 -> 9 -> 11
	*				    |
	*			    	13
	*/
	users.addSubtree(std::move(users));
	

}