package Examples;

/**
 * Created by tazzledazzle on 1/26/15.
 */
public class Worker implements Runnable {


    public void run(){
        while(true) {

            System.out.println("Working hard...");
            try {
                Thread.sleep(100);
            } catch (InterruptedException ie) {
            }
        }
    }
}
