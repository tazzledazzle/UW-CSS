

import java.util.*;

/**
 * Created by tazzledazzle on 2/16/15.
 *
 * Reading/Writing copmutational work done by Test3
 *
 */
class TestThread3b extends Thread{

    private byte[] block;
    public TestThread3b() {}

    public void run(){

        block = new byte[512];
        for (int i = 0; i < 600; i++){
            SysLib.rawwrite(i, block);
            SysLib.rawread(i, block);
        }

        SysLib.exit();
    }
}
