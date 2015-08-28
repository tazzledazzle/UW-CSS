/**
 * @file SuperBlock.java
 * @author Terence Schumacher
 * @author Nick Abel
 *
 * The superblock is a component of the file system implemented in the CSS430 final project in ThreadOS. It is a block
 * of metadata that describes the file system and its componenets. It reads the physical SuperBlock from disk, validates
 * the health of the disk and provides methods for identifying free blocks, adding blocks to the free list, and writing
 * back to disk the contents of SuperBlock. If validation fails, it will format the disk and write a new SuperBlock to
 * disk
 *
 */
public class SuperBlock {
	private final int defaultInodeBlocks = 64;
	private final int totalBlockLocation = 0;
	private final int totalInodeLocation = 4;
	private final int freeListLocation = 8;
	private final int defaultBlocks = 1000;

    public int totalBlocks; // the number of disk blocks
    public int totalInodes; // the number of inodes
    public int freeList;    // the block number of the free list's head

	public int inodeBlocks;

	/** Constructor
	 * Public constructor for SuperBlock accepts a single int argument equal to the total number of blocks on Disk.
	 * The constructor will read the SuperBlock from disk and initialize member variables for the number of blocks, the
	 * number of inodes, and the block number of the free list’s head.
	 * @param numBlocks
	 */
	public SuperBlock(int numBlocks){

		byte [] superBlock = new byte[Disk.blockSize];

		SysLib.rawread(0, superBlock);

		totalBlocks = SysLib.bytes2int(superBlock, totalBlockLocation);
		totalInodes = SysLib.bytes2int(superBlock, totalInodeLocation);

		freeList = SysLib.bytes2int(superBlock, freeListLocation);

		inodeBlocks = totalInodes;

		//disk contents validation
		if (totalBlocks == numBlocks && totalInodes > 0 && freeList >= 2){
			return;     // valid
		}
		else
		{
			totalBlocks = numBlocks;
			format(defaultInodeBlocks);
		}
	}

	/** Sync
	 * The Sync method brings the physical SuperBlock contents (at block zero on disk) in line with any updates
	 * performed to the SuperBlock class instance. Sync will write back to disk the total number of blocks, the total
	 * number of inodes, and the free list.
	 */
	public void sync ()
	{
		byte[] tempData = new byte[Disk.blockSize];
		SysLib.int2bytes(freeList, tempData, freeListLocation);
		SysLib.int2bytes(totalBlocks, tempData, totalBlockLocation);
		SysLib.int2bytes(totalInodes, tempData, totalInodeLocation);

		SysLib.rawwrite(0, tempData);
	}

	/** Next Free Block
	 * The nextFreeBlock method returns the first free block from the free list. The free block is the top block from
	 * the free queue and is returned as an integer value. If there is any error (absence of free blocks) -1 is returned
	 * to notify the user the operation failed.
	 * @return
	 */
	public int nextFreeBlock()
	{
		if (freeList > 0 && freeList < totalBlocks)
		{
			byte[] tempData = new byte[Disk.blockSize];
			SysLib.rawread(freeList, tempData);

			int temp = freeList;

			// update next free block
			freeList = SysLib.bytes2int(tempData, 0);

			// return block location
			return temp;
		}

		return -1; //invalid freeList state
	}

	/** Return Block
	 * The returnBlock method attempts to add a newly freed block back to the free list. The newly freed block is added
	 * to the end of the free block queue which operates as FIFO. If the freed block does not conform to the actual disk
	 * parameters held in SuperBlock, the operation fails and returns false.
	 * @param blockNumber
	 * @return
	 */
	public boolean returnBlock(int blockNumber)
	{
		if (blockNumber > 0 && blockNumber < totalBlocks)
		{
			int nextFree = freeList;
			int temp = 0;

			byte [] next = new byte[Disk.blockSize];

			byte [] newBlock = new byte[Disk.blockSize];


			//erase block
			for(int i = 0; i < Disk.blockSize; i++)
			{
				newBlock[i] = 0;
			}

			SysLib.int2bytes(-1, newBlock, 0);

			while (nextFree != -1)
			{
				SysLib.rawread(nextFree, next);

				temp = SysLib.bytes2int(next, 0);

				if (temp == -1)
				{
					// set next free
					SysLib.int2bytes(blockNumber, next, 0);
					SysLib.rawwrite(nextFree, next);
					SysLib.rawwrite(blockNumber, newBlock);

					return true;    //operation complete
				}

				nextFree = temp;
			}
		}

		return false;   // invalid block returned
	}

	/** Format
	 * The public format method cleans the disk of all data and resets the correct structure if the SuperBlock detects
	 * an illegal state during initialization of an instance. All instance variables of SuperBlock are cleared to
	 * default values and written back to the newly cleared disk.
	 * @param numberOfFiles
	 */
    public void format (int numberOfFiles){

		if (numberOfFiles < 0)
		{
			numberOfFiles = defaultInodeBlocks;
		}

		totalInodes = numberOfFiles;
		inodeBlocks = totalInodes;
		Inode dummy = null;

		for (int i = 0; i < totalInodes; i++)
		{
			dummy = new Inode();
			dummy.flag = 0;
			dummy.toDisk((short) i);
		}

		freeList = (totalInodes / 16) + 2;

		byte [] newEmpty = null;    // new dummy block

		for (int i = freeList; i < defaultBlocks - 1; i++)
		{
			newEmpty = new byte [Disk.blockSize];

			//erase
			for (int j = 0; j < Disk.blockSize; j++)
			{
				newEmpty[j] = 0;
			}

			SysLib.int2bytes(i+1, newEmpty, 0);
			SysLib.rawwrite(i, newEmpty);
		}

		newEmpty = new byte[Disk.blockSize];

		//erase
		for (int j = 0; j < Disk.blockSize; j++)
		{
			newEmpty[j] = 0;
		}

		SysLib.int2bytes(-1, newEmpty, 0);
		SysLib.rawwrite(defaultBlocks - 1, newEmpty);
		byte[] replacementSuper = new byte[Disk.blockSize];

		// copy back all components
		SysLib.int2bytes(totalBlocks, replacementSuper, totalBlockLocation);
		SysLib.int2bytes(totalInodes, replacementSuper, totalInodeLocation);
		SysLib.int2bytes(freeList, replacementSuper, freeListLocation);

		// write new super
		SysLib.rawwrite(0, replacementSuper);

    }
}
