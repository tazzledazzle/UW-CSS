
 /**

 *  @file	lab4TestTimeMain.cpp
 *  @brief	 a second driver file for testing the implementation
 *           of the assigned non-recursive merge sort method
 *  @author	Terence Schumacher
 *	@author Dominic Badzik
 *  @version 1.3
 */

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>
#include <cmath>
#include <cassert>

#include "iterativemergesort.h"
#include "recursivemergesort.h"
#include "quicksort.h"
//#define TEST_SIZE 34
#define NINE 9
#define CASE0 34
#define CASE1 1000
#define CASE2 10000
#define CASE3 400000
#define MIN_SIZE 20

using namespace std;

//#################################
//  Methods
//#################################

 /** Random Number
	@brief generates random number 
	@param max the ceiling for random number creation
	@return randomly generated number
*/
int randomNumber(int max){
    int x = 0;
    x = rand() % max;
	
    return x;
}//end randomNumber

 /** Set Array
	@brieft sets random number inside of array 
	@param injectArray the array to set
	@param arraySize the size of the array
*/
void setArray(int injectArray[], int arraySize){
    int index = 0;
    while (index < arraySize) {
        injectArray[index] = randomNumber(arraySize);
		srand(index);
        index++;
    }//end while
}//end setArray

 /** Print Array
	@brief prints out the array 
	@param printArray the array to print
	@param maximumSize the size of the array
*/
void printArray(int printArray[], int maximumSize){
    int index = 0;
    cout << "{";
    while (index < maximumSize) {
        cout << printArray[index] << ", ";
        index++;
    }//end while
    cout << "}"<< endl<<endl;
}//end printArray

 /** Clock Elapsed
	@brief timing method provided for lab2
	@param clockTimeStart start clock instance
	@param clockTimeEnd end clock instance
*/
void clockElapsed( clock_t clockTimeStart, 
                  clock_t clockTimeEnd ) {  // uses less precise ctime
  clock_t ticks;
  ticks = clockTimeEnd - clockTimeStart;
  cout << "clockElapsed:clock time elapsed: " << ticks << " clock ticks ~= " 
       << (float)ticks / (float)CLOCKS_PER_SEC << " seconds\n"; 
} // clockElapsed

