
Program 1: Sockets
======================
Professor: Munehiro Fukuda
Due date: See the syllabus

1. Purpose
===

This assignment is intended for two purposes: (1) to exercise use of various socket-related system calls and (2) to evaluate dominant overheads of point-to-point communication over 1Gbps networks.

2. Client-Server Model
===
In all your programming assignments through to the final project, your program will use the client-server model where a client process establishes a connection to a server, sends data or requests, and closes the connection while the server sends back responses or acknowledgments to the client.
3. TCP Communication

HW1 focuses on basic connection-oriented socket (SOCK_STREAM) communication between a client and a server process. To establish such communication, those processes should perform the following sequence of operations:
Client
=======
Receive a server's IP port (server_port) and IP name (server_name) as Linux shell command arguments.
Retrieve a hostent structure corresponding to this IP name by calling gethostname( ).
    struct hostent* host = gethostbyname( server_name );
Declare a sockaddr_in structure, zero-initialize it by calling bzero, and set its data members as follows:
    int port = YOUR_ID;  // the last 5 digits of your student id
    sockaddr_in sendSockAddr;
    bzero( (char*)&sendSockAddr, sizeof( sendSockAddr ) );
    sendSockAddr.sin_family      = AF_INET; // Address Family Internet
    sendSockAddr.sin_addr.s_addr =
      inet_addr( inet_ntoa( *(struct in_addr*)*host->h_addr_list ) );
    sendSockAddr.sin_port        = htons( server_port );
Open a stream-oriented socket with the Internet address family.
    int clientSd = socket( AF_INET, SOCK_STREAM, 0 );
Connect this socket to the server by calling connect as passing the following arguments: the socket descriptor, the sockaddr_in structure defined above, and its data size (obtained from the sizeof function).
    connect( clientSd, ( sockaddr* )&sendSockAddr, sizeof( sendSockAddr ) );

Use the write or writev system call to send data.
Use the read system call to receive a response from the server.
Close the socket by calling close.
     close( clientSd );
Server

Declare a sockaddr_in structure, zero-initialize it by calling bzero, and set its data members as follows:
    int port = YOUR_ID;  // the last 5 digits of your student id
    sockaddr_in acceptSockAddr;
    bzero( (char*)&acceptSockAddr, sizeof( acceptSockAddr ) );
    acceptSockAddr.sin_family      = AF_INET; // Address Family Internet
    acceptSockAddr.sin_addr.s_addr = htonl( INADDR_ANY );
    acceptSockAddr.sin_port        = htons( port );
Open a stream-oriented socket with the Internet address family.
    int serverSd = socket( AF_INET, SOCK_STREAM, 0 );
Set the SO_REUSEADDR option. (Note this option is useful to prompt OS to release the server port as soon as your server process is terminated.)
    const int on = 1;
    setsockopt( serverSd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, 
                sizeof( int ) );
Bind this socket to its local address by calling bind as passing the following arguments: the socket descriptor, the sockaddr_in structure defined above, and its data size.
    bind( serverSd, ( sockaddr* )&acceptSockAddr, sizeof( acceptSockAddr ) );
Instructs the operating system to listen to up to five connection requests from clients at a time by calling listen.
    listen( serverSd, 5 );
Receive a request from a client by calling accept that will return a new socket specific to this connection request.
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof( newSockAddr );
    int newSd = accept( serverSd, ( sockaddr *)&newSockAddr, &newSockAddrSize );
Use the read system call to receive data from the client. (Use newSd but not serverSd in the above code example.)
Use the write system call to send back a response to the client. (Use newSd but not serverSd in the above code example.)
Close the socket by calling close.
    close( newSd );
You need to include the following header files so as to call these OS functions:
    #include <sys/types.h>    // socket, bind
    #include <sys/socket.h>   // socket, bind, listen, inet_ntoa
    #include <netinet/in.h>   // htonl, htons, inet_ntoa
    #include <arpa/inet.h>    // inet_ntoa
    #include <netdb.h>        // gethostbyname
    #include <unistd.h>       // read, write, close
    #include <string.h>       // bzero
    #include <netinet/tcp.h>  // SO_REUSEADDR
    #include <sys/uio.h>      // writev
Socket.h and Socket.cpp

