
/**
	@file lab3testmain.cpp
	@author Terence Schumacher
	@version 1.0
*/

#include "compareList.h"
#include <cassert>
#include <fstream>
#include <ctime>
#include <cmath>
#include <string>
#include <cassert>
#define FIB_CEILING 1134903170
#define TEST_CEILING 30
#define FIB_COUNT 9
#define TXT_LIST "c1.txt  c5.txt  h1.txt s10.txt  s154.txt  s4.txt  s8.txt  t2.txt  t6.txt c2.txt  c6.txt  h2.txt  s11.txt  s1.txt    s5.txt  s9.txt  t3.txt  t7.txt c3.txt  c7.txt  license.txt  s12.txt  s2.txt    s6.txt  t0.txt  t4.txt  t8.txt c4.txt  c8.txt  s0.txt     s13.txt  s3.txt    s7.txt  t1.txt  t5.txt "
#define MAX_FILES 50
#define PRIME_COUNT 9

using namespace std;

//
void checkTrue(const bool comparison){
	if (comparison == 0)
		cout << "False";
	else
		cout <<  "True";
	
}//end checkTrue
//
//void clockElapsed( clock_t clockTimeStart, 
//                  clock_t clockTimeEnd ) {  // uses less precise ctime
//  clock_t ticks;
//  ticks = clockTimeEnd - clockTimeStart;
//  cout << "clockElapsed:clock time elapsed: " << ticks << " clock ticks ~= " 
//       << (float)ticks / (float)CLOCKS_PER_SEC << " seconds\n"; 
//} // clockElapsed

