/**
 * Created by tazzledazzle on 3/3/15.
 * 
 * The file system class is responsible for performing all of the operations on disk. It hides all of the implementation
 * details from users by providing a list of operations which users can directly use. The class implements all the basic
 * functions of a file system as described in lecture, and makes appropriate calls to the components of our system to
 * carry out fundamental actions like format, open, write, read, delete, seek, and close. The file system can be viewed
 * as an API for other files or users to run commands against to access the file system and its contents. The file
 * system has the responsibility of instantiating the other classes that compose our solution.
 *
 * @file FileSystem.java
 * @author Terence Schumacher
 * @author Nick Abel
 * 
 */
public class FileSystem {
    //========================================== Attributes ==============================================
    private static final int SEEK_SET = 0;
    private static final int SEEK_CUR = 1;
    private static final int SEEK_END = 2;
    
    //Gives # partition blocks, size of partition blocks, Free block count, pointers
    private SuperBlock superblock;
    private Directory directory;
    private FileTable filetable;
	private final static boolean SUCCESS = true;
	private final static boolean FAILURE = false;
    

    //============================================= Methods ==============================================
    // Creates superblock, directory, and file table. Stores file table in directory.
    public FileSystem (int blocks)
    {
    	superblock = new SuperBlock(blocks);
    	
    	directory = new Directory(superblock.inodeBlocks);
    	filetable = new FileTable(directory);
    	
    	// read the "/" file from disk
    	FileTableEntry directoryEntry = open( "/", "r");
    	int directorySize = fsize( directoryEntry );
    	if ( directorySize > 0 )
    	{
    		// There is already data in the directory
    		// We must read, and copy it to fsDirectory
    		byte[] directoryData = new byte[directorySize];
    		read( directoryEntry, directoryData );
    		directory.bytes2directory(directoryData);
    	}
    	close( directoryEntry );
    }

	/** Sync
	 * The Sync Method syncs the file system back to the physical disk. The sync method will write the directory
	 * information to the disk in byte form in the root directory. The method will also ensure that the superblock
	 * is synced.
	 */
    public void sync()
    {
    	byte[] tempData = directory.directory2bytes();
    	//open root directory with write access
    	FileTableEntry root = open("/", "w");
        //write directory to root
    	write(root, directory.directory2bytes());
        //close root directory
    	close(root);
        //sync superblock
    	superblock.sync();
    }

	/** Format
	 * The format method performs a full format of the disk, erasing all the contents of the disk and regenerating
	 * the superblock, directory, and file tables. This operation is not reversible, once formatted all contents are
	 * lost. The argument stipulates the number of files (inodes) to be created by the superblock.
	 * @param files amount of files being formatted
	 * @return success always
	 */
    public boolean format( int files){
        //call format on superblock for arg number of files
    	superblock.format(files);
        //create directory, and register "/" in directory entry 0
    	directory = new Directory(superblock.inodeBlocks);
        //file table is created and store directory in the file table
    	filetable = new FileTable(directory);
        //return true on completion
        return SUCCESS;
    }

	/** Open
	 * This function is responsible for opening a file specified by he filename String passed into it. In addition to
	 * the String object, it has passed another String object to represent the mode that the filename object shall have
	 * once created. The function starts out by creating a new FileTableEntry object using fileable’s falloc() function.
	 * Once that gets created, it checks to see if the mode that was passed in is a “w” for write. If it is, it deletes
	 * all blocks and starts writing from scratch. After this check occurs, the new FileTableEntry object is returned
	 * to the calling function.
	 * @param filename name of file opening
	 * @param mode purpose of open
	 * @return the file table entry opened
	 */
    public FileTableEntry open(String filename, String mode){
    	//file name is passed to directory
    	//which is passed to file control block
    	//allocate a new filetable entry, specifying the filename and the mode
    	FileTableEntry ftEntry = filetable.falloc(filename, mode);
        // check if writing mode
    	if (mode == "w")
    	{
    		// if so, make sure all blocks are unallocated
    		if ( !deallocAllBlocks( ftEntry ))
    		{
    			return null;
    		}
    	}
        //return FileTableEntry, not null    
    	return ftEntry;
    }

