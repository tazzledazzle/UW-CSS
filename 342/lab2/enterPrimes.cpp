/**
 @file enterPrimes.cpp
 @brief fild all numbers from 1 to n that are prime numbers
 @pre user must enter a valid integer
 @post all integers that are prime are printed out
 */

#include <iostream>

using namespace std;
/** Check Primes
 *  @brief checks to see if number is prime
 *  @pre must have a valid integer passed
 *  @param posPrime the number checked for prime
 *  @return true if prime, false otherwise
 */
bool checkPrime(const int posPrime){

    for (int divisor = 2; divisor < posPrime; divisor++){
 
        if (posPrime % divisor == 0){
    
            return false;
        }
        else{
        //increment
            ;
        }//end if posPrime %
        
    }//end for divisor
    
    //all numbers have remainder
    return true;
    
}//end checkPrime

/** Print Primes
    @brief prints out prime number from 1 to maxNumber
    @pre number passed in must be valid integer
    @post string of prime numbers is printed that are primes
    @param maxNumber limit to which primes are checked
 */
void printPrimes(const int maxNumber){
  
    for (int posPrime = 1; posPrime < maxNumber; posPrime++){
  
        if (checkPrime(posPrime)){
  
            cout << posPrime << " ";
        }
        else{
        //increment
            ;
        }//end if checkPrime
        
    }//end for posPrime
    
    cout << "\nAll Primes Printed!" << endl;

}//end printPrimes

int main()
{
    int numberEntered = 0;
    
    //prompt user to enter an integer number
    cout << "Enter a number: ";
    cin >> numberEntered;
    //print out all prime numbers from 1 to that number (n)
    printPrimes(numberEntered);

    return 0;
}

