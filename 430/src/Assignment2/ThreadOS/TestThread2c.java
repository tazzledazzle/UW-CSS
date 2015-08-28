import java.util.Date;

class TestThread2c extends Thread {

  private String name;
  private int cpuBurst;

  private long submissionTime;
  private long activationTime;
  private long completionTime;
  
  private static final int TIMEQUANTUM = 100;

  public TestThread2c ( String args[] ) {
    name = args[0];
    cpuBurst = Integer.parseInt( args[1] );
    submissionTime = new Date().getTime();
    SysLib.cout( 
      String.format( 
        "%05d: Thread[%s]: submitted\n",
        submissionTime % 100000, name ) );
  }

  public void run() {
    long totalExecutionTime = 0;
    long totalWaitTime = 0;
    activationTime = new Date().getTime();
    for ( int burst = cpuBurst; burst > 0; burst -= TIMEQUANTUM ) {
      totalExecutionTime += TIMEQUANTUM;
      SysLib.sleep( TIMEQUANTUM );
    }
    completionTime = new Date().getTime( );
    long responseTime = activationTime - submissionTime;
    totalWaitTime = completionTime - submissionTime - totalExecutionTime;
    long turnaroundTime = completionTime - submissionTime;
    SysLib.cout( 
      String.format( 
        "%05d: Thread[%s]: response: %5d; wait: %5d; execution: %5d; turnaround: %5d\n",
        completionTime % 100000, name, 
        responseTime, totalWaitTime, totalExecutionTime, turnaroundTime ) );
    SysLib.exit();
  }
}
