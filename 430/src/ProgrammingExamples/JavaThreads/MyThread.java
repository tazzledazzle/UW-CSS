package ProgrammingExamples.JavaThreads;


/**
 * Created by rtdimpsey on 1/14/15.
 */
public class MyThread
{
    public static  void main (String args[])
    {
        String arg = args[0];
        ThreadFunc child = new ThreadFunc(arg);
        child.start();
        for (int i = 0; i < 9; i++)
        {
            try
            {
                Thread.sleep(1000);
            }
            catch (InterruptedException intE) {}
            System.out.println("Parent " + i);
        }
        try
        {
            child.join();
        }
        catch (InterruptedException intE) {}
        System.out.println("Parent DONE!!");
    }
}
