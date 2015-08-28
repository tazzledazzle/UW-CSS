class Test5 extends Thread {
  final static int DEFAULTFILES = 48;
  final int files;
  int fd;
  final byte[] buf16 = new byte[16];
  final byte[] buf32 = new byte[32];
  final byte[] buf24 = new byte[24];
  int size;

  public Test5( String args[] ) {
    files = Integer.parseInt( args[0] );
    // SysLib.cout( "files = " + files + "\n" );
  }

  public Test5() {
    files = DEFAULTFILES;
    // SysLib.cout( "files = " + files + "\n" );
  }

  public void run( ) {
    if ( test1( ) ) // format with specified # of files
      SysLib.cout("Correct behavior of format......................2\n");
    if ( test2( ) ) // open "css430" with "w+"
      SysLib.cout("Correct behavior of open........................2\n");
    if ( test3( ) ) // write buf[16]
      SysLib.cout("Correct behavior of writing a few bytes.........2\n");
    if ( test4( ) ) // close fd
      SysLib.cout("Correct behavior of close.......................2\n");
    if ( test5( ) ) // read buf[16] from "css430"
      SysLib.cout("Correct behavior of reading a few bytes.........2\n");
    if ( test6( ) ) // append buf[32] to "css430"
      SysLib.cout("Correct behavior of appending a few bytes.......1\n");
    if ( test7( ) ) // seek and read from "css430"
      SysLib.cout("Correct behavior of seeking in a small file.....1\n");
    if ( test8( ) ) // open "css430" with "w+"
      SysLib.cout("Correct behavior of read/writing a small file.0.5\n");

    test9( );        // open "bothell" with "w+"
    if ( test10( ) ) // write buf[512 * 13]
      SysLib.cout("Correct behavior of writing a lot of bytes....0.5\n");
    test11( );       // close fd
    if ( test12( ) ) // read buf[512 * 13] from "bothell"
      SysLib.cout("Correct behavior of reading a lot of bytes....0.5\n");
    if ( test13( ) ) // append buf[32] to "bothell"
      SysLib.cout("Correct behavior of appending to a large file.0.5\n");
    if ( test14( ) ) // seek and read from "bothell"
      SysLib.cout("Correct behavior of seeking in a large file...0.5\n");
    if ( test15( ) ) // open "bothell" with "w+"
      SysLib.cout("Correct behavior of read/writing a large file.0.5\n");

    if ( test16( ) ) // delete "css430"
      SysLib.cout("Correct behavior of delete....................0.5\n");
    if ( test17( ) ) // create "uwb0" - "uwb45" of buf[512 * 13]
      SysLib.cout("Correct behavior of creating over 40 files ...0.5\n");
    if ( test18( ) ) // "uwb1" read/written among Test5 and Test6
      SysLib.cout("Correct behavior of two fds to the same file..0.5\n");
  
    SysLib.cout( "Test completed\n" );
    SysLib.exit( );
  }

  private boolean test1( ) {
    //.............................................."
    SysLib.cout( "1: format( " + files + " )..................." );
    SysLib.format( files );
    byte[] superblock = new byte[512];
    SysLib.rawread( 0, superblock );
    int totalBlocks = SysLib.bytes2int( superblock, 0 );
    int inodeBlocks = SysLib.bytes2int( superblock, 4 );
    int freeList = SysLib.bytes2int( superblock, 8 );
    if ( totalBlocks != 1000 ) {
      SysLib.cout( "totalBlocks = " + totalBlocks + " (wrong)\n" );
      return false;
    }
    if ( inodeBlocks != files && inodeBlocks != files / 16 ) {
      SysLib.cout( "inodeBlocks = " + inodeBlocks + " (wrong)\n" );
      return false;
    }
    if ( freeList != 1 + files / 16 && freeList != 1 + files / 16 + 1 ) {
      SysLib.cout( "freeList = " + freeList + " (wrong)\n" );
      return false;
    }
    SysLib.cout( "successfully completed\n" );
    return true;
  }

  private boolean test2( ) {
    //.............................................."
    SysLib.cout( "2: fd = open( \"css430\", \"w+\" )...." );
    fd = SysLib.open( "css430", "w+" );
    if ( fd != 3 ) {
      SysLib.cout( "fd = " + fd + " (wrong)\n" );
      return false;
    }
    SysLib.cout( "successfully completed\n" );
    return true;
  }

  private boolean test3( ) {
    //.............................................."
    SysLib.cout( "3: size = write( fd, buf[16] )...." );
    for ( byte i = 0; i < 16; i++ )
      buf16[i] = i;
    size = SysLib.write( fd, buf16 );
    if ( size != 16 ) {
      SysLib.cout( "size = " + size + " (wrong)\n" );
      return false;
    }
    SysLib.cout( "successfully completed\n" );
    return true;
  }

  private boolean test4( ) {
    //.............................................."
    SysLib.cout( "4: close( fd )...................." );
    SysLib.close( fd );

    size = SysLib.write( fd, buf16 );
    if ( size > 0 ) {
      SysLib.cout( "writable even after closing the file\n" );
      return false;
    }

    SysLib.cout( "successfully completed\n" );
    return true;
  }

  private boolean test5( ) {
    //.............................................."
    SysLib.cout( "5: reopen and read from \"css430\".." );
    fd = SysLib.open( "css430", "r" );

    byte[] tmpBuf = new byte[16];
    size = SysLib.read( fd, tmpBuf );
    if ( size != 16 ) {
      SysLib.cout( "size = " + size + " (wrong)\n" );
      SysLib.close( fd );
      return false;
    }
    for ( int i = 0; i < 16; i++ )
      if ( tmpBuf[i] != buf16[i] ) {
        SysLib.cout( "buf[" + i + "] = " + tmpBuf[i] + " (wrong)\n" );
        SysLib.close( fd );
        return false;
      }
    SysLib.close( fd );
    SysLib.cout( "successfully completed\n" );
    return true;
  }

  private boolean test6( ) {
    //.............................................."
    SysLib.cout( "6: append buf[32] to \"css430\"....." );
    for ( byte i = 0; i < 32; i++ )
      buf32[i] = ( byte )( i + ( byte )16 );

    fd = SysLib.open( "css430", "a" );
    SysLib.write( fd, buf32 );
    SysLib.close( fd );

    fd = SysLib.open( "css430", "r" );
    byte[] tmpBuf = new byte[48];
    size = SysLib.read( fd, tmpBuf );
    if ( size != 48 ) {
      SysLib.cout( "size = " + size + " (wrong)\n" );
      SysLib.close( fd );
      return false;
    }
    for ( int i = 0; i < 16; i++ )
      if ( tmpBuf[i] != buf16[i] ) {
        SysLib.cout( "buf[" + i + "] = " + tmpBuf[i] + " (wrong)\n" );
        SysLib.close( fd );
        return false;
      }
    for ( int i = 16; i < 48; i++ )
      if ( tmpBuf[i] != buf32[i - 16] ) {
        SysLib.cout( "buf[" + i + "] = " + tmpBuf[i] + " (wrong)\n" );
        SysLib.close( fd );
        return false;
      }
    SysLib.close( fd );
    SysLib.cout( "successfully completed\n" );
    return true;
  }

  private boolean test7( ) {
    //.............................................."
    SysLib.cout( "7: seek and read from \"css430\"...." );

    fd = SysLib.open( "css430", "r" );

    int position = SysLib.seek( fd, 10, 0 );
    if ( position != 10 ) {
      SysLib.cout( "seek(fd,10,0)=" + position + " (wrong)\n" );
      SysLib.close( fd );
      return false;
    }
    byte[] tmpBuf = new byte[2];
    size = SysLib.read( fd, tmpBuf );
    if ( tmpBuf[0] != ( byte )10 ) {
      SysLib.cout( "seek(fd,10,0) contents " + tmpBuf[0] + "(wrong\n" );
      SysLib.close( fd );
      return false;
    }

    position = SysLib.seek( fd, 10, 0 );
    position = SysLib.seek( fd, 10, 1 );
    if ( position != 20 ) {
      SysLib.cout( "seek(fd,10,1)=" + position + " (wrong)\n" );
      SysLib.close( fd );
      return false;
    }
    size = SysLib.read( fd, tmpBuf );
    if ( tmpBuf[0] != ( byte )20 ) {
      SysLib.cout( "seek(fd,10,1) contents " + tmpBuf[0] + "(wrong)\n" );
      SysLib.close( fd );
      return false;
    }

    position = SysLib.seek( fd, -2, 2 );
    if ( position != 46 ) {
      SysLib.cout( "seek(fd,-2,2)=" + position + "(wrong)\n" );
      SysLib.close( fd );
      return false;
    }
    size = SysLib.read( fd, tmpBuf );
    if ( tmpBuf[0] != ( byte )46 ) {
      SysLib.cout( "seek(fd,-2,2) contents " + tmpBuf[0] + "(wrong)\n" );
      SysLib.close( fd );
      return false;
    }

    SysLib.close( fd );
    SysLib.cout( "successfully completed\n" );
    return true;
  }

  private boolean test8( ) {
    //.............................................."
    SysLib.cout( "8: open \"css430\" with w+.........." );

    for ( short i = 0; i < 24; i++ )
      buf24[i] = ( byte )( 24 - i );

    fd = SysLib.open( "css430", "w+" );
    SysLib.seek( fd, 24, 0 );
    SysLib.write( fd, buf24 );
  
    SysLib.seek( fd, 0, 0 );
    byte[] tmpBuf = new byte[48];
    SysLib.read( fd, tmpBuf );

    for ( byte i = 0; i < 16; i++ )
      if ( tmpBuf[i] != buf16[i] ) {
        SysLib.cout( "tmpBuf[" + i + "]=" + tmpBuf[i] + " (wrong)\n" );
        SysLib.close( fd );
        return false;
      }
    for ( byte i = 16; i < 24; i++ )
      if ( tmpBuf[i] != buf32[i-16] ) {
        SysLib.cout( "tmpBuf[" + i + "]=" + tmpBuf[i] + " (wrong)\n" );
        SysLib.close( fd );
        return false;
      }
    for ( byte i = 24; i < 48; i++ )
      if ( tmpBuf[i] != buf24[i-24] ) {
        SysLib.cout( "tmpBuf[" + i + "]=" + tmpBuf[i] + " (wrong)\n" );
        SysLib.close( fd );
        return false;
      }

      SysLib.close( fd );
      SysLib.cout( "successfully completed\n" );
      return true;
    }

  //final byte[] buf8192 = new byte[8192];
  final byte[] buf6656 = new byte[6656];

  private boolean test9( ) {
    //.............................................."
    SysLib.cout( "9: fd = open( \"bothell\", \"w\" )...." );
    fd = SysLib.open( "bothell", "w+" );
    if ( fd != 3 ) {
      SysLib.cout( "fd = " + fd + " (wrong)\n" );
      return false;
    }
    SysLib.cout( "successfully completed\n" );
    return true;
  }

  private boolean test10( ) {
    //.............................................."
    SysLib.cout( "10: size = write( fd, buf[6656] )." );
    for ( int i = 0; i < 6656; i++ )
      buf6656[i] = ( byte )( i % 256 );
    size = SysLib.write( fd, buf6656 );
    if ( size != 6656 ) {
      SysLib.cout( "size = " + size + " (wrong)\n" );
      return false;
    }
    SysLib.cout( "successfully completed\n" );
    return true;
  }

  private boolean test11( ) {
    //.............................................."
    SysLib.cout( "11: close( fd )...................." );
    SysLib.close( fd );

    size = SysLib.write( fd, buf16 );
    if ( size > 0 ) {
      SysLib.cout( "writable even after closing the file\n" );
      return false;
    }

    SysLib.cout( "successfully completed\n" );
    return true;
  }

  private boolean test12( ) {
    //.............................................."
    SysLib.cout( "12: reopen and read from \"bothell\"" );
    fd = SysLib.open( "bothell", "r" );

    byte[] tmpBuf = new byte[6656];
    size = SysLib.read( fd, tmpBuf );
    if ( size != 6656 ) {
      SysLib.cout( "size = " + size + " (wrong)\n" );
      SysLib.close( fd );
      return false;
    }
    for ( int i = 0; i < 6656; i++ )
      if ( tmpBuf[i] != buf6656[i] ) {
        SysLib.cout( "buf[" + i + "] = " + tmpBuf[i] + " (wrong)\n" );
        SysLib.close( fd );
        return false;
      }
    SysLib.close( fd );
    SysLib.cout( "successfully completed\n" );
    return true;
  }

  private boolean test13( ) {
    //.............................................."
    SysLib.cout( "13: append buf[32] to \"bothell\"..." );

    fd = SysLib.open( "bothell", "a" );
    SysLib.write( fd, buf32 );
    SysLib.close( fd );

    fd = SysLib.open( "bothell", "r" );
    byte[] tmpBuf = new byte[6688];
    size = SysLib.read( fd, tmpBuf );
    if ( size != 6688 ) {
      SysLib.cout( "size = " + size + " (wrong)\n" );
      SysLib.close( fd );
      return false;
    }
    for ( int i = 0; i < 6656; i++ ) {
      if ( tmpBuf[i] != buf6656[i] ) {
        SysLib.cout( "buf[" + i + "] = " + tmpBuf[i] + " buf6656 = " +
           buf6656[i] + "\n" );
        SysLib.close( fd );
        return false;
      }
    }
    for ( int i = 6656; i < 6688; i++ )
      if ( tmpBuf[i] != buf32[i - 6656] ) {
        SysLib.cout( "buf[" + i + "] = " + tmpBuf[i] + " buf32 = " +
           buf32[i - 6656] + "\n" );
        SysLib.close( fd );
        return false;
      }
    SysLib.close( fd );
    SysLib.cout( "successfully completed\n" );
    return true;
  }

  private boolean test14( ) {
    //.............................................."
    SysLib.cout( "14: seek and read from \"bothell\"..." );

    fd = SysLib.open( "bothell", "r" );

    int position = SysLib.seek( fd, 512 * 11, 0 );
    if ( position != 512 * 11 ) {
      SysLib.cout( "seek(fd,512 * 11,0)=" + position + " (wrong)\n" );
      SysLib.close( fd );
      return false;
    }
    byte[] tmpBuf = new byte[2];
    size = SysLib.read( fd, tmpBuf );
    if ( tmpBuf[0] != ( byte )(512 * 11) ) {
      SysLib.cout( "seek(fd,512*11,0) contents "+tmpBuf[0] + "(wrong)\n" );
      SysLib.close( fd );
      return false;
    }

    position = SysLib.seek( fd, 512 * 11, 0 );
    position = SysLib.seek( fd, 512, 1 );
    if ( position != 512 * 12 ) {
      SysLib.cout( "seek(fd,512,1)=" + position + " (wrong)\n" );
      SysLib.close( fd );
      return false;
    }
    size = SysLib.read( fd, tmpBuf );
    if ( tmpBuf[0] != ( byte )(512 * 12) ) {
      SysLib.cout( "seek(fd,512,1) contents " + tmpBuf[0] + "(wrong)\n" );
      SysLib.close( fd );
      return false;
    }

    position = SysLib.seek( fd, -2, 2 );
    if ( position != 512 * 13 + 32 - 2 ) {
      SysLib.cout( "seek(fd,-2,2)=" + position + "(wrong)\n" );
      SysLib.close( fd );
      return false;
    }
    size = SysLib.read( fd, tmpBuf );
    if ( tmpBuf[0] != ( byte )46 ) {
      SysLib.cout( "seek(fd,-2,2) contents " + tmpBuf[0] + "(wrong)\n" );
      SysLib.close( fd );
      return false;
    }

    SysLib.close( fd );
    SysLib.cout( "successfully completed\n" );
    return true;
  }

  private boolean test15( ) {
    //.............................................."
    SysLib.cout( "15: open \"bothell\" with w+........." );

    for ( short i = 0; i < 24; i++ )
      buf24[i] = ( byte )( 24 - i );

    fd = SysLib.open( "bothell", "w+" );
    SysLib.seek( fd, 512 * 12 - 3, 0 );
    SysLib.write( fd, buf24 );
  
    SysLib.seek( fd, 0, 0 );
    byte[] tmpBuf = new byte[6688];
    SysLib.read( fd, tmpBuf );

    for ( int i = 0; i < 512 * 12 - 3; i++ )
      if ( tmpBuf[i] != buf6656[i] ) {
        SysLib.cout( "tmpBuf[" + i + "]=" + tmpBuf[i] + " (wrong)\n" );
        SysLib.close( fd );
        return false;
      }
    for ( int i = 512 * 12 - 3; i < 512 * 12 - 3 + 24; i++ )
      if ( tmpBuf[i] != buf24[i - ( 512 * 12 - 3)] ) {
        SysLib.cout( "tmpBuf[" + i + "]=" + tmpBuf[i] + " (wrong)\n" );
        SysLib.close( fd );
        return false;
      }
    for ( int i = 512 * 12 -3 + 24; i < 6656; i++ )
      if ( tmpBuf[i] != buf6656[i] ) {
        SysLib.cout( "tmpBuf[" + i + "]=" + tmpBuf[i] + " (wrong)\n" );
        SysLib.close( fd );
        return false;
      }
    for ( int i = 6656; i < 6688; i++ )
      if ( tmpBuf[i] != buf32[i - 6656] ) {
        SysLib.cout( "tmpBuf[" + i + "]=" + tmpBuf[i] + " (wrong)\n" );
        SysLib.close( fd );
        return false;
      }

    SysLib.close( fd );
    SysLib.cout( "successfully completed\n" );
    return true;
  }

  private boolean test16( ) {
    //.............................................."
    SysLib.cout( "16: delete(\"css430\").............." );
    fd = SysLib.open( "css430", "r" );
    if ( fd == -1 ) {
      SysLib.cout( "fd = " + fd + " (wrong)\n" );
      return false;
    }
    SysLib.close( fd );
    SysLib.delete( "css430" );
    fd = SysLib.open( "css430", "r" );
    if ( fd != -1 ) {
      SysLib.cout( "fd = " + fd + " (wrong, css430 still exists!)\n" );
      SysLib.close( fd );
      return false;
    }
    SysLib.cout( "successfully completed\n" );
    return true;
  }

  private boolean test17( ) {
    //.............................................."
    SysLib.cout( "17: create uwb0-29 of 512*13......" );
    int fdes[] = new int[29];
    for ( int i = 0; i < 29; i++ ) {
      Integer suffix = new Integer( i );
      String file = "uwb" + suffix.toString( );
      fdes[i] = SysLib.open( file, "w+" );
      if ( fdes[i] == -1 ) {
        SysLib.cout( "file: " + file + " open failed\n" );
        return false;
      }
    }
    for ( int i = 0; i < 29; i++ ) {
      if ( SysLib.write( fdes[i], buf6656 ) != 6656 ) {
        SysLib.cout( "fd[" + fdes[i] + "] failed in writing\n" );
        return false;
      }
    }
    for ( int i = 0; i < 29; i++ ) {
      if ( SysLib.close( fdes[i] ) == -1 ) {
        SysLib.cout( "fd[" + fdes[i] + "] failed in closing\n" );
        return false;
      }
    }
    SysLib.cout( "successfully completed\n" );
    return true;
  }

  private boolean test18( ) {
    //.............................................."
    SysLib.cout( "18: uwb0 read b/w Test5 & Test6...\n" );
    fd = SysLib.open( "uwb0", "r" );
    String[] cmd = new String[2];
    cmd[0] = "Test6";
    cmd[1] = String.format( "%d", fd );
    SysLib.exec( cmd );
    SysLib.join( );
    SysLib.close( fd );

    SysLib.cout( "Test6.java terminated\n" );
    fd = SysLib.open( "uwb1", "r" );
    byte[] tmpBuf = new byte[512];
    SysLib.read( fd, tmpBuf );
    for ( int i = 0; i < 512; i++ )
      if ( tmpBuf[i] != (byte)100 ) {
        SysLib.cout( "tmpBuf[" + i + "]=" + tmpBuf[i] + " should be 100"
           + "\n" );
        SysLib.close( fd );
        return false;
      }
    SysLib.close( fd );
    return true;
  }
}
