#include "Socket.h"

Socket::Socket( int port )
  : port( port ), clientFd( NULL_FD ), serverFd( NULL_FD ) {
}

Socket::~Socket( ) {
  if ( clientFd != NULL_FD )
    close( clientFd );
  if ( serverFd != NULL_FD )
    close( serverFd );
}

int Socket::getClientSocket( char ipName[] ) {
  // Get the host entry corresponding to ipName
  struct hostent* host = gethostbyname( ipName );
  if( host == NULL ) {
    perror ( "Cannot find hostname." );
    return NULL_FD;
  }
      
  // Fill in the structure "sendSockAddr" with the address of the server.
  sockaddr_in sendSockAddr;
  bzero( (char*)&sendSockAddr, sizeof( sendSockAddr ) );
  sendSockAddr.sin_family      = AF_INET; // Address Family Internet
  sendSockAddr.sin_addr.s_addr =
    inet_addr( inet_ntoa( *(struct in_addr*)*host->h_addr_list ) );
  sendSockAddr.sin_port        = htons( port );

  // Open a TCP socket (an Internet strem socket).
  if( ( clientFd = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 ) {
    perror( "Cannot open a client TCP socket." );
    return NULL_FD;
  }
    
  // Connect to the server.
  while ( connect( clientFd, (sockaddr*)&sendSockAddr, 
		   sizeof( sendSockAddr ) ) < 0 );

  // Connected
  return clientFd;
}

int Socket::getServerSocket( ) {
  if ( serverFd == NULL_FD ) { // Server not ready
    sockaddr_in acceptSockAddr;

    // Open a TCP socket (an internet stream socket).
    if( ( serverFd = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 ) {
      perror( "Cannot open a server TCP socket." );
      return NULL_FD;
    }

    // Set the resuseaddr option
    const int on = 1;
    if ( setsockopt( serverFd, SOL_SOCKET, SO_REUSEADDR,
                     ( char * )&on, sizeof( on ) ) < 0 ) {
      perror( "setsockopt SO_REUSEADDR failed" );
      return NULL_FD;
    }
    
    // Bind our local address so that the client can send to us
    bzero( (char*)&acceptSockAddr, sizeof( acceptSockAddr ) );
    acceptSockAddr.sin_family      = AF_INET; // Address Family Internet
    acceptSockAddr.sin_addr.s_addr = htonl( INADDR_ANY );
    acceptSockAddr.sin_port        = htons( port );
    
    if( bind( serverFd, (sockaddr*)&acceptSockAddr,
	      sizeof( acceptSockAddr ) ) < 0 ) {
      perror( "Cannot bind the local address to the server socket." );
      return NULL_FD;
    }
    
    listen( serverFd, 5 );
  }
  
  // Read to accept new requests
  int newFd = NULL_FD;
  sockaddr_in newSockAddr;
  socklen_t newSockAddrSize = sizeof( newSockAddr );
  
  if( ( newFd =
	accept( serverFd, (sockaddr*)&newSockAddr, &newSockAddrSize ) ) < 0 ) {
    perror( "Cannot accept from another host." );
    return NULL_FD;
  }
  return newFd;
}
