/** 
	@file SortSetList.h
	@version 1.4
*/

#ifndef _SORTSETLIST_H_
#define _SORTSETLIST_H_

#include <iostream>
//#include "Node.h"

using namespace std;

	struct Node {
		int number;
		Node * next;
	};//end Node

class SortSetList{
private:

	Node * head;
	Node * getPointerTo(const int& anEntry) const;
	//void iterateNodes(Node * movingNode1, Node * movingNode2) const;
	void clear();

protected:
   
	friend ostream& operator<<(ostream&, const SortSetList&);
    
    // overloaded >>: takes 2 ints as numerator and denominator, does no
    //    error checking, standard C casting between floats, char, etc occurs
	friend istream& operator>>(istream&, SortSetList&);
    
public:

	SortSetList();
	//this needs to be modified
	SortSetList( const int& firstValue, const int& secondValue, 
			     const int& thirdValue, const int& fourthValue, const int& fifthValue);
	SortSetList( const int& firstValue, const int& secondValue, 
				 const int& thirdValue, const int& fourthValue);

	SortSetList( const int& firstValue, const int& secondValue, 
				 const int& thirdValue);
	SortSetList( const int& firstValue, const int& secondValue);

	SortSetList( const int& firstValue);
	SortSetList(const SortSetList& baseList);
	
	~SortSetList();

	//arithmetic operators
	SortSetList& operator+ (const SortSetList& rightHandList) const;
	SortSetList& operator- (const SortSetList& removalList);
	SortSetList& operator* (const SortSetList& rightHandList) const;
	SortSetList& operator= (const SortSetList& baseList);

	//assignment operators
	SortSetList& operator+= (const SortSetList& rightHandList);
	SortSetList& operator-= (const SortSetList& rightHandList);
	SortSetList& operator*= (const SortSetList& rightHandList);

	//equality operators
	bool operator==(const SortSetList& rightHandList) const;
	bool operator!=(const SortSetList& rightHandList) const;

	bool insert(const int newEntry);
	bool remove(const int& anEntry);
	bool isEmpty() const;
	bool isInSet(const int & selectedEntry);
	Node * getHead() const;
	void setHead(int newHeadValue);
	void setHead(Node * newHeadNode);
	void printList(const SortSetList& );
	int getCurrentSizeIter() const;
	void clearList();
	

};//end class

//#include "SortSetList.cpp"


#endif
