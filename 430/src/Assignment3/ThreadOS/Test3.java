
import java.util.*;
import java.util.Date;

/**
 * Created by tazzledazzle on 2/16/15.
 * Write a user-level test thread called Test3.java which spawns and waits for the
 * completion of X pairs of threads (where X = 1 ~ 4), one conducting only numerical
 * computation and the other reading/writing many blocks randomly across the disk.
 *
 * Those two types of threads may be written in TestThread3a.java and TestThread3b.java
 * separately or written in TestThread3.java that receives an argument and conducts computation
 * or disk accesses according to the argument.
 *
 * Test3.java should measure the time elapsed from the spawn to the termination of its child threads.
 *
 * User enters X

 */
public class Test3 extends Thread {

    private int threadPairs;
    private long startTime;
    private long endTime;
    public Test3(String args[]) {
        threadPairs = Integer.parseInt(args[0]);
    }

    public void run() {
        startTime = new Date().getTime();
        String [] numComp = SysLib.stringToArgs("TestThread3a");
        String [] rwComp = SysLib.stringToArgs("TestThread3b");

        for(int i = 0; i < threadPairs; i++)//for 1 to x execute TestThread3a
        {
            SysLib.exec(numComp);
        }

        for (int i = 0; i < threadPairs; i++)//for 1 to x execute TestThread3b
        {
            SysLib.exec(rwComp);
        }

        //Numerical Work
        for(int i = 0; i < threadPairs; i++)
        {
            SysLib.join();
            SysLib.cout("comp finished...\n");
        }

        //reading/writing
        for(int i = 0; i < threadPairs; i++)
        {
            SysLib.join();
            SysLib.cout("disk finished...\n");
        }

        endTime = new Date().getTime();     //get completion time

        SysLib.cout("Elapsed time = " +(endTime - startTime) + "\n");
        SysLib.exit();
    }
}
