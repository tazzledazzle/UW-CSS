
/*===========================================* 
	@author		Terence Schumacher
	@file		bintree.h
	@version	2.3
*===========================================*/

#ifndef _BINTREE_H_
#define _BINTREE_H_

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

#include <iostream>
#include "nodedata.h"

using namespace std;

class BinTree {

   //Overloaded << operator
   //Displays contents of entire BST inorder
   friend ostream& operator<<(ostream&, const BinTree&);

public:

 //====================================================constructors/destructor
	BinTree();							// default constructor
	BinTree(const BinTree &);			// copy constructor
	~BinTree();							// destructor, calls makeEmpty

 //==========================================================utility functions
	bool isEmpty() const;	    // true if tree is empty, false otherwise
	void makeEmpty();		   // makes the tree empty so isEmpty returns true
	void displaySideways() const;	  // provided, displays the tree sideways
	int getDepth(const NodeData &) const;
	bool retrieve(const NodeData &, NodeData *&) const;
	void bstreeToArray(NodeData* []);     // Puts tree into array of NodeData*
    void arrayToBSTree(NodeData* []);     // Puts NodeData* array into tree
	
 //==================================================================modifiers
	BinTree& operator=(const BinTree &);	//assignment operator
	bool insert(NodeData *);				// inserts into the tree
	bool remove(NodeData *);				// optional removal function
	
 //=================================================================comparison
	bool operator==(const BinTree &) const; // check if lhs object same as rhs
	bool operator!=(const BinTree &) const; //check lhs objec and rhs not same

private:

 //=============================================================Node Structure
	struct Node{
		NodeData * data;			// pointer to data object
		Node * left;				// left subtree pointer
		Node * right;				// right subtree pointer
	};

	Node * root;					// root of the tree

 //==================================================Private recursive Methods
	void sideways(Node* current, int level) const; //displays tree sideways
	void destroyTree(Node*);     //deallocates memory from tree postorder
	void retrievalHelper(Node*, const NodeData & , 
		NodeData*&) const;	     //searches tree for desired node data element
	void bstreeToArrayHelper(Node * , 
		NodeData* [], int& );    //transfers items in tree to an array inorder
	void arrayToBSTreeHelper(Node *& , 
		NodeData * [], int , int ); //transfers items in array to tree binary
	void copyTree(Node*, Node*&); //preorder copies all elements of tree
	int getDepthHelper(Node *, 
		const NodeData &) const;  // recursively counts levels of depth
	void inorderPrint(Node*) const; // prints tree inorder
	bool checkEquality(Node*, Node*) const; //checks each node preorder for ==
	int getNumberOfNodes(Node *) const; //returns number of nodes in tree
};

#endif

