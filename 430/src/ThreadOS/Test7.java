public class Test7 extends Thread {
  public void run() {
    String[] cmd = new String[2];
    int fd1 = SysLib.open( "test1", "w+" );
    SysLib.cout( "Test7: opened fd " + fd1 + "\n" );
    int fd2 = SysLib.open( "test2", "w+" );
    SysLib.cout( "Test7: opened fd " + fd2 + "\n" );
    cmd[0] = "Test7a";
    cmd[1] = String.format( "%d", fd2 );
    // Test7a should close fd2, then open another fd but not close it
    SysLib.exec( cmd );
    SysLib.close( fd2 );
    SysLib.cout( "Test7: closed fd " + fd2 + "\n" );
    int tid = SysLib.join();
    int fd3 = SysLib.open( "test3", "w+" );
    SysLib.cout( "Test7: opened fd " + fd3 + "\n" );
    if ( fd3 != 4 )
      SysLib.cout( "Test7: error; fd should be 4\n" );
    else
      SysLib.cout( "Test7: completed successfully\n" );
    SysLib.close( fd1 );
    SysLib.cout( "Test7: closed fd " + fd1 + "\n" );
    SysLib.close( fd3 );
    SysLib.cout( "Test7: closed fd " + fd3 + "\n" );
    SysLib.cout( "Now formatting to ensure that FileTable is empty\n");
    SysLib.format( 64 );
    SysLib.exit();
  }
}
