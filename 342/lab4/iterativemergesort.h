
/**
	@file recursivemergesort.h
	@author Terence Schumacher
	@author Dominic Badzik
	@version 1.3

*/

#ifndef _ITERATIVEMERGESORT_H
#define _ITERATIVEMERGESORT_H

class iterativeMergeSort{
public:
	void iterativeMergesort(int originArray[], int arrayMaxSize);
	/*void printArray(int anArray[], int size);
	int randomNumber();
	void setArray(int prospectArray[], int size);
	double diffclock();*/
	void alternateMerSort(int originArray[], int arrayMaxSize, int tempArray[],
										   int cycleSize, int beginList1, int tempSize);

};

//#include "iterativemergesort.cpp"

#endif

