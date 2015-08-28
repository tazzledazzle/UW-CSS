/**
 * Created by rtdimpsey on 1/20/15.
 */
public class Worker implements Runnable
{
    public void run()
    {
        while (true)
        {
            System.out.println("Working... Working Hard!");
            try
            {
                Thread.sleep(500);
            }
            catch (InterruptedException ioe) {}
        }
    }
}
