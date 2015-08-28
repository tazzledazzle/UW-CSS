import java.util.Date;

class Test2d extends Thread {

  public void run() {
    long startTime = new Date().getTime();
    String[] args1 = SysLib.stringToArgs( "TestThread2d a 5000" );
    String[] args2 = SysLib.stringToArgs( "TestThread2d b 1000" );
    String[] args3 = SysLib.stringToArgs( "TestThread2d c 3000" );
    String[] args4 = SysLib.stringToArgs( "TestThread2d d 6000" );
    String[] args5 = SysLib.stringToArgs( "TestThread2d e 500" );
    SysLib.exec( args1 );
    SysLib.exec( args2 );
    SysLib.exec( args3 );
    SysLib.exec( args4 );
    SysLib.exec( args5 );
    for (int i = 0; i < 5; i++ )
      SysLib.join();
    long endTime = new Date().getTime();
    long totalTime = endTime - startTime;
    SysLib.cout( "Test2d finished; total time = " + totalTime + "\n" );
    SysLib.exit();
  }
}
