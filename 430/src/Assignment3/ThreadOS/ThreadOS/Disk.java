import java.io.*;

public class Disk extends Thread {
    public static final int blockSize = 512;
    private final int trackSize = 10;
    private final int transferTime = 20;
    private final int delayPerTrack = 1;
    private int diskSize;

    private byte data[];

    private int command;
    private final int IDLE = 0;
    private final int READ = 1;
    private final int WRITE = 2;
    private final int SYNC = 3;
    private boolean readyBuffer;

    private byte[] buffer;
    private int currentBlockId;
    private int targetBlockId;

    public Disk( int totalBlocks ) {
	diskSize = ( totalBlocks > 0 ) ? totalBlocks : 1;
	data = new byte[ diskSize * blockSize ];
	command = IDLE;
	readyBuffer = false;
	buffer = null;
	currentBlockId = 0;
	targetBlockId = 0;
	try {
	    FileInputStream ifstream = new FileInputStream( "DISK" );
	    int readableSize = ( ifstream.available( ) < data.length ) ?
		ifstream.available( ) : data.length; 
	    ifstream.read( data, 0, readableSize );
	    ifstream.close( );
	} catch ( FileNotFoundException e ) {
	    SysLib.cerr( "threadOS: DISK created\n" );
	} catch ( IOException e ) {
	    SysLib.cerr( e.toString( ) + "\n" );
	}
    }

    public synchronized boolean read( int blockId, byte buffer[] ) {

	if ( blockId < 0 || blockId > diskSize ) {
	    SysLib.cerr( "threadOS: a wrong blockId for read\n" );
	    return false;
	}

	if ( command == IDLE && readyBuffer == false ) {
	    this.buffer = buffer;
	    targetBlockId = blockId;
	    command = READ;
	    notify( );
	    return true;
	} else
	    return false;
    }

    public synchronized boolean write( int blockId, byte buffer[] ) {

	if ( blockId < 0 || blockId > diskSize ) {
	    SysLib.cerr( "threadOS: a wrong blockId for write\n" );
	    return false;
	}

	if ( command == IDLE && readyBuffer == false ) {
	    this.buffer = buffer;
	    targetBlockId = blockId;
	    command = WRITE;
	    notify( );
	    return true;
	} else
	    return false;
    }

    public synchronized boolean sync( ) {
	
	if ( command == IDLE && readyBuffer == false ) {
	    command = SYNC;
	    notify( );
	    // System.out.println( "DISK sync notified the disk" );
	    return true;
	} else
	    return false;
    }

    public synchronized boolean testAndResetReady( ) {
	if ( command == IDLE && readyBuffer == true ) {
	    readyBuffer = false;
	    return true;
	} else
	    return false;
    }

    public synchronized boolean testReady( ) {
	if ( command == IDLE && readyBuffer == true ) {
	    return true;
	} else
	    return false;
    }

    private synchronized void waitCommand( ) {
	while ( command == IDLE ) {
	    try {
		wait( );
	    } catch ( InterruptedException e ) {
		SysLib.cerr( e.toString( ) + "\n" );
	    }
	    readyBuffer = false;
	}
    }

    private void seek( ) {
	int seekTime = transferTime + delayPerTrack 
	    * Math.abs( targetBlockId/trackSize - currentBlockId/trackSize );
	try {
	    Thread.sleep( seekTime );
	} catch( InterruptedException e ) {
	    SysLib.cerr( e.toString( ) + "\n" );
	}
	currentBlockId = targetBlockId;
    }

    private synchronized void finishCommand( ) {
	command = IDLE;
	readyBuffer = true;
	SysLib.disk( ); // a disk interrupt
    }

    public void run ( ) {
	
	while ( true ) {
	    waitCommand( );
	    seek( );
	    // System.out.println( "Disk: command = " + command );
	    switch( command ) {
	    case READ:
		System.arraycopy( data, targetBlockId * blockSize, 
				  buffer, 0, 
				  blockSize );
		break;
	    case WRITE:
		System.arraycopy( buffer, 0, 
				  data, targetBlockId * blockSize, 
				  blockSize );
		break;
	    case SYNC:
		try {
		    FileOutputStream ofstream = new FileOutputStream( "DISK" );
		    ofstream.write( data );
		    ofstream.close( );
		} catch ( FileNotFoundException e ) {
		    SysLib.cerr( e.toString( ) );
		} catch ( IOException e ) {
		    SysLib.cerr( e.toString( ) );
		}
		// SysLib.cerr( "threadOS: DISK synchronized\n" );
		break;
	    }
	    finishCommand( );
	}
    }
}
