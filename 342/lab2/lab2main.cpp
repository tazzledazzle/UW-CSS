/** 
	@file lab2test.cpp
	@version 1.4
*/

#include "SortSetArray.h"
#include "SortSetList.h"
#include <cassert>
#include <ctime>
#include <cmath>
#define FIB_CEILING 1134903170
#define TEST_CEILING 30
#define FIB_COUNT 9

using namespace std;


/** fib
 *  @brief Computes a Fibonacci number.
 *  @param n an integer
 *  @return the nth Fibonacci number
 */
 int fib( int maxEntered)
{
	int fib = 0;
	int fib1 = 0;
	int fib2 = 1;
	if (maxEntered == 0 ) {
		return 0;
	}
	//else if (maxEntered == 1){
	//	return 1;
	//}//end if 
	else {
	for (int incrementToMax = 1; incrementToMax <= maxEntered; incrementToMax++){
		fib = fib1 + fib2;
		fib2 = fib1; 
		fib1 = fib;
	}//end for 
	return fib;
	}
}//end fib

 /** Run EratosthenesSieve
	@brief creates
 */
 void printSieve(int upperBound){
 
	int upperBoundSquareRoot = (int) sqrt((double) upperBound);

	bool *isComposite = new bool [upperBound + 1];

	memset(isComposite, 0, sizeof(bool) * (upperBound + 1));
	cout << "Sieve of Erathosthenes: " << endl;
	for (int cycle = 2; cycle <= upperBoundSquareRoot; cycle++){
		if (!isComposite[cycle]){
			cout << cycle << " ";
			for (int marker = cycle*cycle; marker <= upperBound; marker += cycle ){
					isComposite[marker] = true;
			}//end for marker
		
		}//end if !isComposite

	}//end for

	for (int cycle = upperBoundSquareRoot; cycle <= upperBound; cycle++){
		if (!isComposite[cycle])
			cout << cycle << " ";

	}//end for cycle2
	delete [] isComposite;
 }//end runEratosthenesSieve

 /** Insert Eratosthenes Sieve
	@brief inserts the sieve into a linked list
	@param upperBound the maximum for the prime numbers
	@param listCreation the list to insert the primes in
 */
  void insertEratosthenesSieve(int upperBound, SortSetList &listCreation){
 
	int upperBoundSquareRoot = (int) sqrt((double) upperBound);

	bool *isComposite = new bool [upperBound + 1];

	memset(isComposite, 0, sizeof(bool) * (upperBound + 1));

	for (int cycle = 2; cycle <= upperBoundSquareRoot; cycle++){
		if (!isComposite[cycle]){

			listCreation.insert(cycle);
			
			for (int marker = cycle*cycle; marker <= upperBound; marker += cycle ){
					isComposite[marker] = true;
			}//end for marker
		
		}//end if !isComposite

	}//end for

	for (int cycle = upperBoundSquareRoot; cycle <= upperBound; cycle++){
		if (!isComposite[cycle])
			listCreation.insert(cycle);	

	}//end for cycle2

	delete [] isComposite;

 }//end insertEratosthenesSieve

  /** Insert Eratosthenes Sieve
	@brief inserts primes into an array using the Sieve of Eratosthenes
	@param upperBound the maximum for the prime numbers
	@param arrayCreation the array to insert primes into
  */
  void insertEratosthenesSieve(int upperBound, SortSetArray &arrayCreation){
 
	int upperBoundSquareRoot = (int) sqrt((double) upperBound);

	bool *isComposite = new bool [upperBound + 1];

	memset(isComposite, 0, sizeof(bool) * (upperBound + 1));

	for (int cycle = 2; cycle <= upperBoundSquareRoot; cycle++){
		if (!isComposite[cycle]){

			arrayCreation.insert(cycle);
			
			for (int marker = cycle*cycle; marker <= upperBound; marker += cycle ){
					isComposite[marker] = true;
			}//end for marker
		
		}//end if !isComposite

	}//end for

	for (int cycle = upperBoundSquareRoot; cycle <= upperBound; cycle++){
		if (!isComposite[cycle])
			arrayCreation.insert(cycle);	

	}//end for cycle2

	delete [] isComposite;

 }//end insertEratosthenesSieve

 /** Test Printing of Fibbonnaci Sequence
	 @param maxEntered the number of cycles to print
 */
