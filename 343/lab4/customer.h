
/**-----------------------------------------------------------------------* 
 * 	@file customer.h
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/


#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_
#include "movie.h"
#include <iostream>
#include <string>
#include <vector>
#include "transaction.h"

using namespace std;

//----------------------------------------------------------------------------
// Class: Customer
// holds necessary information about customer base of store. Objects are 
// created from text file and stored in array inside of store.
//
//----------------------------------------------------------------------------
// 
//

class Customer {
public:
	Customer();
	Customer(istream&);
	Customer(const Customer&);
	virtual ~Customer();
	
	void setData(istream& infile);

	void displayCustomerHistory() const;
	void addTransaction(Transaction );
	virtual void display() const;
	int getCustomerID() const;
	string getFirstName() const;
	string getLastName() const;
	virtual bool operator==(const Customer& rightSide) const;	
	virtual bool operator!=(const Customer& rightSide) const;
private:
	int id;
	string firstName;
	string lastName;
	vector<Transaction> transactionHistory;

};

#endif


