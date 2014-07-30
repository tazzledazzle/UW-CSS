
  /**=================================
	@file NodeData.cpp
	@author Terence Schumacher
	@author Dominic Badzik
	@version 1.1
*===================================*/

#include "NodeData.h"

using namespace std;

 /** Constructor
 */
NodeData::NodeData(){

	stringValue.frequency = 0;
	stringValue.item = "";

	intValue.item = -1;
	intValue.frequency = 0;

}//end constructor

 /** Copy Constructor
 */
NodeData::NodeData( NodeData& rightHandSide){

	stringValue.frequency = rightHandSide.stringValue.frequency;
	stringValue.item = rightHandSide.stringValue.item;

	intValue.item = rightHandSide.intValue.item;
	intValue.frequency = rightHandSide.intValue.frequency;

}//end copyConstructor


 /** Copy Constructor
 */
NodeData::NodeData( NodeData * rightHandSide){

	stringValue.frequency = rightHandSide->stringValue.frequency;
	stringValue.item = rightHandSide->stringValue.item;

	intValue.item = rightHandSide->intValue.item;
	intValue.frequency = rightHandSide->intValue.frequency;

}//end copyConstructor


NodeData::NodeData(int newInteger){
	stringValue.frequency = 0;
	stringValue.item = "";	
	
	intValue.item = newInteger;
	intValue.frequency = 1;

}//end constructor


NodeData::NodeData(string newString){
	stringValue.frequency = 1;
	stringValue.item = newString;	
	
	intValue.item = -1;
	intValue.frequency = 0;

}//end constructor

NodeData::NodeData(int newInteger, string newString){
	stringValue.frequency = 1;
	stringValue.item = newString;	
	
	intValue.item = newInteger;
	intValue.frequency = 1;


}


	/** < operator
		@brief comparison of less than
		@return true if less than, false otherwise
	*/
	bool NodeData::operator<(NodeData * rightHandSide){
	return (this->intValue.item < rightHandSide->intValue.item);
	}//end operator<

