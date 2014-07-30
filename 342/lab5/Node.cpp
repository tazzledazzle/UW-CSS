
  /**=================================
	@file Node.cpp
	@author Terence Schumacher
	@author Dominic Badzik
	
	@version 1.6
*===================================*/

#include "Node.h"
#define NODE_DESCRIPT  "Node Description: " 
#define INT_MSSG "Integer Data Item--"
#define STR_MSSG "String Data Item--"
#define INT_FREQ_MSSG "Integer Frequency--"
#define STR_FREQ_MSSG "String Frequency--"

using namespace std;

//====constructors

/** Default Constructor
	@brief standard creation of Node
*/
Node::Node(): item(NULL), leftChildPtr(NULL), rightChildPtr(NULL), leftThread(false), rightThread(false)
{
	
}//end default constructor

/** Item Constructor
	@brief constructor created with integer in NodeData
	@param newInteger value to construct  Node with
*/
Node::Node(int newInteger) : leftChildPtr(NULL), rightChildPtr(NULL), leftThread(false), rightThread(false)
{
	NodeData * newData = new NodeData(newInteger);
	this->item = newData;
}//end Constructor

/** Item Constructor
	@brief constructor created with string in NodeData
	@param stringItem value to construct  Node with
*/
Node::Node(string stringItem): leftChildPtr(NULL), rightChildPtr(NULL), leftThread(false), rightThread(false)
{
	NodeData * newData = new NodeData(stringItem);
	this->item = newData;
}//end constructor

/** Item Constructor
	@brief constructor created with NodeData in NodeData
	@param newItem value to construct  Node with
*/
Node::Node(NodeData * newItem): leftChildPtr(NULL), rightChildPtr(NULL), leftThread(false), rightThread(false)
{
	NodeData * newNodeData = new NodeData(newItem);
	this->item = newNodeData;
}//end constructor
	
 /** Full Constructor
	@brief all parameters of Node passed into constructor
	@param stringItem value to construct  Node with
	@param left child on the left
	@param right child on the right
	@param leftT state of left thread
	@param rightT state of right thread
*/
Node::Node(string stringItem, Node * left, Node * right, bool leftT, bool rightT){
	NodeData * newData = new NodeData(stringItem);
	item = newData;
	
	leftChildPtr = left;
	rightChildPtr = right;

	leftThread = leftT;
	rightThread = rightT;
}//end constructor
	
/** Full Constructor
	@brief all parameters of Node passed into constructor
	@param newItem value to construct  Node with
	@param left child on the left
	@param right child on the right
	@param leftT state of left thread
	@param rightT state of right thread
*/
Node::Node(int newItem, Node * left, Node * right, bool leftT, bool rightT){
	
	NodeData * newData = new NodeData(newItem);
	this->item = newData;
		
	leftChildPtr = left;
	rightChildPtr = right;
		
	leftThread = leftT;
	rightThread = rightT;
}//end fullConstructor

/** Copy Constructor
	@brief copies right hand node parameters to left hand node parameters
	@param copyNode node to copy
*/
Node::Node( Node *& copyNode){
	NodeData * newData = new NodeData(copyNode->getData());
	this->item = newData;

	setLeftPtr(copyNode->getLeftPtr());
	setRightPtr(copyNode->getRightPtr());

	setLeftThread(copyNode->getLeftThread());
	setRightThread(copyNode->getRightThread());
}//end Copy Constructor

 /** Destructor
	@brief manages dynamically allocated memory
	@pre Node must be created dynamically

 */
Node::~Node(){	
	this->clear();
	
	delete item;
	item = NULL;
	leftChildPtr = NULL;
	rightChildPtr = NULL;

}//end destructor

//================================================getters

/** Get Item
	@pre must have data
	@return value contained in the Data struct
*/
int Node::getInt(){
	if(hasData())
		return item->intValue.item;
	else
		return -1;
}//end getItem

/** Get String
	@pre must have data
	@return string contained in the Data struct
*/
string Node::getString(){
	if (hasData())
		return item->stringValue.item;
	else
		return "";
}//end getString

 /** Get Data
	@return pointer to the data Item
 */
NodeData* Node::getData(){
	return item;
}//end getData()

/** Get Left Pointer (Child)
	@return location of left child
*/
Node * Node::getLeftPtr(){
return leftChildPtr;
}//end getLeftPtr

/** Get Right Pointer (Child)
	@return location of right child
*/
Node * Node::getRightPtr(){
return rightChildPtr;
}//end getRightPtr

/** Get Left Thread
	@return true if left threaded, false otherwise
*/
bool Node::getLeftThread(){
return leftThread;
}//end getLeftThread

