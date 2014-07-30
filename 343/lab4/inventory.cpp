
/**-----------------------------------------------------------------------* 
 * 	@file inventory.cpp
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/


#include "inventory.h"

//----------------------------------------------------------------------------
// Constructor
// default constructor
//
Inventory::Inventory() : stockNumber(-1), maxStock(0){} //end constructor

//----------------------------------------------------------------------------
// Copy Constructor
// copies information from rightSide into the newly created inventory item
// 
Inventory::Inventory(const Inventory& rightSide) {} //end copy constructor

//----------------------------------------------------------------------------
// Destructor
// deallocates dynamically allocated memory and returns it to the heap
//
 Inventory::~Inventory() {} //end destructor

//----------------------------------------------------------------------------
// Set Max Copies
// sets the maximum copies of a specific inventory item
// @param maxCopies number of the max of the stock
//
void Inventory::setMaxCopies(const int maxCopies) {
	maxStock = maxCopies;

	if (stockNumber < 0)
		stockNumber = maxCopies;
}//end setMaxCopies

//----------------------------------------------------------------------------
// Increase Copies
// increase stock 
//
void Inventory::increaseCopies() {
	if (stockNumber != maxStock)
		stockNumber++;
}//end increaseCopies

//----------------------------------------------------------------------------
// Decrease Copies
// decreases stock
//
void Inventory::decreaseCopies() {
	if (stockNumber != 0)
		stockNumber--;
}//end decreaseCopies

//----------------------------------------------------------------------------
// Get Amount In
// return current stock
// @return integer representing stock available
//
int Inventory::getAmountIn() { 
	return stockNumber; 
}//end getAmountIn

//----------------------------------------------------------------------------
// Get Amount Out
// return the number of borrowed items
// @return integer representing stock out
//
int Inventory::getAmountOut() { 
	return maxStock - stockNumber; 
}//end getAmountOut

