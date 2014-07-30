
  /**=================================
	@file tbst.h
	@author Terence Schumacher
	@author Dominic Badzik
	@version 1.6
*===================================*/

#ifndef _TBST_H
#define _TBST_H
#include "Node.h"
#include "List.h"


using namespace std;

class ThreadedBST {
private:
	Node * root;
	int size;

	void insertLeftChildHelper(Node * targetNode, Node * insertionNode, Node * tempLeftNode);
	void insertRightChildHelper(Node * targetNode, Node * insertionNode, Node * tempRightNode);
	void preorderInsert(Node * currentNode);
	void postorderDeletion(Node * currentNode);
	void printDetails(ofstream& output, Node * current, int &counter);

	Node * parentFinder(Node *& orphanNode);
	Node * stringParentFinder(Node *& orphanNode);

	void destroyNode(Node* currentNode);

	bool leftCheck(Node* current);
	bool rightCheck(Node* current);
	bool onlyRoot();

	void removeWithLeftChild(Node * containsLeftChildNode);
	void removeWithRightChild(Node * containsRightChildNode);
	void removeWithTwoChildren(Node * containsBothChildrenNode);
	void removeWithNoChildren(Node * containsNoChildrenNode);
	void removeLeftMost(Node * containsLeftNull);
	void removeRightMost(Node * containsRightNull);

	void stringRemoveWithLeftChild(Node * containsLeftChildNode);
	void stringRemoveWithRightChild(Node * containsRightChildNode);
	void stringRemoveWithTwoChildren(Node * containsBothChildrenNode);
	void stringRemoveWithNoChildren(Node * containsNoChildrenNode);

	void inorderTraverse(Node * currentNodeLocation, void visit(Node*));
	void preorderTraverse(Node * currentNodeLocation, void visit(Node*));
	void postorderTraverse(Node * currentNodeLocation, void visit(Node*));
public:
	ThreadedBST();
	ThreadedBST(ThreadedBST& copyTree);
	ThreadedBST(const char* fileName);
	~ThreadedBST();

	bool retrieve(int targetInt, Node *& returnedNode);
	bool retrieve(string targetString, Node *& returnedNode);
	
	bool insert(int intValue);
	bool insert(string stringValue);
	bool insert(Node * insertionNode);
	bool insert(NodeData * newData);

	void leastFrequent(int cycleCount);
	void mostFrequent(int cycleCount);

	void postorderStringDeletion(Node * currentNode);

	void iterativeInorderTraverse();
	void inorderTRAV(Node* currentNodeLocation, ofstream& outFile, int& counter);

	void printIntsInTree();
	void printStringsInTree();

	void inorderStrTraverse();
	void preorderStrTraverse();
	void postorderStrTraverse();
	void printAllStringFreq();

	void inorderIntTraverse();
	void preorderIntTraverse();
	void postorderIntTraverse();
	void printAllIntFreq();

	void printOutDetails();
	

	void transferToList(Node * currentNodeLocation, List &insertionList);
	void transferStringsToList(Node * currentNodeLocation, List &insertionList);
	
	bool isEmpty();
	Node *getRoot();
	void setRoot(Node * newRoot);

	void deleteInt(int removalKey);
	void deleteString(string removalKey);
	void deleteNode(Node * removalNode);
	void stringDeleteNode(Node * removalNode);
	
	void printTree();

};

//#include "tbst.cpp"

#endif

