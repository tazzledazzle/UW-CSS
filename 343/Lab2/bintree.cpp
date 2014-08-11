
/*===========================================* 
	@author		Terence Schumacher
	@file		bintree.cpp
	@version	2.0
*===========================================*/

#include "bintree.h"
#include <cassert>
 //---------------------------------------------------------------------------
 // BinTree Class: Contains all declarations of functions and data members
 //				   needed to create, modify, compare and delete a BST. 
 // --Implementation
 //		** Private structure holding pointer to data and left/right children
 //		** functions transferring data from tree to array and array to tree
 // --Assumptions
 //		**User will implement their own NodeData Class
 //		**NodeData class must have proper comparison operators
 //		**NodeData class must also have copy constructor and object member 
 //		  named data
 //---------------------------------------------------------------------------

 //---------------------------------------------------------------------------
 // BinTree()
 // constructor : creates and empty tree with root at NULL.
 // 
BinTree::BinTree() : root(NULL) {

}//end constructor

 //---------------------------------------------------------------------------
 // BinTree(const BinTree&)
 // Copy Constructor: Takes a reference to an existing tree and copies all 
 //					  Nodes within that tree to created tree (deep) copy
 // @param rightHandSide tree object copying from
 // 
BinTree::BinTree(const BinTree &rightHandSide){
	copyTree(rightHandSide.root, root);
}//end copy constructor

 //---------------------------------------------------------------------------
 // copyTree(Node*, Node*&)
 // copy Tree: recursively builds tree by modifying existing node pointers
 // @param rightCurrent Node deep copying from
 // @param leftCurrent Node deep copying to
 //
void BinTree::copyTree(Node * rightCurrent, Node *& leftCurrent ){
	//if current not null
	if (rightCurrent != NULL){
		leftCurrent = new Node(); // create new insertion
		NodeData *newData = new NodeData(*rightCurrent->data);
		leftCurrent->data = newData;
			
	//move left
		copyTree(rightCurrent->left, leftCurrent->left);
	//move right
		copyTree(rightCurrent->right, leftCurrent->right);
	}//end if
	else{
		leftCurrent = NULL;
	}//end if
}//end copyTree

 //---------------------------------------------------------------------------
 // ~BinTree()
 // Destructor: cleans up memory allocated for binary trees by calling the 
 //				make empty function.
 // 
BinTree::~BinTree(){
	makeEmpty();
}//end destructor

 //---------------------------------------------------------------------------
 // isEmpty()
 // is Empty: Returns whether the BST is empty
 // @return true if root equals NULL, false otherwise
 // 
bool BinTree::isEmpty() const{
	return (root == NULL);
}//end isEmpty	// true if tree is empty, false otherwise

 //---------------------------------------------------------------------------
 // makeEmpty()
 // make Empty: Makes the tree empty by calling destroy tree so isEmpty will
 //				returns true
 // 
void BinTree::makeEmpty(){
	Node * current = root;
	if (current != NULL){   // if root not null
		destroyTree(current);
	}//end if 

	assert(isEmpty());
}//end makeEmpty		// makes the tree empty so isEmpty returns true

 //---------------------------------------------------------------------------
 // destroyTree(Node*)
 // destroy Tree: calling this method destroys all nodes within a given tree. 
 //					It is a helper method that is private because of its re-
 //					cursive work.
 // @param current node utilized during postorder deletion
 //
void BinTree::destroyTree(Node * current){
	if (current != NULL){
		destroyTree(current->left);
		destroyTree(current->right);

		//delete memory properly
		delete current->data;
		current->data = NULL;
		delete current;
		current = NULL;
	}//end if

	root = NULL;

}//end destroyTree

 //---------------------------------------------------------------------------
 // operator=(const BinTree&)
 // = operator: Make LHS the same as RHS by a Deep copy of RHS
 // @param rightHandSide tree copying from
 // 
BinTree& BinTree::operator=(const BinTree &rightHandSide){
	if (*this != rightHandSide){
		// make this empty
		destroyTree(root);
		copyTree(rightHandSide.root, root);
	}//end if

	return *this;

}//end operator=	

 //---------------------------------------------------------------------------
 // operator==(const BinTree&)
 // == operator: tests whether two trees are exactly the same by comparing 
 //				their NodeData on each move within a traversal of both trees
 // @param rightHandSide the tree object that is compared with the this object
 // @return true if both trees are the the same, false otherwise
 //
