
 /**===========================
	@file List.cpp
	@author Terence Schumacher
	@author Dominic Badzik
	@version 1.6
*=============================*/

#include "List.h"
#include <fstream>
#include <string>
#include <cassert>
#define DUP_ERROR "ERROR: Duplicate Entry"	
#define CONFIRM_ENTRY " FOUND. Is in Set!"
#define DENIED_ENTRY " NOT FOUND. Not in Set!"
#define FIRST_ALPHA_UPPER  'A' 
#define LAST_ALPHA_UPPER 'Z'
#define FIRST_ALPHA_LOWER 'a'
#define LAST_ALPHA_LOWER 'z'
#define FIRST_NUMER '0'
#define LAST_NUMER '9'
#define FIRST_SPEC_CHAR '!'
#define LAST_SPEC_CHAR '~'
#define END_LINER 7

using namespace std;

 /** Constructor
	@brief default constructor
*/
List::List() : head(NULL), size(0)
{

}//end constructor

 /** Constructor
	@brief constructor with new head value
	@param newHead node for the new list's head
*/
List::List(Node * newHead): head(NULL), size(0){
	newHead->setLeftPtr(head);
	head = newHead;
	size = 1;
}//end constructor

 /** Constructor 
	@brief constructor for testing list creation
	@param newItem integer inserted into a listNode
*/
List::List(int newItem): head(NULL), size(0){
	Node * newNode = new Node();
	newNode->setItem(newItem);
	newNode->setLeftPtr(head);
	head = newNode;
	size = 1;
}//end constructor

 /** Copy Constructor
	@brief copies the contents of the base list into a new list
	@param baseList the list to copy
*/
List::List( List& baseList) : head(NULL), size(0){

	if (baseList.isEmpty())
		return;

	Node * current = baseList.getHead();

	while (!baseList.isEmpty()){
		if (current->hasInt())
			this->insert(current->getInt());
		else
			this->insert(current->getString());

		current = current->getLeftPtr();
	
	}//end while

}//end copy Constructor

 /** constructor from file
 */
List::List(ifstream& inFile){
	
	bool buildingWord = false;
	bool buildingNumber = false;
	string curString;

	// while the stream is open for reading
	while (inFile.good()) {
		char curChar;
		// read a single character into curChar
		curChar = inFile.get();

		if ((curChar >= FIRST_ALPHA_UPPER && curChar <= LAST_ALPHA_UPPER) || 
			(curChar >= FIRST_ALPHA_LOWER && curChar <= LAST_ALPHA_LOWER)) {
			// if it is a letter
			if (!buildingWord) {
				// insert the current string that was being built (unless it's empty)
				//insertAddition(curString, this);
				
				if (!curString.empty())
					this->insert(curString);
				
				curString.clear();
				buildingWord = true;
				buildingNumber = false;
			
			}//end if !building Word
			curString += curChar;
		}//end if a letter

		else if (curChar >= FIRST_NUMER && curChar <= LAST_NUMER) {
		
			if (!buildingNumber) {
				// insert the current string that was being built
				//insertAddition(curString, this);
				
				this->insert(curString);
				curString.clear();
				buildingWord = false;
				buildingNumber = true;
			}
			curString += curChar;
		}
		else {
			// else it is a symbol
			// insert the current string that was being built
			//insertAddition(curString, this);

			if (!curString.empty()){
				this->insert(curString);
			}
			curString.clear();

			buildingWord = false;
			buildingNumber = false;

			if (curChar >= FIRST_SPEC_CHAR && curChar <= LAST_SPEC_CHAR) {
				curString += curChar;
			}//end if a character
		}//end if
	}//end while the infile is good

}//end constructor

 /** Destructor
	@brief Returns memory to the heap
*/
List::~List(){
	//this is the cause of memory leaks 2/28 @ 2:48PM
	this->clear();
	delete head;
	head = NULL;
	delete tail;
	tail = NULL;
}//end destructor

 /** Is Empty
	@brief checks to see if the list is empty
	@return true if list is empty, false otherwise
*/
bool List::isEmpty(){

	return (head == NULL) || (size == 0);

}//end isEmpty

 /** Set Head
	@brief sets the head Pointer
	@param newHeadValue the value to set the head 
*/
void List::setHead(const int newHeadValue){
	Node * newNode = new Node();
	newNode->setItem(newHeadValue);
	head = newNode;
	size++;
	
}//end setHead

 /** Get Head
	@brief returns the value located at head pointer
	@pre method must be called on a valid list
	@return the Head Pointer
*/
Node * List::getHead() {
	return head;
}//end getHead

 /** Get Tail
 */
