/**
 *
 */
public class SyncQueue {
    private QueueNode[] queue;
    private static int DEFAULT_TID = 0;
    private static int DEFAULT_COND = 10;

    /** SyncQueue
     * constructors that create a queue and allow
     * threads to wait for a default condition number (=10) or a condMax
     * number of condition/event types.
     */
    public SyncQueue()
    {
        queue = new QueueNode[DEFAULT_COND];
        for(int i = 0; i < DEFAULT_COND; i++)
        {
            queue[i] = new QueueNode();

        }
    }

    /** SyncQueue
     * constructors that create a queue and allow
     * threads to wait for a default condition number (=10) or a condMax
     * number of condition/event types.
     * @param maxConditions modifies the size of the queue, or number of queues
     */
    public SyncQueue(int maxConditions)
    {
        queue = new QueueNode[maxConditions];
        for(int i = 0; i < maxConditions; i++)
        {
            queue[i] = new QueueNode();
        }
    }

    /** enqueueAndSleep
     * allows a calling thread to sleep until a given condition is satisfied.
     * @param condition position at which we sleep
     * @return success/failure of sleep()
     */
    public int enqueueAndSleep(int condition)
    {
        if(condition < queue.length)
        {
            if(condition >= 0)
            {
                return queue[condition].sleep();
            }
        }
        return -1;
    }

    /** dequeueAndWakeup
     * dequeues and wakes up a thread waiting for a given condition.
     * If there are two or more threads waiting for the same condition,
     * only one thread is dequeued and resumed. The FCFS (first-come-first-service)
     * order does not matter.
     * @param condition given contdition at which the thread is woken up
     */
    public void dequeueAndWakeup(int condition)
    {
        if(condition >= 0)
        {
            if(condition < queue.length)
            {
                queue[condition].wake(DEFAULT_TID);
            }
        }
    }

    /** dequeueAndWakeup
     * dequeues and wakes up a thread waiting for a given condition.
     * If there are two or more threads waiting for the same condition,
     * only one thread is dequeued and resumed. The FCFS (first-come-first-service)
     * order does not matter.
     * @param condition given condition at which the thread is woken up
     * @param tid the specific identification number that will be woken
     */
    public void dequeueAndWakeup(int condition, int tid)
    {
        if(condition >= 0)
        {
            if(condition < queue.length)
            {
                queue[condition].wake(tid);
            }
        }
    }
}
