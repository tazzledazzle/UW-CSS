

  /**=================================
	@file tbst.cpp
	@author Terence Schumacher
	@author Dominic Badzik
	@version 1.6
*===================================*/


#include "tbst.h"
#include <cassert>
#include <fstream>
#define PRINT_ERR "Error on Print"
#define NOT_FOUND " Not Found!"
#define FIRST_ALPHA_UPPER  'A' 
#define LAST_ALPHA_UPPER 'Z'
#define FIRST_ALPHA_LOWER 'a'
#define LAST_ALPHA_LOWER 'z'
#define FIRST_NUMER '0'
#define LAST_NUMER '9'
#define FIRST_SPEC_CHAR '!'
#define LAST_SPEC_CHAR '~'
#define FREQUENCY "]-Freq:="
#define CONTAIN "["
#define CONTAIN_L "]"
#define COMMA_SPACE  ", "
#define SPACE " "


using namespace std;

//==================================Constructors/Destructors
 /** Constructor
	@brief constructs empty Tree
 */
ThreadedBST::ThreadedBST() : root(NULL), size(0)
{

}//end constructor

 /** Copy Constructor
	@brief copies a tree into a new instance of a tree
	@param rightHandTree the tree to copy
 */
ThreadedBST::ThreadedBST(ThreadedBST &rightHandTree): root(NULL), size(0)
{
	if (rightHandTree.isEmpty()){
		return;
	}
	else {
		this->setRoot(NULL);
		preorderInsert(rightHandTree.getRoot());
	}//end if
}//end copy Constructor

 /** Construct from File
	@brief copies all tokens from an infile into nodes, creating a tree
	@param fileName name of file creating tree from
 */
