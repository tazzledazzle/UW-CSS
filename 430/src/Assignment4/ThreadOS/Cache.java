
/**
 * Created by tazzledazzle on 2/23/15.
 */

public class Cache {
    CacheBlock[] cacheBlock;
    private static boolean success = true;
    private static boolean failure = false;
    private static int INVALID = -2;
    private static int empty = -1;
    private int pageSize;
    private int blockSize;
    private int victim;
    private int found;

    private class CacheBlock{
        byte[] blockData;
        int blockFrame;
        boolean referenceBit;
        boolean dirtyBit;

        private CacheBlock(int blockSize){
            blockData = new byte[blockSize];
            blockFrame = empty;
            referenceBit = false;
            dirtyBit = false;
        }
    }
    /**
     *  allocates a cacheBlocks number of cache blocks, each containing blockSize-byte data, on memory
     * @param blockSize
     * @param cacheBlocks
     */
    public Cache(int blockSize, int cacheBlocks){
        cacheBlock = new CacheBlock[cacheBlocks];
        pageSize = cacheBlock.length;
        this.blockSize = blockSize;
        victim = cacheBlocks - 1;
        for (int i = 0; i < pageSize; i++){
            cacheBlock[i] = new CacheBlock(blockSize);
        }
    }

    /** read()
     * reads into the buffer[ ] array the cache block specified by blockId from the disk cache if it is in cache,
     * otherwise reads the corresponding disk block from the disk device. Upon an error, it should return false,
     * otherwise return true.
     *
     * @param blockId
     * @param buffer
     * @return
     */
    public synchronized boolean read(int blockId, byte buffer[]){
        if(blockId < 0) { return failure;}

        found = search(blockId);
        if (found != INVALID)
        {
            cacheRead(found, blockId, buffer);
            return success;
        }
        found = search(empty);
        if (found != INVALID)
        {
            SysLib.rawread(blockId, cacheBlock[found].blockData);   //disk read
            cacheRead(found, blockId, buffer);
            return success;
        }
        diskWrite(victimBit());
        SysLib.rawread(blockId, cacheBlock[victim].blockData);
        cacheRead(victim, blockId, buffer);
        return success;
    }

    /** write()
     * writes the buffer[ ]array contents to the cache block specified by blockId from the disk cache if it is in cache,
     *  otherwise finds a free cache block and writes the buffer [ ] contents on it. No write through.
     *  Upon an error, it should return false, otherwise return true.
     *
     * @param blockId
     * @param buffer
     * @return
     */
    public synchronized boolean write(int blockId, byte buffer[]){
        if (blockId < 0) { return failure; } //check valid blockId

        found = search(blockId);
        //If the corresponding entry has been found in the cache,
        if (found != INVALID)
        {
            // write new data to this cache block.
            cacheWrite(found, blockId, buffer);
            return success;
        }
        found = search(empty);
        if (found != INVALID)
        {
            cacheWrite(found, blockId, buffer);
            return success;
        }
        diskWrite(victimBit());
        cacheWrite(victim, blockId, buffer);
        return success;
    }

    /** sync()
     * writes back all dirty blocks to Disk.java and therefater forces Diskjava to write back all contents to the
     * DISK file.
     * method still maintains clean block copies in Cache.java, On the other hand,
     * the later method should be called when you keep running a different test case without receiving any caching
     * effects incurred by the previous test.
     */
    public synchronized void sync(){
        for (int i = 0; i < pageSize; i++) {
            diskWrite(i);
         }
        SysLib.sync();
    }

    /** flush()
     *  method invalidates all cached blocks.
     *   The former method must be called when shutting down ThreadOS.
     */
    public synchronized void flush(){
        for (int i = 0; i < pageSize; i++)
        {
            diskWrite(i);
            cacheUpdate(i, empty, false);
        }
        SysLib.sync();

    }
    public void cacheUpdate(int index, int frame, boolean refBit){
        cacheBlock[index].blockFrame = frame;
        cacheBlock[index].referenceBit = refBit;
    }
    public int search(int id){
        for (int i = 0; i < pageSize; i++){
            if(cacheBlock[i].blockFrame == id){
                return i;   //found it
            }
        }
        return INVALID;   //invalid
    }
    public void cacheRead(int foundId, int blockId,byte buffer[]){
        System.arraycopy(cacheBlock[foundId].blockData, 0, buffer, 0, blockSize);
        cacheUpdate(foundId, blockId, true);
    }

    public void cacheWrite(int found, int blockId, byte buffer[])
    {
        System.arraycopy(buffer, 0, cacheBlock[found].blockData, 0, blockSize);
        cacheBlock[found].dirtyBit = true;
        cacheUpdate(found, blockId, true);
    }

    public void diskWrite(int index){
        if(cacheBlock[index].dirtyBit && cacheBlock[index].blockFrame != empty)
        {
            SysLib.rawwrite(cacheBlock[index].blockFrame, cacheBlock[index].blockData);
            cacheBlock[index].dirtyBit = false;     //update dirty bit
        }
    }

    /**
     * Second Chance Algorithm
     *
     * @return
     */
    public int victimBit()
    {
        while (true)
        {
            victim = ((++victim) % pageSize);
            if (!cacheBlock[victim].referenceBit)   //if block unused
            {
                return victim;
            }
            cacheBlock[victim].referenceBit = false;    //unset the reference bit
        }
    }
}
