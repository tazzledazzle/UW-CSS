import java.io.*;

public class Loader extends Thread
{
    static final int OK = 0;
    static final int ERROR = -1;

    public Loader( ) {
    }

    public Loader( String args[] ) {
    }

    private static void help( ) {
	SysLib.cout( "?:       print a help message\n" );
	SysLib.cout( "q:       exit from threadOS\n" );
	SysLib.cout( "l prog:  load prog\n" );
    }

    public void run( ) {
	String cmdLine = "";
	char cmd = ' ';

	while ( true ) {
	    do {
		StringBuffer inputBuf = new StringBuffer( );
		SysLib.cerr( "-->" );
		SysLib.cin( inputBuf );
		cmdLine = inputBuf.toString( );
	    } while ( cmdLine.length( ) == 0 );
	    System.out.println( cmdLine );
	    cmd = cmdLine.charAt( 0 );
	    switch( cmd ) {
	    case '?':
		help( );
		break;
	    case 'q':
		SysLib.sync( );
		System.exit( 1 );
		break;
	    case 'l':
		String intrArgs[]
		    = SysLib.stringToArgs( cmdLine.substring( 2 ) );
		if ( SysLib.exec( intrArgs ) == ERROR ) {
		    SysLib.cerr( intrArgs[0] + " failed in loading\n" );
		    break;
		}
		SysLib.join( );
		break;
	    case 'r':
		break;
	    }
	}
    }
}