void printFibs(const int maxEntered){
    for(int cycle = 0; cycle < maxEntered; cycle++)
    {
        int calculatedFib = fib(cycle);
       // cout << cycle << ": " << calculatedFib << endl;
        cout << calculatedFib << " ";
    }//end for
    cout << endl;

}//end printFibs

void insertFibs(const int maxEntered, SortSetList &emptyList){

	for (int cycle = 0; cycle <= maxEntered; cycle++)
	{
		int calculatedFib = fib(cycle);
		emptyList.insert(calculatedFib);

	}//end for
}//end insertFibs

void insertFibs(const int maxEntered, SortSetArray &emptyList){

	for (int cycle = 0; cycle <= maxEntered; cycle++)
	{
		int calculatedFib = fib(cycle);
		emptyList.insert(calculatedFib);

	}//end for
}//end insertFibs

void checkTrue(const bool comparison){
	if (comparison == 0)
		cout << "False";
	else
		cout <<  "True";
	
}//end checkTrue

void clockElapsed( clock_t clockTimeStart, 
                  clock_t clockTimeEnd ) {  // uses less precise ctime
  clock_t ticks;
  ticks = clockTimeEnd - clockTimeStart;
  cout << "clockElapsed:clock time elapsed: " << ticks << " clock ticks ~= " 
       << (float)ticks / (float)CLOCKS_PER_SEC << " seconds\n"; 
} // clockElapsed


int main(){


//create ADT sort set for Time/Space Comparison:
	//Array Based Implementation
	SortSetArray primesArray;
	SortSetArray fibbonaciArray;

	//Linked List Implementation
	SortSetList primesList;
	SortSetList fibbonaciList;

	//Do the following on each implementation:

		//Create Sieve of Eratosthenese List
		insertEratosthenesSieve(TEST_CEILING, primesList);
		cout << "primesList: " << primesList << endl << endl;
		//Create iterative Fibbonaci List
		insertFibs(FIB_COUNT, fibbonaciList);
		cout << "fibbonaciList: " << fibbonaciList << endl << endl;
	
		//Create Sieve of Eratosthenese Array
		insertEratosthenesSieve(TEST_CEILING, primesArray);
		cout << "primesArray: " << primesArray << endl << endl;
		//Create iterative Fibbonaci List
		insertFibs(FIB_COUNT, fibbonaciArray);
		cout << "fibbonaciArray: " << fibbonaciArray << endl << endl;
	
		//		Create sPFdifference
		SortSetList sPFdifference;
	//		Store diff of primes
		clock_t beginDiffList = clock();
		sPFdifference = fibbonaciList - primesList;
		clock_t endDiffList = clock();
		
		cout << "sPFdifference: " << endl; // sPFdifference << endl;
		clockElapsed(beginDiffList, endDiffList);
		cout << "Size of sPFdifference: " << (double)sizeof(sPFdifference) << endl;

		//Create sPFunion
		SortSetList sPFunion;

			//Store union of primes
		clock_t beginUnionList = clock();
		sPFunion = fibbonaciList + primesList;
		clock_t endUnionList = clock();

		cout << "sPFunion: " << endl; //sPFunion << endl;
		clockElapsed(beginUnionList, endUnionList);
		cout << "Size of sPFunion: " << (double)sizeof(sPFunion) << endl;

		//Create sPFintersect
			SortSetList sPFintersect;
			//Store intersection of primes	
			clock_t beginIntersectList = clock();
			sPFintersect = fibbonaciList * primesList;
			clock_t endIntersectList = clock();

			cout << "sPFintersect: " << endl; //sPFintersect << endl;
			clockElapsed(beginIntersectList, endIntersectList);
			cout << "Size of sPFintersect: " << (double)sizeof(sPFintersect) << endl;

	getchar();
	return 0;

} 
//end main

