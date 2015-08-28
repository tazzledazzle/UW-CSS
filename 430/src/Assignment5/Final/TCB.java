
/**
 * Created by tazzledazzle on 3/6/15.
 */
public class TCB {
    public static int MAX_ENTRY = 32;
    public static int ERROR = -1;
    private Thread thread = null;
    private int tid = 0;
    private int pid = 0;
    private boolean terminate = false;

    // User file descriptor table:
    // each entry pointing to a file (structure) table entry
    public FileTableEntry[] ftEnt = null;

    public TCB( Thread newThread, int myTid, int parentTid ) {
        thread = newThread;
        tid = myTid;
        pid = parentTid;
        terminate = false;

        // The following code is added for the file system
        ftEnt = new FileTableEntry[MAX_ENTRY];
//        for ( int i = 0; i < MAX_ENTRY; i++ )
//            ftEnt[i] = null;         // all entries initialized to null
//        // fd[0], fd[1], and fd[2] are kept null.
//    }
    }

    public synchronized Thread getThread(){
        return thread;
    }

    public synchronized int getTid(){
        return tid;
    }

    public synchronized int getPid(){
        return pid;
    }

    public synchronized boolean setTerminated(){
        terminate = true;
        return terminate;
    }

    public synchronized boolean getTerminated(){
        return terminate;
    }

    /**
     *
     * @param entry
     * @return
     */
    public synchronized int getFd(FileTableEntry entry){
        if (entry == null)
            return ERROR;
        for (int i = 3; i < MAX_ENTRY; i++){
            if (ftEnt[i] == null){
                ftEnt[i] = entry;
                return i;
            }
        }
        return ERROR;
    }

    public synchronized FileTableEntry returnFd(int fd){

        if (fd >= 3 && fd < MAX_ENTRY){
            FileTableEntry fte = ftEnt[fd];
            ftEnt[fd] = null;
            return fte;
        }

        return null;
    }

    public synchronized FileTableEntry getFtEnt(int fd){
        if (fd >= 3 && fd < MAX_ENTRY){
            return ftEnt[fd];
        }
        return null;
    }
}