bool BinTree::operator==(const BinTree &rightHandSide) const{
	Node * leftRoot = this->root, * rightRoot = rightHandSide.root;
	//check size
	if (leftRoot == NULL && rightRoot == NULL)
		return true;
	else
		return checkEquality(leftRoot, rightRoot);
}//end operator==

 //---------------------------------------------------------------------------
 // checkEquality(Node*, Node*) const
 // check Equality: recursive helper method called by equality operator to 
 //					check whether two nodes are equal and then move on to the
 //					successive children 
 // @param leftSide a node within the tree on the left side of comparison
 // @param rightSide a node within the tree on the right side of comparison
 // @return true if NodeData contents are the same, false otherwise
 // 
bool BinTree::checkEquality(Node * leftSide, Node * rightSide) const {

	if ((leftSide != NULL && rightSide != NULL) && 
		(*leftSide->data == *rightSide->data))
		return true;

	if ((leftSide == NULL) || (rightSide == NULL))
		return false;

	return ((*leftSide->data == *rightSide->data) &&
		checkEquality(leftSide->left, rightSide->left) &&
		checkEquality(leftSide->right, rightSide->right));
}//end checkEquality

 //---------------------------------------------------------------------------
 // getNumberOfNodes(Node*) const
 // Get Number Of Nodes: returns the number of nodes within a tree.
 //			*Note : this was not required for Lab 2, I just thought that I 
 //					would implement it 
 // @param current Node passed in to initiate count from
 // @return number of nodes within the tree, 0 if empty
 // 
int BinTree::getNumberOfNodes(Node * current) const {
	if (current == NULL)
		return 0;
	else
		return 1 + getNumberOfNodes(current->left) + 
					getNumberOfNodes(current->right);
}//end getNumberOfNodes

 //---------------------------------------------------------------------------
 // operator!=(const BinTree&)
 // != operator: inverse of equality operator
 // @param rightHandSide tree compared to the this object
 // @return true if both trees are not the same, false otherwise
 // 
bool BinTree::operator!=(const BinTree &rightHandSide) const{
	return !(*this == rightHandSide);
}//end operator!=

 //---------------------------------------------------------------------------
 // insert(NodeData*)
 // insert: Inserts a new Node into Binary tree, with data ptr pointed to the
 //			newDataItem. Returns whether insertion of node was successful or 
 //			not.
 // @param newDataItem NodeData item inserted into the tree
 // 
bool BinTree::insert(NodeData * newDataItem){
	// get the root
	Node * current = root, * previous = NULL;
	NodeData * returnData;
	//retrieve aka traverse to specific insertion point
	bool exists = retrieve(*newDataItem, returnData);

	if (exists){
		assert(*returnData == *newDataItem);

		return false;
	} 
	else {    //we need to insert the item

		Node * newNode = new Node();
		newNode->data = newDataItem;
		newDataItem = NULL; //detatch
		
		if (isEmpty()){
			root = newNode;
			return true;
		}//end if empty tree

		while (current != NULL){
			if (*newNode->data < *current->data){
				previous = current;
				current = current->left;
			} 
			else {   //greater than
				previous = current;
				current = current->right;
			}//end if
		}//end while

		if ((*newNode->data < *previous->data) ){
			previous->left = newNode;
			newNode->left = current;
			newNode->right = current;
			
			assert((newNode->left == NULL) && (newNode->right == NULL));
			return true;
		} 
		else {
			previous->right = newNode;
			newNode->left = current;
			newNode->right = current;

			assert((newNode->left == NULL) && (newNode->right == NULL));
			return true;
		}//end if prev == NULL
	
	}//end if exists
	
	return false;	//if for some reason you get here, fail
}//end	insert	

 //---------------------------------------------------------------------------
 // retrieve(const NodeData&, NodeData*&) const
 // retrieve: Returns true if comparisonKey is found in the Binary Search Tree
 //			 and sets returnData pointing to the location it was found at. Uses
 //			 retrieveHelper as a recursive function.
 // @param comparisonKey NodeData Item searching for
 // @param returnData If comparisonKey found, fill with pointer to said loca-
 //					  tion
 //	@return true if returnData != NULL, false if NULL
 // 
