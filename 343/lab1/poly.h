
 /*================================*
	@file poly.h
	@author Terence Schumacher
	
	@version 1.0
 *=================================*/

#ifndef _POLY_H
#define _POLY_H
#include <iostream>

using namespace std;
 //---------------------------------------------------------------------------
 // Poly class: a array-based implementation of a polynomial. Representation 
 // of said polynomial is as follows:
 //   -- coordinating indexes of the array with powers of polynomial
 //   -- each polynomial's coefficient coordinates with the index in the array
 //   -- coefficients of zero will not display on output
 // Examples of polynomials: x^2 + 2x + 1, 4x, x^12 - 47x^3.
 // Implementation and Assumptions:
 //		-- for output a coefficient is necessary
 //		-- in order for any operators to work, a polynomial needs to have 
 //			at least one coefficient stored in a Poly coeffPtr
//---------------------------------------------------------------------------

class Poly {
protected:
	// overloaded <<: outputs the values stored in the coeffPtr in the appro-
	// priate polynomial order (ex. x^2 + x + 1). Will not print values of 
	// coefficient of zero.
	friend ostream& operator<<(ostream&, const Poly&);
    
    // overloaded >>: takes 2 ints as coefficient and degree of poly, exits on 
	// a -1 -1 input. power cannot be negative
	friend istream& operator>>(istream&, const Poly&);
private:
	int * coeffPtr;				//storage space for poly 
	int polyPowSize;			//size of coeffPtr array

public:
	//Poly();						//empty constructor
	//Poly(int);					//constructor with one initial coeff
	Poly(int coefficient = 0, int power = 0);				//constructor with one initial polynomial
	Poly(const Poly&);			//copy constructor 
	~Poly();					//destructor

	bool isEmpty();				//checks coeff for values
	int getCoeff(int);			//returns coeff at location passed in
	void setCoeff(int, int);	//sets coeff and power within coeffPtr
	int getSize() const;
 
//========================================================Arithmetic Operators

	Poly operator+(const Poly& ) const;		//add two polynomials
	Poly operator-(const Poly& ) const;			//subtract two polynomials
	Poly operator*(const Poly& ) const;		//multiply two polynomials
	Poly& operator=(const Poly& );			//assign a poly to another

//========================================================Assignment Operators
	Poly& operator+=(const Poly& );			//current object += the parameter
	Poly& operator-=(const Poly& );			//current object -= the parameter
	Poly& operator*=(const Poly& );			//current object *= the parameter

//==========================================================Equality Operators
	bool operator==(const Poly& ) const;	//is object == to the parameter?
	bool operator!=(const Poly& ) const;	//is object != to the parameter?

};

//#include "poly.cpp"

#endif

