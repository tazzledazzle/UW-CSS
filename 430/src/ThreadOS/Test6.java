public class Test6 extends Thread {
  private int fd;   
  public Test6( String[] args ) {
    if ( args.length > 0 )
      fd = Integer.parseInt( args[0] );
    else
      fd = 3; // default assumption: the fd used in Test5 was 3
  }
  public void run() {
    SysLib.cout( "Test6.java: fd = " + fd );
    byte[] buf16 = new byte[16];
    for ( int i = 0; i < 16; i++ )
      buf16[i] = ( byte ) i;
    byte[] tmpBuf = new byte[16];
    int size = SysLib.read( fd, tmpBuf );
    if ( size != 16 ) {
      SysLib.cout( "Test6.java: size = " + size + "(wrong)" );
      SysLib.cout( "fail\n" );
      SysLib.exit();
      return;
    }
    for ( int i = 0; i < 16; i++ )
      if ( tmpBuf[i] != buf16[i] ) {
        SysLib.cout( "Test6.java: tmpBuf[" + i + "] = " + tmpBuf[i] +
           " buf16[" + i + "] = " + buf16[i] + " (wrong)\n" );
        SysLib.cout( "fail\n" );
        SysLib.exit();
        return;
      }
    SysLib.cout( "successfully completed\n" );
    SysLib.cout( "Correct behavior of parent/child reading the file...0.5\n" );

    //.............................................."
    SysLib.cout( "19: uwb1 written by Test6.java..." );
    int fd2 = SysLib.open( "uwb1", "w+" );
    if ( fd2 == -1 ) {
      SysLib.cout( "Test6.java fd2 = -1 (wrong)\n" );
      SysLib.cout( "fail\n" );
      SysLib.exit();
      return;
    }
    byte[] buf512 = new byte[512];
    for ( int i = 0; i < 512; i++ )
      buf512[i] = ( byte ) 100;
    SysLib.write( fd2, buf512 );
    SysLib.close( fd2 );
    SysLib.exit();
  }
}
