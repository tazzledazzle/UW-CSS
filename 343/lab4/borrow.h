
/**-----------------------------------------------------------------------* 
 * 	@file borrow.h
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/


#ifndef _BORROW_H_
#define _BORROW_H_
#include "transaction.h"

//----------------------------------------------------------------------------
// Class: Borrow
// Object that holds a "borrowed" item. Child of Transaction class. Each 
// object contains all data members contained in a transaction object.
// 
//----------------------------------------------------------------------------
// 
//

class Customer;
class Borrow : public Transaction {
public:
	Borrow();
	Borrow(const Borrow& );
	~Borrow(); //end destructor

	virtual bool setData(string , Inventory * , Customer * );
	virtual void display() const;
	virtual Transaction * create();

};


#endif

