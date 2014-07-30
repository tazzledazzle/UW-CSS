/**-----------------------------------------------------------------------* 
 * 	@file drama.h
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/


#ifndef _DRAMAMOVIE_H_
#define _DRAMAMOVIE_H_
#include "movie.h"


//----------------------------------------------------------------------------
// Class: DramaMovie
// child of movie class, grandchild of inventory class. Holds data contained
// about specific drama movie items. 
//
//----------------------------------------------------------------------------
// 
//

using namespace std;

class DramaMovie : public Movie {
public: 
	DramaMovie();
	DramaMovie(const DramaMovie& ); //end copy constructor
	~DramaMovie(); //end destructor


	virtual void display() const;
	virtual void displayHeader() const;
	virtual void setData(istream& );
	virtual void setData2(istream&);
	virtual bool operator==(const Inventory& ) const;
	virtual bool operator<(const Inventory& ) const;
	virtual Inventory * create(); //end create

private:
	const string GENRE;	//set to drama
};


#endif

