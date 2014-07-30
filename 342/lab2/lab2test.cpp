** 
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


** fib
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

int main () {

	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "  ---------------------Linked Set Impplementation--------------------------  " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;

	//creation
	SortSetList testList, testList2, CopyList, intersectList,
		enteredNumbers, addedSetList, addedSetList2, addedSetList3, combinedSetList, minusSet;
	//test is constructors
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test Copy Constructors                                " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;

	SortSetList AL(9);
	SortSetList BL(15, 3);
	SortSetList CL(10,5,8);
	SortSetList DL(12, 5, 10, 12, -500);
	SortSetList XL(DL);
	cout <<"A: " << AL << endl <<"B: " << BL << endl <<"C: "<< CL << endl <<"D: " << DL 
		<< endl <<"X: " << XL << endl;


	//test is empty
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test Is Empty                                         " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;

	assert(testList.isEmpty());
	cout << "is The List Empty: ";
	checkTrue(testList.isEmpty());
	cout << endl;

	//test operator <<
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator <<                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	testList.insert(2);
	testList.insert(3);
	testList.insert(5);
	testList.insert(7);
	cout << "testList: " << testList << endl;
	insertEratosthenesSieve(300, testList);
	cout << "testList2: " << testList2 << endl;
	cout << "CopyList: " << CopyList << endl;
	cout << "intersectList: " << intersectList << endl;

	//test is in set
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                      Test Is In Set                                         " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "Is 45 in set?" << endl;
	testList.isInSet(45);
	testList.isInSet(3);

	//test insert
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                         Test Insert                                         " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	testList.insert(3);
	cout << testList << endl;
	testList.insert(0);
	testList2.insert(0);
	cout << testList << endl;

	//test remove
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                         Test Remove                                         " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	testList.remove(3);
	testList.remove(0);
	testList2.remove(0);
	cout << testList << endl;
	
	//test insert fibs
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                    Test Insert Fibs, Clock, and print Fib                   " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "Fibs of 0:  ";
	printFibs(0);
	cout << endl;
	cout << "Fibs of 1:  ";
	printFibs(1);
	cout << endl;
	printf("Fibs of %d: ", FIB_COUNT);
	cout << endl;
	clock_t Begin = clock();
	printFibs(FIB_COUNT);
	clock_t End =  clock();
	cout << endl;
	cout << endl;
	clockElapsed(Begin, End);
	cout << endl;
	insertFibs(FIB_COUNT, testList);
	cout << testList << endl;

	//test insert Eratosthense
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                    Test Insert Sieve, Clock, and print Sieve                " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "Sieve of 0: ";
	printFibs(0);
	cout << endl;
	cout << "Sieve of 1: ";
	printFibs(1);
	cout << endl;
	printf("Sieve of %d: ", TEST_CEILING);
	cout << endl;
	clock_t BeginSieve = clock();
	printSieve(TEST_CEILING);
	clock_t EndSieve =  clock();
	cout << endl;
	cout << endl;
	clockElapsed(BeginSieve, EndSieve);
	cout << endl;
	insertEratosthenesSieve(TEST_CEILING, testList2);
	cout << testList2 << endl;

	//test operator=
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                        Test operator =                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	
	CopyList = testList;

	cout << "Original List: "<< testList << endl;
	cout << "Copy List: "<< CopyList << endl;
	cout << endl << "Remove Selected Values [5] and [13]" << endl << endl;
	CopyList.remove(5);
	CopyList.remove(13);
	CopyList.remove(8);
	CopyList.remove(1);
	CopyList.remove(0);
	CopyList.remove(2);
	cout << "Original List: "<< testList << endl;
	cout << "Copy List: "<< CopyList << endl;
	cout << "Original List: "<< testList << endl;
	CopyList = testList = testList2;
	cout << "Copy List: "<< CopyList << endl;
	cout << "Original List: "<< testList2 << endl;

	CopyList.clearList();

	


	//test operator>>
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator >>                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	
	cout << "Enter in numbers to complete your list: ";
	cin >> CopyList;
	cout << CopyList << endl;

	//test operator==
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator ==                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	
	cout << testList << endl;
	
	insertFibs( 8, testList);
	cout << testList << endl;
	insertFibs( 8, testList2);
	cout << testList2 << endl;
	cout << "Are They equal? ";
	checkTrue(testList == testList2);
	cout << endl;

	testList2.clearList();

	cout << "Are They equal? ";
	checkTrue(testList == testList2);
	cout << endl;

	insertFibs( 8, testList2);
	testList2.remove(21);

	cout << "Are They equal? ";
	checkTrue(testList == testList2);
	cout << endl;
	
	testList.clearList();
	testList2.clearList();

	//test operator!=
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator !=                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << testList << endl;
	
	insertFibs( 8, testList);
	cout << testList << endl;
	insertFibs( 8, testList2);
	cout << testList2 << endl;
	cout << "Are They NOT equal? ";
	checkTrue(testList != testList2);
	cout << endl;

	testList2.clearList();

	cout << "Are They NOT equal? ";
	checkTrue(testList != testList2);
	cout << endl;

	insertFibs( 8, testList2);
	testList2.remove(21);

	cout << "Are They NOT equal? ";
	checkTrue(testList != testList2);
	cout << endl;

	
	//test operator+
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator +                                       " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	
	cout << "Added Set: " << endl;
	cout << addedSetList << endl;
	cout << "Added Set2: " << endl;
	cout << addedSetList2 << endl;
	cout << "Added Set3: " << endl;
	cout << addedSetList3 << endl;
	
	for (int i = 0; i < 10; i++){
	addedSetList2.insert(i);}
	
	cout << "Added Set2: " << endl;
	cout << addedSetList2 << endl;

	for (int i = 10; i < 40; i += 2){
		addedSetList3.insert(i);}

	cout << "Added Set3: " << endl;
	cout << addedSetList3 << endl;

	combinedSetList = addedSetList + addedSetList2 + addedSetList3;
	cout << "combined Set: " << endl;
	cout << combinedSetList << endl;

	addedSetList.clearList();
	addedSetList2.clearList();
	addedSetList3.clearList();
	combinedSetList.clearList();

	//test operator-
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator -                                       " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	
	testList.clearList();
	testList2.clearList();

	cout << "List 1: "<< testList << endl;
	cout << "List 2: "<< testList2 << endl;

	insertEratosthenesSieve(20, testList);
	insertFibs(8, testList2);

	cout << "List 1: "<< testList << endl;
	cout << "List 2: "<< testList2 << endl;

	minusSet = testList - testList2;

	cout << "List 1: "<< testList << endl;
	cout << "List 2: "<< testList2 << endl;
	cout << "minusSet: "<< minusSet << endl;

	

	//test operator*
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator *                                       " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	
	testList.clearList();
	testList2.clearList();

	insertFibs(6, testList);
	insertFibs(6, testList2);

	cout << "List 1: "<< testList << endl;
	cout << "List 2: "<< testList2 << endl;

	testList.remove(1);
	testList.remove(2);
	testList.remove(3);

	cout << "List 1: "<< testList << endl;
	cout << "List 2: "<< testList2 << endl;

	testList.insert(34);
	testList.insert(18);
	testList.insert(17);
	testList.insert(4);
	testList.insert(2);

	cout << "List 1: "<< testList << endl;
	cout << "List 2: "<< testList2 << endl;

	intersectList = testList * testList2;

	cout << "intersectList: " << intersectList << endl;
	
	
	//test operator +=
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator +=                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	testList.clearList();
	testList2.clearList();

	insertEratosthenesSieve(14, testList);
	insertFibs(9, testList2);

	cout << "List 1: "<< testList << endl;
	cout << "List 2: "<< testList2 << endl;

	testList += testList2;

	cout << "List 1: "<< testList << endl;
	cout << "List 2: "<< testList2 << endl;


	//test operator -=
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator -=                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	
	testList.clearList();
	testList2.clearList();

	insertEratosthenesSieve(20, testList);
	insertFibs(9, testList2);

	cout << "List 1: "<< testList << endl;
	cout << "List 2: "<< testList2 << endl;

	testList -= testList2;

	cout << "List 1: "<< testList << endl;
	cout << "List 2: "<< testList2 << endl;

	
	//test operator *=
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator *=                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	
	testList.clearList();
	testList2.clearList();

	insertEratosthenesSieve(20, testList);
	insertFibs(9, testList2);

	cout << "List 1: "<< testList << endl;
	cout << "List 2: "<< testList2 << endl;

	testList *= testList2;

	cout << "List 1: "<< testList << endl;
	cout << "List 2: "<< testList2 << endl;

	



	//Array Base Implementation
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "  ---------------------Array Set Impplementation---------------------------  " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	
	//creation
	//test is empty
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test Is Constructors                                  " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	
	SortSetArray A(9);
	SortSetArray B(15, 3);
	SortSetArray C(10,5,8);
	SortSetArray D(12, 5, 10, 12, -500);
	SortSetArray X(D);
	cout <<"A: " << A << endl <<"B: " << B << endl <<"C: "<< C << endl <<"D: " << D 
		<< endl <<"X: " << X << endl;
	
	//test is empty
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test Is Empty                                         " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;

	SortSetArray AtestList;
	checkTrue(AtestList.isEmpty());
	AtestList.insert(3);
	cout << endl;
	checkTrue(AtestList.isEmpty());
	cout << endl;

	//test operator <<
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator <<                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << AtestList << endl;
	AtestList.insert(17);
	AtestList.insert(24);
	cout << AtestList << endl;
	

	//test is in set
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                      Test Is In Set                                         " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
		
		AtestList.insert(1);
		AtestList.isInSet(1);

		AtestList.isInSet(10);

		AtestList.isInSet(45);
		cout << endl;
	//test insert
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                         Test Insert                                         " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "Insert 4" << endl;
	AtestList.insert(4);
	AtestList.isInSet(4);
	AtestList.insert(4);
	cout << "Insert 8" << endl;
	AtestList.insert(8);
	AtestList.isInSet(8);
	cout << "Insert 1111111" << endl;
	AtestList.insert(11111111);
	cout << "Insert 0" << endl;
	AtestList.insert(0);
	cout << "Insert -45" << endl;
	AtestList.insert(-45);
	cout << AtestList << endl;

	
	//test remove
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                         Test Remove                                         " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	AtestList.remove(0);
	cout << AtestList << endl;
	AtestList.remove(1);
	cout << AtestList << endl;
	AtestList.remove(3);
	cout << AtestList << endl;

	AtestList.clear();
	
	//test insert fibs
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                    Test Insert Fibs, Clock, and print Fib                   " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;

	insertFibs(17, AtestList);
	cout << AtestList << endl;
	AtestList.clear();
	cout << AtestList << endl;
	clock_t beginTestFib = clock();
	insertFibs(25, AtestList);
	clock_t endTestFib = clock();

	cout << AtestList << endl;
	clockElapsed(beginTestFib, endTestFib);
	AtestList.clear();

	
	//test insert Eratosthense
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                    Test Insert Sieve, Clock, and print Sieve                " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	
		clock_t beginTestSieve = clock();
		insertEratosthenesSieve(1000, AtestList);
		clock_t endTestSieve = clock();
		cout << AtestList << endl;
		clockElapsed(beginTestSieve, endTestSieve);

		AtestList.clear();
	
	//test operator=
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                        Test operator =                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;

		SortSetArray listTwo;
		insertEratosthenesSieve(100, AtestList);
		cout <<"AtestList: " << AtestList << endl;
		cout <<"listTwo: " << listTwo << endl;
		listTwo = AtestList;
		cout << "AtestList: " << AtestList << endl;
		cout << "listTwo: " << listTwo << endl;

		AtestList.clear();
		listTwo.clear();

	//test operator>>
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator >>                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;

		cout << "Please Enter in numbers to make a set, use -1 to exit: ";
		cin >> AtestList;
		cout << AtestList << endl;
	
		AtestList.clear();
	
	//test operator==
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator ==                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "Empty List: ";
	checkTrue(AtestList == listTwo);
	cout << endl;
	cout << "Not Empty List: ";
	listTwo.insert(45);
	checkTrue(AtestList == listTwo);
	cout << endl;
	listTwo.remove(45);
	cout << listTwo << endl;
	cout << AtestList << endl;
	insertFibs(10, AtestList);
	insertFibs(10, listTwo);
	cout << listTwo << endl;
	cout << AtestList << endl;
	cout << "size list two: " << listTwo.getSize() << endl;
	cout << "size a test list: " << AtestList.getSize() << endl;
	listTwo.remove(2);
	listTwo.remove(0);
	cout << listTwo << endl;
	cout << AtestList << endl;
	cout << "size list two: " << listTwo.getSize() << endl;
	cout << "size a test list: " << AtestList.getSize() << endl;
	cout << "Not Empty List: ";
	checkTrue(AtestList == listTwo);
	cout << endl;

	AtestList.clear();
	listTwo.clear();

		//test operator==
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator !=                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "Empty List: ";
	checkTrue(AtestList != listTwo);
	cout << endl;
	cout << "Not Empty List: ";
	listTwo.insert(45);
	checkTrue(AtestList != listTwo);
	cout << endl;
	listTwo.remove(45);
	cout << listTwo << endl;
	cout << AtestList << endl;
	insertFibs(10, AtestList);
	insertFibs(10, listTwo);
	cout << listTwo << endl;
	cout << AtestList << endl;
	cout << "size list two: " << listTwo.getSize() << endl;
	cout << "size a test list: " << AtestList.getSize() << endl;
	listTwo.remove(2);
	listTwo.remove(0);
	cout << listTwo << endl;
	cout << AtestList << endl;
	cout << "size list two: " << listTwo.getSize() << endl;
	cout << "size a test list: " << AtestList.getSize() << endl;
	cout << "Not Empty List: ";
	checkTrue(AtestList != listTwo);
	cout << endl;

	AtestList.clear();
	listTwo.clear();

	//test operator+
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator +                                       " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	
	insertFibs(10, AtestList);
	insertEratosthenesSieve(200, listTwo);
	cout << AtestList << endl;
	cout << listTwo << endl;
	SortSetArray addSet;
	addSet = AtestList + listTwo;
	cout << "New Set: " << addSet << endl;
	//	delete &addSet;
	addSet.clear();
	AtestList.clear();
	listTwo.clear();

	//test operator-
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator -                                       " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	
	insertFibs(10, AtestList);
	insertEratosthenesSieve(200, listTwo);
	cout << AtestList << endl;
	cout << listTwo << endl;
	SortSetArray combSet;
	combSet = AtestList - listTwo;
	cout << "New Set: " << combSet << endl;
	
	combSet.clear();
	AtestList.clear();
	listTwo.clear();

	
	
	//test operator*
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator *                                       " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;

	insertFibs(10, AtestList);
	insertEratosthenesSieve(200, listTwo);
	cout << AtestList << endl;
	cout << listTwo << endl;

	combSet = AtestList * listTwo;
	cout << "New Set: " << combSet << endl;
	
	combSet.clear();
	AtestList.clear();
	listTwo.clear();


	//test operator +=
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator +=                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;

	insertFibs(10, AtestList);
	insertEratosthenesSieve(200, listTwo);
	cout << AtestList << endl;
	cout << listTwo << endl;

	AtestList += listTwo;
	cout << "New Set: " << AtestList << endl;

	AtestList.clear();
	listTwo.clear();

	
	
	//test operator -=
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator -=                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;

	insertFibs(10, AtestList);
	insertEratosthenesSieve(100, listTwo);
	cout << AtestList << endl;
	cout << listTwo << endl;

	AtestList -= listTwo;
	cout << "New Set: " << AtestList << endl;

	AtestList.clear();
	listTwo.clear();

	
	//test operator *=
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator *=                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	
	insertFibs(10, AtestList);
	insertEratosthenesSieve(100, listTwo);
	cout << AtestList << endl;
	cout << listTwo << endl;

	AtestList *= listTwo;
	cout << "New Set: " << AtestList << endl;

	AtestList.clear();
	listTwo.clear();



	getchar();
	getchar();
	return 0;
}//end main

