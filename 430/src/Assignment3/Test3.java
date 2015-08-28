// -----------------------------------------------------------------------------
// ---------------------------- Written by Josh Brunner ------------------------
// ----------------------- for CSS 430 HW3/pt.2  Assignment --------------------
// -------------------------- Last modified: 5/14/2014 -------------------------
// --------------------------------- Test3.java --------------------------------
/*
 * PURPOSE OF FILE
 * This file is responsible for creating a user level test thread. When 
 * called, it executes X amount of pairs of TestThread3a's and TestThread3b's. 
 * Each of these programs performs heavy work on the computer. Afterwords, the 
 * Test3 programs prints the elapsed time to the console. 
 *
 * ASSUMPTIONS
 * It is assumed that the user understands that Test3 takes in one int.
 * In addition, it is assumed that both TestThread3a and TestThread3b java 
 * files are located in the same folder as this one.
 */

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