bool BinTree::retrieve(const NodeData &comparisonKey, NodeData *& returnData)
						const{
	Node * current = root;

	if (current != NULL){
		retrievalHelper(current, comparisonKey, returnData);
	}
	else //empty
		return false;

	if (returnData != NULL){
		assert(*returnData == comparisonKey);

		return true;
	}
	else
		return false;

}//end retrieve

 //---------------------------------------------------------------------------
 // retrievalHelper(Node*, const NodeData&, NodeData*&) const
 // retrievalHelper: searches a tree inorder privately. this method helps re-
 //					 trieval method above, returns NULL in returnData if not
 //					 found, or returns the location of the NodeData.
 // @param current  Node passed in from prospective tree
 // @param comparisonKey The value to search for
 // @param returnData containter for either returning Null or the the location
 //					  of the found data
 //
void BinTree::retrievalHelper(Node * current, const NodeData & comparisonKey,
							  NodeData *& returnData) const {
	
	if (current == NULL){
		returnData = NULL;
	}
	else if (*current->data == comparisonKey) {   //set return data
		returnData = current->data;
	} 
	else if (comparisonKey < *current->data) {
		retrievalHelper(current->left, comparisonKey, returnData);
	}
	else //move right
	{
		retrievalHelper(current->right, comparisonKey, returnData);
	}//end if
	
}//end retrievalHelper

 //---------------------------------------------------------------------------
 // getDepth(const NodeData&) const
 // get Depth: Returns an integer value that represents the depth of the data-
 //				Item passed into the comparsionKey parameter.
 // @param comparisonKey Item finding the depth for
 //	@return number represented by how deep the Node containing comparisonKey 
 //				 is, otherwise return 0 if comparisonKey not found.
 // 
int BinTree::getDepth(const NodeData &comparisonKey) const{
	Node * current = root;
	if (current == NULL)
		return 0;
	NodeData * returnData;
	bool found = retrieve(comparisonKey, returnData);
	if (found){
		return getDepthHelper(current, comparisonKey);
	}
	else {
		return 0;
	}//end if found 
}//end getHeight

 //---------------------------------------------------------------------------
 // getDepthHelper(Node *, NodeData &)
 // Get Depth Helper : Helper method used by get depth to call recursively 
 //						privately. 
 // @param current	current node helper method located at
 //	@param comparisonKey value at which the method started at
 // @return Number of nodes inside of the tree, 0 if not found
 // 
int BinTree::getDepthHelper(Node * current, const NodeData & comparisonKey)
				const {
	if (current != NULL){
		if (comparisonKey == *current->data){
			return 1;
		}
		else if (comparisonKey < *current->data){
			return 1 + getDepthHelper(current->left, comparisonKey);
		} 
		else {
			return 1 + getDepthHelper(current->right, comparisonKey);
		}//end if
	}//end if not null
	if (current == NULL)
		return 0;
	return 0;
}//end getDepthHelper

 //--------------------------------------------------------------------------- 
 // displaySideways 
 // Displays a binary tree as though you are viewing it from the side;
 // hard coded displaying to standard output.
void BinTree::displaySideways() const {
   sideways(root, 0);
}//end displaySideways

 //---------------------------------------------------------------------------
 // sideways(Node*, int)
 // sideways : helper method implemented by displaySideways to recursively out
 //				put correctly
 // @param current current Node location 
 // @param level integer representing the level at which print will occur
 // 
void BinTree::sideways(Node* current, int level) const {
   if (current != NULL) {
      level++;
      sideways(current->right, level);

      // indent for readability, 4 spaces per depth level 
      for(int i = level; i >= 0; i--) {
          cout << "    ";
      }

      cout << *current->data << endl;        // display information of object
      sideways(current->left, level);
   }
}//end sideways

 //---------------------------------------------------------------------------
 // bstreeToArray(NodeData* [])
 // BSTree to Array: A routine fills an array of NodeData* by using an inorder
 //					 traversal of the tree. It leaves the tree empty by call-
 //					 ing destroyTree. 
 // @param binaryTreeArray NodeData array that will hold the contents of the 
 //							tree
 // 
