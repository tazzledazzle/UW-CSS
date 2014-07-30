/** 
	@file SortSetArray.cpp
	@version 1.3
*/

#include "SortSetArray.h"
#define DUP_ERROR "ERROR: Duplicate Entry"	
#define ARR_OUT_ERROR "ERROR: Array Out of Bounds"
#define CONFIRM_ENTRY " FOUND. Is in Set!"
#define DENIED_ENTRY " NOT FOUND. Not in Set!"

using namespace std;

void SortSetArray::clear(){
	for (int index = 0; index < MAX_FIB; index++)
	set[index] = false;
	
	
	ItemCount = 0;

}//end setFalse
 SortSetArray::SortSetArray() : ItemCount(0)
{
	clear();

 }//end constructor

 SortSetArray::SortSetArray(const int& firstValue, const int& secondValue, 
	 const int& thirdValue, const int& fourthValue, const int& fifthValue): ItemCount(0)
 {
	 clear();

	insert(firstValue);
	insert(secondValue);
	insert(thirdValue);
	insert(fourthValue);
	insert(fifthValue);
 
 }//end constructor

 
 SortSetArray::SortSetArray(const int& firstValue, const int& secondValue, 
	 const int& thirdValue, const int& fourthValue): ItemCount(0){
 
	clear();

	insert(firstValue);
	insert(secondValue);
	insert(thirdValue);
	insert(fourthValue);
 
 
 }//end constructor

 
 SortSetArray::SortSetArray(const int& firstValue, const int& secondValue, 
	 const int& thirdValue): ItemCount(0){
	
	clear();

	insert(firstValue);
	insert(secondValue);
	insert(thirdValue);
 
 }//end constructor

 
 SortSetArray::SortSetArray(const int& firstValue, const int& secondValue): ItemCount(0){
 
	clear();

	insert(firstValue);
	insert(secondValue);

 }//end constructor

 SortSetArray::SortSetArray(const int& firstValue): ItemCount(0){
 
	clear();
	insert(firstValue);

 }//end constructor
 
 SortSetArray::SortSetArray(const SortSetArray& baseArray): ItemCount(0){
	
	 if (baseArray.ItemCount > 0){
		for (int index = 0; index < MAX_FIB; index++){
		 
			if (baseArray.set[index] == true)
			insert(index);

		}//end for
	 }//end if
 
 }//end copy Constructor

 /** is Empty
	@brief checks the size of the array
	@return true if size == 0, false otherwise
*/
bool SortSetArray::isEmpty(){
	
	return (ItemCount == 0);
}//end isEmpty

/** Insert
*/
bool SortSetArray::insert(const int& insertedValue){

	if ((insertedValue < (MAX_FIB - 1) ) && (insertedValue >= 0)){

		if (this->set[insertedValue] != true){

		this->set[insertedValue] = true;
		ItemCount++;
		return true;
		}
		else{

			cout << DUP_ERROR << endl;
			return false;
		}//end if != true
	}
	else 
	{
		cout << ARR_OUT_ERROR << endl;
		return false;

	}//end if 

}//end insert

/** Is In Set
*/
bool SortSetArray::isInSet(const int& checkKey){
	if (isEmpty())
	{
		return false;
	}//end if 
	
	if (checkKey > (MAX_FIB - 1)){
		cout << ARR_OUT_ERROR << endl;
		return false;
	}//end if checkKey >

	if (this->set[checkKey] == true){
		cout << checkKey << CONFIRM_ENTRY << endl;
		return true;
	}
	else
	{
		cout << checkKey << DENIED_ENTRY << endl;
		return false;
	}//end if check entry true
}//end isInSet

/** << operator
	@brief prints the set
*/
ostream& operator<<(ostream& output, const SortSetArray& arrayList){
	
	 output << "{ ";
	
	 if (arrayList.ItemCount > 0){
	 
		 for (int index = 0; index < MAX_FIB; index++)
			{
				if (arrayList.set[index] == true)
				output << index << " ";
				}//end while 
			}//end if
	 output << "}";
	return output;
}//end operator<<

