
// --------------------------------- Cache.java --------------------------------
/*
 * PURPOSE OF FILE
 * This file's purpose serves to implement disk caching baseed upon the approach 
 * of using a Second Chance Algorithm (SCA). While the SCA is described in great
 * detail above the function theVictim(), I'll briefly describe it here. 
 * Bascially, it loops over all data in cache and looks for a victim. If no 
 * victim is found, it loops again to the last referenced block and chooses it.
 *
 * BRIEF NOTE
 * Throughout this program, you'll notice many functions use other functions to
 * accomplish some sort of work. The purpose behind this was to dramatically 
 * shorten the amount of repetitive code throughout similar (yet different 
 * functions). If you're unclear of a certain function's purpose, scroll down 
 * to that function and read the description above it.
 *
 * ASSUMPTIONS
 * 1. It is assumed that the user is running this file in ThreadOS's directory. 
 */

import java.io.*;

public class Cache {

	CacheBlock[] myCache; 
	private static int empty = -1;					//An empty frame is -1
	private static int INVALID = -2;				//Returned if invalid data
	private static boolean isSet = true;			
	private static boolean notSet = false;
	private static boolean success = true;
	private static boolean failure = false;	
	private int victim;								//holds ID of victim block
	private int target;								//Used for comparing 
	private int blockSize;							//Holds the size of blocks
	private int pageSize;							//Holds the size of pages

    // -------------------------------------------------------------------------
    // private object CacheBlock 
    /*
     * SUMMARY
     * This is a neat private object that's used to create the individual 
     * sectors of the cache object. It contains private members that are similar
     * to any normal cache block. 
     */
	private class CacheBlock{
		byte[] dataBlock;
		int blockFrame;
		boolean referenceBit;
		boolean dirtyBit;

		private CacheBlock(int blockSize){
			dataBlock = new byte[blockSize];		//Can contain byte data
			blockFrame = empty;						//This block refers to -1
			referenceBit = false;					//This block was not used
			dirtyBit = false;						//This block is unread
		}
	}

    // -------------------------------------------------------------------------
    // Constructor 
    /*
     * SUMMARY
     * This is  the constructor for the Cache class. It takes in two int values.
     * The first is the size each block should be. The second is the amount of
     * CacheBlock objects to be created (the size of the cache). 
     */
	public Cache(int block_Size, int cacheBlock){
		myCache = new CacheBlock[cacheBlock];		//Create a CacheBlock[]
		pageSize = myCache.length;					//Set the page size
		blockSize = block_Size;						//Update block size
		victim = cacheBlock-1;						//Initialize the victim
		for(int i = 0; i < pageSize; i++){
			myCache[i] = new CacheBlock(block_Size);//Fill the CacheBlock[]
		} 
	}

    // -------------------------------------------------------------------------
    // read 
    /*
     * SUMMARY
     * After ensuring that read() is handed a valid blockId from disk, it looks
     * to see if the blockId is already in Cache. If so, it reads the data from
     * the cache at that blockId's location. If the blockId was not found 
     * (returned INVALID), it searches the cache for an empty blockId. If found,
     * data is first read from disk into cache, then that data is read from 
     * cache to the accompanying buffer. If this empty search did not find an 
     * empty blockId, the Second Chance algorithm is used in order to find a 
     * victim blockId to be read into and read from. If all worked well, this 
     * function returns true, otherwise false.
     */	
	public synchronized boolean read(int blockId, byte[] buffer){
		if(blockId < 0){ return failure; }			//Invalid blockId
		
		target = lookFor(blockId);					//Look for existing blockId
		if(target != INVALID){ 						
			readFromCache(target, blockId, buffer);	//If found, read from cache
			return success; 
		}
		target = lookFor(empty);					//Look for empty blockId
		if(target != INVALID){ 						
			SysLib.rawread(blockId, myCache[target].dataBlock); //read from disk
			readFromCache(target, blockId, buffer);	//If found, read from cache
			return success;
		}		
		writeToDisk(theVictim());					//Find a victim, save first
		SysLib.rawread(blockId, myCache[victim].dataBlock);	 
       	readFromCache(victim, blockId, buffer);		//read from the cache block      	
		return success;
	}

    // -------------------------------------------------------------------------
    // write 
    /*
     * SUMMARY
     * After ensuring that write() is handed a valid blockId from disk, it looks
     * to see if the blockId is already in Cache. If so, it writes the data from
     * the buffer at that blockId's location into cache. If the blockId was not 
     * found (INVALID), it searches the cache for an empty blockId. If found,
     * the data is read from buffer into cache at the empty blockId's location.
     * If this empty search did not find an empty blockId, the Second Chance 
     * algorithm is used in order to find a victim blockId to be write into. 
     * If all worked well, this function returns true, otherwise false.
     */	
	public synchronized boolean write(int blockId, byte[] buffer){
		if(blockId < 0){ return failure; }			//Invalid blockId

		target = lookFor(blockId);					//Look for existing blockId
		if(target != INVALID){ 						
			addToCache(target, blockId, buffer);	//If found, add to cache
			return success; 
		}		
		target = lookFor(empty);					//Look for empty blockFrame
		if(target != INVALID){ 						
			addToCache(target, blockId, buffer);	//If found, add to cache
			return success; 
		}		
		writeToDisk(theVictim());					//Find a victim, save first
		addToCache(victim, blockId, buffer);		//Add to cache
		return success;								
	}