Node * List::getTail() {
	return tail;
}//end getTail

 /** Is in List
	@brief checks whether an integer is in the list
	@param selectedEntry the number to search for
	@return true if found, false otherwise
*/
bool List::isInList(const int & selectedEntry){
	Node * current = head;

	while (current != NULL){
		if (current->getInt() == selectedEntry)
		{
			//cout << selectedEntry << CONFIRM_ENTRY << endl;
			return true;
		}
		else {
			current = current->getLeftPtr();
		}
	}//end while

	cout << selectedEntry << DENIED_ENTRY << endl;
	return false;
}//end isInSet


 /** Insert
	@brief inserts a node at the end of the list
	@param newEntry the value to be inserted
	@return true if entry is successfull
*/
bool List::insert(const int newEntry){

	Node * newNode = new Node();
	newNode->setItem(newEntry);

	if (this->isEmpty()){
		head = newNode;
		assert(head->getInt() == newEntry);
		size++;
		return true;
	}
	else
	{
	Node * current = head;
	Node * previous = NULL;

	while ((current != NULL)&&(current->getInt() < newEntry ))
	{	
		previous = current;
		current = current->getLeftPtr(); 
	}//end while
	

	if (current != NULL){
			if (head->getInt() == current->getInt()){
			
			newNode->setLeftPtr(head);
			head = newNode;
			size++;
			return true;
		}//end if
		
		previous->setLeftPtr(newNode);
		newNode->setLeftPtr(current->getLeftPtr());
		size++;
		return true;
	} 
	else if (current == NULL){
		previous->setLeftPtr(newNode);
		size++;
		return true;
	}//end if
	else
		cout << DUP_ERROR << endl;

		delete newNode;
		newNode = NULL;

		return false;
	}//end if 

	// if something went wrong
	return false;

}//end insert

 /** Insert
	@brief inserts a node at the end of the list
	@param newEntry the value to be inserted
	@return true if entry is successfull
*/
bool List::insertStrFreqs(Node * insertNode){
	Node * newNode = new Node(insertNode);
	newNode->setLeftPtr(NULL);
	newNode->setRightPtr(NULL);

	if (this->isEmpty()){
		newNode->setLeftPtr(NULL);
		newNode->setRightPtr(NULL);
		head = newNode;
		tail = newNode;
		assert(head->getString().compare(insertNode->getString()) == 0);
		size++;
		return true;
	}
	else
	{
	Node * current = head;
	Node * previous = NULL;

	while ((current != NULL) && (current->getStringFrequency() < newNode->getStringFrequency() ))
	{	
		previous = current;
		current = current->getLeftPtr(); 
	}//end while
	

	if (current != NULL){
		if (head->getStringFrequency() == current->getStringFrequency()){
			newNode->setLeftPtr(head);
			head->setRightPtr(newNode);
			head = newNode;
			size++;
			return true;
		}//end if
		
		if (current->getStringFrequency() == newNode->getStringFrequency()){
			while ((current->getStringFrequency() == newNode->getStringFrequency()) &&
					(current->getString().compare(newNode->getString()) > 0)){	
				previous = current;
				current = current->getLeftPtr();
				
				if (current == NULL){
					previous->setLeftPtr(newNode);
					newNode->setRightPtr(previous);
					tail = newNode;
					size++;
				return true;
				}//end if
			}// end while

			previous->setLeftPtr(newNode);
			newNode->setLeftPtr(current);
			newNode->setRightPtr(previous);
			current->setRightPtr(newNode);
			size++;
			return true;
		}//end if

		previous->setLeftPtr(newNode);
		newNode->setLeftPtr(current);
		newNode->setRightPtr(previous);
		current->setRightPtr(newNode);
		size++;
		return true;
	} 
	else if (current == NULL){
		previous->setLeftPtr(newNode);
		newNode->setRightPtr(previous);
		tail = newNode;
		size++;
		return true;
	}//end if
	else
		cout << DUP_ERROR << endl;

		delete newNode;
		newNode = NULL;

		return false;
	}//end if 

	// if something went wrong
	return false;

}//end insert

 /** Insert
	@brief inserts a node at the end of the list
	@param newEntry the value to be inserted
	@return true if entry is successfull
*/
bool List::insertFreqs(Node * insertNode){
	Node * newNode = new Node(insertNode);
	newNode->setLeftPtr(NULL);
	newNode->setRightPtr(NULL);

	if (this->isEmpty()){
		newNode->setLeftPtr(NULL);
		newNode->setRightPtr(NULL);
		head = newNode;
		tail = newNode;
		assert(head->getInt() == insertNode->getInt());
		size++;
		return true;
	}
	else
	{
	Node * current = head;
	Node * previous = NULL;

	while ((current != NULL) && (current->getIntFrequency() < newNode->getIntFrequency() ))
	{	
		previous = current;
		current = current->getLeftPtr(); 
	}//end while
	

	if (current != NULL){
		if (head->getIntFrequency() == current->getIntFrequency()){
			newNode->setLeftPtr(head);
			head->setRightPtr(newNode);
			head = newNode;
			size++;
			return true;
		}//end if
		
		if (current->getIntFrequency() == newNode->getIntFrequency()){
			while ((current->getIntFrequency() == newNode->getIntFrequency()) &&	(current->getInt() < newNode->getInt()))
			{	previous = current;
				current = current->getLeftPtr();
				
				if (current == NULL){
					previous->setLeftPtr(newNode);
					newNode->setRightPtr(previous);
					tail = newNode;
					size++;
				return true;
				}//end if
			}// end while
			
			previous->setLeftPtr(newNode);
			newNode->setLeftPtr(current);
			newNode->setRightPtr(previous);
			current->setRightPtr(newNode);
			size++;
			return true;
		}//end if

		previous->setLeftPtr(newNode);
		newNode->setLeftPtr(current);
		newNode->setRightPtr(previous);
		current->setRightPtr(newNode);
		size++;
		return true;
	} 
	else if (current == NULL){
		previous->setLeftPtr(newNode);
		newNode->setRightPtr(previous);
		tail = newNode;
		size++;
		return true;
	}//end if
	else
		cout << DUP_ERROR << endl;

		delete newNode;
		newNode = NULL;

		return false;
	}//end if 

	// if something went wrong
	return false;

}//end insert

 /** Insert (Needs Modification)
 */
