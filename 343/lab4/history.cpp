
/**-----------------------------------------------------------------------* 
 * 	@file history.cpp
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/

#include "history.h"
#include "customer.h"

//----------------------------------------------------------------------------
// Constructor
// default constructor
//
History::History() : Transaction(){
	transType = "History";
}//end constructor

//----------------------------------------------------------------------------
// Copy Constructor
// copies information from rightSide object to newly created history object
// @param rightSide history object copying from
//
History::History(const History& rightSide) {
	transType = rightSide.transType;
	mediaType = rightSide.mediaType;
	anItem = rightSide.anItem;
}//end copy constructor

//----------------------------------------------------------------------------
// Destructor
// Deallocates dynammically allocated memory back to the heap
//
History::~History(){}// end destructor

//----------------------------------------------------------------------------
// set Data
// sets data for history item 
// @param media unused but kept for polymorphic qualities
// @param item unused but kept for polymorphic qualities
// @param aCustomer customer contained in specific history object
// @return false to signal a non-stored value
//
bool History::setData(string media, Inventory * item, Customer * aCustomer) {
	aCustomer->displayCustomerHistory();
	// just displays customer history to keep polymorphism
	return false; 
}//end setData

//----------------------------------------------------------------------------
// Create
// creates new history object for factory
//
Transaction * History::create() { 
	return new History(); 
}//end create

