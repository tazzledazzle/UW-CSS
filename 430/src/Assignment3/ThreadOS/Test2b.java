import java.util.Date;

class Test2b extends Thread {

    public void run( ) {
	String[] args1 = SysLib.stringToArgs( "TestThread2b a 5000" );
	String[] args2 = SysLib.stringToArgs( "TestThread2b b 1000" );
	String[] args3 = SysLib.stringToArgs( "TestThread2b c 3000" );
	String[] args4 = SysLib.stringToArgs( "TestThread2b d 6000" );
	String[] args5 = SysLib.stringToArgs( "TestThread2b e 500" );
	SysLib.exec( args1 );
	SysLib.exec( args2 );
	SysLib.exec( args3 );
	SysLib.exec( args4 );
	SysLib.exec( args5 );
	for (int i = 0; i < 5; i++ )
	    SysLib.join( );
	SysLib.cout( "Test2b finished\n" );
	SysLib.exit( );
    }
}
