
 /**============================================ 
	@file List.h
	@author Terence Schumacher
	@author Dominic Badzik
	@version 1.6
 =============================================*/

#ifndef _LIST_H
#define _LIST_H

using namespace std;

#include "Node.h"
//#include "List.cpp"

class List{
protected:

	friend ostream& operator<<(ostream& output, List& printList);

private:

	Node * head;
	Node * tail;

	void printDetails(Node * current);
	void printDetails(ostream& outFile, Node * current);

public:
	int size;
	List();
	List(Node * headEntry);
	List(List& baseList);
	List(ifstream& inFile);
	List(int newItem);
	~List();

	void setHead(int newInt);
	Node * getHead();
	Node * getTail();

	bool isEmpty();
	bool isInList(const int & selectedEntry);
	void clear();

	bool insert(Node * insertNode);
	bool insert(int numberToInsert);
	bool insertFreqs(Node * insertNode);
	bool insertStrFreqs(Node * insertNode);
	bool insert(string newEntry);
	bool remove(int nodeKey);

	bool operator==(List& rightHandList);
	bool operator!=(List& rightHandList);
	List& operator=(List& baseList);

	ostream& printList(ostream& output, List &printList);	//refactor
	void printN(int cycleCount, List  &printableList);

};//end List

//#include "List.cpp"

#endif

