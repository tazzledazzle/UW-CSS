
  /**=================================
	@file lab5test.cpp
	@author Terence Schumacher
	@author Dominic Badzik
	@version 1.3
*===================================*/
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"
#include "tbst.h"
#define PRINT_N 21
#define TEXT_FILE "t0.txt"
#define TEXT_FILE2 "t8.txt"
#define MAX 52
#define DEFAULT_NUMBER 13
#define CHAR_UPPER_INDX 64
#define CHAR_LOWER_INDX 71
#define LAST_UPPER_CHAR 26

using namespace std;

 /** Check True
	@brief prints out True or False depending on bool outcome
	@param comparison bool comparison to print out results
 */
void checkTrue(bool comparison){
	if (comparison){
		cout << "True" << endl;
	}else{
		cout << "False" << endl;
	}//end if 

}//end checkTrue


void createTreeAndDeleteEvens(int maxEntered){	
	
	ThreadedBST tree;
	string tempString;

	for (int index = 0; index < maxEntered; index++){
		int randomNumber = rand() % maxEntered;
		char testChar;
		if (randomNumber <= LAST_UPPER_CHAR){
			testChar = (randomNumber + CHAR_UPPER_INDX);
		}else {
			testChar = (randomNumber + CHAR_LOWER_INDX);
		}
		cout << "Insert " << randomNumber << " with "<< testChar << endl;

		tempString += testChar;
		NodeData * tempData = new NodeData(randomNumber, tempString);
		tree.insert(tempData);
		//tree.iterativeInorderTraverse();
		//cout<< endl;
		tempString.clear();
		delete tempData;
		tempData = NULL;
	}
	cout << endl;
	tree.iterativeInorderTraverse();
	cout << endl << "Recursive Version: "  << endl;
	tree.printIntsInTree();



	ThreadedBST * copyTree = new ThreadedBST(tree);
	cout << endl;
	cout << "Copy of Tree: " << endl;
	copyTree->iterativeInorderTraverse();
	for (int index = 0; index < maxEntered; index+= 2){
		//cout << "Delete " << index << endl;
		copyTree->deleteInt(index);
		//tree.iterativeInorderTraverse();
		//cout << endl;
	}
	cout << endl << "Delete all Evens from Tree: " << endl;
	cout << "---------------------------------" << endl;
	cout << "Original: " << endl;
	tree.iterativeInorderTraverse();
	cout << endl;
	cout << "Copy: " << endl;
	copyTree->iterativeInorderTraverse();
	
	delete copyTree;
	copyTree = NULL;
}

 /** Status of Choice
	@brief checks user input whether debug code is necessary or not
	@param choice user entered character
	@return true if Y, false otherwise
 */
