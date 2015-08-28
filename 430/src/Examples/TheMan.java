package Examples;

/**
 * Created by tazzledazzle on 1/26/15.
 */
public class TheMan {
     int NUM_WORKERS = 7;
    public static void main(String args[])
    {
        TheMan man = new TheMan();
    }

    TheMan()
    {
        Runnable[] worker = new Worker[NUM_WORKERS];
        Thread[] myThread = new Thread[NUM_WORKERS];
        for (int i = 0; i < NUM_WORKERS; i++)
        {
            worker[i] = new Worker();
            myThread[i] = new Thread(worker[i]);
            myThread[i].start();
        }

        while(true)
        {
            System.out.println("Manager... are you Working?");
            try{
                Thread.sleep(1000);
            } catch (InterruptedException ie) {}
        }
    }
}
