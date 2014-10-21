#include "Socket.h"

using namespace std;

int main( int argc, char* argv[] ) {

    // need to extract port number and IP address

    int port = atoi( argv[1] );

    cout << "Port: " << port << endl;

    // establish a connection through a socket

    Socket socket( port );
    int fd = socket.getServerSocket();

    cout << "Socket at fd " << fd <<  endl;

    // receive a string from the client

    char buffer[16];
    bzero( buffer, sizeof( buffer ) );
    int count = read( fd, buffer, 15 );

    cout << "Read: '" << buffer << "'" << endl;

    write( fd, buffer, count );

    return 0;
}