	/** Close
	 * This function closes the file corresponding to the given file table entry. It returns true in the case of
	 * successful performance of the operation, false otherwise.
	 * @param entry table entry to close
	 * @return return free status or true
	 */
    public boolean close(FileTableEntry entry){
    	//cast the entry as synchronized
    	synchronized(entry) {
			// decrease the number of users
			entry.count--;

			if (entry.count == 0) {
				return filetable.ffree(entry);
			}
			return true;
		}
    }

	/** Read
	 * Read operation runs atomically. Checks target block to make sure it is valid to read from. Else breaks. Then
	 * reads block and calculates the buffer based on data size. The amount of data read during each loop is determined
	 * by the buffer size, and it gets read from the entry.
	 * @param entry table entry reading from
	 * @param buffer size of data being read
	 * @return amount of data read
	 */
    public int read(FileTableEntry entry, byte[] buffer){
    	//entry is index of file in process open-file table
    	//this accesses system wide open file table
    	//data blocks accessed, file control block returned
    	
        //check write or append status
		if ((entry.mode == "w") || (entry.mode == "a"))
			return -1;

        int size  = buffer.length;   //set total size of data to read
        int rBuffer = 0;            //track data read
        int rError = -1;            //track error on read
        int blockSize = 512;        //set block size
        int itrSize = 0;            //track how much is left to read
//        fileLength = fsize(entry);
//        int fLeft = 0;

        //cast the entry as synchronized
        //loop to read chunks of data
        
        synchronized(entry)
        {
        	while (entry.seekPtr < fsize(entry) && (size > 0))
        	{
        		int currentBlock = entry.inode.findTargetBlock(entry.seekPtr);
        		if (currentBlock == rError)
        		{

        			break;
        		}
				byte[] data = new byte[blockSize];
        		SysLib.rawread(currentBlock, data);
        		
        		int dataOffset = entry.seekPtr % blockSize;
        		int blocksLeft = blockSize - itrSize;
        		int fileLeft = fsize(entry) - entry.seekPtr;
        		
        		if (blocksLeft < fileLeft)
					itrSize = blocksLeft;
				else
				    itrSize = fileLeft;

				if (itrSize > size)
					itrSize = size;

        		System.arraycopy(data, dataOffset, buffer, rBuffer, itrSize);
        		rBuffer += itrSize;
        		entry.seekPtr += itrSize;
        		size -= itrSize;
        	}
        	return rBuffer;
        }
    }

	/** Write
	 * Writes the contents of buffer to the file indicated by entry, starting at the position indicated by the seek
	 * pointer. Increments the seek pointer by the number of bytes to have been written. The return value is the number
	 * of bytes that have been written, or -1 upon an error.
	 * @param entry file table entry writing to
	 * @param buffer contents to be written
	 * @return number of bytes written, -1 if failure
	 */
    public int write(FileTableEntry entry, byte[] buffer){
    	int bytesWritten = 0;
		int bufferSize = buffer.length;
		int blockSize = 512;

		if (entry == null || entry.mode == "r")
		{
			return -1;
		}

		synchronized (entry)
		{
			while (bufferSize > 0)
			{
				int location = entry.inode.findTargetBlock(entry.seekPtr);

				// if current block null
				if (location == -1)
				{
					short newLocation = (short) superblock.nextFreeBlock();

					int testPtr = entry.inode.getIndexBlockNumber(entry.seekPtr, newLocation);

					if (testPtr == -3)
					{
						short freeBlock = (short) this.superblock.nextFreeBlock();

						// indirect pointer is empty
						if (!entry.inode.setIndexBlock(freeBlock))
						{
							return -1;
						}

						// check block pointer error
						if (entry.inode.getIndexBlockNumber(entry.seekPtr, newLocation) != 0)
						{
							return -1;
						}

					}
					else if (testPtr == -2 || testPtr == -1)
					{
						return -1;
					}

					location = newLocation;
				}

				byte [] tempBuff = new byte[blockSize];
				SysLib.rawread(location, tempBuff);

				int tempPtr = entry.seekPtr % blockSize;
				int diff = blockSize - tempPtr;

				if (diff > bufferSize)
				{
					System.arraycopy(buffer, bytesWritten, tempBuff, tempPtr, bufferSize);
					SysLib.rawwrite(location, tempBuff);

					entry.seekPtr += bufferSize;
					bytesWritten += bufferSize;
					bufferSize = 0;
				}
				else {
					System.arraycopy(buffer, bytesWritten, tempBuff, tempPtr, diff);
					SysLib.rawwrite(location, tempBuff);

					entry.seekPtr += diff;
					bytesWritten += diff;
					bufferSize -= diff;
				}
			}

			// update inode length if seekPtr larger

			if (entry.seekPtr > entry.inode.length)
			{
				entry.inode.length = entry.seekPtr;
			}
			entry.inode.toDisk(entry.iNumber);
			return bytesWritten;
		}
    }


