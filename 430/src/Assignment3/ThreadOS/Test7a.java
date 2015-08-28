public class Test7a extends Thread {
  int fd;
  public Test7a( String[] args ) {
    fd = Integer.parseInt( args[0] );
  }
  public void run() {
    try {
        Thread.sleep( 1000 );
    } catch ( InterruptedException e ) {}
    SysLib.close( fd );
    SysLib.cout( "Test7a: closed fd " + fd + "\n" );
    int fd2 = SysLib.open( "test7a", "w+" );
    SysLib.cout( "Test7a: opened fd " + fd2 + "\n" );
    SysLib.exit();
  }
}
