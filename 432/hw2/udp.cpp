//
//  udp.cpp
//  hw2
//
//  Created by Terence Schumacher on 10/11/14.
//  Copyright (c) 2014 Terence Schumacher. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include "UdpSocket.h"
#include "Timer.h"

using namespace std;
// Client Stop and Wait
//
// @param socket    Udp socket sent into function
// @param max       maximun number of messages sent
// @param message   message object sent
//
int clientStopWait(UdpSocket &socket, const int max, int message[]){
    Timer time;
    int count = 0;
    for (int i = 0; i < max; i++) {
        time.start();
        message[0] = i;
        socket.sendTo((char *) message, sizeof(&message));
        
        while (socket.pollRecvFrom() <= 0){
            usleep(1);

            if (time.lap() >= 1500){
                cerr << "ERROR: Resending " << message[0] << endl;
                cerr << "Time: " << time.lap() << endl;
                count++;
                break;
            }
            
        }
        if (time.lap() >= 1500){
            i--;
            continue;
        }

        socket.recvFrom((char *) message, sizeof(&message));

        cerr << "Time: " << time.lap() << endl;
    }
//    cerr << "Time: " << time.lap() << endl;
    return count;
}

// Server For Stop and Wait
//
// @param socket    Udp socket sent into function
// @param max       maximun number of messages sent
// @param message   message object sent
//
int serverReliable(UdpSocket &socket, const int max, int message[]){
    cerr << "Starting Transfers... " << endl;
    for (int i = 0; i < max; i++) {
        if (message[0] == (max - 1))
            break; //i = max;
        
        socket.recvFrom((char *) message, sizeof(&message));
        if (message[0] == i) {
           cerr << "Sending Acknowledgement for: " << message[0] << endl;
            socket.ackTo((char * ) message, sizeof(&message));
            
        }
        else{
            while (socket.pollRecvFrom() <= 0) {
                usleep(1);
            }
            i--;    //go back
            cerr << "Go Back" << endl;
        }
    }
    return message[0];
}

// Client Sliding Window
//
// @param socket    Udp socket sent into function
// @param max       maximun number of messages sent
// @param message   message object sent
// @param windowSize size of window on SWP
//
int clientSlidingWindow( UdpSocket &sock, const int max, int message[],
                        int windowSize ){
    // repeats sending message[] and receiving an acknowledgment at a
    // client side max (=20,000) times using the sock object.
    cerr << "Client Sliding Window..." << endl;
    int count;
    int i = 0;
    int unacknowledged = 0;
    Timer time;
    while (i < max) {
        // the client can continuously send a new message[] as incrementing
        // its sequence number as far as the number of in-transit messages
        while (unacknowledged < windowSize) {   // window has space
            message[0] = i;
            sock.sendTo((char *) message, sizeof(&message));
            cerr << "Sending " << message[0] << endl;
            i++;
            unacknowledged++;   //decrease window space
        }
        // That number should be decremented every time the client
        // receives an acknowledgment.
        if(sock.pollRecvFrom() > 0){
            sock.recvFrom((char *) message, sizeof(&message));
           // cerr << "Received " << message[0] << endl;
            unacknowledged--;   //increase open space once receieved
        }
        else{
            // If # of unacknowledged messages reaches windowSize,
            // the client should start a timer.
            time.start();
            while (sock.pollRecvFrom() <= 0){   //wait for open socket
                usleep(1);
                if (time.lap() >= 1500){ //timeout
                    cerr << "ERROR: Resending " << message[0] << endl;
                    cerr << "Time: " << time.lap() << endl;
                    count++;    //inc retrans
                    break;
                }
            }
            // If a timeout (= 1500usec) has happened, it must send the
            // message with the minimum sequence number among those which
            // have not yet been acknowledged.
            if (time.lap() >= 1500){    // if timeout, then retransmitt
                i--;
                continue;
            }
        }
    }
    // The function must count the number of messages retransmitted
    // and return it to the main function as its return value.
    return count;
}

// Server for Slidning Window
//
// @param socket    Udp socket sent into function
// @param max       maximun number of messages sent
// @param message   message object sent
// @param windowSize size of window on SWP
//
void serverEarlyRetrans( UdpSocket &sock, const int max, int message[],
                        int windowSize ){
    cerr << "server Early Retransmit..." << endl;
    int lfr = 0;    // Last Frame Receieved
    int lastSeq = -1;
    int laf = 0;    // Last Acknowledged Frame
    vector<int> window(windowSize); // cumulative acknowledgement
    for(int i = 0; i < windowSize; i++) { 	//init window
        window[i] = -1;
    }
    // repeats receiving message[] and sending an acknowledgment at a
    // server side max (=20,000) times using the sock object.
    while(lfr < max) {
        while( sock.pollRecvFrom() <=0 ){
            usleep(1);
        }				// pause until message
        
        sock.recvFrom( ( char * ) message, MSGSIZE );   	// udp message receive
        lfr = *message;                     // get the seq # from beginning of msg
        cerr << "Receieved " << message[0] << endl;
        
        // Every time the server receives a new message[], it must memorizes this
        // message's sequence number in its array and
        // returns a cumulative acknowledgment
        int index = lfr % windowSize;
        
        if (index < laf || index >= windowSize) { // lfr is outside window
            sock.ackTo((char *) &lastSeq, sizeof(int));
            continue;										// drop packet
        } else if(index == laf) {				// lfr is next contiguous packet
            window[index] = lfr;
            lastSeq = lfr;
            while(window[laf] > -1) {
                lastSeq = window[laf];              // store value in lastSeq
                window[laf] = -1;
                laf++;								// increment window
                laf = laf % windowSize;
                if (window[laf] == -1) {				// if next slot is empty
                    // ack last contiguous packet
                    sock.ackTo((char *) &lastSeq, sizeof(int));
                }
            }
        } else { // lfr is within window, so store
            window[index] = lfr;					// store lfr in correct slot
            sock.ackTo((char *) &lastSeq, sizeof(int));
        }
        if (lfr == max-1)   //--> done
            break;
    }
}


