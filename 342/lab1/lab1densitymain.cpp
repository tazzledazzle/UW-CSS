#include <iostream>
#include <cassert>
#include <fstream>
#define MAXNAMELENGTH 45
#define MAXRECORDS 250
#define FILE_ERROR_MESSAGE  "File could not be opened."
#define MOST_DENSE_MESSAGE "Most Dense Country Profile: \n"
#define MEDIAN_DENSITY_MESSAGE "Country Profile with Median Density:\n"
#define LEAST_DENSE_MESSAGE "Least Dense Country Profile: \n"
#define TOTAL_DENSITY_MESSAGE "Total Density for All Entries:"
#define ARITHMETIC_AVG_MESSAGE "Arithmetic Average Density for All Entries: "
#define DENSITY_TITLE "Density"
#define POPULATION_TITLE "Population"
#define COUNTRY_TITLE "Country Name"
#define AREA_TITLE "Area"
#define CR "\n"

using namespace std;

char const INPUTFILE[] = "lab1data1.txt" ; 

struct CountryStats {          
char countryName[MAXNAMELENGTH]; 
   int population; 
   int area;                           // km^2 
   double density; 
}; 

//-------------------------------Methods---------------------------------//

double calculateDensity ( CountryStats countryEntry);

void displayMedianDensity( CountryStats storedRecords[],
                          int &sortedArraySize);

void displayCountry( CountryStats countryEntry);

void traverseAndDisplay(CountryStats storedRecords[], int &sortedArraySize);

void displayMostDense( CountryStats storedRecords[]);

void displayLeastDense( CountryStats storedRecords[],
                       int storedArraySize);

void displayTotalDensity(double populationTotal, double areaTotal);

double calculateAverage(double numerator, double denominator);

void displayArithmeticAverage(double densityTotal,
                              int &sortedArraySize);

void moveEntries(CountryStats initialArray[], int insertPoint,
               int &sortedArraySize);
                                                                          
bool insertSorted(CountryStats countryArray[], 
                  CountryStats tempCountry,  int maximum,
                  int &sortedArraySize);

int main(){

CountryStats countries[MAXRECORDS];

ifstream infile(INPUTFILE);

  if (!infile)  { 
     cerr << FILE_ERROR_MESSAGE << endl; 
	 // must be a named constant
     return false;  
  }

int sortedArraySize = 0;

CountryStats temp;

while (infile.peek() != EOF){

   infile >> temp.countryName >> temp.population >> temp.area;
   temp.density = calculateDensity(temp);
   sortedArraySize++;
   insertSorted(countries, temp, MAXRECORDS, sortedArraySize);

}//end while


traverseAndDisplay(countries, sortedArraySize);

return 0;
}//end main


/** Calculate Density
* 
* @brief calculates the denisty of a country
* @pre must input a valid CountryStats object
* @post must output a double value representing the density
* @param countryEntry the CountryStats struct holding area and population
* @return the density of the CountryStats object
*/
double calculateDensity( CountryStats countryEntry) {                    

   if (countryEntry.area > 0){
       return (double) countryEntry.population/ (double) countryEntry.area;
   }
   else { //treat 0 as 1 square kilometer
      return countryEntry.population;
   }//end if 

}//end calculateDensity

/** Display Median Density
* 
  * @brief returns the mid density from an array of CountryStats
  * @pre the array must be in sorted order by density
  * @param tempCountry the array of CountryStats
  * @param sortedArraySize the size of the array
  */
void displayMedianDensity( CountryStats storedRecords[],
						  int &sortedArraySize)
{
       printf(MEDIAN_DENSITY_MESSAGE);
       displayCountry(storedRecords[sortedArraySize/2]);    
       printf(CR);
       
}//end displayMedianDensity

   /** display Country
    * 
    *@brief displays the country by Name, population, and density
    *@param tempCountry the country being displayed
    *@return a formatted version of the entry
   */
void displayCountry( CountryStats countryEntry){

   printf(COUNTRY_TITLE": %s "AREA_TITLE": %d "POPULATION_TITLE
		  ": %d "DENSITY_TITLE": %.2f"CR,
   countryEntry.countryName, countryEntry.area, 
   countryEntry.population, countryEntry.density);

}//end displayCountry

