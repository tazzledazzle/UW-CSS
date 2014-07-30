
/**-----------------------------------------------------------------------* 
 * 	@file movie.h
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/

#ifndef _MOVIE_H_
#define _MOVIE_H_
#include "inventory.h"

using namespace std;
//----------------------------------------------------------------------------
//  Class: Movie
// child of inventory class, and parent to classic, comedy, and drama. 
//
//----------------------------------------------------------------------------
// 
//

class Movie : public Inventory {

public:
	Movie();	//constructor
	Movie(const Movie& rightSide);
	~Movie();	//destructor

	 virtual void display() const;
	 virtual void displayHeader() const = 0;
	 virtual void setData(istream& infile);
	 virtual void setData2(istream&) = 0;	//addition information to set
	
	 virtual string getItem() const;	//return the inventory item
	 string getDirector(); //returns the director
	 string getTitle();	//returns the title
	 int getYear();		//returns the year

	 //these must be overridden in order to determin sort orders
	 virtual bool operator==(const Inventory&) const = 0;
	 virtual bool operator<(const Inventory&) const = 0;
	 virtual Inventory* create() = 0;

protected:
	string title;		//title of movie
	string director;	//director of movie
	int year;			//year created
	//const string GENRE;

};



#endif

