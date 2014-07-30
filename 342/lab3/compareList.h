
 /**
	@file compareList.h
	@author Terence Schumacher
	@version 1.0
*/

#ifndef _COMPARELIST_H
#define _COMPARELIST_H

using namespace std;

#include "Node.h"

class compareList{
protected:

	friend ostream& operator<<(ostream& output, compareList& printList);

private:

	Node * head;

public:
	compareList();
	compareList(Node * headEntry);
	compareList(int newItem);
	compareList(int newInt, char newChar);
	
	compareList(compareList& copyList);
	~compareList();
	
	void setHead(Node * newHeadNode);
	void setHead(int newInt);
	void setHead(int newInt, char newChar);
	Node * getHead();

	//i don't think i use this 
	int getItemCount();
	
	int getCurrentSizeIter();
	bool isEmpty();
	bool isInList(const int & selectedEntry);
	bool isInList(const char & selectedEntry);
	void clear();

	bool insert(Node * insertNode);
	bool insert(int numberToInsert);
	bool insert(const int newInt, const char newChar);
	bool remove(int nodeKey);

	bool operator==(compareList& rightHandList);
	bool operator!=(compareList& rightHandList);
	compareList& operator=(compareList& baseList);

};//end compareList

//#include "compareList.cpp"

#endif

