/**
 * Shell.java
 * 
 * A simple example which shows some of the characteristics of THREADOS
 *
 * @author Bob Dimpsey
 */

class Example extends Thread
{
   private String name = "none";

   public Example( ) 
   {
      SysLib.cout( "Example: constructor invoked \n" );
   }

   public Example( String args[] ) 
   {
      name = args[0];
      SysLib.cout( "Example: constructor invoked \n" );
   }
   
   public void run() 
   {

       SysLib.cout("Example Thread.  Priority = " + getPriority() + "\n");
       SysLib.cout("Example Thread name = " + name + "\n");

       SysLib.cout("Shell[] ");
       StringBuffer buffer = new StringBuffer(); 
       SysLib.cin( buffer );
       String[] command = SysLib.stringToArgs( buffer.toString() );

       int tid = SysLib.exec(command);
       if (tid == -1)
       {
          SysLib.cerr("ERROR: \n");
       }
       else
       {
          SysLib.cout("TID executed: " + tid + "\n");
          tid = SysLib.join();
          SysLib.cout("TID joined: " + tid + "\n");
       }

       SysLib.sleep(1000);
       SysLib.sync( );
       SysLib.exit( );
   }
}
