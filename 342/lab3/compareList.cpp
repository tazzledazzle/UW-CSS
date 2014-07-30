
/**
	@file compareList.cpp
	@author Terence Schumacher
	@version 1.0
*/

#include "compareList.h"
#include <cassert>
#define DUP_ERROR "ERROR: Duplicate Entry"	
#define CONFIRM_ENTRY " FOUND. Is in Set!"
#define DENIED_ENTRY " NOT FOUND. Not in Set!"

using namespace std;

compareList::compareList() : head(NULL)
{

}//end constructor

compareList::compareList(Node * newHead){
	head = newHead;

}//end constructor

compareList::compareList(int newItem){
	Node * newNode = new Node();
	Data * newData = new Data();
	newData->fibNumber = newItem;
	newNode->setItem(newData);
	head = newNode;

}//end constructor

compareList::~compareList(){
	this->clear();
	delete head;
	head = NULL;
}//end destructor

bool compareList::isEmpty(){

	return (head == NULL);

}//end isEmpty

/** Set Head
	@brief sets the head Pointer
	@param newHeadValue the value to set the head 

*/
void compareList::setHead(const int newHeadValue){
	Node * newNode = new Node();
	Data * newData = new Data();
	newData->fibNumber = newHeadValue;
	newNode->setItem(newData);
	head = newNode;
	
}//end setHead

void compareList::setHead(const int newInt, const char newByte){
	Node * newNode = new Node();
	Data * newData = new Data();
	newData->fibNumber = newInt;
	newData->byte = newByte;
	newNode->setItem(newData);
	head = newNode;
	
}//end setHead

/** Get Head
	@pre method must be called on a valid list
	@return the Head Pointer
*/
Node * compareList::getHead() {
	return head;
}//end getHead

 /** Is in List
	@param selectedEntry the number to search for
	@return true if found, false otherwise
*/
bool compareList::isInList(const int & selectedEntry){
	Node * current = head;

	while (current != NULL){
		if (current->getFibNumber() == selectedEntry)
		{
			cout << selectedEntry <<" is in Set" << endl;
			return true;
		}
		else {
			current = current->getNext();
		}
	}//end while

	cout << selectedEntry << " not in Set" << endl;
	return false;
}//end isInSet

 /** Is in List
	@param selectedEntry the number to search for
	@return true if found, false otherwise
*/
bool compareList::isInList(const char & selectedEntry){
	Node * current = head;

	while (current != NULL){
		if (current->getByte() == selectedEntry)
		{
			cout << selectedEntry <<" is in Set" << endl;
			return true;
		}
		else {
			current = current->getNext();
		}
	}//end while

	cout << selectedEntry << " not in Set" << endl;
	return false;
}//end isInSet


//void compareList::printList(const compareList& ){
//	Node * current = head;
//
//	while (current != NULL){
//		cout << current->number << " ";
//		current = current->next;
//	}//end while
//
//}//end printList
//

/** Insert
	@brief inserts a node at the end of the list
	@param newEntry the value to be inserted
	@return true if entry is successfull
*/
bool compareList::insert(const int newEntry){

	Node * newNode = new Node();
	Data * newData = new Data();
	newData->fibNumber = newEntry;
	newNode->setItem(newData);

	if (this->isEmpty()){
		head = newNode;
		assert(head->getFibNumber() == newEntry);
		return true;
	}
	else
	{
	Node * current = head;
	Node * previous = NULL;

	while ((current != NULL)&&(current->getFibNumber() < newEntry ))
	{	
		previous = current;
		current = current->getNext(); 
	}//end while
	

	if (current != NULL){
			if (head->getFibNumber() == current->getFibNumber()){
			
			newNode->setNext(head);
			head = newNode;
			return true;
		}//end if
		
		previous->setNext(newNode);
		newNode->setNext(current->getNext());
		return true;
	} 
	else if (current == NULL){
		previous->setNext(newNode);
		return true;
	}//end if
	else
		cout << DUP_ERROR << endl;

		delete newData;
		newData = NULL;
		delete newNode;
		newNode = NULL;

		return false;
	}//end if 

	//something went wrong
	return false;
}//end insert


/** Insert
	@brief inserts a node at the end of the list
	@param newEntry the value to be inserted
	@return true if entry is successfull
*/
bool compareList::insert(const int newInt, const char newChar){

	Node * newNode = new Node(newInt, newChar);
	

	if (this->isEmpty()){
		head = newNode;
		assert(head->getItem()->fibNumber == newInt);
		return true;
	}
	else
	{
	Node * current = head;
	Node * previous = NULL;

	while ((current != NULL) && (current->getFibNumber() < newInt ))
	{	
		
		previous = current;
		current = current->getNext(); 
		
		if (current == NULL)
			break;

	}//end while

	if (current != NULL){
			if (head->getFibNumber() == current->getFibNumber()){
			
			newNode->setNext(head);
			head = newNode;
			return true;
		}//end if
		
		previous->setNext(newNode);
		newNode->setNext(current);
		return true;
	} 
	else if (current == NULL){
		previous->setNext(newNode);
		return true;
	}//end if
	else
		cout << DUP_ERROR << endl;

		delete newNode;
		newNode = NULL;

		return false;
	}//end if 

	//something went wrong
	return false;
}//end insert


 /** Get Current Size Iteratively
	@return the number of elements in the List
*/
int compareList::getCurrentSizeIter()
{
	Node * current = this->getHead();
	int count = 0;
	while (current != NULL)
	{
		count++;
		current = current->getNext();
	}//end while
	return count;

}  // end getCurrentSize

