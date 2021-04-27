#include <iostream>
#include "BST.h"

int main() {

	BinarySearchTree<double> tree;
	auto i = tree.begin(BinarySearchTree<double>::Traversal::InOrder);
	auto j = tree.end();
	std::cout << not(i != j);
	tree.insert(2);
	tree.insert(1);
	tree.insert(6);
	tree.insert(3);
	tree.insert(7);
	tree.insert(5);
	tree.insert(4);

	for (auto i = tree.begin(BinarySearchTree<double>::Traversal::PostOrder); i != tree.end(); i++)
	{
		std::cout << *i<<", ";
	}
	
}