int main (int argc, char* argv[]) {

	char* textList[MAX_FILES];
	char* prospects[MAX_FILES];
	int fileCount = 0;
	int prospectCount = 0;
	int primes[] = {2, 3, 5, 13, 89, 233, 1597, 28657, 514229};
	
	//create lists
	cout <<" Test List: " << endl;
	for (int index = 1; index < argc - 3; index++){

		cout << argv[index] << " ";
			textList[index-1] = argv[index];
		++fileCount;
	}//end for
	cout << endl;
	
	cout <<" Prospect List: " << endl;
	for (int index = argc-2; index < argc; index++){

		cout << argv[index] << " ";
			prospects[prospectCount] = argv[index];
		++prospectCount;
	}//end for

	cout << endl;
	cout << "File Count: " << fileCount << endl;
	cout << "Prospect Count: " << prospectCount << endl;

	cout <<" Text Array: " << endl;
		for (int index = 0; index < fileCount; index++){
			cout << textList[index] << " ";
	}//end for

	cout <<" Prospect List: " << endl;
		for (int index = 0; index < prospectCount; index++){
			cout << prospects[index] << " ";
	}//end for
	
	char const test[] = "numbers.txt";
	compareList listArray[MAX_FILES];
	//ifstream testFile(test);
	
	for (int fileIndex = 0; fileIndex < fileCount; fileIndex++ ){
	ifstream testFile(textList[fileIndex]);

	compareList testCMPList;
	char line, throwAway;

	if (!testFile){
		cout << "Error with File: " << test << endl;
	}
	else{
	int i = 0, index = 0;
		while  (testFile.peek() != EOF){
			
			while ( index < primes[i]){
				testFile >> throwAway;
				index++;
				//Need to hash out EOF action
				if (testFile.peek() == EOF){
					cout << "End of File!" << endl;
					break;}
			}

			testFile >> line;
			cout << index<<':'<< line << " ";
			
			testCMPList.insert(index, line);

			if (i < PRIME_COUNT)
				i++;
			else 
				break;
		
		}//end while
	
	}//end if

		cout <<"Listing: "<< testCMPList << endl;
		listArray[fileIndex] = testCMPList;
	}//end for

	//print array
	for (int index = 0; index < fileCount; index++){
		cout << textList[index] << "----" << listArray[index] << endl;
	}//end for

	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "  ---------------------Linked Set Impplementation--------------------------  " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;

	
	//test is constructors
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test Copy Constructors                                " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	/*compareList List;
	cout << List << endl;*/
	compareList cmpList;// = new compareList();
	

	//test is empty
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test Is Empty                                         " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;

	assert(cmpList.isEmpty());
	cout << "is The List Empty: ";
	checkTrue(cmpList.isEmpty());
	cout << endl;

	//test operator <<
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator <<                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cmpList.insert(2);
	cmpList.insert(3);
	cmpList.insert(5);
	cmpList.insert(4,'c');
	cmpList.insert(7);
	cmpList.insert(1);
	cmpList.insert(19);
	cout << "testList: " << cmpList << endl;

	//test is in set
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                      Test Is In Set                                         " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "Is 45 in set?" << endl;
	cmpList.isInList(45);
	cmpList.isInList(3);

	////test remove
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                         Test Remove                                         " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cmpList.remove(3);
	cmpList.remove(0);
	cmpList.remove(0);
	cout << cmpList << endl;
	cmpList.clear();
	cout << cmpList << endl;
	
	//test operator=
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                        Test operator =                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	
	//compareList fibList;

	////insertFibs(10, fibList);
	//fibList.insert(4);
	//fibList.insert(8);
	//fibList.insert(0);
	//cout <<"First List: " << fibList << endl;
	//cmpList = fibList;
	//cout << "Second List: " << cmpList << endl;

	//cmpList.remove(8);
	//cout <<"First List: " << fibList << endl;
	//cout << "Second List: " << cmpList << endl;
	//cmpList.clear();
	//fibList.clear();

	////test operator==
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "                       Test operator ==                                      " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	
	cout << cmpList << endl;
	for (int i = 0; i < 12; i++){
		cmpList.insert(i);
	}//end for
	cout << cmpList << endl;
	compareList	oddList, sameList;
	oddList = cmpList;
	for (int i = 0; i < 12; i+=2){
	oddList.remove(i);
	
	}//end for
	cout << oddList << endl;
	sameList = oddList;

	checkTrue(sameList == oddList);
	cout << endl;

	Node * leftSide = cmpList.getHead();
	Node * rightSide = oddList.getHead();

	while ((leftSide != NULL)&&(rightSide != NULL)){

		checkTrue(leftSide == rightSide);
		if (leftSide->getFibNumber() < rightSide->getFibNumber()){
			leftSide = leftSide->getNext();}
		else if (leftSide->getFibNumber() == rightSide->getFibNumber()){
			leftSide = leftSide->getNext();
			rightSide = rightSide->getNext();
		} else{
			rightSide = rightSide->getNext();
		}//end if

	//	if (leftSide->getFibNumber() == rightSide->getFibNumber())
	//	{
	//		if (leftSide->getByte() == rightSide->getByte()){
	//			
	//			
	//			leftSide = leftSide->getNext();
	//			rightSide = rightSide->getNext();

	//		}
	//	}
	//
	}//end while
	
	//insertFibs( 8, testList);
	//cout << testList << endl;
	//insertFibs( 8, testList2);
	//cout << testList2 << endl;
	//cout << "Are They equal? ";
	//checkTrue(testList == testList2);
	//cout << endl;

	//testList2.clearList();

	//cout << "Are They equal? ";
	//checkTrue(testList == testList2);
	//cout << endl;

	//insertFibs( 8, testList2);
	//testList2.remove(21);

	//cout << "Are They equal? ";
	//checkTrue(testList == testList2);
	//cout << endl;
	//
	//testList.clearList();
	//testList2.clearList();

	////test operator!=
	//cout << "-----------------------------------------------------------------------------" << endl;
	//cout << "                       Test operator !=                                      " << endl;
	//cout << "-----------------------------------------------------------------------------" << endl;
	//cout << testList << endl;
	//
	//insertFibs( 8, testList);
	//cout << testList << endl;
	//insertFibs( 8, testList2);
	//cout << testList2 << endl;
	//cout << "Are They NOT equal? ";
	//checkTrue(testList != testList2);
	//cout << endl;

	//testList2.clearList();

	//cout << "Are They NOT equal? ";
	//checkTrue(testList != testList2);
	//cout << endl;

	//insertFibs( 8, testList2);
	//testList2.remove(21);

	//cout << "Are They NOT equal? ";
	//checkTrue(testList != testList2);
	//cout << endl;

  getchar();
	return 0;
}//end main

