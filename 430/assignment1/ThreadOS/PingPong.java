public class PingPong extends Thread {
  private String word;
  private int loop;
  public PingPong( String[] args ) {
    word = args[0];
    loop = Integer.parseInt( args[1] );
  }
  public void run( ) {
    for ( int j = 0; j < 100; j++ ) {
      // substituting SysLib.cout() for System.out.println()
      // System.out.print( word + " " );
      SysLib.cout( word + " " );
      // substituting SysLib.sleep() for busy wait for loop
      // for ( int i = 0; i < loop; i++ ) ;
      SysLib.sleep( loop );
    }
    SysLib.cout( "\n" );
    SysLib.exit( );
  }
}
