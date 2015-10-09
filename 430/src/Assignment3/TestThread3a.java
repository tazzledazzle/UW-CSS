
// ------------------------------ TestThread3a.java ----------------------------
/*
 * PURPOSE OF FILE
 * This file is responsible for creating heavy numerical computation work for 
 * computer to process. It uses the Math function to work through the n^2 for 
 * loop. There's also a factorial function that I wrote to practice my recursion 
 * skills. 
 *
 * ASSUMPTIONS
 * It is assumed that the user knows that this function does absolutely nothing 
 * productive. Rather, this function doesn't do anything really understandable. 
 * It's simply a CPU intensive task.
 */

import java.util.*;
import java.lang.*;

class TestThread3a extends Thread {

    public TestThread3a ( ) {}

    public void run( ) {
    	for(int j = 0; j < 10000; j++){
    		for(int i = 0; i < 10000; i++){
    			Math.sqrt(Math.tan(Math.sqrt(fact(15))));
    		}
    	}
		SysLib.exit( );
    }

    private int fact(int factNum){ return factHelper(factNum); }
    private int factHelper(int fact){
    	if(fact == 1) { return 1; }
    	int result = factHelper(fact-1) * fact;
        return result;
    }
}
