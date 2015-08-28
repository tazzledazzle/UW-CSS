import java.util.Date;

class TestThread2d extends Thread {
  private String name;
  private int cpuBurst;

  private long submissionTime;
  private long activationTime;
  private long completionTime;
  private long lastExecutionTime;
  private long totalExecutionTime;
  private long totalWaitTime;
  
  private static final int TIMEQUANTUM = 100;

  public TestThread2d ( String args[] ) {
    name = args[0];
    cpuBurst = Integer.parseInt( args[1] );
    submissionTime = new Date().getTime();
    SysLib.cout( 
      String.format( 
        "%05d: Thread[%s] submitted\n", submissionTime % 100000, name ) );
  }

  public void run( ) {
    long totalExecutionTime = 0;
    long totalWaitTime = 0;
    activationTime = new Date().getTime();
    lastExecutionTime = activationTime;
    for ( int burst = cpuBurst; burst > 0; burst -= TIMEQUANTUM ) {
      long currentTime = new Date().getTime();
      totalWaitTime += (currentTime - lastExecutionTime);
      totalExecutionTime += TIMEQUANTUM;
      lastExecutionTime = currentTime + TIMEQUANTUM;
      SysLib.cout( 
        String.format( 
          "%05d: Thread[%s] is running (%5d, %5d)\n", 
          currentTime % 100000, name, totalExecutionTime, totalWaitTime ) );
      SysLib.sleep( TIMEQUANTUM );
    }
    completionTime = new Date().getTime();
    long responseTime = activationTime - submissionTime;
    long turnaroundTime = completionTime - submissionTime;
    SysLib.cout( 
      String.format( 
        "%05d: Thread[%s]: response: %5d; wait: %5d; execution: %5d; turnaround: %5d\n",
        completionTime % 100000, name, 
        responseTime, totalWaitTime, totalExecutionTime, turnaroundTime ) );
    SysLib.exit();
  }
}
