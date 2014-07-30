
/**-----------------------------------------------------------------------* 
 * 	@file classic.h
 *	@author Terence Schumacher
 *	lab4
--------------------------------------------------------------------------*/

#ifndef _CLASSICMOVIE_H_
#define _CLASSICMOVIE_H_
#include <string>
#include "movie.h"


//----------------------------------------------------------------------------
// Class: ClassicMovie
// child class of movie class, granchild of inventory class. 
//----------------------------------------------------------------------------
// 
//

class ClassicMovie : public Movie {

public:
	ClassicMovie();
	ClassicMovie(const ClassicMovie& rightSide);
	~ClassicMovie();

	void setData(istream& infile);
	virtual void setData2(istream& infile);
	void display() const;
	virtual void displayHeader() const;
	virtual bool operator==(const Inventory& rightSide) const;
	virtual bool operator<(const Inventory& rightSide) const;
	virtual Inventory * create();
private:
	string actorFName, actorLName;
	int month;
	const string GENRE;
};


#endif
