 /**
 *  @file	lab4performance.cpp
 *  @author	Terence Schumacher
 *  @author Dominic Badzik
 *  @version 1.3
 */
#include <iostream>
#include <ctime>
#include "iterativemergesort.h"
#include "recursivemergesort.h"
#include "quicksort.h"
#define NINE 9


using namespace std;

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
void initArray(int injectArray[], int arraySize){
    int index = 0;
    while (index < arraySize) {
        injectArray[index] = randomNumber(arraySize);
		//srand(index);
        index++;
    }//end while
}//end setArray

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
 
 /** Print Array
	@brief prints out the array 
	@param printArray the array to print
	@param maximumSize the size of the array
*/
void printArray( int anArray[], char arrayName[], int arraySize ) {
  int size = arraySize;

  for ( int index = 0; index < size; index++ ){
   cout << arrayName << "[" << index << "] = " << anArray[index] << "\t";
   if ( ((index > 0) && (index % 7 == 0))  || (index+1) >= size ) cout << endl;
  } // for
}

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

 /** Main
	@brief Why do you need comments on main? Shouldn't the filename describe
			behavior?
	@param argc number of arguments passed in through command line
	@param argv storage array of arguments
	@return 0 if complete, error otherwise
*/
int main(int argc, const char* argv[]){
	// verify arguments                                                          
  if ( argc < 2 ) {
    cerr << "usage: a.out size" << endl;
    return -1;
  }

  // verify an array size                                                      
  int size = atoi( argv[argc-1] );
  //int size = 100;
  if ( size <= 0 ) {
    cerr << "array size must be positive" << endl;
    return -1;
  }
	//int *recursiveMergersortArray = new int[size];
	//int *iterativeMergersortArray = new int[size];
	//int *quickSortArray = new int[size];
	//int *heapSortArray = new int[size];

	int recursiveMergersortArray[size];
	int iterativeMergersortArray[size];
	int quickSortArray[size];
	int heapSortArray[size];

	initArray(recursiveMergersortArray, size);
	initArray(iterativeMergersortArray,size);
	initArray(quickSortArray,size);
	initArray(heapSortArray,size);

	//printArray(recursiveMergersortArray, "R-MergSort", size);
	//printArray(iterativeMergersortArray,"I-MergeSort", size);
	//printArray(quickSortArray,"QuickSort", size);
	//printArray(heapSortArray,"HeapSort", size);
	cout << "=============Unsorted=================" << endl;
	//unsorted
	cout << "Recursive MergeSort:" << endl;
	printFirstAndLast(recursiveMergersortArray, size);
	cout << "Iterative MergeSort:" << endl;
	printFirstAndLast(iterativeMergersortArray, size);
	cout << "Quick Sort:" << endl;
	printFirstAndLast(quickSortArray, size);
	cout << "Heap Sort:" << endl;
	printFirstAndLast(heapSortArray, size);

	iterativeMergeSort iterMerge;
	recursivemergesort recurMerge;
	//quickSort quick;

	clock_t iterBegin = clock();
		iterMerge.iterativeMergesort(iterativeMergersortArray, size);
	clock_t iterEnd = clock();
	
	clock_t mergesortBegin = clock();
		recurMerge.mergesort(recursiveMergersortArray, 0, size-1);
	clock_t mergesortEnd = clock();
	
	clock_t Qbegin = clock();
		quicks(quickSortArray,0, size-1);
    clock_t Qend = clock();
	
	clock_t heapBegin = clock();
		heapSort(heapSortArray, size);
    clock_t heapEnd = clock();
	
	cout << "=============Sorted=================" << endl;
	//sorted
	cout << "Recursive MergeSort:" << endl;
	printFirstAndLast(recursiveMergersortArray, size);
	clockElapsed(mergesortBegin, mergesortEnd);

	cout << "Iterative MergeSort:" << endl;
	printFirstAndLast(iterativeMergersortArray, size);
	clockElapsed(iterBegin, iterEnd);
	
	cout << "Quick Sort:" << endl;
	printFirstAndLast(quickSortArray, size);
	clockElapsed(Qbegin,Qend);
	
	cout << "Heap Sort:" << endl;
	printFirstAndLast(heapSortArray, size);
	clockElapsed(heapBegin, heapEnd);
	
	cout << "yes" << endl;
	//delete [] recursiveMergersortArray;
	//delete [] iterativeMergersortArray;
	//delete [] quickSortArray;
	//delete [] heapSortArray;

	getchar();
	return 0;

}//end main




