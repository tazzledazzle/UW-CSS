
/**-----------------------------------------------------------------------* 
 * 	@file return.cpp
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/


#include "return.h"

//----------------------------------------------------------------------------
// Constructor
// default constructor
Return::Return() : Transaction() {
	transType = "Return";
}//end constructor

//----------------------------------------------------------------------------
// Copy Constructor
// copies data from rightSide object into newly created return object
// @param rightSide object copying data from
//
Return::Return(const Return& rightSide){
	mediaType = rightSide.mediaType;
	transType = rightSide.transType;
	anItem = rightSide.anItem;
} //end copy constructor

//----------------------------------------------------------------------------
// Destructor
// deallocates dynamically allocated memory and returns it to the heap
//
 Return::~Return(){
 }//end destructor

//----------------------------------------------------------------------------
// Set Data
// sets data of the return object from existing inventory item and customer
// @param media mediaType of object
// @param item inventory item returning
// @param aCustomer the customer who is returning the item
// @return true
//
bool Return::setData(string media, Inventory * item, Customer * aCustomer) {

	if (item != NULL){
		mediaType = media;
		anItem = item;

		if (mediaType != "")
			anItem->increaseCopies();
	}//end if
	return true;
}//end setData

//----------------------------------------------------------------------------
// Display
// displays media type and transaction type
//
void Return::display() const{
	cout << mediaType << " " << transType << " ";
} //end display

//----------------------------------------------------------------------------
// Create
// creates new return object for factory
//
Transaction * Return::create() { 
	return new Return(); 
} //create new return object
