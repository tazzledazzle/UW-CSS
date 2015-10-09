
import java.util.Date;
import java.util.*;

class Test3 extends Thread {

	private int compThreads;							//X pairs of threads		
    private long subTime;								//submission time 
    private long compTime;								//completion time

	public Test3(String[] args){ compThreads = Integer.parseInt(args[0]); }

    public void run( ) {
		subTime = new Date( ).getTime( );				//get submission time

		String[] argsA = SysLib.stringToArgs( "TestThread3a" );
		String[] argsB = SysLib.stringToArgs( "TestThread3b" );

		for(int i = 0; i < compThreads; i++){ SysLib.exec( argsA ); }
		for(int i = 0; i < compThreads; i++){ SysLib.exec( argsB ); }	

		for (int i = 0; i < compThreads; i++ ){
		   	SysLib.join( );								//wait for CPU work
			SysLib.cout("comp finished...\n");
		}

		for (int i = 0; i < compThreads; i++ ){
			SysLib.join( );								//wait for READ/WRITE
			SysLib.cout("disk finished...\n");
		}

		compTime = new Date( ).getTime( );				//get completion time

		SysLib.cout("elapsed time = " + (compTime - subTime) + " msec\n");
		SysLib.exit( );
    }
}
