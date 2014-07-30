/**
    @file    fibCycles.cpp
    @brief   prints out the fibonnaci numbers from 0 to n
             recursively
    @author  Terence Schumacher
    @version 1
 */

#include <iostream>

using namespace std;

/** fib
 *  @brief Computes a Fibonacci number.
 *  @param n an integer
 *  @return the nth Fibonacci number
 */
 long fib( int maxEntered)
{
    if (maxEntered <= 2){
        return 1;
    }
    else {
        return fib(maxEntered-1)+fib(maxEntered-2);
    }//end if
    
}//end fib

void printFibs(const int maxEntered){
    for(int cycle = 1; cycle <= maxEntered; cycle++)
    {
        long calculatedFib = fib(cycle);
       // cout << cycle << ": " << calculatedFib << endl;
        cout << calculatedFib << " ";
    }//end for
    cout << endl;

}//end printFibs
int main()
{
    int maxEntered = 0;
    cout << "Enter number of cycles:";
    cin >> maxEntered;
    
    printFibs(maxEntered);

    return 0;
}