bool List::insert(string newEntry){

	Node * newNode = new Node(newEntry);
	//newNode->setItem(newEntry);

	if (this->isEmpty()){
		//newNode->increaseStringFreq();
		newNode->setLeftPtr(NULL);
		head = newNode;
		assert(head->getString() == newEntry);
		//delete newNode;
		//newNode = NULL;
		size++;
		return true;
	}
	else
	{
	Node * current = head;
	Node * previous = NULL;

	while ((current != NULL)&&(current->getString() < newEntry ))
	{	
		previous = current;
		current = current->getLeftPtr(); 
	}//end while
	

	if (current != NULL){      //maybe this is weird
			if (head->getString() == current->getString()){
			//newNode->increaseStringFreq();
			newNode->setLeftPtr(head);
			head = newNode;
			size++;
			return true;
		}//end if
		
		//newNode->increaseStringFreq();
		previous->setLeftPtr(newNode);
		newNode->setLeftPtr(current->getLeftPtr());
		size++;
		return true;
	} 
	else if (current == NULL){
		newNode->increaseStringFreq();
		newNode->setLeftPtr(NULL);
		previous->setLeftPtr(newNode);
		size++;
		return true;
	}//end if
	else
		//increase frequency
		current->increaseStringFreq();
		delete newNode;
		newNode = NULL;
		return true;
	}//end if 
		delete newNode;
		newNode = NULL;
	// if something went wrong
	return false;

}//end insert

 /** Insert
	@brief inserts a node at the end of the list
	@param newInt the integer to insert
	@param newChar the byte to insert
	@return true if entry is successfull
*/
bool List::insert(Node * newNode){     //I don' think this is doing anything

	if (this->isEmpty()){
		newNode->setLeftPtr(NULL);
		newNode->setRightPtr(NULL);
		head = newNode;
		size++;
		return true;
	}
	else
	{
	Node * current = head;
	Node * previous = NULL;

	while (current != NULL)
	{	
		
		previous = current;
		current = current->getLeftPtr(); 


	}//end while

		previous->setLeftPtr(newNode);
		newNode->setLeftPtr(current);
		size++;
		return true;
	} 

	////if something went wrong
	//return false;
}//end insert

/** Destroy Node
	@brief helper method to for remove() 
	@param removalNode the node to remove
*/
void destroyNode(Node * removalNode){    //this might not work
		//removalNode->setItem(NULL);
		delete removalNode->getData();
		//removalNode->setItem(NULL);
		removalNode->setLeftPtr(NULL);
		delete removalNode;
		removalNode = NULL;
}//end destroyNode

 /** Remove
	@brief removes the node containing the selected entry
	@param removalEntry the integer item searchable in the list 
*/
bool List::remove(int removalKey)
{

   bool canRemoveItem = isInList(removalKey);

   if (canRemoveItem)
   {
		Node * current = head;
		Node * previous = NULL;
      
	while ((current != NULL)&&(current->getInt() < removalKey ))
	{	
		previous = current;
		current = current->getLeftPtr(); 
	}//end while

		if (current == head){

			head = head->getLeftPtr();
			
			destroyNode(current);
			size--;
			return true;
		} else if (current->getLeftPtr() == NULL) {
				//end node
			//I don't think this is needed
			destroyNode(current);
			size--;
			return true;

		} else {
			previous->setLeftPtr(current->getLeftPtr());

			destroyNode(current);
			size--;
			return true;
		}//end if
   } // end if
   
	return canRemoveItem;
}  // end remove

