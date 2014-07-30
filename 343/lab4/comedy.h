
/**-----------------------------------------------------------------------* 
 * 	@file comedy.h
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/


#ifndef _COMEDYMOVIE_H_
#define _COMEDYMOVIE_H_
#include "movie.h"


//----------------------------------------------------------------------------
// Class: ComedyMovie
// child class of movie class, granchild of inventory class. 
//----------------------------------------------------------------------------
// 
//

class ComedyMovie : public Movie {
public: 
	ComedyMovie();
	ComedyMovie(const ComedyMovie& );
	~ComedyMovie();//end destructor

	virtual void display() const;
	virtual void displayHeader() const;
	virtual void setData(istream& );
	virtual void setData2(istream& );
	virtual bool operator==(const Inventory& ) const;
	virtual bool operator<(const Inventory& ) const;
	virtual Inventory * create(); //end create
private:
	const string GENRE;
};



#endif

