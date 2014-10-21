// Project:      CSS432 UDP Socket Class
// Professor:    Munehiro Fukuda
// Organization: CSS, University of Washington, Bothell
// Date:         March 5, 2004

#ifndef _TIMER_H_
#define _TIMER_H_

#include <iostream>

using namespace std;

extern "C"
{
#include <sys/time.h>
}

class Timer {
 public:
  Timer( );                  // Constructor
  void start( );             // Memorize the curren time in startTime
  long lap( );               // endTime - startTime
  long lap( long oldTv_sec, long oldTv_usec ); // endTime - oldTime
  long getSec( );            // get startTime.tv_sec
  long getUsec( );           // get startTime.tv_usec
 private:
  struct timeval startTime;  // Memorize the time to have started an evaluation
  struct timeval endTime;    // Memorize the time to have stopped an evaluation
};

#endif
