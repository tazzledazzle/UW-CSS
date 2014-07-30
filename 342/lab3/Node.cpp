
 /**
	@file Node.cpp
	@author Terence Schumacher
	@version 1.0
*/


#include "Node.h"
using namespace std;


Node::Node() : next(NULL), dataItem(NULL)
{

} // end default constructor


Node::Node(Node* newNode):dataItem(newNode->getItem()), next(newNode->getNext())
{
	
}//end constructor

Node::Node(int newItem, char newByte){
	Data *data = new Data();
	data->fibNumber = newItem;
	data->byte = newByte;

	dataItem = data;
	next = NULL;

}//end constructor

Node::Node(Data* anItem) : dataItem(anItem), next(NULL)
{
} // end constructor


Node::Node(Data * anItem, Node* nextNodePtr) :
               dataItem(anItem), next(nextNodePtr)
{
} // end constructor


Node::~Node(){
	dataItem->fibNumber = -1;
	dataItem->byte = ' ';
	delete dataItem;
		dataItem = NULL;

	delete next;
	next = NULL;
}//end destructor


void Node::setItem(Data * anItem)
{
  dataItem = anItem;
} // end setItem

void Node::setItem(int number, char byte)
{
	dataItem->fibNumber = number;
	dataItem->byte = byte;
}


void Node::setNext(Node* nextNodePtr)
{
   next = nextNodePtr;
} // end setNext


Data* Node::getItem() const
{
   return dataItem; 
} // end getItem

int Node::getFibNumber(){
	return dataItem->fibNumber;
}//end getFibNubmer

char Node::getByte(){
	return dataItem->byte;
}//end getByte


Node* Node::getNext() const
{

	return next;
} // end getNext

	/** == operator
		@return true if nodes are equal, false otherwise
	*/

bool Node::operator==(Node * rightHandNode) {

	
	return ((this->getFibNumber() == rightHandNode->getFibNumber()));
	// &&
			 //(this->dataItem->byte == rightHandNode->dataItem->byte))
			 

} //end operator==


	
	/** != operator
		@return true if nodes are not equal, false otherwise
	*/

bool Node::operator!=(Node * rightHandNode){
	
		return !(this == rightHandNode);
} //end operator!=
	
	/** = operator
		@pre assume an empty dataItem pointer is an empty node;
		@param baseNode the node to pull data from
	*/

	Node * Node::operator=(Node * baseNode){
		
		if (this->dataItem != NULL){
			
			delete dataItem;
			dataItem = NULL;

		}//end if

			Data * newData = new Data();
			newData->fibNumber = baseNode->dataItem->fibNumber;
			newData->byte = baseNode->dataItem->byte;
			this->dataItem = newData;
			this->next = baseNode->next;
		return this;
	} //end operator=


