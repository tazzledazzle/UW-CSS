
  /**=================================
	@file Node.h
	@author Terence Schumacher
	@version 1.6
*===================================*/

#ifndef _NODE_H
#define _NODE_H

#include <iostream>
#include <string>
#include <cassert>
#include "NodeData.h"

using namespace std;

class Node {
private:
	NodeData * item;
	Node * leftChildPtr;
	Node * rightChildPtr;
	bool leftThread;
	bool rightThread;
public:
	Node();
	Node(int item);
	Node(string item);
	Node(NodeData * newItem);
	Node(int item, Node * left, Node * right, bool leftT, bool rightT);
	Node(string item, Node * left, Node * right, bool leftT, bool rightT);
	Node( Node *& copyNode);
	~Node();

	int getInt();
	string getString();
	NodeData* getData();
	Node * getLeftPtr();
	Node * getRightPtr();
	bool getLeftThread();
	bool getRightThread();
	
	int getIntFrequency();
	int getStringFrequency();

	void clear();
	
	void increaseIntFreq();
	void decreaseIntFreq();
	void increaseStringFreq();
	void decreaseStringFreq();

	void setItem(int newItem);
	void setItem(string newString);
	void setItem(NodeData* newData);
	void setLeftPtr(Node * newLeft);
	void setRightPtr(Node * newRight);
	void setLeftThread(bool conclusion);
	void setRightThread(bool conclusion);
	void setIntFrequency(int newFreq);
	void setStringFrequency(int newFreq);

	Node* operator=( Node& rightHandSide);
	bool operator<(Node& rightHandSide);
	bool operator>(Node& rightHandSide);

	bool isEmpty();
	bool isLeftChild();
	bool isRightChild();
	bool isLeaf();
	
	bool hasData();
	bool hasString();
	bool hasInt();
	bool hasOnlyLeftChild();
	bool hasOnlyRightChild();
	bool hasTwoChildren();
	bool hasNoChildren();

	void checkReturn(int countReturn, ostream& output);
	void printNode(Node * printNode);

	Node * findLeftFloor();
	Node * iterate();

};//end Node

//#include "Node.cpp"

#endif
