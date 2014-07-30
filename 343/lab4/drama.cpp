
/**-----------------------------------------------------------------------* 
 * 	@file drama.cpp
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/

#include "drama.h"
//----------------------------------------------------------------------------
// Constructor
// default constructor 
//
DramaMovie::DramaMovie() : Movie(), GENRE("DRAMA") { 
}//end constructor

//----------------------------------------------------------------------------
// Copy Constructor
// copies information about right side object to newly created drama movie 
// object.
//
DramaMovie::DramaMovie(const DramaMovie& rightSide) {
	title = rightSide.title;
	director = rightSide.director;
	year = rightSide.year;
} //end copy constructor

//----------------------------------------------------------------------------
// Destructor
// Deallocates dynamically allocated memory back to the heap
//
DramaMovie::~DramaMovie() {}//end destructor

//----------------------------------------------------------------------------
// display
// displays the title, year, month, director, and actor for specific movie
//
void DramaMovie::display() const { 
	cout << left << setw(22) << title << " "
		 << setw(18) << director << " "
		<< setw(5) << year << endl;
}//end display

//----------------------------------------------------------------------------
// display Header
// displays specific drama movie header for object
//
void DramaMovie::displayHeader() const {
	cout << "IN/OUT *TITLE*                *DIRECTOR*         *YEAR*  " <<
	endl;
	cout <<
	"---------------------------------------------------------------------"
		<< endl;
}//end displayHeader

//----------------------------------------------------------------------------
// set Data
// sets data within the drama movie object read in from istream object
// @pre istream object must be valid
// @param infile istream object reading data from
//
void DramaMovie::setData(istream& infile) {
	infile.get();
	getline(infile, director, ',');

	infile.get();
	getline(infile, title, ',');

	infile.get();
	infile >> year;

} //end setData

//----------------------------------------------------------------------------
// set Data 2
// process transaction data setting method. This is used because transaction
// istream object of a different format than inventory istream object.
// @pre istream object must be valid
// @param infile istream object reading from
//
void DramaMovie::setData2(istream& infile) {
	infile.get();
	getline(infile, director, ',');

	infile.get();
	getline(infile, title, ',');
}//end setData2

//----------------------------------------------------------------------------
// operator ==
// overloaded == operator tests equality in two drama movie objects
// @param rightSide object testing equality against
// @return true if equal, false otherwise
//
bool DramaMovie::operator==(const Inventory& rightSide) const{
	//cast Inventory down to DramaMovie
	const DramaMovie& aDrama = static_cast<const DramaMovie&>(rightSide);

	return (title == aDrama.title && director == aDrama.director);
} //end operator==

//----------------------------------------------------------------------------
// operator <
// overloaded < operator tests less than in two drama movie objects
// @param rightSide object testing less than against
// @return true if less than, false otherwise
//
 bool DramaMovie::operator<(const Inventory& rightSide) const {
	const DramaMovie& aDrama = static_cast<const DramaMovie&>(rightSide);

	if (director < aDrama.director){
		return true;
	}
	else if (director == aDrama.director){
		return (title < aDrama.title);
	}
	else
		return false;
}// end operator <

//----------------------------------------------------------------------------
// create
// creates new drama movie object for factor
//
 Inventory * DramaMovie::create() {
	 return new DramaMovie(); 
 }//end create

