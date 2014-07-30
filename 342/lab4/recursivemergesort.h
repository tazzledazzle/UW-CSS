
/**
	@file recursivemergesort.h
	@author Terence Schumacher
	@author Dominic Badzik
	@version 1.3

*/

#ifndef _RECURSIVEMERGESORT_H
#define _RECURSIVEMERGESORT_H

class recursivemergesort{
public:
	void mergesort(int anArray[], int lowEnd, int highEnd );
	void merge(int array[], int first, int mid, int last, int x);

};

//#include "recursivemergesort.cpp"

#endif

