#include <iostream>
#include<assert.h>
#include<vector>
#include<queue>
using namespace std;

// Author: Kamal Ali

void MaxHeapify(int array[], int size, int i);
void MaxHeapifyNR(int array[], int size, int i);

int max(int array[], int, int);
void swap(int array[], int, int);
bool isEven(int);
bool isOdd(int);
void printArray(int array[], int size);
void assertIsMaxHeap(int array[], int size, int i);

int main(){
    int size=9;
    int* array= new int[size];
    for(int i=0; i<size; i++){
        *(array+i) = i+1;
    }

    MaxHeapify(array, size, 0);
    assertIsMaxHeap(array,size,0);
    printArray(array, size);

}


void MaxHeapify(int array[], int size, int i){
    
    // Precondition
    assert(size>0 and i>=0 and i<size); 

    if(2*i+2<size){
        MaxHeapify(array, size, 2*i+1); // Although the question assumes children are max heaps, we can
        MaxHeapify(array, size, 2*i+2); // call the method on both children first

        // Get maximum of two children nodes
        int greater = max(array, 2*i+2, 2*i+1);

        // If a child is greater than the parent node, swap them and call MaxHeapify on swapped child
        if( array[greater] > array[i]){
            swap(array, greater, i);
            MaxHeapify(array, size, greater); // To ensure the sub-tree at i is still a Max Heap after the swap
           
            assertIsMaxHeap(array, size, i); // Asserts that the sub-tree rooted at i is a Max Heap
        }
    }

    // Edge case where the last parent has only one child
    else if(2*i+1<size){
        if(array[2*i+1]>array[i]){
            swap(array, 2*i+1 ,i);
            // No need to call MaxHeapify on child here since this case would only be valid if child is a leaf node
        }
    }
}


// Non-Recursive version of MaxHeapify
void MaxHeapifyNR(int array[], int size, int i){
    assert(size>0); //assert(i>0)
    int parentNode;
    queue<int> worklist;//worklist/workset
    worklist.push(i);


    while(worklist.size()>0){
       int x = worklist.front();
       worklist.pop();

       cout<<"Working on: "<< array[x]<< "at position: "<< x << "\n"; 
       if(isEven(x) and x!=0){
           worklist.push(x-2);
           int greater = max(array, x, x-1);
           parentNode = (x-2)/2;
           if(array[greater] > array[parentNode]){
               swap(array, greater, parentNode);
               worklist.push(greater);
           }
       } // end if(isEven(x) and x!=0)

       else if(isOdd(x)){
           parentNode = (i-1)/2;
           worklist.push(i-1);
           if(array[x]>array[parentNode]){
               swap(array, x, parentNode);
           }
                      
       } // end else if    
    } // end while
} //end MaxHeapNR


//returns the index of the greater one, not its value
int max(int array[], int x, int y){
    int result;
    if(array[x]>array[y]){
        result=x;
    }
    else{
        result=y;
    }
    return result;
}


void swap(int array[], int x, int y){
    int temp = array[x];
    array[x] = array[y];
    array[y] = temp;
}


bool isEven(int x){
    return (x%2 == 0);
}


bool isOdd(int x){
    return (x%2 != 0);
}


void printArray(int array[], int size){
    for (int i=0; i<size; i++){
        cout<<array[i]<<" ";
    }
    cout<<"\n";
}


void assertIsMaxHeap(int array[], int size, int i){

    if(2*i+2<size){
        assert(array[i]> array[2*i+1] and array[i]>array[2*i+2]);
        assertIsMaxHeap(array, size, 2*i+1); 
        assertIsMaxHeap(array, size, 2*i+2);
    }

    else if(2*i+1<size){
        assert(array[i]> array[2*i+1]);
    }
    
    else{
        return;// Do nothing
    }
}