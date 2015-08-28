package ProgrammingExamples.JavaThreads;

/**
 * Created by rtdimpsey on 1/14/15.
 */
public class ThreadFunc extends Thread
{
    private String param;
    public ThreadFunc(String strInit)
    {
        param = strInit;
    }
    public void run()
    {
        for (int i = 0; i < 2; i++)
        {
            try
            {
                Thread.sleep(2000);
            }
            catch (InterruptedException ioe) {}
            System.out.println("Child " + i + " " + param);
        }
    }
}
