
/**-----------------------------------------------------------------------* 
 * 	@file borrow.cpp
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/


#include "borrow.h"

//----------------------------------------------------------------------------
// Constructor
// default constructor
//
Borrow::Borrow() : Transaction() {
	transType = "Borrow";
} //end constructor

//----------------------------------------------------------------------------
// Copy Constructor
// Constructor copying data from another Borrow type
// @param rightSide the borrow object copying from
//
Borrow::Borrow(const Borrow& rightSide) {
	transType = rightSide.transType;
	mediaType = rightSide.mediaType;
	anItem = rightSide.anItem;
} //end copy constructor

//----------------------------------------------------------------------------
// Destructor
// returning dynamically allocated memory back to the heap
Borrow::~Borrow() {} //end destructor

//----------------------------------------------------------------------------
// Set Data
// sets data of Borrow object
// @param media type of media contained in borrow object
// @param item inventory item contained in borrow object
// @param aCustomer customer object borrowing the item
// @return true no matter what
//
bool Borrow::setData(string media, Inventory * item, Customer * aCustomer){
	if (item != NULL){
		mediaType = media;
		anItem = item;

		if (mediaType != ""){
			anItem->decreaseCopies();
		}//end if

	}//end if 
	return true;
}//end setData

//----------------------------------------------------------------------------
// Display
// displays the mediaType and transaction Type of object
//
void Borrow::display() const{
	cout << mediaType << " " << transType << " ";
}//end display

//----------------------------------------------------------------------------
// Create
// creates a new borrow object for factory
//
Transaction * Borrow::create() {
	return new Borrow();
}//end create

