
/**-----------------------------------------------------------------------* 
 * 	@file bintree.cpp
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/


#include "bintree.h"
//----------------------------------------------------------------------------
// Constructor
// enpty constructor
//
BinTree::BinTree() : root(NULL) {
}//end constructor

//----------------------------------------------------------------------------
// Copy Constructor
// unimplementented copy constructor, used to copy a complete inventory 
// @param rightSide the tree building from
//
BinTree::BinTree(const BinTree& rightSide){} //end copy constructor

//----------------------------------------------------------------------------
// Destructor
// used in memeory management of inventory items and binary tree
//
BinTree::~BinTree(){
	if (root != NULL)
		makeEmpty();
} //end destructor

//----------------------------------------------------------------------------
// Insert
// Inserts movie item inside of the tree as well as sets the number of copies
// the item inserted has
// @param insertMovie inventory item inserted
// @param copiesIn number of stock for inserted item
//
bool BinTree::insert(Inventory* insertMovie, const int copiesIn) {
	Node* ptr = new Node();    
	ptr->movie = insertMovie; //Link to current NodeData
	ptr->movie->setMaxCopies(copiesIn);
	insertMovie = NULL; //Disconnect
	ptr->left = ptr->right = NULL;
	if (isEmpty())
	{
		root = ptr; //Empty, set as root
	}
	else
	{
		Node* current = root;
		bool inserted = false;

		// if data is less than current data, insert in left subtree,
		// otherwise insert in right subtree
		while (!inserted)
		{
			if (*ptr->movie == *current->movie) //Duplicate, dont insert
			{
				delete ptr; 
				ptr = NULL;
				return false;
			}
			else if (*ptr->movie < *current->movie)
			{
				if (current->left == NULL) 
				{
					current->left = ptr;
					inserted = true;
				}
				else
					current = current->left;               
			}
			else {
				if (current->right == NULL) 
				{
					current->right = ptr;
					inserted = true;
				}
				else
					current = current->right;              
			}
		}
	}
	return true;
} //end insert

//----------------------------------------------------------------------------
// is Empty
// Checks whether the root is empty or not
// @return true if root NULL, false otherwise
//
bool BinTree::isEmpty() const {
	return (root == NULL); 
} //end isEmpty

//----------------------------------------------------------------------------
// Make Empty 
// calls private method destroyTree() to clear all tree data
//
void BinTree::makeEmpty() { 
	destroyTree(root); 
} //end makeEmpty

//----------------------------------------------------------------------------
// DestroyTree
// postorder deletion of nodes in the tree
// @param tree current node passed into recursive function
//
void BinTree::destroyTree(Node*& tree){
	if (tree != NULL){
		destroyTree(tree->left); //destroy left
		destroyTree(tree->right); //destroy right

		delete tree->movie; //delete NodeData
		tree->movie = NULL;
		delete tree; //Delete Node
		tree = NULL;
	}
} //end destroyTree

//----------------------------------------------------------------------------
// Retrieve
// Locates an item within the tree by storing it in a node data item
// @param dataItem item searching for
// @param dataFound return item, NULL if not found
// @return true if dataFound not NULL, false otherwise
//
bool BinTree::retrieve(const Inventory& dataItem, Inventory*& dataFound) 
														const {
	retrieveHelper(root, dataItem, dataFound);

	if (dataFound != NULL)
		return true;
	else
		return false;
} // end retireve

//----------------------------------------------------------------------------
// RetrieveHelper
// Recursive function called privately by retrieve aiding the search for data
// Item within tree
// @param curPtr current location in tree
// @param dataItem item searching for
// @param dataFound return item, NULL if not found
//
void BinTree::retrieveHelper(Node* curPtr, const Inventory & dataItem, 
								Inventory*& dataFound) const {
	if (curPtr == NULL)
		dataFound = NULL;
	else if (dataItem == *curPtr->movie){
		dataFound = curPtr->movie;
	}
	else if (dataItem < *curPtr->movie)
		retrieveHelper(curPtr->left, dataItem, dataFound);
	else
		retrieveHelper(curPtr->right, dataItem, dataFound);
}//end retrieveHelper

//----------------------------------------------------------------------------
// In-Order Display
// Displays all items in tree from lowest presidence to highest
// @param current current location within tree
//
void BinTree::inorderDisplay(Node * current) const{
	if (current == root){
		current->movie->displayHeader();
	}//end if 

	if (current != NULL){
		inorderDisplay(current->left);

		cout << right << setw(2) << current->movie->getAmountIn() << "  " <<
			left << setw(3) << current->movie->getAmountOut() << " ";
		current->movie->display();

		inorderDisplay(current->right);
	}//end if 
}//end inorderDisplay

//----------------------------------------------------------------------------
// Get Root
// Returns the root 
// @return root of tree
//
BinTree::Node * BinTree::getRoot() const { return this->root; }//end getRoot

