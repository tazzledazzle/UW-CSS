/** Starter code for timing functions
   It includes some timing code. Test and compare results. 

   This code does not meet style requirements, is not ideal nor guaranteed.
   
   As with all work you submit, 
   you must make it meet quality/modularity/readability standards.

   Your version must accept/use  command line arguments; 
   and must set a default value if none is provided 
   instead of issuing an error message.
   
   @file timerMain.cpp 
   @author MF & RCS
   @param size - from the command line, the number of data elements to sort
   @return -1 if there are any problems, 0 otherwise
   @pre first user supplied command line argument must be a positive integer
   @post data will have been passed to the included sort routine
*/

#define DEFAULT_SIZE 42 
#include <iostream>
#include <string.h>  // for strcmp
// #include <vector>
#include <stdlib.h>
#include <sys/time.h>  // for gettimeofday() and timeval
#include <ctime>       // for  clock()and clock_t and CLOCKS_PER_SEC
//#include <chrono> // new time utilities (after 2011 update?) 
using namespace std;

// #include "dummyBubbleSort.cpp"   // must work with current data types/formats
#include "bubbleIntArray.cpp"  

/**  fill array with random numbers 
   does not meet style requirements
*/
// void initArray( vector<int> &array, int randMax ) {
void initArray( int array[], int randMax ) {

 int size = randMax;  //  array.size( );

 for ( int i = 0; i < size; ) {
   int tmp = ( randMax == -1 ) ? rand( ) : rand( ) % randMax;
   bool hit = false;
   for ( int j = 0; j < i; j++ ) {
     if ( array[j] == tmp ) {
       hit = true;
       break;
     } // if
   } // for
   if ( hit )
     continue;
   array[i] = tmp;
   i++;
 } // if
} // initArray

// array printing, comment out for performance only
// void printArray( vector<int> &array, char arrayName[] ) {
void printArray( int array[], int size){ // char arrayName[] ) {
// int size = array.size( );

 for ( int i = 0; i < size; i++ )
//   cout << arrayName << "[" << i << "] = " << array[i] << endl;
    cout << "[" << i << "] = " << array[i] << endl;
} // printArray

// performance evaluation
/* you may consider http://support.microsoft.com/kb/815668 and 
  http://stackoverflow.com/questions/1739259/how-to-use-queryperformancecounter
  to learn about queryperformancecounter
*/
/* according to connect.microsoft, one can use <chrono> ; but it is not very accurate
see http://connect.microsoft.com/VisualStudio/feedback/details/719443/c-chrono-headers-high-resolution-clock-does-not-have-high-resolution
  Actual results from code below
156000 ticks.
15600000 ns. 
  Expected results
An interval less than about 100 nanosecons.

  Compile the following C++ code in Release mode for x64:

#include <iostream>
#include <chrono>
using namespace std;

int main() {
  typedef std::chrono::high_resolution_clock Clock;
  auto t1 = Clock::now();
  auto t2 = Clock::now();
  while (t2-t1 == Clock::duration::zero() ) {
     t2 = Clock::now();
  }
  std::cout << (t2-t1).count() << " ticks.\n";
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns.\n";

  cin.get(); // to hold cmd window open until oyu press a key
}
*/

void elapsed( timeval &startTime, timeval &endTime ) { // uses <sys/time.h>
  long seconds, microseconds; // milliSecTime,
  seconds  = endTime.tv_sec  - startTime.tv_sec;
  microseconds = endTime.tv_usec - startTime.tv_usec;
  if ( microseconds < 0 ){ 
      microseconds += 1000000 ;  // correct for roll over
  }
  cout << "elapsed: elapsed time: " << seconds << " sec, " << microseconds << " microsec." << endl;
} // elapsed

void clockElapsed( clock_t clockTimeStart, 
                  clock_t clockTimeEnd ) {  // uses less precise ctime
  clock_t ticks;
  ticks = clockTimeEnd - clockTimeStart;
  cout << "clockElapsed:clock time elapsed: " << ticks << " clock ticks ~= " 
       << (float)ticks / (float)CLOCKS_PER_SEC << " seconds\n"; 
} // clockElapsed


int main( int argc, char* argv[] ) {
  bool debug = false;
  if ( strcmp(argv[argc -1], "DEBUG") == 0) {
     debug = true;
     cout << "debugging is set to :" << debug << endl;
  }
   
  int size = 0; // how could one eliminate work done later ?
                                                     
  if ( argc <= 1 ) {  // did user select an array size
   size = DEFAULT_SIZE;  //  why not return -1;
   cerr << "usage: a.out size; you will get an array of "<< size << endl;
 }

 size = atoi( argv[1] ); // validate array size
 if ( size <= 0 ) {
   cerr << "array size must be positive" << endl;
   return -1;
 }
 
                                                          
 srand( size ); // seed for array generation;
//  vector<int> items( size );
 int* items_ptr = new int[size];  // use items_ptr as an array, e.g. items_ptr[1] = 3;
 initArray( items_ptr, size );
 cout << "dummyBubbleSort initial: size =" << size << endl;
 if (debug) printArray( items_ptr, size); // "items" ); // comment out when evaluating performance only

// new type clock syntax
// using Clock = std::chrono::high_resolution_clock;
// the above is the same as "typedef std::chrono::high_resolution_clock Clock;"
// but easier to read and the syntax supports being templated
// using Time_point = Clock::time_point;
// Time_point tp = Clock::now(); 
 
 // mergesort
 struct timeval startTime, endTime;
 
 clock_t clockTimeStart, clockTimeEnd;
 clockTimeStart = clock();
 
 gettimeofday( &startTime, 0 ); // second parameter was for timezone; but that no longer works

 //usleep(4000); // testing: 4000 microsec = 4 millisec 
 bubbleSort( items_ptr, size );  
 gettimeofday( &endTime, 0 );
 
 clockTimeEnd = clock();
 elapsed( startTime, endTime ); // cout << "elapsed time (in ms): " << elapsed( startTime, endTime ) << endl;
 clockElapsed (clockTimeStart, clockTimeEnd);

//Time_point tp2 = Clock::now();
//using std::chrono::milliseconds;
//using std::chrono::duration_cast;
//std::cout << duration_cast<milliseconds>(tp2 - tp).count() << '\n';

 cout << "dummyBubbleSort sorted:" << endl;    
 if (debug) printArray( items_ptr, size); // "items" ); // turn off when evaluating performance only

 return 0;
}
