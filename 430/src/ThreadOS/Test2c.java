import java.util.Date;

class Test2c extends Thread {

  public void run() {
    long startTime = new Date().getTime();
    String[] args1 = SysLib.stringToArgs( "TestThread2c a 5000 0" );
    String[] args2 = SysLib.stringToArgs( "TestThread2c b 1000 0" );
    String[] args3 = SysLib.stringToArgs( "TestThread2c c 3000 0" );
    String[] args4 = SysLib.stringToArgs( "TestThread2c d 6000 0" );
    String[] args5 = SysLib.stringToArgs( "TestThread2c e 500  0" );
    SysLib.exec( args1 );
    SysLib.exec( args2 );
    SysLib.exec( args3 );
    SysLib.exec( args4 );
    SysLib.exec( args5 );
    for (int i = 0; i < 5; i++ )
      SysLib.join();
    long endTime = new Date().getTime();
    long totalTime = endTime - startTime;
    SysLib.cout( "Test2c finished; total time = " + totalTime + "\n" );
    SysLib.exit();
    }
}
