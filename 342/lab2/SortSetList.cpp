/**
	@file SortSetList.cpp
	@version 1.4
*/

#include "SortSetList.h"
#include <cassert>
#define DUP_ERROR "ERROR: Duplicate Entry"	
#define CONFIRM_ENTRY " FOUND. Is in Set!"
#define DENIED_ENTRY " NOT FOUND. Not in Set!"

using namespace std;

/** Constructor
*/
SortSetList::SortSetList():head(NULL)
{

}//end constructor

SortSetList::SortSetList( const int& firstValue, const int& secondValue, 
						  const int& thirdValue, const int& fourthValue, const int& fifthValue)
{
	
	if (firstValue >= 0)
	setHead(firstValue);

	if (secondValue >= 0){
		insert(secondValue);
	}//end if second

	if (thirdValue >= 0){
		insert(thirdValue);
	}//end if third

	if (fourthValue >= 0){
		insert(fourthValue);
	}//end if foruth

	if (fifthValue >= 0){
		insert(fifthValue);
	}//end if fifth

}//end constructor


SortSetList::SortSetList( const int& firstValue, const int& secondValue, 
						  const int& thirdValue, const int& fourthValue)
{
	if (firstValue >= 0)
	setHead(firstValue);

	if (secondValue >= 0){
		insert(secondValue);
	}//end if second

	if (thirdValue >= 0){
		insert(thirdValue);
	}//end if third

	if (fourthValue >= 0){
		insert(fourthValue);
	}//end if foruth
}//end constructor


SortSetList::SortSetList( const int& firstValue, const int& secondValue, 
						  const int& thirdValue)
{
	if (firstValue >= 0)
	setHead(firstValue);

	if (secondValue >= 0){
		insert(secondValue);
	}//end if second

	if (thirdValue >= 0){
		insert(thirdValue);
	}//end if third

}//end constructor

SortSetList::SortSetList( const int& firstValue, const int& secondValue)
{
	if (firstValue >= 0)
	setHead(firstValue);

	if (secondValue >= 0){
		insert(secondValue);
	}//end if second

}//end constructor

SortSetList::SortSetList( const int& firstValue)
{
	if (firstValue >= 0)
	setHead(firstValue);
}//end constructor

SortSetList::SortSetList(const SortSetList& baseList){
	
	Node * insertionPoint = baseList.getHead();
	setHead(insertionPoint->number);

	while (insertionPoint != NULL){

		insert(insertionPoint->number);
		insertionPoint = insertionPoint->next;
	}//end while

}//end copy Constructor

/** Destructor
*/
SortSetList::~SortSetList(){

	clear();
	delete head;
	head = NULL;

}//end destructor

/** Set Head
	@brief sets the head Pointer
	@param newHeadValue the value to set the head 

*/
void SortSetList::setHead(const int newHeadValue){
	Node * newNode = new Node();
	newNode->number = newHeadValue;
	head = newNode;
	
}//end setHead

/** Set Head
	@brief sets the value of the private member head
	@param newHeadNode node value desired for head
*/
void SortSetList::setHead(Node * newHeadNode){
	newHeadNode->next = head;
	head = newHeadNode;
}//end setHead

/** Get Head
	@pre method must be called on a valid list
	@return the Head Pointer
*/
Node * SortSetList::getHead() const{
	return head;
}//end getHead

/** Is in Set
	@param selectedEntry the number to search for
	@return true if found, false otherwise
*/
bool SortSetList::isInSet(const int & selectedEntry){
	Node * current = head;

	while (current != NULL){
		if (current->number == selectedEntry)
		{

			//cout << selectedEntry <<" is in Set" << endl;

			return true;
		}
		else {
		
			current = current->next;
		}
	}//end while

	//cout << selectedEntry << " not in Set" << endl;
	
	return false;
}//end isInSet

void SortSetList::printList(const SortSetList& ){
	Node * current = head;

	while (current != NULL){
		cout << current->number << " ";
		current = current->next;
	}//end while

}//end printList

/** Is Empty
	@return true if list is empty, false otherwise
*/
bool SortSetList::isEmpty() const{

	return (head == NULL);
}//end isEmpty