	/** Seek
	 * This function updates the seek pointer corresponding to a given file table entry. It returns 0 if the update was
	 * successful, -1 otherwise. In the case that the user attempts to set the seek pointer to a negative number, the
	 * method will set it to 0. In the case that the user wants to set the pointer beyond the file size the method sets
	 * the seek pointer to the end of the file. In both cases the method returns that the operation was performed
	 * successfully.
	 * @param entry the file table entry querying
	 * @param offset initial offset
	 * @param location start of seek pointer
	 * @return seek pointer of the entry
	 */
    public int seek(FileTableEntry entry, int offset, int location){
    	
    	synchronized (entry)
		{
			switch(location)
			{
				//beginning of file
				case SEEK_SET:
					//set seek pointer to offset of beginning of file
					entry.seekPtr = offset;
					break;
				// current position
				case SEEK_CUR:
					entry.seekPtr += offset;
					break;
				// if from end of file
				case SEEK_END:
					// set seek pointer to size + offset
					entry.seekPtr = entry.inode.length + offset;
					break;
				// unsuccessful
				default:
					return -1;
			}

			if (entry.seekPtr < 0)
			{
				entry.seekPtr = 0;
			}

			if (entry.seekPtr > entry.inode.length)
			{
				entry.seekPtr = entry.inode.length;
			}

			return entry.seekPtr;
		}
    }

	/** Deallocate All Blocks
	 * Checks if inodes blocks are valid, else error. Then runs through all the direct pointer blocks and calls
	 * superblock to return if valid. It then handles indirect pointer from inode and calls returnBlock(). It finishes
	 * by writing back inodes to disk.
	 * @param fileTableEntry entry deallocating
	 * @return true if successful, false othewise
	 */
    private boolean deallocAllBlocks(FileTableEntry fileTableEntry){
    short invalid = -1;
    	if (fileTableEntry.inode.count != 1)
		{
			SysLib.cerr("Null Pointer");
			return false;
		}

		for (short blockId = 0; blockId < fileTableEntry.inode.directSize; blockId++)
		{
			if (fileTableEntry.inode.direct[blockId] != invalid)
			{
				superblock.returnBlock(blockId);
				fileTableEntry.inode.direct[blockId] = invalid;
			}
		}

		byte [] data = fileTableEntry.inode.freeIndirectBlock();

		if (data != null)
		{
			short blockId;
			while((blockId = SysLib.bytes2short(data, 0)) != invalid)
			{
				superblock.returnBlock(blockId);
			}
		}
		fileTableEntry.inode.toDisk(fileTableEntry.iNumber);
		return true;
    }

	/** Delete
	 * This function is responsible for deleting a specified file as per determined by the filename string param passed
	 * in. It begins by opening and creating a temporary FileTableEntry object to contain the iNode (TCB) object. This
	 * allows us to have access to all private members of this desired filename entry. With this iNode, we use it’s
	 * iNumber to free it up from Directory’s tables. Afterwards, we close the FileTableEntry object using the close()
	 * function. As long as both the free() and close() are successful, we return true. Otherwise we return false
	 * indicating that it is still open elsewhere.
	 * @param fileName name of the file set for deletion
	 * @return state of operation
	 */
	boolean delete(String filename) {
		FileTableEntry tcb = open(filename, "w");       //Grab the TCB (iNode)
		if (directory.ifree(tcb.iNumber) && close(tcb)) { //try to free and
			// delete
			return SUCCESS;                              //Delete was completed
		} else {
			return FAILURE;                              //Was not last open
		}
	}

	/** fSize
	 * Returns the file size in bytes atomically.
	 * @param entry the fileTableEntry querying
	 * @return size of entry
	 */
    public synchronized int fsize(FileTableEntry entry){
        //cast the entry as synchronized
    	synchronized(entry)
    	{
	        // Set a new Inode object to the entries Inode
			Inode inode = entry.inode;
	        // return the length on the new Inode object
    		return inode.length;
    	}
    }
}
