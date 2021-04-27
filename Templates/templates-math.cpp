/*
Function Templates:
    1) Couldn't find the symbols
    2) No errors for int and double. For string, 
         error C2676: binary '/': 'T' does not define this operator or a conversion to a type acceptable to the predefined operator
        with
        [
            T=std::string
        ]
        message : see reference to function template instantiation 'T average<std::string>(std::vector<std::string,std::allocator<std::string>>)' being compiled
        with
        [
            T=std::string
        ]
        It is impossible to have string as the type, becauser the average function involves division.
    3) error C2672: 'average': no matching overloaded function found
    error C2783: 'T average(std::vector<T,std::allocator<_Ty>>)': could not deduce template argument for 'T'
    Fixed by specifying the type for the average function:
    cout << average<double>({ 1,2,3,4 });
    4)The implementation has to be in the header file because the compiler needs to know the type during compilatio  tto create  a version of the function with the given type.

*/

#include <iostream>
#include "templates.h"
using namespace std;


int main()
{
   /*
    double x = 1, y = 1;
    cout << "x + y = " << add(x, y) << "\n";
    return 0;
    */
    /*
    vector<int> colors;
    colors.push_back(2);
    colors.push_back(3);
    colors.push_back(10);
    //cout << "x + y = " << add(x, y) << "\n";
    cout << "Average of integers 1,3, and 10: " << average(colors) << endl;

    vector<double> rates;
    rates.push_back(11.4);
    rates.push_back(13.5);
    rates.push_back(2);
    cout << "Average of doubles 11.4 ,13.5, and 2: " << average(rates) << std::endl;
    */
    /*
    vector<string> rows;
    rows.push_back("gg");
    rows.push_back("jdj");
    cout << average(rows);
    return 0;
    */
    cout << average({ 1,2,3,4 });
}