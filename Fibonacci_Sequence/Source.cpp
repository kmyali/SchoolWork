/*

*/

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
using namespace std;

int fibonacci_recursive(double n) {
    //First and second terms are defined as 1
    if (n == 1 || n == 0) { 
        return 1;
    }
    // Otherwise, each term is defined as the sum of previous two terms. For example, {1,1,2,3,5,8,13...} 5=3+2, 13=8+5
    else {
        return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
    }
}

int fibonacci_iterative(double n) {
    //First and second terms are defined as 1
    double temp, previousTerm = 1, currentTerm = 1;
    // saves the previous loop's currentTerm into previousTerm. The new current term is the previous term plus the current term of the previous loop.
    for (int i=2; i <= n; i++) {
        temp = previousTerm;
        previousTerm = currentTerm;
        currentTerm += temp;
    }
    return currentTerm;
}

int main() {



    //Repeats finding the fibonacci of (0-4000) 12 times so that their average can be taken
    //for (int i = 0; i < 12; i++) {
        int n = 0;
        ofstream f;

        //Opening the file stream in append mode to a csv file where the time taken for each function for each value will be saved
        f.open("fibonacci.csv", ios_base::app);

        //Tells the user if the file was not opened successfully
        if (!f.is_open()) {
            cout << "Not open\n";
        }
        cout << "N\tTime for iterative\n"; // Time for recursive\n";
        f << "Value,Time for iterative,Time for recursive\n"; //writes to file

        //Looping through factorial(i) from i=0 to i=4000 in increments of 500 for both functions
        for (int i = 5; i <= 50; i +=5 ) {

            //time for iterative
            auto start = std::chrono::high_resolution_clock::now();
            fibonacci_iterative(i);
            auto end = std::chrono::high_resolution_clock::now();

            //Printing time to console
            cout << i << "\t" << (end - start).count()<<"\n";
            if (i == 200) {
                cout << fibonacci_iterative(200);
            }

            //Writing time to csv
            f << i << "," << (end - start).count() << ",";


            //time for recursive
            //start = std::chrono::high_resolution_clock::now();
            //fibonacci_recursive(i);
            //end = std::chrono::high_resolution_clock::now();
            //cout << "\t\t\t" << (end - start).count() << "\n";
            //f << (end - start).count() << "\n";
        }
       
       // f.close(); // Closing the file
//    }

}
