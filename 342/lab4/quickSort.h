
/**
	@file quicksort.h
	@author Terence Schumacher
	@author Dominic Badzik
	@version 1.3
*/


#ifndef _QUICKSORT_H
#define _QUICKSORT_H

class quicksort {
public:
	void quicks(int theArray[], int first, int last);
	void partition(int array[], int first, int last, int& pivotIndex);
	void choosePivot(int array[], int first, int last);
	void swap(int left, int right);
	void QuickSort(int A[], int lowValue, int highValue);

};

//#include "quickSort.cpp"

#endif

