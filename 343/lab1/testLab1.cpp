
 /*================================*
	@file testLab1.cpp
	@author Terence Schumacher
	@version 1.0
 *=================================*/
#include "poly.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#define TEST_SIZE 18
using namespace std;



 /** Main
 */
int main(int argc, char* argv[]){
Poly A(5,7), B(3,4), C(2), D(A), X, Y;
  Poly A2, B2, Z1, Z2;

  // set polynomials A and B to desired values
  // A = +5x^7 -4x^3 +10x -2
  // B = +3x^4 +1x^3 
  //cout << "Enter terms for polynomial A.  Enter a coefficient " << endl
  //     << "then exponent for each term. Enter -1 -1 to terminate." << endl;
  //cin >> A;                                     // or use a bunch of setCoeff
  //cout << "Enter terms for polynomial B.  Enter a coefficient " << endl
  //     << "then exponent for each term. Enter -1 -1 to terminate." << endl;
  //cin >> B;                                     // or use a bunch of setCoeff
		A.setCoeff(5, 7);
		A.setCoeff(-4, 3);
		A.setCoeff(10, 1);
		A.setCoeff(-2, 0);
		
		B.setCoeff(3, 4);
		B.setCoeff(1, 3);
  // outputs exactly what is in quotes: "A = +5x^7 -4x^3 +10x -2"
  cout << "A =" << A << endl;
  // outputs exactly what is in quotes: "B = +3x^4 +1x^3"
  cout << "B =" << B << endl << endl;

  A2 = A;
  B2 = B;
  C = A + B;  
  cout << "Compute C = A + B: " << C << endl << endl;

  cout <<  ( (A == B) ? "A == B" : "A is not == B" ) << endl;
  cout <<  ( (A != B) ? "A is not == B" : "A == B" ) << endl << endl;

  Z1 = A2 - B2;
  cout << "Compute  Z1 = A2 - B2: " << Z1 << endl;
  Z2 = B2 - A2;
  cout << "Compute  Z2 = B2 - A2: " << Z2 << endl << endl;

  cout << "Compute  D = A * B - 15" << endl;
  cout << "Before: D =" << D << endl;
  D = A * B - 15;
  cout << "After:  D =" << D << endl << endl;

  cout << "Test assignment operators" << endl;
  X = C = D = D;  
  Y += A -= B *= A;
  cout << "X =" << X << endl;
  cout << "Y =" << Y << endl << endl;

  cout << "Get and Set coefficient" << endl;
  int coeff = D.getCoeff(0); 
  cout << "coeff of subscript 0 of D is: " << coeff << endl;
  cout << "Doing getCoeff for term -20000" << endl;
  coeff = D.getCoeff(-20000);              // handle value out of range
  D.setCoeff(50,0);                        // set x^0 coeff to 50
  D.setCoeff(50,20000);                    // set x^20000 coeff to 50
  cout << "D =" << D << endl << endl;

/*
  cout << "And now for my tests... " << endl << endl;

  Poly testPoly(8, TEST_SIZE);

  for (int i = 0; i < TEST_SIZE; i++)
	  testPoly.setCoeff(rand() % 100, rand() % 100);

  cout << "Test Poly: " << testPoly << endl;

  D = testPoly + A - B2;

  cout << "New D: " << D << endl;*/

	getchar();
	getchar();
	getchar();
	return 0;

}//end main

