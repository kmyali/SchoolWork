#include <iostream>
#include <stack>

//Author: Kamal Ali

void populateStack(std::stack<int>&, int);
void printStack(std::stack<int>);
void reverseStack(std::stack<int>&);
void insertAtBottom(std::stack<int>&, int);

int main(){

    // Create an empty stack
    std::stack<int> stack1;

    // Add numbers to the stack
    populateStack(stack1, 15);
    
    // Print the initial stack
    printStack(stack1);

    // Reverse the stack
    reverseStack(stack1);

    // Print the reversed stack
    printStack(stack1);
    

}

// Create a stack of size x, with x at bottom of stack and 1 at top of stack.
void populateStack(std::stack<int>& stack, int x){
    for(int i=x; i>0; i--)
    {
        stack.push(i);
    }
    
}

// General algorithm is: Remove and store the current top element, reverse the rest of the stack, 
// then insert the stored element at the bottom 
// Pre-condition: stack.size()>0
void reverseStack(std::stack<int>& stack){
    int x = stack.top();
    stack.pop();

    // Variant expression is stack.size()
    if (stack.size() != 0)
    {
        reverseStack(stack);
    }
        insertAtBottom(stack, x);
}

// Post-condition: ∀i ∈ {0,.. depth} ⋅ stack(i) = old(stack( depth - 1 - i ) ); where depth = stack.size();
    

// Also a recrusive function. 
// Algorithm: remove the top element recursively, insert the new element at the bottom, push all the elements back recusrisvely
// Pre-condition: stack.size()>=0 
void insertAtBottom(std::stack<int>& stack, int x){

    //Variant: stack.size() 
    if (stack.size() != 0)
    {
        int y = stack.top();
        stack.pop();
        insertAtBottom(stack, x);
        stack.push(y);
    }
    
    else if (stack.size() == 0)
    {
        stack.push(x);
    }
}
//Post-condition: 
// ∀i ∈ {0,.. depth-1} ⋅ stack(i) = old( stack(i) )
// ∧ stack(depth-1) = x 
// ∧ stack.size = old(stack.size()) + 1


void printStack(std::stack<int> stack){
    while (!stack.empty())
    {
        std::cout << stack.top() << " ";
        stack.pop();
    }
    std::cout << "\n";
}