bool statusOfChoice(char choice){
		switch (choice){
			case 'y':
			case 'Y':
				return true;
				break;
			case 'n' :
			case 'N':
				return false;
				break;
			default:
				return false;
		}//end switch
}//end statusOfChoice

  /** ==================== Main =======================
	@brief Runs tests on methods
	@param argc number of arguments
	@param argv array of arguments
	@return 0 if execution completes, error otherwise
*/
int main(int argc, const char* argv[]){
	
	int maxEntered = atoi(argv[argc-1]);

	if (maxEntered > 52 || maxEntered < 1){
			createTreeAndDeleteEvens(DEFAULT_NUMBER);
	}
	else{

		createTreeAndDeleteEvens(maxEntered);



		char choice; 
		bool debug = false;
		cout << endl << endl << "Do you want to debug? Y/N: ";
		cin >> choice;
		debug = statusOfChoice(choice);
		
		if (debug){
		cout << "Test: Output- ";
	cout << "Hello to YOU!!!" << endl;
	

	cout << "============================================================" << endl;
	cout << " Test Node Class" << endl;
	cout << "============================================================" << endl;
	//----------------------------------------------------------------------//
	//						NODE TESTING									//
	//----------------------------------------------------------------------//
	cout << "Testing Nodes:" << endl << endl;
	//----------------------------------------------------------------------//
	//						Constructors									//
	//----------------------------------------------------------------------//
	cout << "Default Constructor:" << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	Node * testNode = new Node();
	testNode->printNode(testNode);
	cout << endl;
	cout << "Item Constructor:" << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	Node * testNode2 = new Node(4);
	testNode2->printNode(testNode2);
	cout << endl;
	cout << "Full Constructor: " << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	Node * testNode3 = new Node(4, testNode, testNode2, false, true);
	testNode3->printNode(testNode3);
	cout << endl;
	cout << "Copy Constructor: " << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	Node * testCopy = new Node(testNode3);
	testCopy->printNode(testCopy);
	cout << endl;

	//----------------------------------------------------------------------//
	//							Getters										//
	//----------------------------------------------------------------------//
	cout << "Testing Getters:" << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	cout << "Item ";
	cout << testCopy->getInt() << " ";
	cout << "Frequency ";
	cout << testCopy->getIntFrequency() << " ";
	cout << "Left Child ";
	cout << testCopy->getLeftPtr() << " ";
	cout << "Right Child ";
	cout << testCopy->getRightPtr() << " ";
	cout << "Left Threaded? ";
	checkTrue(testCopy->getLeftThread());
	cout << "Right Threaded? ";
	checkTrue(testCopy->getRightThread());
	cout << endl << endl;

	//----------------------------------------------------------------------//
	//							Setters										//
	//----------------------------------------------------------------------//
	cout << "Testing Setters:" << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	testNode3->setIntFrequency(9999);
	cout <<         "setIntFrequency(): ";
	checkTrue(testNode3->getIntFrequency() == 9999);
	testNode3->setItem(100001);
	cout << endl << "setItem():         ";
	checkTrue(testNode3->getInt() == 100001);
	testNode3->setLeftPtr(testCopy);
	cout << endl << "setLeftPtr():      ";
	checkTrue(testCopy == testNode3->getLeftPtr());
	testNode3->setRightPtr(testCopy);
	cout << endl << "setRightPtr():     ";
	checkTrue(testCopy == testNode3->getRightPtr());
	testNode3->setLeftThread(true);
	cout << endl << "setLeftThread():   ";
	checkTrue(testNode3->getLeftThread());
	testNode3->setRightThread(true);
	cout << endl << "setRightThread():  ";
	checkTrue(testNode3->getRightThread());
	cout << endl << endl;

	//----------------------------------------------------------------------//
	//							Operators									//
	//----------------------------------------------------------------------//
	cout << "Testing Operators:" << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	cout <<         "Less than:         ";
	checkTrue(testNode < testNode2);
	cout << endl << "Greater than:      ";
	checkTrue(testNode2 > testNode);
	cout << endl << endl;

	//----------------------------------------------------------------------//
	//							Comparison									//
	//----------------------------------------------------------------------//
	cout << "Testing Comparisons:" << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	cout <<         "isLeaf testNode2:  ";
	checkTrue(testNode2->isLeaf());
	cout << endl << "isLeaf testNode:   ";
	checkTrue(testNode->isLeaf());
	cout << endl << "hasOnlyLeftChild:  ";
	checkTrue(testNode->hasOnlyLeftChild());
	cout << endl << "hasOnlyRightChild: ";
	checkTrue(testNode->hasOnlyRightChild());
	testNode->setRightPtr(NULL);
	cout << endl << "After setting right" << endl << "child to null," << endl <<
					"hasOnlyLeftChild:  ";
	checkTrue(testNode->hasOnlyLeftChild());
	testNode->setRightPtr(testNode2);
	testNode->setLeftPtr(NULL);
	cout << endl << "After setting left" << endl << "child to null" << endl <<
					"and adding a right child," << endl <<
					"hasOnlyRightChild: ";
	checkTrue(testNode->hasOnlyRightChild());
	cout << endl << "hasData():         ";
	checkTrue(testNode->hasData());
	cout << endl << endl;
	//----------------------------------------------------------------------//
	//						TBST TESTING									//
	//----------------------------------------------------------------------//
	cout << "TBST Testing:" << endl 
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	ThreadedBST * generateFromFile3 = new ThreadedBST(TEXT_FILE);
	generateFromFile3->inorderStrTraverse();
	List * stringTester = new List();
	generateFromFile3->transferStringsToList(generateFromFile3->getRoot(), *stringTester);

	//----------------------------------------------------------------------//
	//							Insertion 									//
	//----------------------------------------------------------------------//
	cout << "Testing Int Insertion:" << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;

	ThreadedBST integerTree;
	for (int i = 0; i < 20; i++){
		int insertionNumber = rand() % 100;
		integerTree.insert(insertionNumber);
		cout << "Inserted: " << insertionNumber << endl;
	}//end for		
	cout << "In Recursive Order:   ";
	integerTree.inorderIntTraverse();
	cout << endl;
	cout << "Pre Recursion Order:  ";
	integerTree.preorderIntTraverse();
	cout << endl;
	cout << "Post Recursion Order: ";
	integerTree.postorderIntTraverse();
	cout << endl;
	cout << "In Iterative Order:   ";
	integerTree.iterativeInorderTraverse();
	cout << endl << endl;

	cout << "Testing String Insertion:" << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	ThreadedBST * stringTree = new ThreadedBST(TEXT_FILE2);
	cout << "In Recursive Order:   ";
	stringTree->inorderStrTraverse();
	cout << endl;
	cout << "Pre Recursion Order:  ";
	stringTree->preorderStrTraverse();
	cout << endl;
	cout << "Post Recursion Order: ";
	stringTree->postorderStrTraverse();
	cout << endl;

	//----------------------------------------------------------------------//
	//							Removal 									//
	//----------------------------------------------------------------------//
	cout << "Testing Int Removal:" << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	integerTree.deleteInt(15);
	integerTree.inorderIntTraverse();
	cout << endl;
	integerTree.deleteInt(40);
	integerTree.inorderIntTraverse();
	cout << endl;
	integerTree.insert(15);
	integerTree.insert(15);
	integerTree.inorderIntTraverse();
	cout << endl << endl;
	cout << "Remove all Evens" << endl;
	for (int index = 0; index < 100; index += 2){
		integerTree.deleteInt(index);
	}//end for
	cout << "In Recursive Order:   ";
	integerTree.inorderIntTraverse();
	cout << endl;
	cout << "Pre Recursion Order:  ";
	integerTree.preorderIntTraverse();
	cout << endl;
	cout << "Post Recursion Order: ";
	integerTree.postorderIntTraverse();
	cout << endl << endl;

	cout << "Testing String Removal:" << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	stringTree->deleteString("lemons");
	stringTree->deleteString("Cave");
	stringTree->deleteString(",");
	stringTree->deleteString(".");
	stringTree->deleteString("burn");
	stringTree->deleteString("house");
	stringTree->deleteString("asdfasdfasdfasdf");

	cout << "In Recursive Order:   ";
	stringTree->inorderStrTraverse();
	cout << endl;
	cout << "Pre Recursion Order:  ";
	stringTree->preorderStrTraverse();
	cout << endl;
	cout << "Post Recursion Order: ";
	stringTree->postorderStrTraverse();
	cout << endl << endl;

	//----------------------------------------------------------------------//
	//						Copy Constructor								//
	//----------------------------------------------------------------------//
	cout << "Testing Copiers:" << endl 
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	cout << "Integer: " << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;	
	ThreadedBST copyTree(integerTree);
	cout << "Copy:     ";
	copyTree.inorderIntTraverse();
	cout << endl << "Original: ";
	integerTree.inorderIntTraverse();
	
	copyTree.deleteInt(35);
	
	cout << endl << "Copy:     ";
	copyTree.inorderIntTraverse();
	cout << endl << "Original: ";
	integerTree.inorderIntTraverse();
		cout << endl;
	cout << "String: " << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	ThreadedBST copyStringTree(*stringTree);

	cout << endl << "Copy:     ";
	copyStringTree.inorderStrTraverse();
	cout << endl << "Original: ";
	stringTree->inorderStrTraverse();

	stringTree->deleteString("Johnson");

	cout << endl << "Copy:     ";
	copyStringTree.inorderStrTraverse();
	cout << endl << "Original: ";
	stringTree->inorderStrTraverse();
	List againStringFreq;
	cout << endl << endl;


	//----------------------------------------------------------------------//
	//							Printing 									//
	//----------------------------------------------------------------------//
	cout << "Testing Printing:" << endl 
	<<"----------------------------------------------------------------------"
	<< endl << endl;

	for (int i = 0; i < 250; i++){
		int insertionNumber = rand() % 100;
		integerTree.insert(insertionNumber);
		//cout << "Inserted: " << insertionNumber << endl;
	}//end for	
	
	// for (int index = 0; index < 100; index += 2){
	// 	cout << "deleting " << index << endl;
	// 	integerTree.deleteInt(index);				//THIS CODE DON'T WORK
	// 	cout << "deleted " << index << endl;
	// }//end for

	List frequencies;
	cout << "Numbers: " << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	integerTree.transferToList(integerTree.getRoot(), frequencies);
	frequencies.printList(cout, frequencies);

	List strFrequencies;
	cout << "Strings: " << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	stringTree->transferStringsToList(stringTree->getRoot(), strFrequencies);
	strFrequencies.printList(cout, strFrequencies);
	cout << endl;

	cout << "Printint most and least frequent:" << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	cout << "Integer List: " << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	frequencies.printN(PRINT_N, frequencies);
	cout << endl << "String List: " << endl
	<<"----------------------------------------------------------------------"
	<< endl << endl;
	strFrequencies.printN(PRINT_N, strFrequencies);

	//----------------------------------------------------------------------//
	//							Clean Up 									//
	//----------------------------------------------------------------------//

	getchar();
	
	delete generateFromFile3;
	generateFromFile3 = NULL;
	delete stringTester;
	stringTester = NULL;
	delete testNode;
	testNode = NULL;
	delete testNode2;
	testNode2 = NULL;
	delete testNode3;
	testNode3 = NULL;
	delete testCopy;
	testCopy = NULL;
	delete stringTree;
	stringTree = NULL;
	}//end if debug


}//end if
	cout << "Done..." << endl;


return 0;

}//end main