/** operator <<
	@brief Prints out the contents of the Set
	@param output the output stream 
	@param list the list to send to the output stream
	@return the output stream containing the contents of the list
*/
 ostream& operator<<(ostream& output, List &printList){
	Node *current =  printList.getHead();
	// output << "{ ";

	 while (current != NULL)
	 {
		output << "[" << current->getInt() << ": " ;
		output  << current->getString();
		output << "]";
		current = current->getLeftPtr();
	 }//end while 
	// output << '}';

	 return output;
}//end operator<<

 /** operator <<
	@brief Prints out the contents of the Set
	@param output the output stream 
	@param list the list to send to the output stream
	@return the output stream containing the contents of the list
*/
 ostream& List::printList(ostream& output, List &printList){
	Node *current =  printList.getHead();
	int countReturn = 0;
	 while (current != NULL)
	 {
		printList.printDetails(output, current);
		//output << current->getByte() << "] ";
		current = current->getLeftPtr();
		current->checkReturn(countReturn, output);
	 }//end while 
	// output << '}';
	 output << "List Size: " << printList.size << endl;

	 return output;
}//end operator<<

 void List::printDetails(Node * current){
	if (current->hasInt()){
		cout << "["<< current->getInt() << "]-Freq:=" <<
			current->getIntFrequency() << ", ";
		//cout << endl;
	}
	else{
		cout << "[" << current->getString() <<  "]-Freq:=" 
		 << current->getStringFrequency() << ", ";
		//cout << endl;
	}//end if
	

 }//end printDetails

  void List::printDetails(ostream& outFile, Node * current){
	if (current->hasInt()){
		outFile << "["<< current->getInt() << "]-Freq:=" <<
			current->getIntFrequency() << ", ";
		outFile << endl;
	}
	else{
		outFile << "[" << current->getString() <<  "]-Freq:=" 
		 << current->getStringFrequency() << ", ";
		outFile << endl;
	}//end if
	

 }//end printDetails

  /** Print N
  */
 void List::printN(int cycleCount, List &printableList){
	 if (isEmpty()){
		return;
	 }
	 else if (this->size < cycleCount){
		cycleCount = size;
	 }//end if

	 int count = 0;
	Node * current = printableList.getHead();
	cout << endl << "Least Frequent: " << endl;
	while ((current != NULL) && (count < cycleCount)){
		cout << (count+1) << ":=";
		printDetails(current);
		current = current->getLeftPtr();
		count++;
		if ((count) % END_LINER == 0)
			cout << endl;
	}//end while
		cout << endl;
	count = 1;
	current = printableList.getTail();
	while (count < cycleCount){
		current = current->getRightPtr();
		count++;
	}//end while
	count = 0;
	cout << "Most Frequent: " << endl;
	while ((current != NULL) && (count < cycleCount)){
		
		cout << (count+1) << ": ";
		printDetails(current);
		current = current->getLeftPtr();
		count++;
		if ((count)% END_LINER == 0)
			cout << endl;
	}//end while

 }//end printN

 /** Clear
	@brief Clears an entire list of all nodes
	@pre List must contain at least one element
	@post List is empty
 */
 void List::clear() {
	 while (head != NULL){
		Node * deleteNode = head;
		head = head->getLeftPtr();
		//delete deleteNode->getData();
		//deleteNode->setData() = NULL;

		delete deleteNode;
		deleteNode = NULL;
		size--;
	 }	
	 tail = NULL;

		//delete head;
		//head = NULL;
	assert(isEmpty());
 }//end clear

 /** = Operator
	@brief sets one lists values to another
	@param testList2 the values that will transfer
	@return a copy of the the list passed in
*/
List& List::operator=(List& rightHandSide) 
	{
	if (!isEmpty()){
		this->clear();}
	Node * rightSide = rightHandSide.getHead();
	Node * current = this->head;
	while(rightSide != NULL){
		int newInt = rightSide->getInt();
		//char newChar = rightSide->getByte();
	Node * newNode = new Node(newInt);
	
	if (this->isEmpty()){
		this->head = newNode;
		assert(this->getHead()->getInt() == newInt);
		
		current = this->head;
		rightSide = rightSide->getLeftPtr();
	} else{
		current->setLeftPtr(newNode);

		rightSide = rightSide->getLeftPtr();
		current = current->getLeftPtr();
		
	}//end if

	}//end while
	return *this;
}//end operator=

