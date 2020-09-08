#include <cassert>
#include <cstddef>      // for definition of size_t
#include <functional>   // std::function
#include <memory>       // std::unique_ptr
#include <stack>

template<typename T, typename Comparator = std::less<T>>
class BinarySearchTree
{
private:
	struct Node;
public:
	enum class Traversal
	{
		PreOrder,
		InOrder,
		PostOrder,
	};

	//! Insert a new value into the appropriate place in the tree.
	void insert(T value)
	{
		insert(std::move(value), root_);
	}

	void dot(std::ostream& o) const
	{
		o << "digraph {\n";

		if (root_)
		{
			root_->dot(o);
		}

		o << "}\n";
	}

	/**
	 * An iterator that can traverse the BST in some order.
	 *
	 * The iterator contains a "current" node, a stack of parent nodes and
	 * a Traversal value to remind it which strategy it's following.
	 */
	class Iterator
	{
	public:
		Iterator() {
			//empty constructor
		}

		Iterator(Traversal order_) {
			order = order_;
		}

		void setPtr(Node* other) {
			current = other;
		}

		//Iterator& operator = (Iterator other){}

		Iterator operator ++ (int) {
			if (order == Traversal::PreOrder) {
				return PreNext();
			}
			else if (order == Traversal::PostOrder) {
				return PostNext();
			}
			// (order == Traversal::InOrder)
			else {
				return InNext();
			}
		}

		const T& operator * () {
			return current->element_;
		}

		bool operator != (const Iterator& other) {
			if (current != other.current) {
				return true;
			}
			else {
				return false;
			}
		}

		void PostBegin() {
			// if there is a left
			if (current->left_) {
				nodeStack.push(current);
				current = current->left_.get();
				this->PostBegin();
			}

			// No left, only right
			else if (current->right_) {
				nodeStack.push(current);
				current = current->right_.get();
				this->PostBegin();
			}

			//No left nor right
			else if (not current->left_ and not current->right_) {
				// Do nothing. The recursion terminates
			}

			else {
				throw"Unexpected condition in PostBegin";
			}
		}

		void InOrderBegin() {
			if (current->left_) {
				nodeStack.push(current);
				current = current->left_.get();
				InOrderBegin();
			}

			// When the iterator reaches the minimum
			else {
				//Do nothing. The recursion terminates.
			}
		}

	private:
		Traversal order;
		Node* current;
		std::stack<Node*> nodeStack;

		Iterator PreNext() {

			//Case 0: end of iteration, checked first to avoid logic errors
			if (nodeStack.size() == 0 and not current->left_ and not current->right_) {
				current = nullptr;
			}

			//Case 1: either (a left and a right exist) or (a left only exists)
			else if (current->left_) {

				if (current->right_) {
					nodeStack.push(current->right_.get()); // Stack a non-owning pointer to the right node if it exists
				}

				current = current->left_.get(); //Go to left node either way
			}

			//Case 2: only a right exists
			else if (current->right_) {
				current = current->right_.get();
			}

			//Case 3: Neither a left nor a right
			else if (not current->left_ and not current->right_) {
				current = nodeStack.top(); // Go to the node at the top of the stack
				nodeStack.pop();	// Delete it from the stack
			}

			//To catch potential logic errors while testing
			else {
				throw "unexpected condition reached in PreOrder";
			}

			return *this;
		}
		Iterator PostNext() {
			if (nodeStack.size() == 0 ) {
				current = nullptr;
			}
			// When pointing to a leaf node
			else if (not current->left_ and not current->right_) {

				// If pointing to the left child and haven't visited right yet
				if (current != nodeStack.top()->right_.get()) {

					// Make sure right child exists first, then visit it in post order
					if (nodeStack.top()->right_.get() != nullptr) {
						current = nodeStack.top()->right_.get();
						this->PostBegin();
					}

					//Right child is a nullptr, so visit the parent
					else {
						current = nodeStack.top();
						nodeStack.pop();
					}
				}

				//If pointing to the right child, visit the parent next
				else {
					current = nodeStack.top();
					nodeStack.pop();
				}
			}

			//If current has at least a left, then we already visited it
			else if (current->left_) {
				
				//if we are already at the right child, visit parent
				if (nodeStack.top()->right_.get() == current) {
					current = nodeStack.top();
					nodeStack.pop();
				}
				//Make sure a right child of this node's parent exists, if it does visit it in Post Order
				else if (nodeStack.top()->right_.get() != nullptr) {
					current = nodeStack.top()->right_.get();
					this->PostBegin();
				}
				
				// We are at left child of parent, but parent has no right, then visit parent
				else {
					current = nodeStack.top();
					nodeStack.pop();
				}
				
			}

			//No left, only right and we visited right, visit parent
			else if (current->right_) {

				//check if parent has a right child that is not the current node, if yes visit it
				if (nodeStack.top()->right_.get() != nullptr and nodeStack.top()->right_.get() != current) {
					current = nodeStack.top()->right_.get();
					this->PostBegin();
				}
				else {
					current = nodeStack.top();
					nodeStack.pop();
				}
				
			}

			return *this;
		}
		Iterator InNext() {

			if (not current->right_ and nodeStack.size() == 0) {
				current = nullptr;
			}
			//If we are at a leaf node, take from the stack
			else if (not current->left_ and not current->right_) {
				current = nodeStack.top();
				nodeStack.pop();
			}

			//Having either (left and right) or (right only) follows the same logic
			else if (current->right_) {
				current = current->right_.get();
				this->InOrderBegin();
			}

			//Having only a left, visit parent
			else if (current->left_) {
				current = nodeStack.top();
				nodeStack.pop();
			}
			//The above cases should cover all cases.
			return *this;

		}

	};



