
 /*================================*
	@file poly.cpp
	@author Terence Schumacher
	@version 2.0
 *=================================*/

#include "poly.h"

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


 //---------------------------------------------------------------------------
 // operator<<
 // overloaded <<: outputs the values stored in the coeffPtr in the appro-
 // priate polynomial order (ex. x^2 + x + 1). Will not print values of 
 // coefficient of zero.
 // @param output the output stream entered to output to
 // @param basePolynomial the poly class to output
ostream& operator<<(ostream& output, const Poly& basePolynomial){
		int temp = 0;
	for (int index = basePolynomial.getSize()-1; index >= 0; index--){
		temp = basePolynomial.coeffPtr[index];
		if(temp != 0){
			output << " ";
			if (temp > 0){
				output << "+";
			}
			
			output << temp; 
		
		if (index == 0){
			//output no x
		}	
		else if (index > 1){
			output << "x^";
			output << index;
		}
		else{
				output << "x";
				//output << " ";
			}// end if index greater than 0
		}//end if not equal 0
	}//end for
	//if (basePolynomial.coeffPtr[1] != 0){
	//output << " ";
	//if (basePolynomial.coeffPtr[1] > 0){
	//	output << "+";
	//	}
	//output << basePolynomial.coeffPtr[1];
	//output << "x";
	//}
	//if (basePolynomial.coeffPtr[0] != 0){
	//output << " ";
	//if (basePolynomial.coeffPtr[0] > 0){
	//	output << "+";
	//}
	//output << basePolynomial.coeffPtr[0];
	//}
	output << endl;
	return output;
}//end operator<<

 //---------------------------------------------------------------------------
 // operator>>
 // overloaded >>: takes 2 ints as coefficient and degree of poly, exits on 
 // a -1 -1 input. power cannot be negative
 // @param input input stream writing to
 // @param basePolynomial polynomial writing to
istream& operator>>(istream& input, const Poly& basePolynomial){

	 while (!input.eof()){
		 int tempCoeff = 0, tempPower = 0;
	 input >> tempCoeff >> tempPower;

	if (tempPower < 0 )
		break;

	basePolynomial.coeffPtr[tempPower] = tempCoeff;
	 }//end while
	 return input;

}//end operator>>

 //---------------------------------------------------------------------------
 // Poly()
 // constructor: Default Constructor
 // default constructor for poly class
//Poly::Poly() : coeffPtr(NULL), polyPowSize(0)
//{
//	
//}//end constructor

 //---------------------------------------------------------------------------
 // Poly(int)
 // constructor: Single Coefficient Constructor
 // constructor with one coefficient entered into the x^0 cell
 //	@param newCoeff coefficient entered into the 0 cell
 //
//Poly::Poly(int newCoeff)
//{
//		polyPowSize = 1;
//	coeffPtr = new int[polyPowSize];
//
//	coeffPtr[0] = newCoeff;
//
//}//end constructor

 //---------------------------------------------------------------------------
 // Poly(int, int)
 // constructor: Full constructor
 // specified constructor with coefficient entered at designated cell location
 // @param newCoeff coefficient value entered
 // @param newPower power of entered coefficient coordinated with appropriate 
 //					cell location
Poly::Poly(const int newCoeff, const int newPower): coeffPtr(NULL), 
	polyPowSize(0) {

	if (newPower > 0 || newCoeff != 0){
	coeffPtr = new int[newPower+1];
	for (int i = 0; i < newPower+1; i++)
		coeffPtr[i] = 0;

	polyPowSize = newPower+1;
	coeffPtr[newPower] = newCoeff;
	}//end if 

}//end constructor

 //---------------------------------------------------------------------------
 // Poly(Poly&)
 // Copy Constructor
 // Copies the contents of a Poly object to a newly created Poly object
 // @param rightHandSide the Poly object copying from 
 //
Poly::Poly(const Poly& rightHandSide){
	
	polyPowSize = rightHandSide.polyPowSize;
	coeffPtr = new int[polyPowSize];
	
	for (int index = 0; index < polyPowSize; index++)
		coeffPtr[index] = rightHandSide.coeffPtr[index];

}//end copy constructor

 //---------------------------------------------------------------------------
 // ~Poly
 // Destructor: deallocates memory allocated by Poly object class
 //
Poly::~Poly(){
	polyPowSize = 0;
	delete [] coeffPtr;
	coeffPtr = NULL;

}//end destructor

 //---------------------------------------------------------------------------
 // IsEmpty()
 // is empty: verifies whether or not the coeffPtr, storing all of the coeffi-
 //			  cients, is equal to null or not
 //	@return true if coeffPtr == NULL, false otherwise
 //
bool Poly::isEmpty(){
	
	return (coeffPtr == NULL) && (polyPowSize == 0);

}//end isEmpty

 //---------------------------------------------------------------------------
 // SetArrValues(int*, int*, int)
 // set Array Values: sets values from one array into another
 // @param array1 array assigning values to
 // @param array2 array assigning values from
 // @param size number of assignments desired
 // Note: This is to to modularize code blocks but hasn't been implemented
 //		  fully yet.
 //
