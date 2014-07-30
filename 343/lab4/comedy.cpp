
/**-----------------------------------------------------------------------* 
 * 	@file comedy.cpp
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/

#include "comedy.h"

//----------------------------------------------------------------------------
// Constructor
// default constructor
ComedyMovie::ComedyMovie() : Movie(), GENRE("COMEDY") { 
}//end constructor

//----------------------------------------------------------------------------
// Copy constructor
// copies the contents of rightSide to a newly created comedyMovie object
// @param rightSide right side object copying from
// 
ComedyMovie::ComedyMovie(const ComedyMovie& rightSide){
	title = rightSide.title;
	year = rightSide.year;
	director = rightSide.director;
} //end copy constructor

//----------------------------------------------------------------------------
//  Destructor
// Deallocates dynamically allocated memory back to the heap
//
ComedyMovie::~ComedyMovie() {}//end destructor

//----------------------------------------------------------------------------
// Display
// displays the title, year, month, director, and actor for specific movie
//
void ComedyMovie::display() const { 	
	cout << left << setw(22) << title << " "
		 << setw(18) << director << " "
		 << setw(5) << year << endl;
}//end display

//----------------------------------------------------------------------------
// Display Header
// displays specific header for comedy movie type
//
void ComedyMovie::displayHeader() const {
	cout << "IN/OUT *TITLE*                *DIRECTOR*         *YEAR*  " 
		<< endl;
	cout <<
	"---------------------------------------------------------------------"
		<< endl;
}//end displayHeaders

//----------------------------------------------------------------------------
// Set Data
// Sets the data for the comedy movie object from the istream parameter
// @pre istream object must be valid
// @param infile istream object pulling data from
//
void ComedyMovie::setData(istream& infile) {
	infile.get();
	getline(infile, director, ',');
	if (director.size() > 18){
		title.resize(18);	
	}//end if

	infile.get();
	getline(infile, title, ',');
	if (title.size() > 22){
		title.resize(22);	
	}//end if
	
	infile.get();
	infile >> year;
}// end setData

//----------------------------------------------------------------------------
// Set Data
// process transaction set data for inventory item contained. This istream 
// object is formatted differently than previous object.
// @pre istream object must be valid
// @param infile istream object reading data in from
//
void ComedyMovie::setData2(istream& infile) {
	infile.get();
	getline(infile, title, ',');

	infile >> year;

}//end setData2

//----------------------------------------------------------------------------
// Operator ==
// overloaded == operator tests equality between two comedy movie objects
// @param movieItem right hand side of equality operation
// @return true if equal, false otherwise
//
bool ComedyMovie::operator==(const Inventory& movieItem) const {
	//static cast down to ComedyMovie
	const ComedyMovie& aComedy = static_cast<const ComedyMovie&>(movieItem);
	return (title == aComedy.title && year == aComedy.year);
}//end operator ==

//----------------------------------------------------------------------------
// Operator <
// overloaded < tests less than between two comedy movie objects
// @param movieItem right hand side of less than operation
// @return true if less than, false otherwise
//
bool ComedyMovie::operator<(const Inventory& movieItem) const {
	//static cast down to ComedyMovie
	const ComedyMovie& aComedy = static_cast<const ComedyMovie&>(movieItem);

	if (title < aComedy.title)
		return true;
	else if (title == aComedy.title){
		return (year < aComedy.year);
	}
	else
		return false;
}//end operator <

//----------------------------------------------------------------------------
// Create
// create new comedy movie object for factory
//
Inventory * ComedyMovie::create() { 
	return new ComedyMovie();
}//end create

