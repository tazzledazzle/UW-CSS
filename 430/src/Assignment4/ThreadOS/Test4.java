import java.util.Arrays;
import java.util.Date;
import java.util.Random;

/**
 * Created by tazzledazzle on 2/23/15.
 */
public class Test4 extends Thread{
    private static final int blockSize = 512;
    private static final int arraySize = 350;
    private byte[] writeBlock;
    private byte[] readBlock;
    private int test = 0;
    private boolean caching = false;
    private long startReadTime;
    private long startWriteTime;
    private long stopReadTime;
    private long stopWriteTime;
    private Random random;
    private String label = "Uninitialized";

    public Test4 (String args[]){
        test = Integer.parseInt(args[1]);
        writeBlock = new byte[blockSize];
        readBlock = new byte[blockSize];
        random = new Random();
        random.nextBytes(writeBlock);
        if (args[0].equals("enabled")){
            caching = true;
        }
        else {
            caching = false;
        }

    }
    public void run(){
        SysLib.flush();

        switch (test){
            case 1: randomAccess();
                break;
            case 2: localizedAccess();
                break;
            case 3: mixedAccess();
                break;
            case 4: adversaryAccess();
                break;
            default: SysLib.cout("WARN: Invalid Argument\n ");
                break;
        }
        sync();
        SysLib.exit();
    }
    //    random accesses with cache disabled
    //    random accesses with cache enabled
    public void randomAccess(){
        label = "Random Access Test ";
        int [] randomLocation = new int[arraySize];
        for (int i = 0; i < arraySize; i++){
            randomLocation[i] = randomInt(512);
        }
        startWriteTime = getTime();
        for (int i = 0; i < arraySize; i++){
            write(randomLocation[i], writeBlock);
        }
        stopWriteTime = getTime();
        startReadTime = getTime();
        for (int i = 0; i < arraySize; i++){
            read(randomLocation[i], readBlock);
        }
        stopReadTime = getTime();
        validate();
        results();

    }

    //    localized accesses with cache disabled
    //    localized accesses with cache enabled
    public void localizedAccess(){
        label = "Localized Access Test";
        startWriteTime = getTime();
        for (int i = 0; i < arraySize; i++){
            for (int j = 0; j < 10; j++){
                write(j, writeBlock);
            }
        }
        stopWriteTime = getTime();
        startReadTime = getTime();
        for (int i = 0; i < arraySize; i++){
            for (int j = 0; j < 10; j++){
                read(j, readBlock);
            }
        }
        stopReadTime = getTime();

        validate();
        results();
    }

    //    mixed accesses with cache disabled
    //    mixed accesses with cache enabled
    public void mixedAccess(){
        label = "Mixed Access Test";
        int [] mixedAcc = new int[arraySize];
        for (int i = 0; i < arraySize; i++){
            if (randomInt(10) < 9){
                mixedAcc[i] = randomInt(10);
            }
            else{
                mixedAcc[i] = randomInt(512);
            }
        }

        startWriteTime = getTime();
        for (int i = 0; i < arraySize; i++){
            write(mixedAcc[i], writeBlock);
        }
        stopWriteTime = getTime();

        startReadTime = getTime();
        for (int i = 0; i < arraySize; i++){
            read(mixedAcc[i], readBlock);
        }
        stopReadTime = getTime();
        validate();
        results();
    }

    //    adversary accesses with cache disabled
    //    adversary accesses with cache enabled
    public void adversaryAccess(){
        label = "Adversary Access Test";

        startWriteTime = getTime();
        for (int i = 0; i < blockSize; i++){
            write(i, writeBlock);
        }
        stopWriteTime = getTime();

        startReadTime = getTime();
        for (int i = 0; i < blockSize; i++){
            read(i, readBlock);
        }
        stopReadTime = getTime();

        validate();
        results();
    }
    public void sync(){
        if (caching){
            SysLib.csync();
        }
        else{
            SysLib.sync();
        }
    }
    public void read(int blockId, byte buffer[]){
        if (caching){
            SysLib.cread(blockId, buffer);
        } else {
            SysLib.rawread(blockId, buffer);
        }
    }
    public void write(int blockId, byte buffer[]){
        if (caching){
            SysLib.cwrite(blockId, buffer);
        } else {

            SysLib.rawwrite(blockId, buffer);
        }
    }
    public void validate(){
        if(!Arrays.equals(readBlock, writeBlock))
        {
            SysLib.cout("WARN: read and write block differ\n");
        }
    }
    public void results(){
        String status = caching ? "Enabled" : "Disabled";
        SysLib.cout("Test: " + label + " With Caching " + status + "\n");
        SysLib.cout("Average Write: " + getAverageWrite() + " msec Average Read: " + getAverageRead() +" msec \n" );
    }
    public int randomInt(int max){
        return (Math.abs(random.nextInt() % max));
    }
    //Timers
    public long getAverageWrite() {
        return (stopWriteTime - startWriteTime) / arraySize;
    }
    public long getAverageRead(){
        return (stopReadTime - startReadTime) / arraySize;
    }
    public long getTime() {
        return new Date().getTime();
    }
    //The 1st argument: directs that a test will use the disk cache or not.
        // Test4.java uses SysLib.rawread, SysLib.rawwrite, and SysLib.sync system
        // calls if the argument specifies "no use of disk cache", otherwise SysLib.cread,
        // SysLib.cwrite, and SysLib.csync system calls.
    //The 2nd argument: directs one of the above four performance tests.
   // For each test, your Test4.java should display the average read time and average write time. Compare the performance and consider the results when you run each of the above four test cases with and without the disk cache.
}