void setArrValues(int * array1, int * array2, int size){
	for (int index = 0; index < size; index++){
		array1[index] = array2[index];			
	}//end for

}//end setArrValues

 //---------------------------------------------------------------------------
 // getCoeff(int)
 // get coeff: returns the coefficient stored in the powerIndex of coeffPtr
 // @param powerIndex the cell index querying, if empty or out of bounds
 //					  return -404
 //	@return coefficient located at index, -404 if empty
 //
int Poly::getCoeff(int powerIndex){
	if (!isEmpty()){
		
		if ((powerIndex <= polyPowSize) && (powerIndex >= 0))
			return coeffPtr[powerIndex];
		else {
			//cout << "Out of Bounds!" << endl;
			return -404;
		}//end if
	} 
	else
		return -404;
}//end getCoeff

 //---------------------------------------------------------------------------
 // getSize()
 // get size: returns the size of the array stored in coeffPtr
 // @return integer representing the number of cells in the coeffPtr array, 0 
 //			if empty
 //
int Poly::getSize() const {
	return polyPowSize;
}//end getSize

 //---------------------------------------------------------------------------
 // setCoeff(int, int)
 // set coefficient: sets a new polynomial coefficient with specified power
 // @param coefficient number entere d in at power cell index within coeffPtr
 // @param power cell index coefficient sits at in coeffPtr
 //
void Poly::setCoeff(int coefficient, int power){
	
	if (power >= 0) //Only perform if value in range
	{
		//checks to see whether to increase array size
		if ((power+1) > polyPowSize) 
		{
			int *temp = new int[power+1]; //Create new array
			
			setArrValues(temp, coeffPtr, polyPowSize);

			for (int i = 0; i < polyPowSize; i++)
				temp[i] = coeffPtr[i]; 

			for (int j = polyPowSize; j < (power+1); j++)
				temp[j] = 0;
			//set coeff value in specified location
			temp[power] = coefficient; 
			
			delete [] coeffPtr; 
			coeffPtr = NULL;
			coeffPtr = temp; 
			temp = NULL; 
			polyPowSize = power + 1; 
		}
		else //less than or equal
			coeffPtr[power] = coefficient; 
	}//end if	
	
}//end setCoeff


 //=======================================================Arithmetic Operators


 //---------------------------------------------------------------------------
 // operator+(Poly)
 // + operator: addes two polynomials together, creating a new polynomial of 
 //				their union
 // @param rightHandSide object located to the right of the + operator, will 
 //			combine with the object to the left of the + operator
 //
Poly Poly::operator+(const Poly& rightHandSide) const {
	
	if (this->polyPowSize > rightHandSide.polyPowSize){
		Poly newPoly(*this);

		for (int i = 0; i < rightHandSide.polyPowSize; i++){
			newPoly.coeffPtr[i] = newPoly.coeffPtr[i] +
					      rightHandSide.coeffPtr[i];
		}//end for
		
		return newPoly;

	} else {
		Poly newPoly(rightHandSide);
		
		for (int i = 0; i < this->polyPowSize; i++){
			newPoly.coeffPtr[i] = newPoly.coeffPtr[i] + 
			                      rightHandSide.coeffPtr[i];
		}//end for
		
		return newPoly;

	}//end if

}//end operator+

 //---------------------------------------------------------------------------
 // operator-(Poly )
 // - operator: subtracts the right hand side object from the left hand side 
 // @param rightHandSide the polynomial subtracting from the base object
 //
Poly Poly::operator-(const Poly& rightHandSide) const {
		
	if (this->polyPowSize < rightHandSide.polyPowSize){
		
		Poly newPoly(rightHandSide);

		for (int i = 0; i < rightHandSide.polyPowSize; i++){
			newPoly.coeffPtr[i] *= -1;//make all values negative
		}//end for
		

		for (int i = 0; i < this->polyPowSize; i++){
			newPoly.coeffPtr[i] = newPoly.coeffPtr[i] + 
			                   this->coeffPtr[i];
		}//end for
		
		return newPoly;

	} else {
		
		Poly newPoly(*this);

		for (int i = 0; i < rightHandSide.polyPowSize; i++){
			newPoly.coeffPtr[i] = newPoly.coeffPtr[i] - 
			                      rightHandSide.coeffPtr[i];
		}//end for
		
		return newPoly;

	}//end if

}//end operator-

 //---------------------------------------------------------------------------
 // operator*(Poly )
 // * operator: multiplies one polynomial by another, returns their product 
 //				in a new polynomial object
 // @param rightHandSide polynomial object multiplied by the base object
 //
