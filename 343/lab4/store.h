
/**-----------------------------------------------------------------------* 
 * 	@file store.h
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/

#ifndef _STORE_H_
#define _STORE_H_
#define MAXCUSTOMERS 10000
#define MAXINVENTORY 53
#include <fstream>
#include <vector>
#include "customer.h"
#include "factory.h"
#include "bintree.h"



//----------------------------------------------------------------------------
// Class: Store
// maintains all customers, inventory items, and transactions within class.
// creates, modifies, and manipulates all data involving these objects as well
//
//----------------------------------------------------------------------------
// 
//

using namespace std;

class Store {

public:
	Store();
	Store(string );
	Store(const Store& );
	~Store();	//destructor

	void createCustomers(istream&);
	void createInventory(istream&);
	void processTransactions(istream&);
	void display();
	void displayInventory() const;
	void displayCustomerBase() const;
	bool lookUpCustomer(int) const;
	string getBusinessName() const;
	Customer getCustomer(const int) const;

private:
	Customer customerList[MAXCUSTOMERS];
	BinTree inventoryList[MAXINVENTORY];
	vector<Transaction> storeTransactionHistory;
	Factory factory;

	string name;
};

#endif