/** traverseAndDisplay
* 
* @brief displays the second pass through the array
* @param storedRecords the list to be displayed
* @param storedArraySize size of the list
*/
void traverseAndDisplay(CountryStats storedRecords[], int &sortedArraySize)
{
	double populationTotal = 0;
	double areaTotal = 0;
	double densityTotal = 0;

     for (int currentRecord = (MAXRECORDS - sortedArraySize);
       currentRecord < MAXRECORDS; currentRecord++)
		{
			displayCountry(storedRecords[currentRecord]);
			populationTotal += storedRecords[currentRecord].population;
			assert(populationTotal > 0);
			areaTotal += storedRecords[currentRecord].area;
			assert(areaTotal > 0);
			densityTotal += storedRecords[currentRecord].density;
			assert(densityTotal > 0);
		}//end for

       printf(CR, CR);
       displayMostDense(storedRecords);
       displayLeastDense(storedRecords, sortedArraySize);
       displayMedianDensity(storedRecords, sortedArraySize);
       displayArithmeticAverage(densityTotal, sortedArraySize);
       displayTotalDensity(populationTotal, areaTotal);
       //explainResults();
   
   }//end display

/** Display Most Dense
*
* @brief displays highest density entry
* @param storedRecords the list to be displayed
* @pre must be a valid array of records
*/
void displayMostDense( CountryStats storedRecords[]){
   printf(MOST_DENSE_MESSAGE);
   displayCountry(storedRecords[MAXRECORDS -1]);
   printf(CR);

}//end displayMostDense

/** Display Least Dense
*
* @brief displays least dense country
* @pre array size must not be zero and must contain a valid array
* @param storedRecords the list to be displayed
* @param storedArraySize the number of entries containing
*                        data in the array
*/
void displayLeastDense( CountryStats storedRecords[],
                        int storedArraySize)
{
   printf(LEAST_DENSE_MESSAGE);
   displayCountry(storedRecords[(MAXRECORDS - storedArraySize)]);
   printf(CR);
   
}//end displayLeastDense

/** Display Total Density
*
* @brief displays the total amount of density
* @param populationTotal all populations of Countries added together
* @param areaTotal all areas of Countries added together 
*/
void displayTotalDensity(double populationTotal, double areaTotal){

   printf(TOTAL_DENSITY_MESSAGE" %.2f"CR CR, 
   calculateAverage(populationTotal, areaTotal));

}//end displayTotalDensity

/** Calculate Average
*
* @brief helper method converting integers to doubles
* @param numerator the number to be divided
* @param denominator the number of parts to divide
* @return double value of a fraction
*/
double calculateAverage(double numerator, double denominator){

   assert(denominator > 0);
   return (numerator/ denominator);

}//end calculateAverage

/** Display Arithmetic Average
*
*@brief displays density over number of entries
*@param densityTotal the sum of every entries density
*@param sortedArraySize the size of the list
*/
void displayArithmeticAverage(double densityTotal, int &sortedArraySize){

   printf(ARITHMETIC_AVG_MESSAGE"%.2f" CR CR, 
   calculateAverage(densityTotal, sortedArraySize));

}//end displayArithmeticAverage

/** Move Entries
*
* @brief provides an entry point for insertion sort
* @param initialArray the array that needs modification
* @param insertPoint index where the array needs space
* @param sortedArraySize the size of the array
*/
void moveEntries(CountryStats initialArray[], int insertPoint,
               int &sortedArraySize)
{
   for (int placeOfMove = ((MAXRECORDS-1) - sortedArraySize);
        placeOfMove < insertPoint ; placeOfMove++)
   {
      initialArray[placeOfMove] = initialArray[placeOfMove + 1];
   }//end for

}//end moveEntries

/** Insert Sorted
*
* @brief insert elements into an array using insertion sort initially
* @param countryArray the array data is entered into
* @param tempCountry the item to add
* @param maximum the size of the array
* @param sortedArraySize size of elements inserted
*/
bool insertSorted(CountryStats countryArray[], 
                  CountryStats tempCountry,  int maximum,
                  int &sortedArraySize)
{
   int insertionPoint;

   for (insertionPoint = (MAXRECORDS-1); insertionPoint > 0; 
        insertionPoint--)
   {
      if (tempCountry.density < countryArray[insertionPoint].density)
      {

         ; //move down
      }
      else if ((tempCountry.density == 
                countryArray[insertionPoint].density) && 
               (strcmp(tempCountry.countryName, 
                countryArray[insertionPoint].countryName) < 0))
      {
         ; //move down
      }
      else {
         moveEntries(countryArray,insertionPoint,
         sortedArraySize);
         countryArray[insertionPoint] = tempCountry;
         return true;
      }//end if
   }//end for
   
   return false;
}//end insertSorted
