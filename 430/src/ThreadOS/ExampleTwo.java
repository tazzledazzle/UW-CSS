


class ExampleTwo extends Thread
{
     
     private String name = "none";

     public ExampleTwo( )
     {
       SysLib.cout("ExampleTwo Constructor running\n");
     }
     
     public ExampleTwo( String args[])
     {
      name = args[0];
      SysLib.cout("ExampleTwo Constructor running. name = " + name + "\n");
     }

     public void run()
     {
      SysLib.cout("ExampleTwo Thread. Priority = " + getPriority() + "\n");
      SysLib.cout("assignment1.ThreadOS.Shell[]: ");
      StringBuffer buffer = new StringBuffer();
      SysLib.cin(buffer);
      String[] commands = SysLib.stringToArgs(buffer.toString());
      
      int tid = SysLib.exec(commands);
      if (tid == -1)
      {
            
      }
      else
      {
       while(tid != SysLib.join())
       {}
      }
      SysLib.sleep(2000);
       
      SysLib.sync();
      SysLib.exit();
     }
}