void BinTree::bstreeToArray(NodeData* binaryTreeArray[]){
	int index = 0;
	bstreeToArrayHelper(this->root, binaryTreeArray, index);
	destroyTree(this->root);
} //Puts tree into array of NodeData*

 //---------------------------------------------------------------------------
 // toArrayFiller(Node*, NodeData *, int& )
 // To Array Filler: Helper method implemented in bstreeToArray to recursively
 //					 fill the array inorder.
 // @param current current Node location 
 // @param binaryTreeArray the array that holds the BST NodeData after 
 //							transfer
 // @param index the index of insertion into the BST NodeData array
 // 
void BinTree::bstreeToArrayHelper(Node * current, NodeData* binaryTreeArray[],
							int& index){
	if (current != NULL){
		bstreeToArrayHelper(current->left, binaryTreeArray, index);
			binaryTreeArray[index] = current->data;
			current->data = NULL;	//detach data
			index++;
		bstreeToArrayHelper(current->right, binaryTreeArray, index);
	}//end if
}//end toArrayFiller

 //---------------------------------------------------------------------------
 // arrayToBSTree(NodeData* [])
 // array To Binary Search Tree: A method that builds a binary Tree from a 
 //								sorted array of NodeData*, leaving the array
 //								filled with NULLs.
 // @param sortedArray	array to pull NodeData* information from
 // 
void BinTree::arrayToBSTree(NodeData* sortedArray[]){
	int high = 0;
	int low = 0;
	for (int i = 0; i < 20; i++){
		if (sortedArray[i] != NULL)
			high++;
		else
			;		//nothing to be done	
	}
	
	if (isEmpty()){
	arrayToBSTreeHelper(this->root, sortedArray, low, high-1);
	}
	else {
		destroyTree(this->root);
		arrayToBSTreeHelper(this->root, sortedArray, low, high-1);
	}//end if 
} //Puts NodeData* array into tree

 //---------------------------------------------------------------------------
 // arrayToBSTreeHelper(Node *&, NodeData * [], int, int)
 // Array To Binary Search Tree Helper: Helper method implemented by 
 //								arrayToBSTreeHelper recursively. Each insert
 //								will be at the (low + high)/2 index.
 // @param current Current Node to insert to
 // @param sortArray Array that NodeData* is pulled from
 // @param low lower index of binary partition created by helper
 // @param high upper index of binary partition created by helper
 // 
void BinTree::arrayToBSTreeHelper(Node *& current, NodeData * sortArray[],
								  int low, int high){
	if (low > high) {
		current = NULL;
	} 
	else{
		int binIndex = (low+high)/2;
	NodeData* temp;
	temp = sortArray[binIndex];
	sortArray[binIndex] = NULL;
	insert(temp);
	arrayToBSTreeHelper(current->left, sortArray, low, binIndex - 1 );
	arrayToBSTreeHelper(current->right, sortArray, binIndex + 1, high);
	}//end if
}//end arrayToBSTreeHelper

 //---------------------------------------------------------------------------
 // operator<<(ostream&, const BinTree&)
 // << operator : Output operator that prints the tree inorder
 // @param output output stream
 // @param printableTree the tree that provides the output data
 // 
ostream& operator<<(ostream& output, const BinTree& printableTree){

	if (printableTree.isEmpty()){
		output << "Empty Tree!" << endl;
	}
	else{
	printableTree.inorderPrint(printableTree.root);
	output << endl;
	}//end if

	return output;
}//end operator<<

 //---------------------------------------------------------------------------
 // inorderPrint(Node* current)
 // inorder Print: Helper method that recursively walks through the BinTree to 
 //					print out the Node NodeData* contents inorder.
 //	@param current the current node passed into the function
 //
void BinTree::inorderPrint(Node* current) const {
	
	if (current != NULL){
	inorderPrint(current->left);
	cout << *current->data << " ";
	inorderPrint(current->right);
	}//end if

}//end inorderPrint