	Iterator begin(Traversal order) {
		Iterator it(order);

		//if a root exists, start from there
		if (root_) {
			it.setPtr(root_.get()); 
		}
		else {
			it.setPtr(nullptr);
			return it;
		}

		if (order == Traversal::PreOrder) {
			return it; //preOrder starts at the root
		}


		else if (order == Traversal::PostOrder) {
			it.PostBegin();
		}

		//If in order return a pointer to minimum
		else if (order == Traversal::InOrder) {
			it.InOrderBegin();
		}
		return it;
	}
	Iterator end() {
		Iterator it(Traversal::InOrder);//default to InOrder to match the parameter list of constructor. wouldn't affect result because it is not compared
		it.setPtr(nullptr);
		return it;
	}
	Iterator max() {

	}
private:
	struct Node
	{
		Node(T value) : element_(std::move(value))
		{
		}

		void dot(std::ostream& o) const
		{
			// NOTE: this is slightly more complicated than strictly
			//       necessary (using addresses as names, etc.), but
			//       it will produce valid Dot output even when the
			//       node values are things like money (e.g., $17)

			o
				<< "  \"" << this << "\""
				<< " [ label = \"" << element_ << "\" ];\n";

			if (left_)
			{
				o
					<< "  \"" << this << "\""
					<< " -> "
					<< "\"" << left_.get() << "\""
					<< " [ label = \"L\" ]\n";

				left_->dot(o);
			}

			if (right_)
			{
				o
					<< "  \"" << this << "\""
					<< " -> "
					<< "\"" << right_.get() << "\""
					<< " [ label = \"R\" ]\n";

				right_->dot(o);
			}
		}

		T element_;
		std::unique_ptr<Node> left_;
		std::unique_ptr<Node> right_;
	};

	/**
	 * Internal implementation of recursive insert.
	 *
	 * @param   value      the value to insert
	 * @param   node       the root of the (sub-)tree being inserted into;
	 *                     may be null if the (sub-)tree is empty
	 */
	void insert(T&& value, std::unique_ptr<Node>& node)
	{
		if (not node)
		{
			node = std::make_unique<Node>(std::move(value));
		}
		else if (compare_(value, node->element_))
		{
			insert(std::move(value), node->left_);
		}
		else if (compare_(node->element_, value))
		{
			insert(std::move(value), node->right_);
		}
		else
		{
			// assuming no duplicates
		}
	}

	Comparator compare_;
	std::unique_ptr<Node> root_;
};