/** Get Right Thread
	@return true if right threaded, false otherwise
*/
bool Node::getRightThread(){
return rightThread;
}//end getRightThread

/** Get Frequency
	@pre must have data
	@return frequency count of item in the Data struct
*/
int Node::getIntFrequency(){
	if (hasData())
		return item->intValue.frequency;
	else
		return 0;
}//end getFrequency

	/** Get String Frequency
	@pre must have data
	@return frequency count of item in the Data struct
*/
int Node::getStringFrequency() {
	if (hasData())
		return item->stringValue.frequency;
	else
		return 0;
}//end getStringFrequency

//=======================================================setters

/** Print Node
	@brief prints node info for test data
	@param printNode node to obtain information to print
*/
void Node::printNode(Node * printNode){

	cout <<NODE_DESCRIPT << endl << endl;
	cout << INT_MSSG << printNode->getInt() << endl;
	cout << INT_FREQ_MSSG << printNode->getIntFrequency()<< endl;
	cout << STR_MSSG << printNode->getString() << endl;
	cout << STR_FREQ_MSSG << printNode->getStringFrequency()<< endl;
	cout << "Left Child--" << printNode->getLeftPtr() << endl;
	cout << "Right Child--" << printNode->getRightPtr() << endl;
	cout << "Left Thread--" << printNode->getLeftThread() << endl;
	cout << "Right Thread--" << printNode->getRightThread() << endl;

}//end printNode


/** Clear
	@brief clears the node
	@pre node must have data
*/
void Node::clear(){
	if (hasData()){
		item->intValue.item = -1;
		item->intValue.frequency = 0;
		item->stringValue.item = "";
		item->stringValue.frequency = 0;
		delete item;
		item = NULL;
	}
	else
	{
		leftChildPtr = NULL;
		rightChildPtr = NULL;
		leftThread = false;
		rightThread = false;
	}
}//end clear

/** Increase Integer Frequency
	@brief increases frequency
*/
void Node::increaseIntFreq(){
	item->intValue.frequency++;
}//end increaseFreq
	
/** Decrease Integer Frequency
	@brief decreases frequency
*/
void Node::decreaseIntFreq(){
	item->intValue.frequency--;
}//end decreaseFreq
	
	/** Increase String Frequency
	@brief increases frequency
*/
void Node::increaseStringFreq(){
	item->stringValue.frequency++;
}//end increaseFreq
	
/** Decrease String Frequency
	@brief decreases frequency
*/
void Node::decreaseStringFreq(){
	item->stringValue.frequency--;
}//end decreaseFreq

/** Set Item
	@param newItem value to set
	@post frequency is reset to one
*/
void Node::setItem(int newItem){
	if (hasData()){
		item->intValue.item = newItem;
		item->intValue.frequency = 1;
	}
	else{
		NodeData * newData = new NodeData(newItem);
		item = newData;
	}//end if

	assert(item->intValue.item == newItem);
	assert(item->intValue.frequency == 1);
}//end setItem

 /** Set Item
	@param newString value to set
	@post frequency is reset to one
 */
void Node::setItem(string newString){
	if (hasData()){
		item->stringValue.item = newString;
		item->stringValue.frequency = 1;
	}
	else {
		NodeData * newData = new NodeData(newString);
		item = newData;
	}//end if
		
	assert(item->stringValue.item == newString);
	assert(item->stringValue.frequency == 1);
}//end setItem

 /** Set Item
	@param newData value to set
	@post data Item passed in is deleted
 */
void Node::setItem(NodeData * newData){
	NodeData * createData = new NodeData(newData);
	item = createData;
	
	assert(newData->intValue.item == item->intValue.item);
	assert(newData->intValue.frequency == item->intValue.frequency);

	assert(newData->stringValue.item == item->stringValue.item);
	assert(newData->stringValue.frequency == item->stringValue.frequency);
}//end setData

/** Set Left Pointer (Child)
	@param newLeft new left child
*/
void Node::setLeftPtr(Node * newLeft){
	leftChildPtr = newLeft;
}//end setLeftPtr

/** Set Right Pointer (Child)
	@param newRight new right child
*/
void Node::setRightPtr(Node * newRight){
	rightChildPtr = newRight;
}//end setRightPtr
	
/** Set Left Thread
	@param conclusion sets whether threaded or not
*/
void Node::setLeftThread(bool conclusion){
	leftThread = conclusion;
}//end setLeftThread

/** Set Right Thread
	@param conclusions sets whether threaded or not
*/
void Node::setRightThread(bool conclusion){
	rightThread = conclusion;
}//end setRightThread

