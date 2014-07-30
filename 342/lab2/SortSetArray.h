/** 
	@file SortSetArray.h
	@version 1.3
*/
#ifndef _SORTSETARRAY_H_
#define _SORTSETARRAY_H_
#define MAX_FIB 112500

#include <iostream>
 
using namespace std;
class SortSetArray {
private:
	bool set[MAX_FIB];
	int ItemCount;

protected:
	// overloaded <<: prints "DIVIDE BY ZERO ERROR!!!" if denominator is zero,
    //    prints whole numbers without denominator (as ints), otherwise uses '/'
    friend ostream& operator<<(ostream&, const SortSetArray&);
    
    // overloaded >>: takes 2 ints as numerator and denominator, does no
    //    error checking, standard C casting between floats, char, etc occurs
    friend istream& operator>>(istream&, SortSetArray&);
public:
	SortSetArray();
	SortSetArray(const int& firstValue, const int& secondValue, 
			     const int& thirdValue, const int& fourthValue, const int& fifthValue);
	SortSetArray(const int& firstValue, const int& secondValue, 
				 const int& thirdValue, const int& fourthValue);

	SortSetArray(const int& firstValue, const int& secondValue, 
				 const int& thirdValue);
	SortSetArray(const int& firstValue, const int& secondValue);

	SortSetArray(const int& firstValue);
	SortSetArray(const SortSetArray& baseList);
	//~SortSetArray();

//arithmetic operators
	SortSetArray& operator+ (const SortSetArray& rightHandList) const;
	SortSetArray& operator- (const SortSetArray& removalList);
	SortSetArray& operator* (const SortSetArray& rightHandList) const;
	SortSetArray& operator= (const SortSetArray& baseList);

	//assignment operators
	SortSetArray& operator+= (const SortSetArray& rightHandList);
	SortSetArray& operator-= (const SortSetArray& rightHandList);
	SortSetArray& operator*= (const SortSetArray& rightHandList);

	//equality operators
	bool operator==(const SortSetArray& rightHandList) const;
	bool operator!=(const SortSetArray& rightHandList) const;
	int getSize();
	bool insert(const int& newEntry);
	bool remove(const int removalEntry);
	bool isEmpty();	
	bool isInSet(const int & selectedEntry);
	void clear();


};//end class

#endif