void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}

 /** Print First and Last
	@brief prints first nine values and last nine values of an array
	@param printArray array passed in to print
	@param max maximum number of elements for the array
*/
void printFirstAndLast(int printArray[], int max){
	cout << "First 9: ";
	for (int index = 0; index < NINE-1; index++){
		cout << printArray[index] << ", ";
	}//end for
	cout << printArray[NINE-1] << endl;
	cout << "Last 9: ";
	for (int index = (max) - NINE; index < max; index++ ){
		cout << printArray[index] << ", ";
	}//end for
	cout << endl;
}//end printFirstAndLast

 /** sift Down
	@brief implementation of Heapify like method, switching "nodes" if contents
			are less than child contents
	@param numbers Array to sort
	@param root	low value to create basis of comparison
	@param bottom max value to create basis of comparison
*/
void siftDown(int numbers[], int root, int bottom)
{
  int maxChild, temp;

  bool done = false;

  while ((root*2 <= bottom) && (!done))
  {
    if (root*2 == bottom)
      maxChild = root * 2;
    else if (numbers[root * 2] > numbers[root * 2 + 1])
      maxChild = root * 2;
    else
      maxChild = root * 2 + 1;

    if (numbers[root] < numbers[maxChild])
    {
      temp = numbers[root];
      numbers[root] = numbers[maxChild];
      numbers[maxChild] = temp;
      root = maxChild;
    }//end if
    else
      done = true;
  }//end while

}//end shift down

 /** Heap Sort
	@brief Sorts numbers in a replicated "heapify" binary tree variation
	@param numbers array to sort
	@param arraySize size of the array
*/
void heapSort(int numbers[], int arraySize)
{
  int index, tempStorage;

  for (index = (arraySize / 2)-1; index >= 0; index--)
    siftDown(numbers, index, arraySize);

  for (index = arraySize-1; index >= 1; index--)
  {
    tempStorage = numbers[0];
    numbers[0] = numbers[index];
    numbers[index] = tempStorage;
    siftDown(numbers, 0, index-1);
  }//end for

}//end heapsort

 /** Main
	@brief runs tests
	@param argc number of arguments passed to function
	@param argv storage of char* passed arguemnts
*/
int main(int argc, const char * argv[])
{
		// verify arguments                                                          
  if ( argc < 2 ) {
    cerr << "usage: a.out size" << endl;
    return -1;
  }
  int TEST_SIZE = 0;
  // verify an array size                                                      
  TEST_SIZE = atoi( argv[argc-1] );
  //int size = 100;
  if ( TEST_SIZE <= 0 ) {
    cerr << "array size must be positive" << endl;
    return -1;
  }
 cout << "Test Random:" << endl;
 cout << "-------------------------------------------------------------------------";
 cout << endl;
 cout << "Random Number = " <<randomNumber(45) << endl;
 cout << "Another = " <<randomNumber(45) << endl;

  cout << "Test Print Array :" << endl;
 cout << "-------------------------------------------------------------------------";
 cout << endl;
 int testArray[TEST_SIZE];
 cout << "I have an Array ->";
 for (int index = 0; index < TEST_SIZE; index++)
	 testArray[index] = 0;
 printArray(testArray, TEST_SIZE);
 
  cout << "Test Set Array :" << endl;
 cout << "-------------------------------------------------------------------------";
 cout << endl;

 cout << "And Now I set it ->";
 setArray(testArray, TEST_SIZE);
 printArray(testArray, TEST_SIZE);
 
 cout << "Test Clock :" << endl;
 cout << "-------------------------------------------------------------------------";
 cout << endl;
 
 clock_t testBeginning = clock();
 cout << "Wait 3 seconds..." << endl; 
 wait(3);
 clock_t testEnding = clock();
 clockElapsed(testBeginning, testEnding);

 cout << "Test Print First 9 and Last 9:" << endl;
 cout << "-------------------------------------------------------------------------";
 cout << endl;
	cout << "All values are index +1 --";
	for(int index = 0; index < TEST_SIZE; index++){
		testArray[index] = (index + 1);
	}//end for
	printArray(testArray, TEST_SIZE);
	cout << "And Now for the First and Last ->";
	printFirstAndLast(testArray, TEST_SIZE);


 cout << "Establish Arrays:" << endl;
 cout << "=======================================================================";
 cout << endl;
    
     // MergeSort
      int mergesortArray1[CASE1];
      int mergesortArray2[CASE2];
      int mergesortArray3[CASE3];

      //QuickSort
      int QanArray1[CASE1];
      int QanArray2[CASE2];
      int QanArray3[CASE3];    

		//iterative Alternating Mergesort
	  int iterArray1[CASE1];
	  int iterArray2[CASE2];
	   int iterArray3[CASE3];

	   //HeapSort
	  int heapArray1[CASE1];
	  int heapArray2[CASE2];
	   int heapArray3[CASE3];

	   // ===================Logging times
//for (int cycle = 0; cycle < 8; cycle++){


	    cout << endl;
 //cout << "Cycle " << cycle << endl;
 cout << "Merge, iter, Quick, and Heap Arrays:" << endl;
 cout << "-------------------------------------------------------------------------";
 cout << endl;
    
    //----------MERGESORT-----------------------
    //set up an array with random values of 10
    setArray(mergesortArray1, CASE1);
    //print it
	cout << "Array 1: " << endl;
	printFirstAndLast(mergesortArray1, CASE1);
  //  printArray(mergesortArray1, CASE1);

    //set up an array with random values of 100
    setArray(mergesortArray2, CASE2);
    //print it
	cout << "Array 2: " << endl;
	printFirstAndLast(mergesortArray2, CASE2);
  //  printArray(mergesortArray2, CASE2);

	    //set up an array with random values of 100
    setArray(mergesortArray3, CASE3);
    //print it
	cout << "Array 3: " << endl;
	printFirstAndLast(mergesortArray3, CASE3);
  //  printArray(mergesortArray2, CASE2);
    
    cout << endl;
    //-----------QUICKSORT----------------------
    //set up an array with random values of 10
    setArray(QanArray1, CASE1);
    //print it
	cout << "Quick Sort Array 1: " << endl;
	printFirstAndLast(QanArray1, CASE1);
 //   printArray(QanArray1, CASE1);

    //set up an array with random values of 100
    setArray(QanArray2, CASE2);
    //print it
	cout << "Quick Sort Array 2: " << endl;
	printFirstAndLast(QanArray2, CASE2);
 //   printArray(QanArray2, CASE2);

    //set up an array with random values of 100
    setArray(QanArray3, CASE3);
    //print it
	cout << "Quick Sort Array 3: " << endl;
	printFirstAndLast(QanArray3, CASE3);
 //   printArray(QanArray2, CASE2);
	cout << endl;
//-----------------ALTERNATINGITERATIVEMERGESORT---------
    //set up an array with random values of 10
    setArray(iterArray1, CASE1);
    //print it
	cout << "Iterative Alternating Array1: " << endl;
		printFirstAndLast(iterArray1, CASE1);
  //  printArray(iterArray1, CASE1);

    //set up an array with random values of 100
    setArray(iterArray2, CASE2);
    //print it
	cout << "Iterative Alternating Array2: " << endl;
		printFirstAndLast(iterArray2, CASE2);
 //   printArray(iterArray2, CASE2);

	    //set up an array with random values of 100
    setArray(iterArray3, CASE3);
    //print it
	cout << "Iterative Alternating Array3: " << endl;
		printFirstAndLast(iterArray3, CASE3);
 //   printArray(iterArray2, CASE2);

		cout << endl;

	//-----------------HEAPSORT---------
    //set up an array with random values of 10
    setArray(heapArray1, CASE1);
    //print it
	cout << "Heap Array1: " << endl;
		printFirstAndLast(heapArray1, CASE1);
  //  printArray(iterArray1, CASE1);

    //set up an array with random values of 100
    setArray(heapArray2, CASE2);
    //print it
	cout << "Heap Array2: " << endl;
		printFirstAndLast(heapArray2, CASE2);
 //   printArray(iterArray2, CASE2);

	    //set up an array with random values of 100
    setArray(heapArray3, CASE3);
    //print it
	cout << "Heap Array3: " << endl;
		printFirstAndLast(heapArray3, CASE3);
 //   printArray(iterArray2, CASE2);

		cout << endl;
 cout << endl;
 cout << "Sorting and timing arrays Arrays:" << endl;
 cout << "-------------------------------------------------------------------------";
 cout << endl;

   recursivemergesort recMer;
    //----------MERGESORT-----------------------
     //start the timer
     clock_t mergesortBegin = clock();
     //run the recursive merge sort
	 // wait(CASE1);
     recMer.mergesort(mergesortArray1, 0, CASE1-1);
     //stop the timer
     clock_t mergesortEnd = clock();
     //print results
	 cout << "MergeSortArray1: " << endl;
	 printFirstAndLast(mergesortArray1, CASE1);
  //   printArray(mergesortArray1, CASE1);
     //save the time
	 clockElapsed(mergesortBegin, mergesortEnd);

    //start the timer
    clock_t begin2 = clock();
    //run the recursive merge sort
	 // wait(CASE2);
    recMer.mergesort(mergesortArray2, 0, CASE2-1);
    //stop the timer
    clock_t end2 = clock();
    //print results
	 cout << "MergeSortArray2: " << endl;
	 printFirstAndLast(mergesortArray2, CASE2);
 //   printArray(mergesortArray2, CASE2);
    //save the time
   clockElapsed(begin2, end2);

       //start the timer
    clock_t begin3 = clock();
    //run the recursive merge sort
	 // wait(CASE3);
    recMer.mergesort(mergesortArray3, 0, CASE3-1);
    //stop the timer
    clock_t end3 = clock();
    //print results
	 cout << "MergeSortArray3: " << endl;
	 printFirstAndLast(mergesortArray3, CASE3);
 //   printArray(mergesortArray2, CASE2);
    //save the time
   clockElapsed(begin3, end3);

    cout << "-------------------------------------------------------------------------";
 cout << endl;
  //  //------------QUICKSORT----------------------

 quicksort quickie; 
	cout << "This stopped working for some reason..." << endl;
	quickie.QuickSort(QanArray1, 0, CASE1);
	printFirstAndLast(QanArray1, CASE1);
	cout << "So I rewrote it in one method-->" << endl;
    //start the timer
    clock_t Qbegin = clock();
    //run the recursive merge sort
	 // wait(CASE1);
    quickie.quicks(QanArray1, 0, CASE1);
    //stop the timer
    clock_t Qend = clock();
    //print results
	cout << "Quick Sort Array 1: " << endl;
	printFirstAndLast(QanArray1, CASE1);
 //   printArray(QanArray1, CASE1);
    //save the time
    clockElapsed(Qbegin, Qend);

    //start the timer
    clock_t Qbegin2 = clock();
    //run the recursive merge sort
	 // wait(CASE2);
    quickie.quicks(QanArray2, 0, CASE2);
    //stop the timer
    clock_t Qend2 = clock();
    //print results
	cout << "Quick Sort Array 2: " << endl;
	printFirstAndLast(QanArray2, CASE2);
 //   printArray(QanArray2, CASE2);
    //save the time
    clockElapsed(Qbegin2, Qend2);

	    //start the timer
    clock_t Qbegin3 = clock();
    //run the recursive merge sort
	 // wait(CASE3);
    quickie.quicks(QanArray3, 0, CASE3);
    //stop the timer
    clock_t Qend3 = clock();
    //print results
	cout << "Quick Sort Array 3: " << endl;
	printFirstAndLast(QanArray3, CASE3);
 //   printArray(QanArray2, CASE2);
    //save the time
    clockElapsed(Qbegin3, Qend3);

    cout << "-------------------------------------------------------------------------";
 cout << endl;
	 //-----------------ALTERNATINGITERATIVEMERGESORT---------
    //start the timer
    clock_t iterBegin = clock();
    //run the recursive merge sort
	iterativeMergeSort m;
	 // wait(CASE1);
    m.iterativeMergesort(iterArray1, CASE1);
    //stop the timer
    clock_t iterEnd = clock();
    //print results
	cout << "iterative Alternating Array1: " << endl;
	printFirstAndLast(iterArray1, CASE1);
  //  printArray(iterArray1, CASE1);
    //save the time
    clockElapsed(iterBegin, iterEnd);
    
	//start the timer
    clock_t iterBegin2 = clock();
    //run the recursive merge sort
	 // wait(CASE2);
    m.iterativeMergesort(iterArray2, CASE2);
    //stop the timer
    clock_t iterEnd2 = clock();
    //print results
    cout << "iterative Alternating Array2: " << endl;
	printFirstAndLast(iterArray2, CASE2);
//	printArray(iterArray2, CASE2);
    //save the time
    clockElapsed(iterBegin2, iterEnd2);

		//start the timer
    clock_t iterBegin3 = clock();
    //run the recursive merge sort
	 // wait(CASE3);
    m.iterativeMergesort(iterArray3, CASE3);
    //stop the timer
    clock_t iterEnd3 = clock();
    //print results
    cout << "iterative Alternating Array3: " << endl;
	printFirstAndLast(iterArray3, CASE3);
//	printArray(iterArray2, CASE2);
    //save the time
    clockElapsed(iterBegin3, iterEnd3);

	    cout << "-------------------------------------------------------------------------";
 cout << endl;
	 //-----------------HEAPSORT---------
    //start the timer
    clock_t heapBegin = clock();
    //run the recursive merge sort
	
	 // wait(CASE1);
    heapSort(heapArray1, CASE1);
    //stop the timer
    clock_t heapEnd = clock();
    //print results
	cout << "Heap Array1: " << endl;
	printFirstAndLast(heapArray1, CASE1);
  //  printArray(heapArray1, CASE1);
    //save the time
    clockElapsed(heapBegin, heapEnd);
    
	//start the timer
    clock_t heapBegin2 = clock();
    //run the recursive merge sort
	 // wait(CASE2);
   heapSort(heapArray2, CASE2);
    //stop the timer
    clock_t heapEnd2 = clock();
    //print results
    cout << "Heap Array2: " << endl;
	printFirstAndLast(heapArray2, CASE2);
//	printArray(heapArray2, CASE2);
    //save the time
    clockElapsed(heapBegin2, heapEnd2);

		//start the timer
    clock_t heapBegin3 = clock();
    //run the recursive merge sort
	 // wait(CASE3);
    heapSort(heapArray3, CASE3);
	
    //stop the timer
    clock_t heapEnd3 = clock();
    //print results
    cout << "Heap Array3: " << endl;
	printFirstAndLast(heapArray3, CASE3);
//	printArray(heapArray2, CASE2);
    //save the time
    clockElapsed(heapBegin3, heapEnd3);
     cout << "-------------------------------------------------------------------------";
 cout << endl; 
 cout << "-------------------------------------------------------------------------";
 cout << endl;


 //}//end for

  //  getchar();
    
    return 0;
    }//end main

