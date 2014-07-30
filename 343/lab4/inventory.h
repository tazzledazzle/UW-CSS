
/**-----------------------------------------------------------------------* 
 * 	@file inventory.h
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/


#ifndef _INVENTORY_H_
#define _INVENTORY_H_
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//----------------------------------------------------------------------------
// Class: Inventory
// parent class of all items stored within the store. contains all virtual
// and pure virtual methods necessary for transactions as well as setting data
// of child classes.
//
//----------------------------------------------------------------------------
// 
//

class Inventory {
public:
	Inventory(); //constructor
	Inventory(const Inventory&); //copy constructor

	virtual ~Inventory(); //destructor
	virtual void setData(istream& ) = 0; //sets data of inventory itme
	virtual void setData2(istream& ) = 0;	//addition information to set
	virtual void display() const = 0;	//display all data
	virtual void displayHeader() const = 0;
	virtual string getItem() const = 0;	//return the inventory item

	void setMaxCopies(const int);
	void increaseCopies();
	void decreaseCopies();
	int getAmountIn();		//return current stock
	int getAmountOut();		//return current stock

	virtual bool operator==(const Inventory&) const = 0;	
	virtual bool operator<(const Inventory&) const = 0;
	virtual Inventory* create() = 0;
private:
	int stockNumber;
	int maxStock;

};

#endif


