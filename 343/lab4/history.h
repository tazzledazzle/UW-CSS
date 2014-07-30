
/**-----------------------------------------------------------------------* 
 * 	@file history.h
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/

#ifndef _HISTORY_H_
#define _HISTORY_H_
#include "transaction.h"

//----------------------------------------------------------------------------
// Class : History
// child of transaction, displays the history for specific customer.
// 
//----------------------------------------------------------------------------
// 
//

class Customer;
class History : public Transaction{
public:
	History();
	History(const History& rightSide);
	~History(); //destructor

	virtual bool setData(string, Inventory *, Customer *);
	virtual Transaction * create();

};


#endif
