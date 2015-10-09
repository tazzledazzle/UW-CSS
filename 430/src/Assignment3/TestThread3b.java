
// ------------------------------ TestThread3b.java ----------------------------
/*
 * PURPOSE OF FILE
 * This file is responsible for creating heavy workload for the CPU to process 
 * READ/WRITE jobs. The run function starts out by creating a block of the 
 * maximum size, afterwords, it loops an absurd amount of times to perform 
 * numerous requests to the DISK. 
 *
 * ASSUMPTIONS
 * Similar to TestThread3a, this function does absolutely nothing productive. 
 */

import java.util.*;

class TestThread3b extends Thread {

	private byte[] myBlock;								//init a byte array

    public TestThread3b ( ) {}							//constructor

    public void run( ) {
		myBlock = new byte[512];						//initialize a block
		for (int i = 0; i < 600; i++){
			SysLib.rawwrite(i, myBlock);				//write to disk
			SysLib.rawread(i, myBlock);					//read from disk			
		}
		SysLib.exit( );
    }
}
