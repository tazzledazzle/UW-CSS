//  Server.cpp
//  HMW1
//
//  Created by Terence Schumacher on 10/2/14.
//  Copyright (c) 2014 Terence Schumacher. All rights reserved.
//============================================================================

#include <sys/types.h>    // socket, bind
#include <sys/socket.h>   // socket, bind, listen, inet_ntoa
#include <netinet/in.h>   // htonl, htons, inet_ntoa
#include <arpa/inet.h>    // inet_ntoa
#include <netdb.h>        // gethostbyname
#include <unistd.h>       // read, write, close
#include <string.h>       // bzero
#include <netinet/tcp.h>  // TCP_NODELAY
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include "Socket.h"
#define BUFSIZE 1500

using namespace std;

int fd;
int repetition;


/** my Function
 * @brief reads incoming data from socket via signal() function
 * @param repetitions necessary parameter for the signal() function
*/
void my_function(int repetitions){
    char databuf[BUFSIZE];
    struct timeval startTime, stopTime;

    gettimeofday(&startTime, NULL);
    int count;
    for (int i = 0; i < repetition; i++){
        for (int nRead = 0; (nRead += read(fd, databuf + nRead,
                                    BUFSIZE - nRead)) < BUFSIZE; ++count);
    }
    gettimeofday(&stopTime, NULL);
    
    long diffTime;
    diffTime = (stopTime.tv_sec - startTime.tv_sec) * 1000000;
    diffTime += (stopTime.tv_usec - startTime.tv_usec);
    
    cout << "Time Received: " << diffTime << " usec" << endl;
    cerr << diffTime << endl;
    write(fd, &count, sizeof(count));
    exit(0);

}

/** Main Program
 */
int main(int argc, char * argv[]){
    
    int port = atoi(argv[1]);   //port#
    repetition = atoi(argv[2]); //#of reps on read
    
    Socket socket(port);
    
     fd = socket.getServerSocket();
    
    //Change the socket into an asynchronous connection
    signal(SIGIO, my_function);
    fcntl(fd, F_SETOWN, getpid());
    fcntl(fd, F_SETFL, FASYNC);
    
    while (true) {
        sleep(1000);
    }
    
}//end main


