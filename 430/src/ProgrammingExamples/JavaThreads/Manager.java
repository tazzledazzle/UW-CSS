/**
 * Created by rtdimpsey on 1/20/15.
 */
public class Manager
{
    private final static int NUM_WORKERS;
    static
    {
        NUM_WORKERS = 10;
    }

    public static void main(String args[])
    {
        Manager man = new Manager();
    }

    Manager()
    {
        Runnable[] workers = new Worker[NUM_WORKERS];
        Thread[] myThreads = new Thread[NUM_WORKERS];

        for (int i = 0; i < NUM_WORKERS; i++)
        {
            workers[i] = new Worker();
            myThreads[i] = new Thread(workers[i]);
            myThreads[i].start();
        }
        while (true)
        {
            System.out.println("Manager ....");
            try
            {
                Thread.sleep(2000);
            }
            catch (InterruptedException ioe) {}
        }
    }
}
