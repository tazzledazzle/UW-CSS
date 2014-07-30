
/**
	@file Node.h
	@author Terence Schumacher
	@version 1.0
*/

#ifndef _NODE_H
#define _NODE_H
#include <cstddef>
#include <iostream>
#include "Data.h"

using namespace std;
class Node {

private:
	Data * dataItem;
	Node * next;
public:
	Node();
	Node(int newItem, char newByte);
	Node(Node *);
	Node(Data *);

	Node(Data * anItem, Node* nextNodePtr);

	~Node();

	Data * getItem() const;
	Node * getNext() const;
	int getFibNumber();
	char getByte();
	
	void setNext(Node * newNext);
	void setItem(Data * newItem);
	void setItem(int number, char byte);
	
	bool operator==(Node * rightHandNode);
	bool operator!=(Node * rightHandNode);
	Node * operator=(Node * baseNode);

};//end Node


#endif


