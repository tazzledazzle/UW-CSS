
#ifndef BINTREE_H
#define BINTREE_H
#include "movie.h"
struct Node;

//----------------------------------------------------------------------------
// Class: BinTree
//
//----------------------------------------------------------------------------
// 
//

//Struct holds pointers to data and left/right ancestors
struct Node
{
	Inventory* movie; //Pointer to Item
	Node* left, *right; //Left/Right child pointers 
};

class BinTree
{
	//Overloaded << operator
	//Displays contents of entire BST inorder
	friend ostream& operator<<(ostream& output, BinTree& tree);
	struct Node;

public:


	BinTree();
	BinTree(const BinTree&); // copy constructor
	~BinTree();

	//Functions used to modify BST
	bool insert(Inventory* insertMovie, const int copiesIn);
	bool isEmpty() const;// true if tree is empty, otherwise false
	void makeEmpty(); // make the tree empty so isEmpty returns true 
	bool retrieve(const Inventory& dataItem, Inventory*& dataFound) const;
	void retrieveHelper(Node* curPtr, 
		const Inventory & dataItem, Inventory*& dataFound) const;
	void inorderDisplay(Node * current) const;
	Node * getRoot() const;//end getRoot
private:
	//Struct holds pointers to data and left/right ancestors
	struct Node
	{
		Inventory* movie; //Pointer to Item
		Node* left, *right; //Left/Right child pointers 
	};
	Node *root; // root of the tree

	// utility functions
	void inOrderDisplayHelper(Node* current) const;
	//bool isEqual(Node*, Node*) const; //Checks if two nodes equal
	void destroyTree(Node*& tree);
};
#endif