ThreadedBST::ThreadedBST(const char* fileName): root(NULL), size(0)
{
	ifstream inFile(fileName, ifstream::in);

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
				
				this->insert(curString);
				curString.clear();
				buildingWord = false;
				buildingNumber = true;
			}//end if !buildingNumber
			curString += curChar;
		}
		else {
			// else it is a symbol
			// insert the current string that was being built
			if (!curString.empty()){
				this->insert(curString);
			}//end if !empty

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
	@brief deallocates memory allocated to create trees
 */
ThreadedBST::~ThreadedBST(){
	if (root->hasInt()){
		postorderDeletion(root);
	} 
	else if (root->hasString())  {
		postorderStringDeletion(root);
	}//end if 
}//end destructor

//====================================================Private Methods

 /** Preorder Insert
	@brief helps copy constructor construct tree
	@param currentNode node to insert into this tree
 */
void ThreadedBST::preorderInsert(Node * currentNode){
	if (currentNode == NULL){
		return;
	}//end if 

	if (currentNode->hasString()){
		insert(currentNode->getData());
	}
	else {
		insert(currentNode->getInt());
	}//end if
	
	if (!currentNode->getLeftThread())
		preorderInsert(currentNode->getLeftPtr());
	
	if (!currentNode->getRightThread())
		preorderInsert(currentNode->getRightPtr());

}//end preorderInsert
 
 /** Destroy Node
	@brief helper method to deallocate memory
	@param currentNode the node to destroy
 */
void ThreadedBST::destroyNode(Node* currentNode){
	currentNode->clear();
	delete currentNode;
	currentNode = NULL;
	size--;
}//end destroyNode

 /** Only Root
	@brief tests whether root is only node in the tree
	@return true if both left and right children null, false otherwise
 */
bool ThreadedBST::onlyRoot(){
	return ((getRoot()->getLeftPtr() == NULL) &&
			(getRoot()->getRightPtr() == NULL));
}//end onlyRoot

 /** Is Empty
	@brief checks to see whether the root is NULL
	@return true if NULL, false otherwise
 */
bool ThreadedBST::isEmpty(){
	return (root == NULL);
}//end isEmpty

 /** Left Check
	@brief helper method checks left child for null or threaded
	@param current node checking
 */
bool ThreadedBST::leftCheck(Node* current){
	return ((current->getLeftPtr() == NULL) || (current->getLeftThread()));
}//end leftCheck

 /** Right Check
	@brief helper method checks left child for null or threaded
	@param current node checking

 */
bool ThreadedBST::rightCheck(Node* current){
	return ((current->getRightPtr() == NULL) || (current->getRightThread()));
}//end rightCheck

 /** Set Pointers NULL
	@brief helper method setting intial pointers null
	@param specifiedNode node modifying
 */
void setPointersNull(Node* specifiedNode){
	specifiedNode->setLeftPtr(NULL);
	specifiedNode->setRightPtr(NULL);
}//end setPointersNull

 /** Print Int
	@brief prints out integer contents
	@param currentNodeLocation node printing from
 */
void printInt(Node* currentNodeLocation){
		cout << currentNodeLocation->getInt() << SPACE;
}//end printInt

 /** Print Full
	@brief prints out integer contents
	@param currentNodeLocation node printing from
 */
void printFull(Node* currentNodeLocation){
		cout << CONTAIN<< currentNodeLocation->getInt() << COMMA_SPACE;
		cout << currentNodeLocation->getString() << CONTAIN_L;
}//end printInt


 /** Print String
	@brief prints out string contents
	@param currentNodeLocation node printing from
 */
void printString(Node * currentNodeLocation){
	cout << currentNodeLocation->getString() << SPACE;
}//end printString

 /** Print Int Frequency
	@brief prints frequency of integer value in node along with integer
	@param currentNodeLocation node printing from
 */
void printIntFreq(Node* currentNodeLocation){
			cout << CONTAIN << currentNodeLocation->getInt()
		<< FREQUENCY << currentNodeLocation->getIntFrequency() << endl;
}//end printIntFreq

 /** Print String Frequency
	@brief Prints frequency of String Value in node along with string
	@param currentNodeLocation node print from 
 */
void printStringFreq(Node* currentNodeLocation){
		cout << CONTAIN << currentNodeLocation->getString()
			<< FREQUENCY << currentNodeLocation->getIntFrequency() << endl;
}//end printStringFreq

 /** Print Integer With/Write Frequency
	@brief prints integer with frequency to specified output
	@param current node printing from
	@param output output writing to
 */
void printIntWFreq(Node* current, ofstream& output){		
	output << CONTAIN<< current->getInt() << FREQUENCY <<
			current->getIntFrequency() << COMMA_SPACE;
}//end printIntWFreq

 /** Print String With/Write Frequency
	@brief prints string with frequency to specified output
	@param current node printing from
	@param output output writing to
 */
void printStringWFreq(Node* current, ofstream& output){
			output << CONTAIN<< current->getString() << FREQUENCY <<
			current->getStringFrequency() <<COMMA_SPACE;
}//end printStringWFreq

 /** Clear Node
 */
void clearNode(Node* insertionNode){
		delete insertionNode;
		insertionNode = NULL;
}//end clearNode

void newLineCheck(int counter, ofstream& output){
		if ((counter % 7) == 0)
				output << endl;
}//end newLineCheck

void moveRight(Node*& tempNode){   //Needs to implement
	while((!tempNode->getRightThread()) && (tempNode->getRightPtr() != NULL))
			tempNode = tempNode->getRightPtr();
}//end moveRight

void moveLeft(Node *& tempNode){
	while((!tempNode->getLeftThread()) && (tempNode->getLeftPtr() != NULL))
				tempNode = tempNode->getLeftPtr();
}//moveLeft

 /** Inorder Traverse
	@brief recursive inorder Traversal of tree
	@param currentNodeLocation node to traverse
 */
void ThreadedBST::inorderTraverse(Node * currentNodeLocation, void visit(Node *)){
	
	if (!currentNodeLocation->isEmpty()){
	if(!currentNodeLocation->getLeftThread())
		inorderTraverse(currentNodeLocation->getLeftPtr(), visit);
	
		visit(currentNodeLocation);

	if(!currentNodeLocation->getRightThread())
		inorderTraverse(currentNodeLocation->getRightPtr(), visit);
	}//end if
}//end inorderTraverse

 /** Pre order Traverse
	@brief recursive preorder Traversal of tree
	@param currentNodeLocation node to traverse
 */
void ThreadedBST::preorderTraverse(Node * currentNodeLocation, void visit(Node*)){
	if (!currentNodeLocation->isEmpty()){
	visit(currentNodeLocation);
	if(!currentNodeLocation->getLeftThread())
		preorderTraverse(currentNodeLocation->getLeftPtr(), visit);

	if(!currentNodeLocation->getRightThread())
		preorderTraverse(currentNodeLocation->getRightPtr(), visit);
	}//end if 
}//end preorderTraverse

 /** Post order Traverse
	@brief recursive postorder Traversal of tree
	@param currentNodeLocation node to traverse
 */
void ThreadedBST::postorderTraverse(Node * currentNodeLocation, void visit(Node*)){
	if (!currentNodeLocation->isEmpty()){
	if(!currentNodeLocation->getLeftThread())
		postorderTraverse(currentNodeLocation->getLeftPtr(), visit);

	if(!currentNodeLocation->getRightThread())
		postorderTraverse(currentNodeLocation->getRightPtr(), visit);
	visit(currentNodeLocation);
	}//end if
}//end postorderTraverse

 /** postorder Deletetion
	@brief helper for clear and destructor
 */
void ThreadedBST::postorderDeletion(Node * currentNode){
		if (currentNode != NULL){

	 if (onlyRoot()){
			destroyNode(currentNode);
			root = NULL;
			return;
	}//end if

	if (!currentNode->getLeftThread()){
		postorderDeletion(currentNode->getLeftPtr());
	}//end if !left
	if (!currentNode->getRightThread()){
		postorderDeletion(currentNode->getRightPtr());
	}//end if !right

	destroyNode(currentNode);
		}//end if

	if (size == 0){
		root = NULL;
		return;
	}//end if 
}//end postorderDeletion

 /** postorder String Deletetion
	@brief helper method for destructor and clear
 */
void ThreadedBST::postorderStringDeletion(Node * currentNode){
	if (currentNode != NULL){
		 if (onlyRoot()){
			destroyNode(currentNode);
			root = NULL;
			return;
		}//end if
	
		if (!currentNode->getLeftThread()){
			postorderStringDeletion(currentNode->getLeftPtr());
		}//end if !left

		if (!currentNode->getRightThread()){
			postorderStringDeletion(currentNode->getRightPtr());
		}//end if !right

		destroyNode(currentNode);
	}
		if (size == 0){
			root = NULL;
			return;
		}//end if

}//end inorderDeletion

 /** Retrieve
	@brief returns whether or not a target number is in the tree
	@param targetInt the number to search for
	@param returnNode pointer to location of select node or prospective position
	@return True if containted in tree, false otherwise; both cases return pointer location
 */
bool ThreadedBST::retrieve(int targetInt, Node*& returnNode){

	if (isEmpty()){
		returnNode = NULL;
		return false;
	}
	else{
	//	walk through the tree
			Node * current = root;
			Node * positionHolder = NULL;

			while (positionHolder == NULL){
				if (current->getInt() == targetInt){
					positionHolder = current;
				}
				else if (targetInt < current->getInt()){
					if (leftCheck(current))
						positionHolder = current;
					else
						current = current->getLeftPtr();
				}
				else{
					if (rightCheck(current))
							positionHolder = current;
					else
						current = current->getRightPtr();
				}//end if
			}//end while
		
			returnNode = positionHolder;
			return (returnNode->getInt() == targetInt);
	}//end if
	return false;
}//end retrieve

Node * ThreadedBST::getRoot(){
	return root;
}//end getRoot

void ThreadedBST::setRoot(Node * newRoot){
	root = newRoot;
}//end setRoot

 /** Retrieve
	@brief returns whether or not a target number is in the tree
	@param targetInt the number to search for
	@param returnNode pointer to location of select node or prospective position
	@return True if containted in tree, false otherwise; both cases return pointer location
 */
bool ThreadedBST::retrieve(string targetString, Node*& returnNode){
	if (isEmpty()){
		returnNode = NULL;
		return false;
	}
	else{
	//	walk through the tree
			Node * current = root;
			Node * positionHolder = NULL;

			while (positionHolder->isEmpty()){
				if (current->getString() == targetString){
					positionHolder = current;
				}
				else if (targetString.compare(current->getString()) < 0){
					if (leftCheck(current))
						positionHolder = current;
					else
						current = current->getLeftPtr();
				}
				else{
					if (rightCheck(current))
							positionHolder = current;
					else
						current = current->getRightPtr();
				}//end if
			}//end while
		
			returnNode = positionHolder;
			return (returnNode->getString() == targetString);
	}//end if	
	return false;
}//end retrieve

/** Insert
	@brief inserts integer number into tree
	@return true if successful, false otherwise
*/
bool ThreadedBST::insert(int intValue){
	
	//create new node with int value
	Node * insertionNode = new Node(intValue);
	setPointersNull(insertionNode);

	int intTarget = insertionNode->getInt();

		//check for empty tree
			if (this->isEmpty()){
				setPointersNull(insertionNode);
				root = insertionNode;
				return true;
			}//end if empty
	
			Node * proximalNode = NULL;
		//	 exists = (look for the node)
			bool exists = retrieve(intTarget, proximalNode);

		if (exists){
			proximalNode->increaseIntFreq();	
			clearNode(insertionNode);
			return true;
		}
		else{
			if( intTarget < proximalNode->getInt()){
				assert(leftCheck(proximalNode));
				
				Node * tempLeftChild = proximalNode->getLeftPtr();
				insertLeftChildHelper(proximalNode, insertionNode, tempLeftChild);
			}
			else{
				assert(rightCheck(proximalNode));
				
				Node * tempRightChild = proximalNode->getRightPtr();	
				insertRightChildHelper(proximalNode, insertionNode, tempRightChild);
			}//end if on right or left
			return true;
		}//end if
	//return failure	
	return false;
}//end insert

bool ThreadedBST::insert(NodeData * newData){
	
	//create new node with int value
	Node * insertionNode = new Node(newData);
	setPointersNull(insertionNode);

	int intTarget = insertionNode->getInt();

		//check for empty tree
			if (this->isEmpty()){
				setPointersNull(insertionNode);
				root = insertionNode;
				return true;
			}//end if empty
	
			Node * proximalNode = NULL;
		//	 exists = (look for the node)
			bool exists = retrieve(intTarget, proximalNode);

		if (exists){
			proximalNode->increaseIntFreq();	
			clearNode(insertionNode);
			return true;
		}
		else{
			if( intTarget < proximalNode->getInt()){
				assert(leftCheck(proximalNode));
				
				Node * tempLeftChild = proximalNode->getLeftPtr();
				insertLeftChildHelper(proximalNode, insertionNode, tempLeftChild);
			}
			else{
				assert(rightCheck(proximalNode));
				
				Node * tempRightChild = proximalNode->getRightPtr();	
				insertRightChildHelper(proximalNode, insertionNode, tempRightChild);
			}//end if on right or left
			return true;
		}//end if
	//return failure	
	return false;
}//end insert


 /** Insert
	@brief inserts string token into tree
	@return true if successful, false otherwise
*/
bool ThreadedBST::insert(string stringValue){

		string stringTarget = stringValue;

		//check for empty tree
			if (isEmpty()){
				Node * insertionNode = new Node(stringValue);
				setPointersNull(insertionNode);
				root = insertionNode;
				return true;
			}//end if empty
	
			Node * proximalNode = NULL;
		//	 exists = (look for the node)
			bool exists = retrieve(stringTarget, proximalNode);

		if (exists){
			proximalNode->increaseStringFreq();
			return true;
		}
		else{
			Node * insertionNode = new Node(stringValue);

			if( stringTarget.compare(proximalNode->getString()) < 0){
				assert(leftCheck(proximalNode));
				
				Node * tempLeftChild = proximalNode->getLeftPtr();
				insertLeftChildHelper(proximalNode, insertionNode, tempLeftChild);
			}
			else{
				assert(rightCheck(proximalNode));
				
				Node * tempRightChild = proximalNode->getRightPtr();
				insertRightChildHelper(proximalNode, insertionNode, tempRightChild);
			}//end if on right or left
			return true;
		}//end if
	//return failure	
	return false;

}//end insert

 

 /** Insert Left Child Helper
	@brief does repetitive wiring
	@oaram targetNode node to insert Left child
	@param insertionNode node inserting as left child
	@param tempLeftNode parent node necessary for threading
*/
void ThreadedBST::insertLeftChildHelper(Node * targetNode, Node * insertionNode,
											Node * tempLeftNode){
	targetNode->setLeftThread(false);
	targetNode->setLeftPtr(insertionNode);
	insertionNode->setLeftPtr(tempLeftNode);
	insertionNode->setLeftThread(true);
	insertionNode->setRightPtr(targetNode);
	insertionNode->setRightThread(true);
	if (tempLeftNode->isEmpty())
		insertionNode->setLeftThread(false);
	size++;
}//end insertLeftChildAssignment

 /** Insert Right Child Helper
	@brief does repetitive wiring
	@oaram targetNode node to insert Left child
	@param insertionNode node inserting as left child
	@param tempRightNode parent node necessary for threading
*/
void ThreadedBST::insertRightChildHelper(Node * targetNode, Node * insertionNode,
											 Node * tempRightNode){
	targetNode->setRightThread(false);
	targetNode->setRightPtr(insertionNode);
	insertionNode->setRightPtr(tempRightNode);
	insertionNode->setRightThread(true);
	insertionNode->setLeftPtr(targetNode);
	insertionNode->setLeftThread(true);
	if (tempRightNode->isEmpty())
		insertionNode->setRightThread(false);
	size++;
}//end insertRightChildAssignment

 /** Insert
	@brief inserts Node into tree
	@param insertionNode node to insert
	@return true if successful, false otherwise
*/
bool ThreadedBST::insert(Node * insertionNode){

	if (insertionNode->hasString()){
		string stringValue = insertionNode->getString();
		
		destroyNode(insertionNode);
		return insert(stringValue);
	} 
	else {
		int integerValue = insertionNode->getInt();

		destroyNode(insertionNode);
		return insert(integerValue);
	}//end if

	destroyNode(insertionNode);
	return false;
}//end insert

 /** Inorder Iterative Traversal
	@brief traverses the tree iteratively utilizing the threads of the tree
 */
void ThreadedBST::iterativeInorderTraverse() {
  
	// empty tree
	if(isEmpty()){
        return;
    }   // end if

    Node* current = getRoot();//->getLeftPtr();

    current = current->findLeftFloor();

    while(current != NULL){

		printFull(current);
        current = current->iterate();
    }   // end while
}//end iterativeInorderTraverse


void ThreadedBST::inorderTRAV(Node* currentNodeLocation, ofstream& outFile, int &counter){
	
	 if (onlyRoot()){
			printDetails(outFile, currentNodeLocation, counter);
		return;
	}
	 else if (currentNodeLocation->isEmpty()){
		return;
	 }//end if
	
	 if(!currentNodeLocation->getLeftThread())
		inorderTRAV(currentNodeLocation->getLeftPtr(), outFile, counter);

		printDetails(outFile, currentNodeLocation, counter);

	if(!currentNodeLocation->getRightThread())
		inorderTRAV(currentNodeLocation->getRightPtr(), outFile, counter);

}//end TRAV

void ThreadedBST::printDetails(ofstream& output, Node * current, int &counter){

	if (current->hasInt()){
		printIntWFreq(current, output);
		counter++;
		newLineCheck(counter, output);
	}
	else{
		printStringWFreq(current, output);
		counter++;
		newLineCheck(counter, output);
	}//end if
}//end chuck

//==================================================Integer Traversals

void ThreadedBST::printIntsInTree(){
	inorderTraverse(getRoot(), printInt);
}

void ThreadedBST::inorderIntTraverse(){
	inorderTraverse(getRoot(), printInt);
}

void ThreadedBST::preorderIntTraverse(){
	preorderTraverse(getRoot(), printInt);
}

void ThreadedBST::postorderIntTraverse(){
	postorderTraverse(getRoot(), printInt);
}

 /** Inorder Traverse
	@brief recursive inorder Traversal of tree
	@param currentNodeLocation node to traverse
 */
void ThreadedBST::printAllIntFreq(){
	inorderTraverse(getRoot(), printIntFreq);
}//end inorderTraverse

//===========================================String Traversals

 /** Inorder Traverse
	@brief recursive inorder Traversal of tree
	@param currentNodeLocation node to traverse
 */
void ThreadedBST::inorderStrTraverse(){
	inorderTraverse(getRoot(), printString);
	/*
	if(!currentNodeLocation->getLeftThread())
		inorderStrTraverse(currentNodeLocation->getLeftPtr(), visit);
		visit(currentNodeLocation);

	if(!currentNodeLocation->getRightThread())
		inorderStrTraverse(currentNodeLocation->getRightPtr(), visit);
*/
}//end inorderTraverse

 /** Pre order Traverse
	@brief recursive preorder Traversal of tree
	@param currentNodeLocation node to traverse
 */
void ThreadedBST::preorderStrTraverse(){
	preorderTraverse(getRoot(), printString);
}//end preorderTraverse

 /** Post order Traverse
	@brief recursive postorder Traversal of tree
	@param currentNodeLocation node to traverse
 */
void ThreadedBST::postorderStrTraverse(){
	postorderTraverse(getRoot(), printString);
}//end postorderTraverse


void ThreadedBST::printAllStringFreq(){
	inorderTraverse(getRoot(), printStringFreq);
}//end printAllStringFreq

void ThreadedBST::printStringsInTree(){
	inorderTraverse(getRoot(), printString);
}//end printStringsInTree

//=================================================IntegerRemove

 /** Parent Finder
	@brief finds node above node to modify
	@param orphanNode node that's missing a parent
	@return parent location or NULL
 */
Node * ThreadedBST::parentFinder(Node *& orphanNode){

	if (orphanNode == root)
		return NULL;

	int orphanData = orphanNode->getInt();
	Node * current = root;

	while ((current->getLeftPtr() != orphanNode) && (current->getRightPtr() != orphanNode)){
		
		if (orphanData < current->getInt())
			current = current->getLeftPtr();
		else 
			current = current->getRightPtr();

	}//end while

	if ((!current->getLeftPtr()->isEmpty()) && current->getLeftPtr()->getInt() == orphanData){
		return current;
	}//end if left equal

	if ((!current->getRightPtr()->isEmpty()) && current->getRightPtr()->getInt() == orphanData){	
		return current;		
	}//end if right equal
	
	return NULL;
}//end parentFinder
	
void ThreadedBST::removeLeftMost(Node * containsLeftNull){
	Node * parent = parentFinder(containsLeftNull);
	Node * transitionNode = containsLeftNull->getRightPtr();
	if (parent == NULL){
		root = transitionNode;
		moveLeft(transitionNode);
	}
	else{
		parent->setLeftPtr(transitionNode);
		if (transitionNode != parent){
			moveLeft(transitionNode);
		}
	}//end if NULL
	transitionNode->setLeftPtr(NULL);
	transitionNode->setLeftThread(false);

	destroyNode(containsLeftNull);
}//end removeLeftMost

void ThreadedBST::removeRightMost(Node * containsRightNull){
	Node * parent = parentFinder(containsRightNull);
	Node * transitionNode = containsRightNull->getLeftPtr();
	if (parent == NULL){
		root = transitionNode;

		moveRight(transitionNode);
	}
	else{
		parent->setRightPtr(transitionNode);
		if (transitionNode != parent){
			moveRight(transitionNode);
		}//end if
	}//end if NULL
	transitionNode->setRightPtr(NULL);
	transitionNode->setRightThread(false);

	destroyNode(containsRightNull);
}//end removeRightMost

/** Removal With Left Child
	@brief removes node with only left child
	@param removalNode node to remove
 */
void ThreadedBST::removeWithLeftChild(Node * removalNode){
	Node * temp = removalNode->getLeftPtr();
	Node * parent = parentFinder(removalNode);

	if (parent == NULL){
		root = temp;

		moveRight(temp);

		temp->setRightPtr(parent);

	}
	else {
		if (parent->getLeftPtr() == removalNode){
			parent->setLeftPtr(temp);

			moveRight(temp);

			temp->setRightPtr(removalNode->getRightPtr());
			assert(temp->getRightThread());
		}
		else{
			
			parent->setRightPtr(temp);
		
			moveLeft(temp);

			temp->setLeftPtr(parent);
			assert(temp->getLeftThread());

			temp = removalNode->getLeftPtr();

			moveRight(temp);
			temp->setRightPtr(removalNode->getRightPtr());
		}//end if on left or right
	}//end if parent NULL

	//delete removalNode;
	destroyNode(removalNode);
}//end removeWithLeftChild
 
 /** Removal with Right Child
	@brief
	@param
 */
void ThreadedBST::removeWithRightChild(Node * removalNode){
	
	Node * temp = removalNode->getRightPtr();
	Node * parent = parentFinder(removalNode);

	if (parent == NULL){
		root = temp;

		moveLeft(temp);
		temp->setLeftPtr(parent);
	}
	else {
		
		if (parent->getLeftPtr() == removalNode){
			
			parent->setLeftPtr(temp);

			moveRight(temp);
			temp->setRightPtr(parent);
			assert(temp->getRightThread());

			//set other side
			temp = removalNode->getRightPtr();

			moveLeft(temp);
			temp->setLeftPtr(removalNode->getLeftPtr());
			assert(temp->getLeftThread());
		}
		else {
			
			parent->setRightPtr(temp);

			moveLeft(temp);
			temp->setLeftPtr(parent);
			assert(temp->getLeftThread());
		}//end if left or right removal
	}//end if parent == NULL

	destroyNode(removalNode);
}//end removeWithRightChild 

 /** Removal with No Children
	@brief 
	@param
 */
void ThreadedBST::removeWithNoChildren(Node * removalNode){

	Node * parent = parentFinder(removalNode);

	if (parent->isEmpty())
		root = NULL;
	else if (parent->getLeftPtr() == removalNode) {
		parent->setLeftPtr(removalNode->getLeftPtr());
		parent->setLeftThread(true);
	}
	else if (parent->getRightPtr() == removalNode){
		parent->setRightPtr(removalNode->getRightPtr());
		parent->setRightThread(true);
	}//end if null, left, or right

	destroyNode(removalNode);
}//end removeWithNoChildren

 /** Removal With Two Children
	@brief 
	@param
 */
void ThreadedBST::removeWithTwoChildren(Node * removalNode){

	Node * transitionNode = removalNode->getRightPtr();
	moveLeft(transitionNode);

	removalNode->setItem(transitionNode->getInt());
	removalNode->setIntFrequency(transitionNode->getIntFrequency());
	removalNode->setItem(transitionNode->getString());
	removalNode->setIntFrequency(transitionNode->getStringFrequency());
	transitionNode->setIntFrequency(0);
	transitionNode->setStringFrequency(0);
	
	deleteNode(transitionNode);

}//end removeWithTwoChildren

 /** Delete Int
 */
void ThreadedBST::deleteInt(int removalKey){
	
	Node * prospectRemovalNode = NULL;

	bool found = retrieve(removalKey, prospectRemovalNode);

	if (found){
		deleteNode(prospectRemovalNode);
		//prospectRemovalNode = NULL;
	}
	else{
		//cout << removalKey << NOT_FOUND << endl;
	}//end if

}//end deleteInt

 /** Delete Node
	@brief deletes a specified Noded
	@param removalNode the node to delete
 */
void ThreadedBST::deleteNode(Node * removalNode){
	
	bool hasLeftChild = (removalNode->getLeftPtr() != NULL) && (!removalNode->getLeftThread());
	bool hasRightChild = (removalNode->getRightPtr() != NULL) && (!removalNode->getRightThread());

	if (removalNode->getRightPtr() == NULL){
		removeRightMost(removalNode);
	}
	else if (removalNode->getLeftPtr() == NULL){
		removeLeftMost(removalNode);
	}
	else if (hasLeftChild && hasRightChild)	{	//This guy is causing problems
		removeWithTwoChildren(removalNode);
	}
	else if (hasLeftChild){
		removeWithLeftChild(removalNode);
	}
	else if (hasRightChild){
		removeWithRightChild(removalNode);
	} 
	else {//if (removalNode->isLeaf()) {
		removeWithNoChildren(removalNode);
	} 

	//}//end if
	//else{
	//	cout << "This is Not Supposed to Happen!!!" << endl;
	//}

}//end deleteNode

//===================StringRemove

 /** Parent Finder
 */
Node * ThreadedBST::stringParentFinder(Node *& orphanNode){
	//removing root
	if (orphanNode == root)
		return NULL;

	string orphanData = orphanNode->getString();
	Node * current = root;

	while ((current->getLeftPtr() != orphanNode) && (current->getRightPtr() != orphanNode)){
		
		if (orphanData.compare(current->getString()) < 0)
			current = current->getLeftPtr();
		else 
			current = current->getRightPtr();

	}//end while

	if (current->getLeftPtr()->getString() == orphanData){
		if (orphanData == current->getString()){
			//this needs to be fixed in order to continue 2/27 5:30PM
			//Node * tempDelete = current->getLeftPtr();
			//current->setLeftPtr(tempDelete->getLeftPtr());
			//tempDelete->setLeftPtr(NULL);
			//tempDelete->setRightPtr(NULL);
			//tempDelete->setItem(-1);
			//tempDelete->setIntFrequency(0);
			//delete tempDelete;
			//tempDelete = NULL;
		}//end if
			
	//	cout << "On the Left" << endl;
		return current;
	}//end if left equal

	if (current->getRightPtr()->getString() == orphanData){
		if (orphanData == current->getString()){
			//this needs to be fixed in order to continue 2/27 5:30PM
			//Node * tempDelete = current->getRightPtr();
			//current->setRightPtr(tempDelete->getRightPtr());
			//tempDelete->setLeftPtr(NULL);
			//tempDelete->setRightPtr(NULL);
			//tempDelete->setItem(-1);
			//tempDelete->setIntFrequency(0);
			//delete tempDelete;
			//tempDelete = NULL;
		}//end if

		//cout << "On the Right" << endl;
		return current;		
	}//end if right equal
	 return NULL;
}//end parentFinder

/** Removal With Left Child
	@brief
	@param
 */
void ThreadedBST::stringRemoveWithLeftChild(Node * removalNode){
	Node * temp = removalNode->getLeftPtr();
	Node * parent = stringParentFinder(removalNode);

	if (parent == NULL){
		root = temp;

		moveRight(temp);
		temp->setRightPtr(parent);

	}
	else {
		if (parent->getLeftPtr() == removalNode){
			parent->setLeftPtr(temp);

			moveRight(temp);
			temp->setRightPtr(removalNode->getRightPtr());
			assert(temp->getRightThread());
		}
		else{
			
			parent->setRightPtr(temp);

			moveLeft(temp);
			temp->setLeftPtr(parent);
			assert(temp->getLeftThread());

			temp = removalNode->getLeftPtr();

			moveRight(temp);
			temp->setRightPtr(removalNode->getRightPtr());
		}//end if on left or right
	}//end if parent NULL

	destroyNode(removalNode);

}//end removeWithLeftChild
 
 /** Removal with Right Child
	@brief
	@param
 */
void ThreadedBST::stringRemoveWithRightChild(Node * removalNode){
	
	Node * temp = removalNode->getRightPtr();
	Node * parent = stringParentFinder(removalNode);

	if (parent == NULL){
		root = temp;

	moveLeft(temp);
		temp->setLeftPtr(parent);
	}
	else {
		
		if (parent->getLeftPtr() == removalNode){
			
			parent->setLeftPtr(temp);
			moveRight(temp);
			temp->setRightPtr(parent);
			assert(temp->getRightThread());

			//set other side
			temp = removalNode->getRightPtr();

			moveLeft(temp);
			temp->setLeftPtr(removalNode->getLeftPtr());
			assert(temp->getLeftThread());
		}
		else {
			
			parent->setRightPtr(temp);

			moveLeft(temp);
			temp->setLeftPtr(parent);
			assert(temp->getLeftThread());
		}//end if left or right removal
	}//end if parent == NULL

	destroyNode(removalNode);

}//end removeWithRightChild 

 /** Removal with No Children
	@brief 
	@param
 */
void ThreadedBST::stringRemoveWithNoChildren(Node * removalNode){

	Node * parent = stringParentFinder(removalNode);

	if (parent == NULL)
		root = NULL;
	else if (parent->getLeftPtr() == removalNode) {
		parent->setLeftPtr(removalNode->getLeftPtr());
		parent->setLeftThread(true);
	}
	else if (parent->getRightPtr() == removalNode){
		parent->setRightPtr(removalNode->getRightPtr());
		parent->setRightThread(true);
	}//end if null, left, or right

	//delete removalNode;
	//removalNode = NULL;
	destroyNode(removalNode);
}//end removeWithNoChildren

 /** Removal With Two Children
	@brief 
	@param
 */
void ThreadedBST::stringRemoveWithTwoChildren(Node * removalNode){

	Node * transitionNode = removalNode->getRightPtr();

	moveLeft(transitionNode);

	removalNode->setItem(transitionNode->getString());
	removalNode->setIntFrequency(transitionNode->getStringFrequency());
	transitionNode->setIntFrequency(0);
	stringDeleteNode(transitionNode);

}//end removeWithTwoChildren

 /** Delete String
 */
void ThreadedBST::deleteString(string removalKey){
	
	Node * prospectRemovalNode = NULL;

	bool found = retrieve(removalKey, prospectRemovalNode);

	if (found){
		stringDeleteNode(prospectRemovalNode);
	}
	else{
		//cout << removalKey << NOT_FOUND << endl;
	}
}//end deleteString

 /** Delete Node
	@brief deletes a specified Noded
	@param removalNode the node to delete
 */
void ThreadedBST::stringDeleteNode(Node * removalNode){
	
	if (removalNode->hasOnlyLeftChild()){
		stringRemoveWithLeftChild(removalNode);
	}
	else if (removalNode->hasOnlyRightChild()){
		stringRemoveWithRightChild(removalNode);
	} 
	else if (removalNode->isLeaf()) {
		stringRemoveWithNoChildren(removalNode);
	} 
	else {
		stringRemoveWithTwoChildren(removalNode);
	}//end if

}//end deleteNode

 /** Transfer To List
 */
void ThreadedBST::transferToList(Node * currentNodeLocation, List &insertionList){

	if (isEmpty()){
		return;
	}
	else if (onlyRoot()){
		insertionList.insertStrFreqs(getRoot());
		return;
	}//end if only root or empty
	else if (currentNodeLocation->isEmpty()){
		return;
	}

	if(!currentNodeLocation->getLeftThread())
		transferToList(currentNodeLocation->getLeftPtr(), insertionList);
	
		insertionList.insertFreqs(currentNodeLocation);

	if(!currentNodeLocation->getRightThread())
		transferToList(currentNodeLocation->getRightPtr(), insertionList);

}//transferToList

 /** Transfer To List
 */
void ThreadedBST::transferStringsToList(Node * currentNodeLocation, List &insertionList){
		
	if (isEmpty()){
		return;
	}
	else if (onlyRoot()){
		insertionList.insertStrFreqs(getRoot());
		return;
	}//end if only root or empty
	else if (currentNodeLocation->isEmpty()){
		return;
	}

	if(!currentNodeLocation->getLeftThread())
		transferStringsToList(currentNodeLocation->getLeftPtr(), insertionList);
	
		insertionList.insertStrFreqs(currentNodeLocation);

	if(!currentNodeLocation->getRightThread())
		transferStringsToList(currentNodeLocation->getRightPtr(), insertionList);

}//transferToList
