
/**
 * @file Inode.java
 * @author Terence Schumacher
 * @author Nick Abel
 *
 *
 * The main purpose of inode is to describe a file. It holds 12 pointers (11 direct and 1 indirect) of the index block.
 * Inode includes the length of the corresponding file, the number of file table entries that point to the node, and a
 * flag to indicate used or not, plus additional status values. A total of 16 indoors can be stored in a  block.
 *
 */
public class Inode {
    private final static int iNodeSize = 32;       // fix to 32 bytes
    public final static int directSize = 11;      // # direct pointers
    private final static int maxBytes = 512;
    private final static int blockSize = 16;
    private final static int intBlock = 4;
    private final static int shortBlock = 2;
    private final static int ERROR = -1;

    public int length;                             // file size in bytes
    public short count;                            // # file-table entries pointing to this
    public short flag;                             // 0 = unused, 1 = used, ...
    public short direct[] = new short[directSize]; // direct pointers
    public short indirect;                         // a indirect pointer

    /** default constructor
     *
     */
    Inode( ) {                                     // a default constructor
        length = 0;
        count = 0;
        flag = 1;
        for ( int i = 0; i < directSize; i++ )
            direct[i] = -1;
        indirect = -1;
    }

    /** Constructor
     *
     * @param iNumber
     */
    Inode( short iNumber ) {                       // retrieving inode from disk
        // design it by yourself.

        //find the number of blocks to read
        int blockNumber = 1 + iNumber / blockSize;

        //allocate bytes
        byte[] data = new byte[maxBytes];
        SysLib.rawread(blockNumber,data);

        //define the offset
        int offset = (iNumber % 16) * iNodeSize;

        //create space
        length = SysLib.bytes2int(data, offset);
        offset += intBlock;
        count = SysLib.bytes2short(data, offset);
        offset += shortBlock;
        flag = SysLib.bytes2short(data, offset);
        offset += shortBlock;

        for (int i = 0; i < directSize; i++){
            direct[i] = SysLib.bytes2short(data, offset);
            offset += shortBlock;
        }
        indirect = SysLib.bytes2short(data, offset);
        offset += shortBlock;
    }

    /** toDisk
     *
     * @param iNumber
     * @return
     */
    int toDisk( short iNumber ) {                  // save to disk as the i-th inode
        // design it by yourself.
        byte [] data = new byte[iNodeSize];

        int offset = 0;

        SysLib.int2bytes(length, data, offset);
        offset += intBlock;
        SysLib.short2bytes(count, data, offset);
        offset += shortBlock;
        SysLib.short2bytes(flag, data, offset);
        offset += shortBlock;

        for (int i = 0; i < directSize; i++){
            SysLib.short2bytes(direct[i], data, offset);
            offset += shortBlock;
        }

        SysLib.short2bytes(indirect, data, offset);
        offset += shortBlock;

        int blockNumber = 1 + iNumber / blockSize;
        byte[] newData = new byte[maxBytes];
        SysLib.rawread(blockNumber,newData);

        offset = (iNumber % blockSize) * iNodeSize;

        System.arraycopy(data, 0, newData, offset, iNodeSize);
        SysLib.rawwrite(blockNumber,newData);

        return 0;
    }

    /** get Index Block Number
     *
     * @param entry
     * @param offset
     * @return
     */
    int getIndexBlockNumber(int entry, short offset){
        int target = entry/maxBytes;

        if (target < directSize){
            if(direct[target] >= 0){
                return -1;
            }

            if ((target > 0 ) && (direct[target - 1 ] == -1)){
                return -2;
            }

            direct[target] = offset;
            return 0;
        }

        if (indirect < 0){
            return -3;
        }

        else{
            byte[] data = new byte[maxBytes];
            SysLib.rawread(indirect,data);

            int blockSpace = (target - directSize) * 2;
            if ( SysLib.bytes2short(data, blockSpace) > 0){
                return ERROR;
            }
            else
            {
                SysLib.short2bytes(offset, data, blockSpace);
                SysLib.rawwrite(indirect, data);
            }
        }
        return 0;
    }

    /** set Index Block
     *
     * @param blockNumber
     * @return
     */
    boolean setIndexBlock(short blockNumber){
        for (int i = 0; i < directSize; i++){
            if (direct[i] == ERROR){
                return false;
            }
        }

        if (indirect != ERROR){
            return false;
        }

        indirect = blockNumber;
        byte[ ] data = new byte[maxBytes];

        for(int i = 0; i < (maxBytes/2); i++){
            SysLib.short2bytes((short) ERROR, data, i * 2);
        }
        SysLib.rawwrite(blockNumber, data);

        return true;

    }

    /** find Target Block
     *
     * @param offset
     * @return
     */
    int findTargetBlock(int offset){
        int target = offset / maxBytes;

        if (target < directSize){
            return direct[target];
        }

        if (indirect < 0){
            return -1;
        }

        byte[] data = new byte[maxBytes];
        SysLib.rawread(indirect, data);

        int blockSpace = (target - directSize) * 2;
        return SysLib.bytes2short(data, blockSpace);

    }

    /** free indirect block
     *
     * @return
     */
    byte[] freeIndirectBlock(){
        if (indirect >= 0)
        {
            byte[] data = new byte[maxBytes];
            SysLib.rawread(indirect, data);
            indirect = -1;
            return data;
        }
        else
        {
            return null;
        }
    }

}
