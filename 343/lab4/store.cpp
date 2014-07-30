
/**-----------------------------------------------------------------------* 
 * 	@file store.cpp
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/


#include "store.h"

//----------------------------------------------------------------------------
// Constructor
// default constructor of store
//
Store::Store() : name("") {
	
}//end constructor

//----------------------------------------------------------------------------
// Name Constructor
// constructor assigning a name to the store, name is necessary for header
// output
// @param aName value defined as store's name
//
Store::Store(string aName) : name(aName) {}//end name Constructor

//----------------------------------------------------------------------------
// Copy Constructor
// unimplemented copy constructor, useful if you wanted to copy the state of 
// a store item at any given point.
// @param rightSide store object copying from
//
Store::Store(const Store& rightSide) {}//end copy constructor

//----------------------------------------------------------------------------
// Destructor
// destructor of store item for proper memory management
//  
Store::~Store() {}//end destructor

//----------------------------------------------------------------------------
// Create Customers
// Creates customer base from istream object and stores in store's customer
// list.
// @pre must be valid istream object
// @param infile istream object reading customer base from
//
void Store::createCustomers(istream& infile){	
	//creates customers from customer textfile

	for (;;){
		Customer* cust = new Customer();
		cust->setData(infile);

		if (infile.eof()){
			delete cust;
			cust = NULL;
			break;
		}//end if
		customerList[cust->getCustomerID()] = *cust;
		delete cust;
		cust = NULL;
	}//end for
}//end createCustomers

//----------------------------------------------------------------------------
// Create Inventory
// Produces Inventory Objects from factory object and stores these objects 
// within the inventoryList. The istream is processed and data is sent to the
// factory for futher processing.
// @pre istream object must be valid before read
// @param infile istream object containing inventory information 
//
void Store::createInventory(istream& infile){		
	//creates inventory from inventory textfile
	char ch = ' ';

	for (;;){
		infile >> ch;

		if (infile.eof()) break;

		Inventory * addedMovie = factory.createMovie(ch, infile);

		if (addedMovie != NULL){
			addedMovie->setData(infile);

			bool inserted = inventoryList[factory.convertToSubscript(ch)]
				.insert(addedMovie, 10);

			if (!inserted){
				delete addedMovie;
				//addedMovie = NULL;
				cout << "Not Inserted" << endl;
			}//end if not inserted
		}//end if
		addedMovie = NULL;
		delete addedMovie;
	}//end for
}//end createInventory

//----------------------------------------------------------------------------
// Process Transactions
// Processes Transactions recorded in the istream object. Customer history and
// store inventory are updated accordingly depending on each transaction item.
// @param infile
//
void Store::processTransactions(istream& infile) {
	char actCh = ' ';
	char movCh = ' ';
	char medCh = ' ';
	int custID = 0;
	bool found = false;
	string mediaType = "";
	char EOL = '\n';
	Inventory * itemLoc = NULL;
	Customer * tempCust = NULL;
	Inventory *  tempItem = NULL;

	for (;;){
		infile >> actCh;
		if (infile.eof()) break; //check for end of file

		if (actCh == 'S'){
			displayInventory();
			actCh = ' ';
		}
		else if (infile.get() == EOL)
			actCh = ' ';
		else {
			Transaction * processedTran = factory
							.createTransaction(actCh, infile);

			if (processedTran != NULL){ //no action code
				infile >> custID;

				if (infile.eof()) break;

				if (lookUpCustomer(custID)){ //customer exists
					tempCust = &customerList[custID];

					bool isHistory = processedTran->
								setData(mediaType, itemLoc, tempCust);

					if (infile.get() != EOL && isHistory){ 
						//not EOL or is history

						infile >> medCh;

						mediaType = factory.getMediaType(medCh);


						if (mediaType != ""){  //movie genre

							infile >> movCh;

							tempItem = factory.createMovie(movCh, infile);

							if (tempItem != NULL){
								tempItem->setData2(infile);

								found = inventoryList[factory.
									convertToSubscript(movCh)].
									retrieve(*tempItem, itemLoc);

								if (found == false)	//if movie not found
								{
									cout << "ERROR: Invalid Movie Request!"
										<< tempItem->getItem() << endl;
								}//end if
								delete tempItem;
								tempItem = NULL;

								bool found2 = processedTran->
									setData(mediaType, itemLoc, tempCust);
		
								if ((found && found2) && mediaType != ""){
									customerList[custID]
										.addTransaction(*processedTran);
									
								}
								delete processedTran;
								processedTran = NULL;
							}
							else{
								cout << "ERROR: " << movCh 
									 << " not Found!" << endl;

								if (processedTran != NULL)
									delete processedTran;
								processedTran = NULL;
							}//end if

							string temp;
							getline(infile, temp, EOL);
							delete tempItem;
							tempItem = NULL;

						}
						else{
							string temp;
							getline(infile, temp, EOL);

							cout << "ERROR: Invalid Code " << medCh << endl;

							if (processedTran != NULL)
								delete processedTran;
							processedTran = NULL;
						}//end if not media type
					}
					else {
						if (processedTran != NULL)
							delete processedTran;
						processedTran = NULL;
					}//end if not EOL and isHistory
				}
				else {
					cout << "Error: Invalid Customer ID " << custID << endl;

					if (processedTran != NULL)
						delete processedTran;
					processedTran = NULL;

					string temp;
					getline(infile, temp, EOL);
				}//end if customer exists
			}
			else {
				cout << "ERROR: Invalid Action Code " << actCh << endl;

				if (processedTran != NULL)
					delete processedTran;
				processedTran = NULL;
			}//end if no action code
		}//end process infile if

		found = false;
		custID = 0;
		itemLoc = NULL;
		tempCust = NULL;
		tempItem = NULL;
	}//end for
}//end processTransaction


//----------------------------------------------------------------------------
// Display
// used for testing purposes. displays all items within store
//
void Store::display() {
	displayCustomerBase();
	displayInventory();
}//end display

//----------------------------------------------------------------------------
// Display Inventory
// Displays all items within in the inventory along with their stock in and
// out.
//
void Store::displayInventory() const {
	if (name != ""){
		cout 
		<< "--------------------------------------------------------------"
		<< endl;
		cout << "Inventory for " << name << endl;
		cout 
		<< "--------------------------------------------------------------"
		<< endl;
	}//end if

	for (int i = 0; i < MAXINVENTORY; i++){
		if (!inventoryList[i].isEmpty()){
			
			inventoryList[i].inorderDisplay(inventoryList[i].getRoot());
		cout << endl;
		}//end if
	}//end for
}//end displayInventory

//----------------------------------------------------------------------------
// Display Customer Base
// Displays the customer base stored within the Store.
// 
void Store::displayCustomerBase() const {
	for (int i = 0; i < MAXCUSTOMERS; i++){
		if (lookUpCustomer(i)){
			getCustomer(i).display();
		}//end if
	}//end for
}//end displayCustomerBase

//----------------------------------------------------------------------------
// lookup Customer
// Checks whether a customer is within the store's customer list by checking 
// if their idnumber is in the list.
// @param IDNumber customer ID number searching the customer list for
// @return true if found, false otherwise
//
bool Store::lookUpCustomer(int IDNumber) const {
	if (customerList[IDNumber].getCustomerID() == -1){
		return false;
	}
	else
		return true;
} //end lookupcustomer

//----------------------------------------------------------------------------
// Get Business Name
// returns the business name
// @return name of business
//
string Store::getBusinessName() const {
	return name;
}//end getBusinessName

//----------------------------------------------------------------------------
// Get Customer
// returns the customer within the list with the ID number passed in as a 
// parameter. 
// @pre IDNumber must not exceed MAXCUSTOMERS
// @param IDNumber potential customer's Id number
// @return Customer object if valid IDNumber, -1 otherwise
Customer Store::getCustomer(const int IDNumber) const {
	return customerList[IDNumber];
}//end getCustomer