/** Insert
	@brief inserts a node at the end of the list
	@param newEntry the value to be inserted
	@return true if entry is successfull
*/
bool SortSetList::insert(const int newEntry){

	Node * newNode = new Node();
	newNode->number = newEntry;

	if (this->isEmpty()){
		head = newNode;
		assert(head->number == newEntry);
		return true;
	}
	else
	{
	Node * current = head;

	while (current->next != NULL){
		current = current->next; 
	}//end while

	if (current->number != newEntry){
	current->next = newNode;

	return true;
	}
	else {
		cout << DUP_ERROR << endl;
		
		delete newNode;
		newNode = NULL;

		return true;}
	}//end if 

	//something went wrong
	return false;
}//end insert

/** Get Current Size Iteratively
	@return the number of elements in the List
*/
int SortSetList::getCurrentSizeIter() const
{
	Node * current = getPointerTo(head->number);
	int count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}//end while
	return count;

}  // end getCurrentSize

/** Get Pointer To
	@param anEntry
	@return The location of the value entered, NULL otherwise
*/
Node * SortSetList::getPointerTo(const int& anEntry) const
{
   bool found = false;
   Node * curPtr = head;
   
   while (!found && (curPtr != NULL))
   {
      if (anEntry == curPtr->number)
         found = true;
      else
         curPtr = curPtr->next;
   } // end while
   
   return curPtr;
} // end getPointerTo

/** Remove
	@brief removes the node containing the selected entry
	@param removalEntry the searchable item 
*/
bool SortSetList::remove(const int& anEntry)
{
	//Find the node containing the deleted entry
   Node * entryNodePtr = getPointerTo(anEntry);
   bool canRemoveItem = isInSet(anEntry);

   if (canRemoveItem)
   {
 
      Node * nodeToDeletePtr = entryNodePtr;

	  if (entryNodePtr == head){
      // Delete first node
      nodeToDeletePtr = entryNodePtr;
      head = head->next;

	  }
	  else{
	  //delete node in between
		  entryNodePtr = head;

		  while (entryNodePtr->next != nodeToDeletePtr)
		  { 
			  entryNodePtr = entryNodePtr->next;
		  }//end while

		  entryNodePtr->next = nodeToDeletePtr->next;

	  }//end if

      // Return node to the system
      nodeToDeletePtr->next = NULL;

      delete nodeToDeletePtr;
      nodeToDeletePtr = NULL;
      
   } // end if
   
	return canRemoveItem;
}  // end remove

/** Prints out the contents of the Set
	@param output the output stream 
	@param list the list to send to the output stream
	@return the output stream containing the contents of the list
*/
 ostream& operator<<(ostream& output, const SortSetList &printList){
	Node *current =  printList.getHead();
	 output << "{ ";
	 while (current != NULL)
	 {
		output << current->number << ' ';
		current = current->next;
	 }//end while 
	 output << '}';

	 return output;
}//end operator<<

 /** Enter in Values for the set
	@param input the input stream used
	@param enteredValueList the list the values are being added to
	@return list with values inserted into it
 */
 istream& operator>>(istream& input, SortSetList& listCreation){

	 while (!input.eof()){
		 int temp = 0;
	 input >> temp;
	if (temp < 0 )
		break;

	listCreation.insert(temp);
	 }//end while
	 return input;
    }//end operator>>
 
 /** Clear
	@brief Clears out an entire list
	@pre List must contain at least one element
	@post List is empty
 */
 void SortSetList::clear() {
//	 assert(!isEmpty());

	while (!isEmpty())
		remove(head->number);

	assert(isEmpty());
 }//end clear

 /** = Operator
	@brief sets one lists values to another
	@param testList2 the values that will transfer
	@return a copy of the the list passed in
*/
SortSetList& SortSetList::operator=(const SortSetList& rightHandSide) 
	{
	if (!isEmpty()){
		this->clear();}
	Node * current = rightHandSide.getHead();
	while(current != NULL){
		
		insert(current->number);
		current = current->next;
	}//end while
	return *this;
}//end operator=

/** + operator
	@brief the set of elements that are contained in either or both sets
	@param
	@return  the union of two sets in a new List
*/
SortSetList& SortSetList::operator+(const SortSetList& rightSideList) const {

	SortSetList * newList = new SortSetList();	
	Node * leftSideListPtr = this->getHead(), 
		 * rightSideListPtr = rightSideList.getHead();

	//ordered insertion
	while((leftSideListPtr != NULL) && (rightSideListPtr != NULL))
	{
		if (leftSideListPtr->number < rightSideListPtr->number)
		{
			newList->insert(leftSideListPtr->number);		//left is smaller
			leftSideListPtr = leftSideListPtr->next;		// left++
		}
		else 
		{
			newList->insert(rightSideListPtr->number);		//right is smaller
			rightSideListPtr = rightSideListPtr->next;		// right++
		}//end if left side < right side

	}//end while

	//make sure there are no stragglers
	while (leftSideListPtr != NULL){
			newList->insert(leftSideListPtr->number);		//left is smaller
			leftSideListPtr = leftSideListPtr->next;		// left++
	}//end left not null

	while (rightSideListPtr != NULL) {
			newList->insert(rightSideListPtr->number);		//right is smaller
			rightSideListPtr = rightSideListPtr->next;		// right++
	}//end right not null

	return *newList;
}//end operator+

