

import java.util.Vector;

/**
 * @file FileTable.java
 * @author Terence Schumacher
 * @author Nick Abel
 *
 * File (Structure) Table is a class which represents the set of file table entries. Each file table entry represents
 * one file descriptor. The main purpose of this class is to create a new file table entry when it is required and then
 * add that to the Vector of file table entry. It removes the file table entry from Vector when it is freed.
 *
 */
public class FileTable {
    public final static int UNUSED = 0;
    public final static int USED = 1;
    public final static int READ = 2;
    public final static int WRITE = 3;

    private Vector<FileTableEntry> table;         // the actual entity of this file table
    private Directory dir;        // the root directory

    /** Consturctor
     * Instantiates FileTableEntry table and sets directory to passed Directory reference
     * @param directory creation directory
     */
    public FileTable( Directory directory ) { // constructor
        table = new Vector<FileTableEntry>( );     // instantiate a file (structure) table
        dir = directory;           // receive a reference to the Director
    }                             // from the file system

    // major public methods

    /** falloc
     * Function is responsible for creating a FileTableEntry for requested file. It’s ensure, that the file is not
     * opened for write mode for more than one thread and when file is being written other threads cannot read it.
     * When thread wants to open file for write mode, which is already opened of write mode its waiting until previous
     * thread which writes to this file close its FileTableEntry. When file does not exist and is being opened for write
     * mode it is being created. It also increments the number of threads used given the inode as well it is saving
     * created FileTableEntry into internal arrays.
     * @param filename name of allocated resource
     * @param mode type of situation
     * @return
     */
    public synchronized FileTableEntry falloc( String filename, String mode ) {
        short iNumber = -1; // inode number
        Inode inode = null; // holds inode

        while (true) {
            // get the inumber form the inode for given file name
            iNumber = (filename.equals("/") ? (short) 0 : dir.namei(filename));

            // if the inode for the given file exist
            if (iNumber >= 0) {
                inode = new Inode(iNumber);

                // if the file is requesting ofr reading
                if (mode.equals("r")) {

                    // and its flag is read or used or unused
                    // (nobody has read or written to that file)
                    if (inode.flag == READ
                            || inode.flag == USED
                            || inode.flag == UNUSED) {

                        // change the flag of the node to read and break
                        inode.flag = READ;
                        break;

                        // if the file is already written by someone, wait until finish
                    } else if (inode.flag == WRITE) {
                        try {
                            wait();
                        } catch (InterruptedException e) { }
                    }

                    // if the file is requested for writing or writing/riding or append
                } else {

                    // and the flag of that file is used, change the flag to write
                    if (inode.flag == USED || inode.flag == UNUSED) {
                        inode.flag = WRITE;
                        break;

                        // if the flag is read or write, wait until they finish
                    } else {
                        try {
                            wait();
                        } catch (InterruptedException e) { }
                    }
                }

                // if the node for the given file does not exist,
                // create a new inode for that file, use the alloc function from
                // directory to get the inumber
            } else if (!mode.equals("r")) {
                iNumber = dir.ialloc(filename);
                inode = new Inode(iNumber);
                inode.flag = WRITE;
                break;

            } else {
                return null;
            }
        }

        inode.count++;  // increse the number of users
        inode.toDisk(iNumber);
        // create new file table entry and add it to the file table
        FileTableEntry entry = new FileTableEntry(inode, iNumber, mode);
        table.addElement(entry);
        return entry;
    }

    /** ffree
     * This function is responsible for closing and removing FileTableEntry from cached list. If the thread was the
     * last user of FileTableEntry, it wakes up another thread with reading status, or all threads if writing status
     * occurs.
     * @param entry table entry to free
     * @return boolean depicting the status of free
     */
    public synchronized boolean ffree( FileTableEntry entry ) {
        // receive a file table entry reference
        Inode inode = new Inode(entry.iNumber);
        //try and remove FTE if it is in table, the remove will return true
        // return true if this file table entry found in my table
        if (table.remove(entry))
        {
            if (inode.flag == READ)
            {
                if (inode.count == 1)
                {
                    // free this file table entry.
                    notify();
                    inode.flag = USED;
                }
            }
            else if (inode.flag == WRITE)
            {
                inode.flag = USED;
                notifyAll();
            }
            //decrease the count of users of that file
            inode.count--;
            // save the corresponding inode to the disk
            inode.toDisk(entry.iNumber);
            return true;
        }
        return false;
    }

    /** fempty
     * This function returns true if there is not any FileTableEntry cached inside FileTable, and false otherwise.
     * @return boolean value depicting the state of entry
     */
    public synchronized boolean fempty( ) {
        return table.isEmpty( );  // return if table is empty
    }                            // should be called before starting a format
}
