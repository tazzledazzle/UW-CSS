
/**-----------------------------------------------------------------------* 
 * 	@file return.h
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/


#ifndef _RETURN_H_
#define _RETURN_H_
#include "transaction.h"

//----------------------------------------------------------------------------
// Class: Return
// return object, child of transaction. Used when processing items within 
// store.
//
//----------------------------------------------------------------------------
// 
//

class Customer;		//forward declaration
class Return : public Transaction {

public:
	Return();
	Return(const Return&);
	virtual ~Return(); //end destructor
	virtual bool setData(string, Inventory *, Customer *);
	virtual void display() const;
	virtual Transaction * create(); //create new return object

};

#endif

