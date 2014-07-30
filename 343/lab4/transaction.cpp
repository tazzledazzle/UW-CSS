
/**-----------------------------------------------------------------------* 
 * 	@file transaction.cpp
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/

#include "transaction.h"

//----------------------------------------------------------------------------
// Constructor
// default constructor
//
Transaction::Transaction() : 
		transType("Transaction"), mediaType(""), anItem(NULL) 
{}//end constructor

//----------------------------------------------------------------------------
// Copy Constructor
// copies information from rightSide object into newly created transaction
// object
//
Transaction::Transaction(const Transaction& rightSide){
	transType = rightSide.transType;
	mediaType = rightSide.mediaType;
	anItem = rightSide.anItem;
} //end copy constructor

//----------------------------------------------------------------------------
// Destructor
// deallocates dynamically allocated memory and returns it to the heap
//
Transaction::~Transaction(){}//end destructor

//----------------------------------------------------------------------------
// Set Data
// sets data of transaction from inventory item and customer
// @param media mediaType
// @param item inventory item
// @param aCustomer customer involved with transaction
// @return true
//
bool Transaction::setData(string media, Inventory * item, 
													Customer * aCustomer){
	mediaType = media;
	anItem = item;
	return true;
}	//end setData

//----------------------------------------------------------------------------
// Display
// displays media type and transaction type
//
void Transaction::display() const {
	cout << mediaType << " " << transType << ": ";
}//end display

//----------------------------------------------------------------------------
// Create
// creates new transaction object for factory
//
Transaction * Transaction::create() {
	return new Transaction();
}//end create

//----------------------------------------------------------------------------
// Get Media Type
// @return mediaType
//
string Transaction::getMediaType() { 
	return mediaType; 
}//end getMediaType

//----------------------------------------------------------------------------
// Get Transaction Type
// @return transType
//
string Transaction::getTransactionType() { 
	return transType; 
}//end getTransactionType

//----------------------------------------------------------------------------
// get Item
// @return anItem
//
Inventory * Transaction::getItem() const {
	return anItem; 
}//end getItem