    // -------------------------------------------------------------------------
    // sync 
    /*
     * SUMMARY
     * This function is responsible for maintaining clean block copies.
     */	
	public synchronized void sync(){
		for(int i = 0; i < pageSize; i++) { writeToDisk(i); }
		SysLib.sync();								//Sync to disk
	}

    // -------------------------------------------------------------------------
    // flush 
    /*
     * SUMMARY
     * This function is responsible for invalidating all cached blocks
     */	
	public synchronized void flush(){
		for(int i = 0; i < pageSize; i++){			//Loop over all pages
			writeToDisk(i);							//Write data to disk
			updateCache(i, empty, notSet);			//Update status of data
		}	
		SysLib.sync();								//Sync to disk
	}
    // -------------------------------------------------------------------------
    // lookFor 
    /*
     * SUMMARY
     * This function is primarily used to shorten repetitive code. It simply
     * scans over the cache (pageSize) and looks to see if a blockFrame matches
     * what is handed to it by the user. If the blockFrame is found, that 
     * location in the cache is returned back to the calling function.
     */	
	private int lookFor(int prospect){
		for(int i = 0; i < pageSize; i++){			//Loop over all pages
			if(myCache[i].blockFrame == prospect){	//Is this what what we want?
				return i;							//If so, return it
			}
		}
		return INVALID;								//Otherwise, return INVALID
	}

    // -------------------------------------------------------------------------
    // addToCache 
    /*
     * SUMMARY
     * This is another helper function used to shorten repetitive code. Its 
     * basic purpose is to copy the data from one byte array to another. In 
     * essence, it copies data from the buffer (sent in) to the cache array.
     * Afterwords, the dirty bit is marked as set (true) to say that this block
     * has been written to. Afterwords, the other trackers are updated in the
     * cache to keep track of written blocks. 
     */
	private void addToCache(int target, int blockId, byte[] buffer){
		System.arraycopy(buffer, 0, myCache[target].dataBlock, 0, blockSize);
		myCache[target].dirtyBit = isSet;			//update dirty bit as true
		updateCache(target, blockId, isSet);
	}

    // -------------------------------------------------------------------------
    // readFromCache 
    /*
     * SUMMARY
     * Similar to the addToCache function, this function is responsible for
     * copying data from the cache into the buffer. After that is done, the 
     * cache block is updated to keep track of blocks recently read from.
     */
	private void readFromCache(int target, int blockId, byte[] buffer){
		System.arraycopy(myCache[target].dataBlock, 0, buffer, 0, blockSize);
		updateCache(target, blockId, isSet);	
	}

    // -------------------------------------------------------------------------
    // updateCache 
    /*
     * SUMMARY
     * This function is called from other functions. Its purpose is to mark
     * a cache block when it is referenced so that they don't get deleted during
     * the next found of the Second Chance algorithm.
     */
	private void updateCache(int target, int frame, boolean boolVal){
		myCache[target].blockFrame = frame;				//Save this frame number
		myCache[target].referenceBit = boolVal;			//update last reference
	}

    // -------------------------------------------------------------------------
    // writeToDisk 
    /*
     * SUMMARY
     * This function is used to write data (save) to disk before the data is 
     * removed from cache. It first checks if a block is written (dirty bit set)
     * If so, it write the data to disk and updates the dirty bit to not set.
     */
	private void writeToDisk(int target){
		if(myCache[target].dirtyBit && myCache[target].blockFrame != empty){
			SysLib.rawwrite(myCache[target].blockFrame, myCache[target].dataBlock);
			myCache[target].dirtyBit = notSet;			//Update dirty to false
		}
	}

    // -------------------------------------------------------------------------
    // theVictim (Second Chance Algorithm)
    /*
     * SUMMARY
     * In essence, this is the Second Chance algorithm. It loops through the 
     * cache over and over until it finds a victim ID. The basic description of 
     * the algorithm is as follows: Starting at the beginning of the array, 
     * check each block's reference bit. If the reference bit is not set 
     * (meaning it hasn't been recently used), return this as the victim. If the
     * reference bit is set (the block has been recently used), move onto the 
     * next block in a circular fashion. However, before leaving that last 
     * block, mark its reference bit to false (hasn't been recently used), 
     * effectively giving the block a second chance.
     */
	private int theVictim(){
		while(true){									//Loop forever
			victim = ((++victim) % pageSize);			//Grab next victim
			if(!myCache[victim].referenceBit){ return victim; } 
				myCache[victim].referenceBit = notSet; 	//mark as not used
		}
	}	
}
