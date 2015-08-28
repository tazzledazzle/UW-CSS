import java.util.Date;

class TestThread2 extends Thread {
    private String name;
    private int cpuBurst;

    private long submissionTime;
    private long responseTime;
    private long completionTime;

    public TestThread2 ( String args[] ) {
	name = args[0];
	cpuBurst = Integer.parseInt( args[1] );
	
	submissionTime = new Date( ).getTime( );
    }

    public void run( ) {
	responseTime = new Date( ).getTime( );

	for ( int burst = cpuBurst; burst > 0; burst -= 100 ) {
	    SysLib.sleep( 100 );
	}

	completionTime = new Date( ).getTime( );
	SysLib.cout( "Thread[" + name + "]:" +
		     " response time = " + (responseTime - submissionTime) +
		     " turnaround time = " + (completionTime - submissionTime)+
		     " execution time = " + (completionTime - responseTime)+
		     "\n");
	SysLib.exit( );
    }
}
