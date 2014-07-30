
/**-----------------------------------------------------------------------* 
 * 	@file classic.cpp
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/


#include "classic.h"

//----------------------------------------------------------------------------
// Constructor
// default constructor for classic movie object
 //
ClassicMovie::ClassicMovie() : Movie(), actorFName(""), actorLName(""), 
							   month(0), GENRE("CLASSIC"){ 
}//end constructor

//----------------------------------------------------------------------------
// Copy Constructor
// copies an existing classicMovie object to a newly created classicMovie
// object.
//
ClassicMovie::ClassicMovie(const ClassicMovie& rightSide){
	director = rightSide.director;
	title = rightSide.title;
	actorFName = rightSide.actorFName;
	actorLName = rightSide.actorLName;
	month = rightSide.month;
	year = rightSide.year;
}// end copy constructor

//----------------------------------------------------------------------------
// Destructor
// Deallocates dynamically allocated memory back to the heap
//
ClassicMovie::~ClassicMovie() {}//end destructor

//----------------------------------------------------------------------------
// setData
// Sets the data of a classicMovie object to the data read in from the 
// istream.
// @pre istream must be valid
// @param infile istream information about specific classic movie object
//
void ClassicMovie::setData(istream& infile) {
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
	infile >> actorFName >> actorLName;
	infile >> month >> year;
}// end setData

//----------------------------------------------------------------------------
// set Data 2
// process transaction data setting. This istream is in a  different format 
// than istream containing movie data.
// @pre istream must be valid
// @param infile istream containing data read in
//
void ClassicMovie::setData2(istream& infile) {
	infile >> month;
	infile >> year;
	infile >> actorFName;
	infile >> actorLName;

}//end setData2

//----------------------------------------------------------------------------
// display
// displays the classic movie object's information
//
void ClassicMovie::display() const {
	
	cout << left << setw(22) << title << " "
		 << setw(18) << director << " "
		 << setw(3) << month << " "
		 << setw(5) << year << " "
		 << actorFName << " " << actorLName << endl;
}//end display

//----------------------------------------------------------------------------
// display Header
// displays specific header for classic movie object.
//
void ClassicMovie::displayHeader() const {
	cout << "IN/OUT *TITLE*                *DIRECTOR*         *MO**YEAR* " <<
		"*ACTOR* " << endl;
	cout <<
	"---------------------------------------------------------------------"
		<< endl;
}//end displayHeader

//----------------------------------------------------------------------------
// operator ==
// overloaded == operator for classic movie types
// @param rightSide the right side of bool comparison
// @return true if they are the same, false otherwise
//
 bool ClassicMovie::operator==(const Inventory& rightSide) const{
	//cast Inventory down to ClassicMovie
	const ClassicMovie& aClassic = static_cast<const ClassicMovie&>(rightSide);

	return (year == aClassic.year && month == aClassic.month
		&& actorFName == aClassic.actorFName &&
		actorLName == aClassic.actorLName);
}//end operator ==

//----------------------------------------------------------------------------
// operator <
// overloaded < operator for classic movie types
// @param rightSide the right side of the bool comparison
// @return true if left side less than, false otherwise
//
 bool ClassicMovie::operator<(const Inventory& rightSide) const {
	const ClassicMovie& aClassic = static_cast<const ClassicMovie&>
																(rightSide);

	if (year < aClassic.year)
		return true;
	else if (year == aClassic.year){
		if (actorFName < aClassic.actorFName)
		{
			return true;
		}
		else if (actorFName == aClassic.actorFName)
		{
			return (actorLName < aClassic.actorLName);
		}
		else
			return false;
	}
	else
		return false;
}//end operator<

//----------------------------------------------------------------------------
// Create
// creates new classic movie object for Inventory factory
//
Inventory * ClassicMovie::create() { 
	return new ClassicMovie(); 
}//end create