/** - operator
	@brief creates the difference between two sets
	@param rightHandList the items of removal from this 
	@return difference of leftSide and rightSide
*/
SortSetList& SortSetList::operator-(const SortSetList& rightHandList){
	
	int valueOfDeletion;
	bool found;
	SortSetList * listDifference = new SortSetList();

	Node * current = this->getHead();
	
	//There's a simpler way but I can't figure it out now
	while (current != NULL){
	listDifference->insert(current->number);
	current = current->next;
	}//end while

	current = rightHandList.getHead();

	while(current != NULL){
	//find L2's value in L1
	 valueOfDeletion = current->number;
	 found = listDifference->isInSet(valueOfDeletion);
		//if found
	if (found){
			//remove it 
		listDifference->remove(current->number);
		}//end if
			current = current->next;

	}//end while

	return *listDifference;
}//end operator-

/** Public access of clear
	@brief clears the list
	@post List is empty
*/
void SortSetList::clearList(){

	this->clear();
}//end clearList

/** == Operator
	@brief compares all elements in lists to see if they are equal or not
	@pre must have two non empty lists to compare
	@param rightHandList the list tested against for equality
*/
bool SortSetList::operator==(const SortSetList& rightHandList) const {
	int leftHandSideSize = this->getCurrentSizeIter();
	int rightHandSideSize = rightHandList.getCurrentSizeIter();
	Node * currentLeft, * currentRight;

	if (leftHandSideSize != rightHandSideSize)
		return false;
	else{
		
		currentLeft = this->getHead();
		currentRight = rightHandList.getHead();
		
		while(currentLeft != NULL){
			
			if (currentLeft->number != currentRight->number){
				return false;
			}//end if
		
			currentLeft = currentLeft->next;
			currentRight = currentRight->next;

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
bool SortSetList::operator!=(const SortSetList& rightHandList) const {
	
	return (!(*this == rightHandList));
	
}//end operator==

/** * operator (intersection)
	@brief returns a list with values contained in both lists compared
	@param rightHandList a list compared to this
	@return the intersection of the two lists inside a new list
*/
SortSetList& SortSetList::operator*(const SortSetList& rightHandList) const {
	
	SortSetList * intersection = new SortSetList();
	
	Node * leftCurrent = this->getHead(), 
		 * rightCurrent = rightHandList.getHead();

	while((leftCurrent != NULL) && (rightCurrent != NULL)){
		
		if (leftCurrent->number == rightCurrent->number){

			intersection->insert(leftCurrent->number);
			
			//move both down
			leftCurrent = leftCurrent->next;
			rightCurrent = rightCurrent->next;
		}
		else
		{
				if (leftCurrent->number < rightCurrent->number)
				{
					leftCurrent = leftCurrent->next;
				}
				else 
				{
					rightCurrent = rightCurrent->next;
				}//end if
		
		}//end if 
		
	}//end while

	return *intersection;

}//end operator*

	//assignment operators

/** + = operator
	@brief assigns union
	@param rightHandList list added
	@return this + rightHandList inside of this
*/
SortSetList& SortSetList::operator+= (const SortSetList& rightHandList)  {
	
	*this = (*this + rightHandList);

	return *this;
}//end operator+=

/** - = operator
	@brief assigns difference
	@param rightHandList list items removed from this
	@return this - rightHandList inside of this
*/
SortSetList& SortSetList::operator-= (const SortSetList& rightHandList) {

	*this = (*this - rightHandList);

	return *this;
}//end operator -=

/** * = operator
	@brief assigns intersection
	@param rightHandList list items compared to this
	@return this * rightHandList inside of this
*/
SortSetList& SortSetList::operator*= (const SortSetList& rightHandList) {

	*this = (*this * rightHandList);

	return *this;
}//end operator*=
