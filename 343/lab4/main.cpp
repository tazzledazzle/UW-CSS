
/**-----------------------------------------------------------------------* 
 * 	@file main.cpp
 *	@author Terence Schumacher
 *	lab4
 *  creates a store object, processes three provided files and ouputs results.
 *
--------------------------------------------------------------------------*/


#include "store.h"

using namespace std;
//----------------------------------------------------------------------------
// Main
// Runs the program
//
int main(){

	Store bizManager("MOVIE: Buy My Stuff");
	ifstream infilePatron("data4customers.txt");
	ifstream infileMovies("data4movies.txt");
	ifstream infileTransactions("data4commands.txt");


	if ((!infilePatron) || (!infileMovies) || (!infileTransactions)){
		cout << "File Could Not be Opened!" << endl;
		getchar();
		return 1;
	}
	
	bizManager.createCustomers(infilePatron);
	bizManager.createInventory(infileMovies);
	bizManager.processTransactions(infileTransactions);

	return 0;

}//end main