///** Get Pointer To
//	@param anEntry
//	@return The location of the value entered, NULL otherwise
//*/
//Node * compareList::getPointerTo(const int& anEntry) const
//{
//   bool found = false;
//   Node * curPtr = head;
//   
//   while (!found && (curPtr != NULL))
//   {
//      if (anEntry == curPtr->number)
//         found = true;
//      else
//         curPtr = curPtr->next;
//   } // end while
//   
//   return curPtr;
//} // end getPointerTo
//

void destroyNode(Node * removalNode){
		removalNode->setNext(NULL);
		delete removalNode;
		removalNode = NULL;
}//end destroyNode

///** Remove
//	@brief removes the node containing the selected entry
//	@param removalEntry the searchable item 
//*/
bool compareList::remove(int removalKey)
{
	//Find the node containing the deleted entry
  // Node * entryNodePtr = getPointerTo(anEntry);
   bool canRemoveItem = isInList(removalKey);

   if (canRemoveItem)
   {
		Node * current = head;
		Node * previous = NULL;
      
	while ((current != NULL)&&(current->getFibNumber() < removalKey ))
	{	
		previous = current;
		current = current->getNext(); 
	}//end while

		if (current == head){

			head = head->getNext();
			
			destroyNode(current);
			
			return true;
		} else if (current->getNext() == NULL) {
				//end node
			//I don't think this is needed
			destroyNode(current);

		} else {
			previous->setNext(current->getNext());

			destroyNode(current);
		
		}//end if
   } // end if
   
	return canRemoveItem;
}  // end remove



/** Prints out the contents of the Set
	@param output the output stream 
	@param list the list to send to the output stream
	@return the output stream containing the contents of the list
*/
 ostream& operator<<(ostream& output, compareList &printList){
	Node *current =  printList.getHead();
	// output << "{ ";

	 while (current != NULL)
	 {
		output << "[" << current->getFibNumber() << ": ";
		output << current->getByte() << "] ";
		current = current->getNext();
	 }//end while 
	// output << '}';

	 return output;
}//end operator<<

 /** Clear
	@brief Clears out an entire list
	@pre List must contain at least one element
	@post List is empty
 */
 void compareList::clear() {
//	 assert(!isEmpty());

	while (!isEmpty())
		remove(head->getFibNumber());

	assert(isEmpty());
 }//end clear

// /** = Operator
//	@brief sets one lists values to another
//	@param testList2 the values that will transfer
//	@return a copy of the the list passed in
//*/

compareList& compareList::operator=( compareList& rightHandSide) 
	{
	if (!isEmpty()){
		this->clear();}
	Node * rightSide = rightHandSide.getHead();
	Node * current = this->head;
	while(rightSide != NULL){
		int newInt = rightSide->getFibNumber();
		char newChar = rightSide->getByte();
	Node * newNode = new Node(newInt, newChar);
	
	if (this->isEmpty()){
		this->head = newNode;
		assert(this->getHead()->getFibNumber() == newInt);
		
		current = this->head;
		rightSide = rightSide->getNext();
	} else{
		current->setNext(newNode);

		rightSide = rightSide->getNext();
		current = current->getNext();
		
	}//end if

	}//end while
	return *this;
}//end operator=

 /** == Operator
	@brief compares all elements in lists to see if they are equal or not
	@pre must have two non empty lists to compare
	@param rightHandList the list tested against for equality
*/
bool compareList::operator==( compareList& rightHandList) {
	int leftHandSideSize = this->getCurrentSizeIter();
	int rightHandSideSize = rightHandList.getCurrentSizeIter();
	Node * currentLeft, * currentRight;

	if (leftHandSideSize != rightHandSideSize)
		return false;
	else{
		
		currentLeft = this->getHead();
		currentRight = rightHandList.getHead();
		
		while(currentLeft != NULL){
			
			if (currentLeft->getFibNumber() != currentRight->getFibNumber()){
				return false;
			}//end if
		
			currentLeft = currentLeft->getNext();
			currentRight = currentRight->getNext();

		}//end while currentLeft not NULL
	
		return true;

	}//end if 

	return false;	//if for some reason you get here
}//end operator==

/** == Operator
	@brief compares all elements in lists to see if they are equal or not
	@pre must have == operator overloaded and two non empty lists
	@param rightHandList the list tested against for equality 

*/
bool compareList::operator!=(compareList& rightHandList)  {
	
	return (!(*this == rightHandList));
	
}//end operator==


