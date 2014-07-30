
/**
	@file recursivemergesort.cpp
	@author Terence Schumacher
	@author Dominic Badzik
	@version 1.3

*/

#include "recursivemergesort.h"

/** recursive mergesort
	@param anArray the array to sort
	@param lowEnd lower bound of the array
	@param highEnd upper bound of the array
*/
void recursivemergesort::mergesort(int anArray[], int lowEnd, int highEnd ){
	int indexSize = highEnd;

	if (lowEnd < highEnd)
	{
		int midValue = (highEnd + lowEnd)/2;
		mergesort(anArray, lowEnd, midValue);
		mergesort(anArray, midValue+1, highEnd);
		merge(anArray, lowEnd, midValue, highEnd, indexSize);
	}//end if 

}//end mergesort

/**
 Merges two sorted array segments theArray[first..mid] and
 theArray[mid+1...last] into one sorted array.
 
 */
void recursivemergesort::merge(int array[], int first, int mid, int last, int x){
   int tempArray[x];
   //int *tempArray = new int[x];
	int first1 = first;     //beginning of first subarray
    int last1 = mid;        //end of first subarray
    int first2 = mid+1;     //beginning of second subarray
    int last2 = last;       //end of second subarray
   
    int index = first1;     //next available location in

    for(; (first1 <= last1)&&(first2 <= last2); ++index){
        //Invariant: tempArray[first...index-1] is in order
        if (array[first1]< array[first2]) {
            tempArray[index] = array[first1];
            ++first1;
        }
        else{
            tempArray[index] = array[first2];
            ++first2;
        }//end if
    }//end for
    
    //finish off the non-empty subarray
    
    //finish off the first subarray, if necessary
    for(; first1 <= last1; ++first1, ++index )
    {   //Invariant: the array is already in order
        tempArray[index] = array[first1];
    }//end for
    
    //finish off the second subarray, if necessary
    for (; first2 <= last2; ++first2, ++index) {
        //Invariant: the array is already in order
        tempArray[index] = array[first2];
    }//end for
    
    //copy the results back into the original array
    for (index = first; index <= last; ++index) {
        array[index] = tempArray[index];
    }//end for
    
	//delete [] tempArray;

}//end merge

