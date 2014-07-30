  /**=================================
	@file NodeData.h
	@author Terence Schumacher
	@author Dominic Badzik
	@version 1.1
*===================================*/

#ifndef _NODEDATA_H
#define _NODEDATA_H
#include <string>

using namespace std;

struct intData{

	int item;
	int frequency;

};//end intData

struct stringData{
	
	string item;
	int frequency;

};//end stringData

class NodeData{
public:
	
	intData intValue;
	stringData stringValue;

	NodeData();
	NodeData(int newInteger, string newString);
	NodeData( NodeData& rightHandSide);
	NodeData( NodeData * rightHandSide);
	//~NodeData();
	
	
	NodeData(int newInteger);
	NodeData(string aString);

	bool operator<(NodeData * rightHandSide);
};

// #include "NodeData.cpp"

#endif