Poly Poly::operator*(const Poly& rightHandSide) const{
	
	int leftIndex = (this->polyPowSize -1);
	int rightIndex = (rightHandSide.polyPowSize - 1);
	int combineSize = leftIndex + rightIndex;

	Poly newPoly(0, combineSize);

	for (int i = leftIndex; i >= 0; i--){
		for (int j = rightIndex; j >= 0; j--){
			newPoly.coeffPtr[i + j] += 
				this->coeffPtr[i] * rightHandSide.coeffPtr[j];
		}//end for rightIndex
	}//end for leftIndex

	return newPoly;

}//end operator*

 //---------------------------------------------------------------------------
 // operator=(Poly )
 // = operator: assigns one polynomial's contents to that of another, via the
 //				coeffPtr
 // @param rightHandSide the polynomial's contents that will be assigned
 // 
Poly& Poly::operator=(const Poly& rightHandSide){
	if (&rightHandSide != this){
		delete [] coeffPtr;
		coeffPtr = NULL; 
		polyPowSize = rightHandSide.polyPowSize;
		coeffPtr = new int[polyPowSize];

		for (int i = 0; i < rightHandSide.polyPowSize; i++){
			this->coeffPtr[i] = rightHandSide.coeffPtr[i];
		}//end for
	}//end if
	return *this;
}//end operator=

 //=======================================================Assignment Operators
 
 
 //---------------------------------------------------------------------------
 // operator+=(Poly)
 // += operator: addes two polynomials together, and assigns this polynomial 
 // 				of their union to an existing polynomial object
 // @param rightHandSide object located to the right of the += operator, will 
 //			 combine with the object to the left of the += operator
 //
Poly& Poly::operator+=(const Poly& rightHandSide){


	if (this->polyPowSize >= rightHandSide.polyPowSize){
		for (int i = 0; i < rightHandSide.polyPowSize; i++){
			this->coeffPtr[i] = this->coeffPtr[i] +
					    rightHandSide.coeffPtr[i];
		}//end for
	
	} else {
		int size = rightHandSide.polyPowSize;
		int * temp = new int[size];
		
		for (int i = 0; i < size; i++)
			temp[i] = rightHandSide.coeffPtr[i];
		for (int i = 0; i < this->polyPowSize; i++)
			temp[i] = temp[i] + this->coeffPtr[i];

		delete [] coeffPtr;
		coeffPtr = NULL;

		coeffPtr = temp;
		polyPowSize = size;
	}//end if 
	/**this = *this + rightHandSide;*/
	return *this;

}//end operator+=

 //---------------------------------------------------------------------------
 // operator-=(Poly )
 // -= operator: subtracts the right hand side object from the left hand side 
 // @param rightHandSide the polynomial subtracting from the base object
 //
Poly& Poly::operator-=(const Poly& rightHandSide){
	if (this->polyPowSize >= rightHandSide.polyPowSize){
		for (int i = 0; i < rightHandSide.polyPowSize; i++){
			this->coeffPtr[i] = this->coeffPtr[i] -
						rightHandSide.coeffPtr[i];
		}//end for
	}
	else {
		int size = rightHandSide.polyPowSize;
		int * temp = new int[size];
	
		for (int i = 0; i < size; i++)
			temp[i] = (rightHandSide.coeffPtr[i] * -1);
	
		for (int i = 0; i < this->polyPowSize; i++)
			temp[i] = temp[i] + this->coeffPtr[i];

		delete [] coeffPtr;
		coeffPtr = NULL;

		coeffPtr = temp;
		polyPowSize = size;
	}
	

	//*this = *this - rightHandSide;
	return *this;

}//end operator-=

 //---------------------------------------------------------------------------
 // operator*=(Poly )
 // *= operator: multiplies one polynomial by another, returns their product 
 //				in a new polynomial object
 // @param rightHandSide polynomial object multiplied by the base object
 //
Poly& Poly::operator*=(const Poly& rightHandSide){
	
	*this = *this * rightHandSide;
	return *this;

}//end operator*=


 //=========================================================Equality Operators

 //---------------------------------------------------------------------------
 // operator==(Poly )
 // == operator: test whether one Poly object is equal to another, checking 
 //			   first the size of each coeffPtr, then each value
 //	@param rightHandSide right side of the equality comparison
 //
bool Poly::operator==(const Poly& rightHandSide) const{
	
	if (this->polyPowSize != rightHandSide.polyPowSize){
		return false;
	}//end if size not equal

	 //compare elements until one does not match
	for (int i = 0; i < rightHandSide.polyPowSize; i++){ 
		if (this->coeffPtr[i] != rightHandSide.coeffPtr[i]){
			return false;
		}//end if
	}//end for 	
	
	return true;  // return true if all don't fail
}//end operator==

 //---------------------------------------------------------------------------
 // operator!=(Poly )
 // != operator: test whether one Poly object is equal to another, checking 
 //				 first the size of each coeffPtr, then each value
 //	@param rightHandSide right side of the equality comparison
 //
bool Poly::operator!=(const Poly& rightHandSide) const{
	
	return !(*this == rightHandSide);
}//end operator!=


