
/**-----------------------------------------------------------------------* 
 * 	@file transaction.h
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/

#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_
#include "movie.h"

//----------------------------------------------------------------------------
// Class: Transaction
// parent class of borrow, return, and history. 
// 
//----------------------------------------------------------------------------
// 
//

class Customer;
class Transaction {
public:
	Transaction(); // constructor
	Transaction(const Transaction& ); //copy constructor
	virtual ~Transaction(); // destructor

	virtual bool setData(string media, Inventory * item, Customer * aCustomer);	// setData
	virtual void display() const;// display
	virtual Transaction * create();

	string getMediaType();//get media type
	string getTransactionType();	// transaction type
	Inventory * getItem() const;	//pointer to Inventory Item

protected:
	string transType;
	string mediaType;
	Inventory * anItem;

};

#endif