/** Set Frequency
	@param newFreq update the frequency
*/
void Node::setIntFrequency(int newFreq){
	item->intValue.frequency = newFreq;
}//end setFrequency

/** Set String Frequency
	@param newFrequency update to the frequency
	*/
void Node::setStringFrequency(int newFrequency){
	item->stringValue.frequency = newFrequency;
}//end setStringFrequency

//=========================================================operators
	
/** = Operator
	@brief assignment operator for nodes
	@param rightHandSide the node to set this to
	@return copy of rightHandSide
*/
Node* Node::operator=( Node& rightHandSide) {
	this->clear();

	this->setItem(rightHandSide.getData());
	this->setLeftPtr(rightHandSide.getLeftPtr());
	this->setRightPtr(rightHandSide.getRightPtr());
	this->setLeftThread(rightHandSide.getLeftThread());
	this->setRightThread(rightHandSide.getRightThread());

	/*	
	this->dataItem.item = rightHandSide.getItem();
	this->dataItem.frequency = rightHandSide.getFrequency();
	this->leftChildPtr = rightHandSide.getLeftPtr();
	this->rightChildPtr = rightHandSide.getRightPtr();
	this->leftThread = rightHandSide.getLeftThread();
	this->rightThread = rightHandSide.getRightThread();
*/
	return this;
}//end operator=

/** < operator
	@brief comparison of less than
	@return true if less than, false otherwise
*/
bool Node::operator<(Node& rightHandSide){
return (this->getInt() < rightHandSide.getInt());
}//end operator<

/** > operator
	@brief comparison of greater than
	@return true if greater than, false otherwise
*/
bool Node::operator>(Node& rightHandSide){
return (this->getInt() > rightHandSide.getInt());
}//end operator>

//====comparisons
/** Is Empty?
*/
bool Node::isEmpty(){
	return (this == NULL);
}//end isEmpty

/** Is Leaf
	@return true of right and left ptr null, false otherwise
*/
bool Node::isLeaf(){
	return ((getLeftThread()) && (getRightThread()));
}//end isLeaf

/** Has Only Left Child
	@return true if right child null and left child not, false otherwise
*/
bool Node::hasOnlyLeftChild(){
	return ((leftChildPtr != NULL) && (getRightThread()) && (!getLeftThread()));
}//end hasOnlyLeftChild

/** Has Only Right Child
	@return true if left child null and right child not, false otherwise
*/
bool Node::hasOnlyRightChild(){
	return ((rightChildPtr != NULL) && (getLeftThread()) && (!getRightThread()));
}//end hasOnlyRightChild

bool Node::hasNoChildren(){
	return ((getRightThread()|| getRightPtr()->isEmpty())&&(getLeftThread() || getLeftPtr()->isEmpty()));
} //hasNoChildren

bool Node::hasTwoChildren() {

		//return (!hasOnlyRightChild()) && (!hasOnlyLeftChild());
	return ((getRightPtr() != NULL && !getRightThread()) && (getLeftPtr() != NULL && !getRightThread()));
}//end hasTwoChildren
	
/** Has Data
	@return true if data present, false otherwise
*/
bool Node::hasData(){
	return (item != NULL);
}//end hasData

	/** Has String
	@brief checks to see if there's a string in the Node
	@return true if string present, false otherwise
	*/
bool Node::hasString(){
	if (isEmpty()){
		return false;
	}//end if 
	else
	return ((item->stringValue.frequency != 0) && (item->stringValue.item != ""));
}//end hasString
	
	/** Has Int
	@brief checks to see if there's an integer in the Node
	@return true if integer present, false otherwise
	*/
bool Node::hasInt(){
	if (isEmpty()){
		return false;
	}//end if
	else
	return ((item->intValue.frequency != 0) && (item->intValue.item != -1));
}//end hasString

void Node::checkReturn(int countReturn, ostream& output){
//write this man!!!

}//end checkReturn

 /** Find Left Floor
 */
Node * Node::findLeftFloor(){
	
	Node * walker = this;
	Node * temp = this;
	if (isEmpty())
		return walker;

	while ((walker->getLeftPtr() != temp )&&
		  ( walker->getLeftPtr() != NULL) && (!walker->getLeftThread())){
		walker = walker->getLeftPtr();
	}//end while
	
	return walker;
}//end findLeftFloor

 /** Iterate
 */
Node * Node::iterate(){
	
	Node * iteratorNode = this;

	if (iteratorNode->getRightThread()){
		iteratorNode = iteratorNode->getRightPtr();
	}
	else{
		iteratorNode = iteratorNode->getRightPtr()->findLeftFloor();
	}
	return iteratorNode;
}//end iterate

