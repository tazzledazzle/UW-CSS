//*****************************************************************************
//**  File: TestPingPong.java
//**  Date: October 2011
//**  Author: Joe McCarthy
//**
//**  Description: A demonstration of using SysLib simulated system calls 
//**    SysLib.exec() and SysLib.join()
//**    to execute either sequential or concurrent processes.
//**    After this program has been byte-compiled (--> TestPingPong.class),
//**      Boot ThreadOS (via 'java Boot' at  Linux shell prompt),
//**      and run this program via the Loader ('l TestPingPong').
//*****************************************************************************

public class TestPingPong extends Thread {

    public TestPingPong() {
	// nothing to initialize in constructor
    }

    // have to define the run() method for any Thread class extension
    public void run() {
	int tid1, tid2;          // thread IDs, created via SysLib.exec() calls
	int status1, status2;    // values returned when SysLib.join() called
	String argstr1, argstr2; // strings representing PingPong commands
	String[] args1, args2;   // PingPong string commands split into arguments
	SysLib.cout( "Testing PingPong\n" );
	argstr1 = "PingPong abc 100";  // 2x slower than argstr2
	args1 = SysLib.stringToArgs( argstr1 );  // split into args
	argstr2 = "PingPong xyz 50";   // 2x faster than argstr1
	args2 = SysLib.stringToArgs( argstr2 );
	// sequential processes
	SysLib.cout( "Running '" + argstr1 + " ; " + argstr2 + " ;'\n" );
	tid1 = SysLib.exec( args1 ); // start 1st proces
	status1 = SysLib.join();     // wait for 1st process to end
	tid2 = SysLib.exec( args2 ); // now exec() 2nd process
	status2 = SysLib.join();     // wait for 2nd process to end
	SysLib.cout( "tid1: " + tid1 + "; status1: " + status1 + "\n" );
	SysLib.cout( "tid2: " + tid2 + "; status2: " + status2 + "\n" );
	// concurrent processes
	SysLib.cout( "Running '" + argstr1 + " & " + argstr2 + " &'\n" );
	tid1 = SysLib.exec( args1 ); // start 1st process
	tid2 = SysLib.exec( args2 ); // start 2nd process
	status1 = SysLib.join();     // wait for some process to end
	status2 = SysLib.join();     // wait for other process to end
	SysLib.cout( "tid1: " + tid1 + "; status1: " + status1 + "\n" );
	SysLib.cout( "tid2: " + tid2 + "; status2: " + status2 + "\n" );
	SysLib.exit();
    }
}