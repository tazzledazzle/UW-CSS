import java.io.*;

public class Boot
{
    static final int OK = 0;
    static final int ERROR = -1;

    public static void main ( String args[] ) {
	SysLib.cerr( "threadOS ver 1.0:\n" );
	SysLib.boot( );
	SysLib.cerr( "Type ? for help\n" );

	String[] loader = new String[1];
	loader[0] = "Loader";
	SysLib.exec( loader );
    }
}
