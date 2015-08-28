/*
A simple sample program that will load and run under ThreadOS; 
HelloWorld outputs "Hello world" to standard output and exits.

@author Joe McCarthy

To run this program:
1. Compile the source file in your ThreadOS directory ("javac HelloWorld.java")
2. Boot TheadOS ("java Boot")
3. Load the class file in ThreadOS

Here is an example of what this sequence might look like 
for a user with the UW NetID "joemcc" 
running a shell on uw1-320-16
in the subdirectory ~/ThreadOS:
  [joemcc@uw1-320-16 ThreadOS]$ javac HelloWorld.java
  [joemcc@uw1-320-16 ThreadOS]$ java Boot
  threadOS ver 1.0:
  Type ? for help
  threadOS: a new thread (thread=Thread[Thread-3,2,main] tid=0 pid=-1)
  -->l HelloWorld
  l HelloWorld
  threadOS: a new thread (thread=Thread[Thread-5,2,main] tid=1 pid=0)
  Hello, world
  -->q
  q
  Superblock synchronized
  [joemcc@uw1-320-16 ThreadOS]$ 

*/

public class HelloWorld extends Thread {
  // Any Java class run by ThreadOS must be an extension of the Java Thread class
  // http://download.oracle.com/javase/6/docs/api/java/lang/Thread.html

  public HelloWorld() {
  }
  
  public void run() {
	  SysLib.cout( "Hello, world\n" );  // using SysLib vs System.out
	  SysLib.exit();                    // (see SysLib.java)
	  return;
  }
}
