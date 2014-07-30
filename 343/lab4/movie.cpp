
/**-----------------------------------------------------------------------* 
 * 	@file movie.cpp
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/


#include "movie.h"

//----------------------------------------------------------------------------
// Constructor
// default constructor
//
Movie::Movie() : Inventory(), title(""), director(""), year(0) {
}//end constructor

//----------------------------------------------------------------------------
// Copy Constructor
// copies data from rightSide object into newly created movie object
// @param rightSide movie object copying from
//
Movie::Movie(const Movie& rightSide){
	title = rightSide.title;
	director = rightSide.director;
	year = rightSide.year;
}//end copy constructor

//----------------------------------------------------------------------------
// Destructor
// deallocates dynamically allocated memory and returns it to the heap
//
Movie::~Movie(){
}//end destructor

//----------------------------------------------------------------------------
// Display
// displays the title, year, month, director, and actor for specific movie
//
void Movie::display() const { 
	cout << title << " " << director
		<< " "
		<< year
		<< endl;
}//end display

//----------------------------------------------------------------------------
// Set Data
// sets data for specific movie object from istream object parameter
// @pre infile must be valid
// @param infile istream object reading data from
//
void Movie::setData(istream& infile) {
	infile.get();
	getline(infile, director, ',');

	infile.get();
	getline(infile, title, ',');

	infile.get();
	infile >> year;
} //end setData

//----------------------------------------------------------------------------
// Display Header
//
void Movie::displayHeader() const {
	cout << " ****** MOVIE ITEM ***** "
		 << endl;
}	//end displayHeader

//----------------------------------------------------------------------------
// Get Item
// returns the title of movie
// @return title
//
string Movie::getItem() const {
	return title; 
}//end getItem

//----------------------------------------------------------------------------
// Get Director
// returns the director of movie
// @return director
//
string Movie::getDirector() { 
	return director; 
} //end getDirector

//----------------------------------------------------------------------------
// Get Title
// returns the title of the movie
// @return title
//
string Movie::getTitle() { 
	return title;
}//end getTitle

//----------------------------------------------------------------------------
// Get Year
// returns the year
// @return year
//
int Movie::getYear() {
	return year; 
}//end getYear
