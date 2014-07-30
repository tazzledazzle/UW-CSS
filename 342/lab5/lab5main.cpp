
 /**====================================
	@file lab5main.cpp
	@author Terence Schumacher
	@author Dominic Badzik
	@version 1.3
 ======================================*/
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <ctime>
#include "Node.h"
#include "tbst.h"
#define MAX_FILES 50
#define MAX_LIST_COUNT 100
#define DEBUG "DEBUG"
#define FILE "FILE"
#define DEFAULT_FILE "hamlet.txt"
#define FILEPOS 2
#define OUTPUT_FILE "lab5out.txt"
#define LINE_ONE_BRIEF "This program produces a frequency count of all tokens within a file."
#define DIRECTIONS " Make sure the number of files entered under 50, default is hamlet.txt"
#define LINE_TWO_BRIEF "--Written by Terence Schumacher and Dominic Badzik--"
#define TIME_MSSG "Time: "
#define INFILE_MSSG "File Read In: "
#define ELAPSED_MSSG "clockElapsed:clock time elapsed: "
#define TICKS_MSSG " clock ticks ~= "
#define SEC_MSSG " seconds\n"
#define TREE_MSSG "Binary Tree Traversal: "
#define LIST_MSSG "List of Frequencies: "
#define EXCEED_FILE_MAX_ERR "ERROR: Too many files read in, Maximum 50!"
#define ERR_EMPTY_MSSG "ERROR: Tree or List Empty!"
#define WRITE_ERR_EMPTY_MSSG "FILE WRITE ERROR: Tree or List Empty!"
#define OUT_COUNT 21
#define SPACE " "

using namespace std;


 /** Clock Elapsed
	@brief timing method provided for lab2
	@param clockTimeStart start clock instance
	@param clockTimeEnd end clock instance
*/
void clockElapsed( clock_t clockTimeStart, 
                  clock_t clockTimeEnd ) {  // uses less precise ctime
  clock_t ticks;
  ticks = clockTimeEnd - clockTimeStart;
  cout << ELAPSED_MSSG << ticks << TICKS_MSSG 
       << (float)ticks / (float)CLOCKS_PER_SEC << SEC_MSSG; 
} // clockElapsed

 /** Debug Printing
	@brief prints full output if DEBUG passed in
	@param decision switch for output
	@param tBSTree tree printing from
	@param list list of frequencies
	@return true if decision true, false otherwise
 */
bool debugPrinting(bool decision, ThreadedBST * tBSTree, List * list){
	if(tBSTree->isEmpty() || list->isEmpty()){
		cout << ERR_EMPTY_MSSG << endl;
		return false;
	}
	else if(decision){
		cout << TREE_MSSG << endl;
		tBSTree->inorderStrTraverse();
		cout << LIST_MSSG << endl;
		list->printList(cout, *list);
		return true;
	}//end if
	
	return false;

}//end debugPrinting

 /** File Writer
	@brief writes to a file based on boolean parameter
	@param status decision of whether or not to output to file
	@param tBSTree tree outputting from
	@param file name of file tree created from
	@return true if output to file, false otherwise
 */
bool fileWriter(bool status, ThreadedBST *tBSTree, const char* file, ofstream& outFile){

	if (tBSTree->isEmpty()){
		cout << WRITE_ERR_EMPTY_MSSG << endl;
		return false;
	}
	else if (status){
		
		int counter = 0;
		outFile << file << endl << endl;
		tBSTree->inorderTRAV(tBSTree->getRoot(), outFile,counter);
		outFile << endl << endl;
		return true;
	}

	return false;

}//end fileWriter
 
 /** Print Intr
	@brief prints out introduction of authors and program
 */
void printIntr(){
	cout << endl;
	cout << LINE_ONE_BRIEF << endl;
	cout << LINE_TWO_BRIEF << endl;
	cout << endl;
	cout << endl;
	cout << DIRECTIONS << endl;
}//end printIntro

 /** Print File And Time
	@brief prints out the time elapsed and the file name
	@param begin beginning clock instance
	@param end end clock instance
	@param file name of file read in
 */
void printFileAndTime(clock_t begin, clock_t end, const char* file){

		cout << INFILE_MSSG << file << SPACE;
		cout << TIME_MSSG;
		clockElapsed(begin, end);
}//end printFileAndTime

 /** compileAnd Print
	@brief compiles the tokens into a tree, then transfers nodes into list
	@param tempTree temporary tree read to
	@param tempList temporary list read to
	@param file file name creating from
 */
void compileAndPrint(ThreadedBST *& tempTree, List *& tempList, const char * file){
		clock_t Begin = clock();
		tempTree = new ThreadedBST(file);
		tempList = new List();
	
		tempTree->transferStringsToList(tempTree->getRoot(), *tempList);
		clock_t End = clock();

		tempList->printN(OUT_COUNT, *tempList);
		cout << endl;

		printFileAndTime(Begin, End, file);
}//end compileAndPrint

 /** Kill Memory
	@brief destroys dynamic allocated tree and list
	@param tempTree tree to destroy
	@param tempList list to destroy
 */
void killMemory(ThreadedBST*& tempTree, List*& tempList){
		delete tempTree;
		tempTree = NULL;
		delete tempList; 
		tempList = NULL;

}//end killMemory

 /** check Input For Array Size
	@brief checks size of files read in
	@param file status of whether or not FILE is present
	@param firstChoice first size to set
	@param secondChoice second size to set
 */
int checkInputForArraySize(bool file, int firstChoice, int secondChoice){
	if (file)
		return firstChoice;
	else 
		return secondChoice;

}//end checkInputForArraySize

 /** Main
	@brief Runs the program
	@param argc number of command line arguments
	@param argv string representation of said arguments
	@return 0 if completed
 */
int main (int argc, const char* argv[]){
	
	ThreadedBST * tempTree;
	List * tempList;
	
		//turnary operator checking if DEBUG and FILE are present
	bool debug = (strcmp(argv[argc - 1], DEBUG) == 0) ? true : false;
	bool file = (strcmp(argv[argc - FILEPOS], FILE) == 0) ? true : false;

	string textList[MAX_LIST_COUNT];
	ofstream outFile;
	outFile.open(OUTPUT_FILE);

	int fileCount = 0;
	printIntr();
	
	int length = checkInputForArraySize(file, (argc-FILEPOS), (argc-1));

	for (int index = 1; index < length; index++){

		cout << argv[index] << SPACE;
		if (strcmp(argv[index], FILE) == 0){
			textList[index-1] = "";
		}
		else{
			textList[index-1] = argv[index];
			++fileCount;
		}
	}//end for

	cout << endl;

	if ((length > MAX_FILES)) {

		cout << EXCEED_FILE_MAX_ERR << endl << endl;

		compileAndPrint(tempTree,tempList,DEFAULT_FILE);
		
		debugPrinting(debug, tempTree, tempList);
		fileWriter(file, tempTree, DEFAULT_FILE, outFile);
		cout << endl;
		cout << endl;
	killMemory(tempTree, tempList);

	}
	else {

	int sizeOfFileList = (file)? (argc - FILEPOS) :(argc - 1);
	for (int index = 1; index < sizeOfFileList; index++)	
	{
		compileAndPrint(tempTree, tempList, argv[index]);
		
		debugPrinting(debug, tempTree, tempList);
		fileWriter(file, tempTree, argv[index], outFile);
		cout << endl;
		cout << endl;
		killMemory(tempTree, tempList);


	}//end for

	}//end if
	outFile.close();
	return 0;
}//end main