/** get Size
	@brief returns the size of the set
*/
int SortSetArray::getSize(){

	return ItemCount;
}//end getSize

/** Remove
	@brief Removes items from the list
	@pre list must contain item to remove
	@param 
*/
bool SortSetArray::remove(const int removalEntry){
	if ((removalEntry >= 0 ) && (removalEntry < (MAX_FIB - 1)))
	{
		set[removalEntry] = false;
		ItemCount--;
		return true;
	}
	else {
		return false;
	}//end if

}//end remove

/** = Operator
	@brief Overload of the = operator
*/
SortSetArray& SortSetArray::operator= (const SortSetArray& baseList) {

	this->clear();
	
	for(int index = 0; index < MAX_FIB; index++){
		this->set[index] = baseList.set[index];	
	}//end for
	this->ItemCount = baseList.ItemCount;
	return *this;
}//end operator=

/** >> Operator
	@brief reads in and creates a set
	@param input input stream
	@param destinationList
*/
istream& operator>>(istream &input, SortSetArray &destinationList){
    while(!input.eof()) {
        int temp = 0;
        input >> temp;
        if (temp < 0){
            break;
        }//end if
        destinationList.set[temp] = true;
    }//end while
    return input;
}//end operator>>

/** == operator
	@brief checks to see whether two sets are equal
	@param rightHandList this checked against the *this
	@return true if equal, false othewise
*/
bool SortSetArray::operator==(const SortSetArray& rightHandList) const{

	if (this->ItemCount == rightHandList.ItemCount){
	
		for (int index = 0; index < (MAX_FIB ); index++){
			if (this->set[index] != rightHandList.set[index]){
				return false;
			}//end if
		}//end for

		//if you've made it this far
		return true;
	}
	else
	{
		return false;
	}//end if

}//end == operator

/** != operator
	@brief checks to see whether two sets are not equal
	@param rightHandList this checked against the *this
	@return true if unequal, false otherwise
*/
bool SortSetArray::operator!=(const SortSetArray& rightHandList) const{
	return !(*this == rightHandList);
}//end operator!=
/** + operator
	@brief creates union of two array sets
*/
SortSetArray& SortSetArray::operator+ (const SortSetArray& rightHandList) const{
	SortSetArray * newSet = new SortSetArray();
	newSet->clear();
	for (int index = 0; index < MAX_FIB; index++ ){
		
		if ((this->set[index] == true) || (rightHandList.set[index] == true)){
		newSet->insert(index);
		}//end if
	
	}

	return *newSet;

}//end operator+

/** - operator
	@brief returns the difference of two sets
*/
SortSetArray& SortSetArray::operator- (const SortSetArray& removalList){
	SortSetArray * newSet = new SortSetArray(*this);
	/*newSet->clear();
	newSet = this;*/
	for (int index = 0; index < MAX_FIB; index++){
		if (newSet->set[index] == removalList.set[index])
		{
		
			newSet->remove(index);
		
		}//end if
	}//end for
	return * newSet;
	delete newSet;
	
}//end operator-

/** * operator
	@brief returns the intersection of the two sets
*/
SortSetArray& SortSetArray::operator* (const SortSetArray& rightHandList) const{
	SortSetArray * newSet = new SortSetArray();
	newSet->clear();
	for (int index = 0; index < MAX_FIB; index++){
	if ((this->set[index] == true) && (rightHandList.set[index] == true)){
		newSet->insert(index);
	}//end if 

}//end for
		return *newSet;
	delete newSet;
}//end operator*


/** += operator
	@brief assignment of + operator
*/
SortSetArray& SortSetArray::operator+= (const SortSetArray& rightHandList) {
	
	*this = *this + rightHandList;
	return *this;

}//end +=operator

/** -= operator
	@brief assignment of - operator
*/
SortSetArray& SortSetArray::operator-=(const SortSetArray& rightHandList){

	*this = *this - rightHandList;
	return *this;

}//end operator-=
	

/** *= operator
	@brief assignment of * operator
*/
SortSetArray& SortSetArray::operator*= (const SortSetArray& rightHandList){
	
	*this = *this * rightHandList;
	return *this;

}//end operator*=

