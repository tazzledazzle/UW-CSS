
/**
	@file quicksort.cpp
	@author Terence Schumacher
	@author Dominic Badzik
	@version 1.3
*/

#include "quicksort.h"

/** swap
	@brief Swaps integers 
	@param left first value
	@param right second value
*/
void quicksort::swap(int left, int right){
    int temp;
    temp = left;
    left = right;
    right = temp;
}//end swap

 /** 
	@brief Choose a pivot for quicksort's partition algorithm
		   and swaps  it with the first item in an array
	@param array the array to select a pivot
	@param first beginning value of the array
	@param last ending value of the array
 */
void quicksort::choosePivot(int array[], int first, int last){
    int middle = (first + last)/2;
    swap(array[middle], array[first]);
    
}//end choosePivot

 /** Partition
 * @brief Partitions an array for quicksort.
 * @pre theArray[first..last] is an array; first <= last.
 * @post Partitions theArray[first..last] such that:
 *    S1 = theArray[first..pivotIndex-1] <  pivot
 *         theArray[pivotIndex]          == pivot
 *    S2 = theArray[pivotIndex+1..last]  >= pivot
 * @param theArray  The given array.
 * @param first  The first element to consider in theArray.
 * @param last  The last element to consider in theArray.
 * @param pivotIndex  The index of the pivot after partitioning. 
 */
void quicksort::partition(int array[], int first, int last, int& pivotIndex){
    choosePivot(array, first, last);        //find the pivot point
    int pivot = array[first];               //set a pivot
    int lastS1 = first;                     //pivot index
    int firstUnknown = first + 1;           //first value outside of pivot
		
    for (; firstUnknown <= last; ++firstUnknown) {
        if(array[firstUnknown] < pivot){
            ++lastS1;
            swap(array[firstUnknown], array[lastS1]);
        }//end for

    }//end for

    //decide a new pivot
    swap(array[first], array[lastS1]);
    pivotIndex = lastS1;
		
}//end partition

 /** Quick Sort
	@brief Sorts an array into ascending order. Uses the quick sort with
		   median-of-three pivot selection for arrays of at least MIN_SIZE
		   entries, and uses the insertion sort for other arrays.
	@pre  theArray[first..last] is an array.
	@post  theArray[first..last] is sorted.
	@param theArray  The given array.
	@param first  The first element to consider in theArray.
	@param last  The last element to consider in theArray.
*/
void quicksort::QuickSort(int theArray[], int first, int last)
{	

	if (last <= first){return;}//end if
        int pivotIndex;
		 //Create the partition: S1, pivot, S2  
        partition(theArray, first, last, pivotIndex);
        
        //sort regions S1 and S2
        QuickSort(theArray, first, pivotIndex-1);
        QuickSort(theArray, pivotIndex+1, last);

}  // end quickSort


/** Quicks
	@brief this was created because there was a problem with 
			the carrano implementation
	@param theArray array to sort
	@param low lower bound 
	@param high upper bound
*/
void quicksort::quicks(int theArray[], int low, int high)
{
      int index = low;                
      int jindex = high;
      int pivot = theArray[(low+high)/2]; 
      do {
          while(theArray[index] < pivot) ++index;  
          while(theArray[jindex] > pivot) --jindex;  
          if(index <= jindex)
		  {           
              int temp = theArray[index];
              theArray[index] = theArray[jindex];
              theArray[jindex] = temp;
              index++; jindex--;
          }
      } while(index < jindex);
      if(low < jindex) quicks(theArray, low, jindex);
      if(index < high) quicks(theArray, index, high);
}//end quicks