If you would like to take an easy-going option, you may use Socket.h and Socket.cpp that the professor has implemented in ~css432/hw1/. In this case, you don't need to include the header files listed above. However, there are few comments in these files. At least, you have to learn how to use this class. :-)
4. Statement of Work

Write Client.cpp and Server.cpp that establish a TCP connection between a pair of client and server, repeat sending a set of data buffers, (each with the same size) in three different scenarios from the client to the server, and send back an acknowledgment from the server to the client.
Client.cpp

Your client program must receive the following six arguments:
port: a server IP port
repetition: the repetition of sending a set of data buffers
nbufs: the number of data buffers
bufsize: the size of each data buffer (in bytes)
serverIp: a server IP name
type: the type of transfer scenario: 1, 2, or 3 (see below)
From the above parameters, you need to allocate data buffers below:
     char databuf[nbufs][bufsize]; // where nbufs * bufsize = 1500
The three transfer scenarios are:
multiple writes: invokes the write( ) system call for each data buffer, thus resulting in calling as many write( )s as the number of data buffers, (i.e., nbufs).
     for ( int j = 0; j < nbufs; j++ )
       write( sd, databuf[j], bufsize );    // sd: socket descriptor
writev: allocates an array of iovec data structures, each having its *iov_base field point to a different data buffer as well as storing the buffer size in its iov_len field; and thereafter calls writev( ) to send all data buffers at once.
     struct iovec vector[nbufs];
     for ( int j = 0; j < nbufs; j++ ) {
       vector[j].iov_base = databuf[j];
       vector[j].iov_len = bufsize;
     }
     writev( sd, vector, nbufs );           // sd: socket descriptor
single write: allocates an nbufs-sized array of data buffers, and thereafter calls write( ) to send this array, (i.e., all data buffers) at once.
     write( sd, databuf, nbufs * bufsize ); // sd: socket descriptor
The client program should execute the following sequence of code:
Open a new socket and establish a connection to a server.
Allocate databuf[nbufs][bufsize].
Start a timer by calling gettimeofday.
Repeat the repetition times of data transfers, each based on type such as 1: multiple writes, 2: writev, or 3: single write
Lap the timer by calling gettimeofday, where lap - start = data-sending time.
Receive from the server an integer acknowledgment that shows how many times the server called read( ).
Stop the timer by calling gettimeofday, where stop - start = round-trip time.
Print out the statistics as shown below:
     Test 1: data-sending time = xxx usec, round-trip time = yyy usec, #reads = zzz
Close the socket.
Server

Your client program must receive the following two arguments:
port: a server IP port
repetition: the repetition of sending a set of data buffers
The main function should be:
Accept a new connection.
Change this socket into an asynchronous connection.
     signal( SIGIO, your_function ); // you need to define your_function a priori
     fcntl( fd, F_SETOWN, getpid( ) );
     fcntl( fd, F_SETFL, FASYNC );
Let this server sleep forever.
Server.cpp must include your_function (whatever the name is) which is called upon an I/O interrupt (a.k.a. a signal in Unix). This functioin receives just an integer argument and returns void. The argument is the signal identifier, (i.e., SIGIO) which you don't have to take care of in the function. This function should:
Allocate databuf[BUFSIZE], where BUFSIZE = 1500.
Start a timer by calling gettimeofday.
Repeat reading data from the client into databuf[BUFSIZE]. Note that the read system call may return without reading the entire data if the network is slow. You have to repeat calling read like:
       for ( int nRead = 0; 
            ( nRead += read( sd, buf, BUFSIZE - nRead ) ) < BUFSIZE; 
            ++count );
Check the manual page for read carefully.
Stop the timer by calling gettimeofday, where stop - start = data-receiving time.
Send the number of read( ) calls made, (i.e., count in the above) as an acknowledgment.
Print out the statistics as shown below:
     data-receiving time = xxx usec
Close this connection.
Terminate the server process by calling exit( 0 ).
You must conduct performance evaluation over 1Gbps network between two different computing nodes of uw1-320-00 ~ uw1-320-15 For each network, your performance evaluation should cover the following nine test cases:
repetition = 20000
Three combinations of nbufs * bufsize = 15 * 100, 30 * 50, 60 * 25, and 100 * 15
Three test scenarios such as type = 1, 2, and 3
You may have to repeat your performance evaluation and to average elapsed times.
