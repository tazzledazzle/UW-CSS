
import java.util.Vector;

/** QueueNode
 *  This is used when utilizing the SyncQueue. It holds each thread inside of a "queue" and
 *  wakes it up or puts it to sleep
 */
public class QueueNode {
    
    private Vector<Integer> queue;

    /** Default Constructor
     * Instantiates the queue, represented by a Vector
     */
    public QueueNode(){ queue = new Vector<>(); }

    /** Sleep
     * Responsible for putting the thread to sleep using wait()
     * @return success/failure of removal from the queue
     */
    public synchronized int sleep( ) {
        if(queue.size() == 0){ 
            try {
                wait( );

            } catch ( InterruptedException e ) {   
                SysLib.cerr(e.toString() + "\n");   //an error has occured
            }
            return queue.remove(0);
        }
        return -1;
    }

    /** wake
     * wakes up a thread by enqueuing it into the queue.
     * @param tid identifier of the specific thread enqueued
     */
    public synchronized void wake(int tid){
        queue.add(tid);
        notify();
    }
}
