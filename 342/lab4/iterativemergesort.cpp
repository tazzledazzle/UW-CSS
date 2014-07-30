/**
	@file iterativemergesort.cpp
	@author Terence Schumacher
	@author Dominic Badzik
	@version 1.3

*/

#include "iterativemergesort.h"

void iterativeMergeSort::alternateMerSort(int originArray[], int arrayMaxSize, int tempArray[],
							int cycleSize, int beginList1, int tempSize){

 int listOneIndex, listTwoIndex, endList1, beginList2, endList2;	

	        /*Index for temp array*/
        while ( beginList1 + cycleSize < arrayMaxSize)
        {
            endList1 = beginList1 + cycleSize - 1;
            beginList2 = endList1 + 1;
            endList2 = beginList2 + cycleSize - 1;

            if( endList2 >= arrayMaxSize ) /* highList2 exceeds the limlt of array */
                endList2 = arrayMaxSize - 1;
            
			/*Merge the two pairs with lower limits lowList1 and lowList2*/
            listOneIndex = beginList1;  
			listTwoIndex = beginList2;
            
            while((listOneIndex <= endList1) && (listTwoIndex <= endList2 ))
            {
                if( originArray[listOneIndex] <= originArray[listTwoIndex] ){
                    tempArray[tempSize]= originArray[listOneIndex];
                    tempSize++;
                    listOneIndex++;
                }
                else{
                    tempArray[tempSize]= originArray[listTwoIndex];
                    tempSize++;
                    listTwoIndex++;
                }//end if
                
            }//end while

            while(listOneIndex <= endList1){
                tempArray[tempSize]= originArray[listOneIndex];
                tempSize++;
                listOneIndex++;
			}//end while

            while(listTwoIndex <= endList2){
                tempArray[tempSize]= originArray[listTwoIndex];
                tempSize++;
                listTwoIndex++;
            }//end while
            
 /**Merging completed**/
            
            beginList1 = endList2 + 1; /*Take the next two pairs for merging */

        }//End while ( beginList1 + cycleSize < arrayMaxSize)
        
		/*any pair left */
        for(listOneIndex = beginList1; tempSize < arrayMaxSize; listOneIndex++){ 
            tempArray[tempSize]= originArray[listOneIndex];
            tempSize++;
        }//end for

		//set the original array to the temp
        for(listOneIndex = 0; listOneIndex < arrayMaxSize; listOneIndex++)            
            originArray[listOneIndex] = tempArray[listOneIndex];

}//end alternateMerSort


void iterativeMergeSort::iterativeMergesort(int originArray[], int arrayMaxSize){
    int cycleSize;
    int beginList1 = 0;
    int tempSize = 0;
	int count =2;
   int tempArray[arrayMaxSize];
//    int *tempArray = new int[arrayMaxSize];
    /*lowList1 lower bound of first pair and so on*/
    for(cycleSize = 1; cycleSize < arrayMaxSize; cycleSize = cycleSize*2 )
    {
		if ((count % 2) == 0){
			alternateMerSort(originArray, arrayMaxSize, tempArray, cycleSize, beginList1, tempSize);
		}
		else{
			alternateMerSort(tempArray, arrayMaxSize, originArray, cycleSize, beginList1, tempSize);
		}//end if
        
    }//end for
    
}//end myMerge

