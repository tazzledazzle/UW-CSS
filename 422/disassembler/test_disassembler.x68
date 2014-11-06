*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
test        EQU     $1004
    ORG    $1000
*       PRINT OUT
*     LEA       BEG_MSG,A1  move message into a1
*     MOVE.B    #14,D0  print out trap code moved to d0
*     TRAP      #15     execute trap code
*
*
START:                  ; first instruction of program
* i/o
*      prompt for starting address
*      user entry captured
*      repeate if bad entry
*
*      prompt for ending address
*      user entry captured
*      repeat if bad entry
* 
*      send pointers to op-code
*      if garbage is present 
*      write address and data (hex value)
*      otherwise let opcode run

            **** I/O ****
            LEA     INTRO,A1    ; PRINT WELCOME MESSAGE
            MOVE.B  #14,D0
            TRAP    #15
        ;   print out "enter the starting address" 
LOOP        LEA     BEG_MSG,A1
            MOVE.B  #14,D0
            TRAP    #15
           ;------- accept user input   *Start address – formatted as follows:
           MOVE.B   #4,D0               *  o   1-8 characters
           TRAP     #15                 *  o   Only hex values
                                        *  o   Greater than $00002000
                                        *  o   Less than $000FFFFF
           ;------- check it
           CMP.B    $00002000,D1
           BLT      INVALID
           CMP.B    $000FFFFF,D1
           BGT      INVALID
            
               
                     
        ;   save the address
           MOVE.B   D1,D4
        ;   print out "enter ending address "
            LEA     END_MSG,A1
            MOVE.B  #14,D0
            TRAP    #15
           ;------- accept user input
           MOVE.B   #4,D0
           TRAP     #15
           ;------- check it
           CMP.B    $00002000,D1
           BLT      INVALID
           CMP.B    $000FFFFF,D1
           BGT      INVALID
           CMP.B    D4,D1
           BLT      INVALID
            * End address formatted as follows
                * o   1-8 characters
                * o   Only hex values
                * o   Greater than $00002000
                * o   Less than $000FFFFF
                * o   Greater than Start address
        ;   save the address
        ;   move the disassembler to that starting address
        ;   while current address location is less than ending address
            ;   while i < 30
                ; get address location
                ; get action
                ; get data
                ; print out line
                ; i++
                ; address++
            ;   check more pages
                * Paging (y/q) – formatted as follows:
                *  o   Only y/Y or q/Q char followed by enter
            ; if yes
                ;   continue along
            ; if no
                ;   end process and exit
                
            
MIN_START EQU   $00002000
MAX_START EQU   $000FFFFF

MIN_END   EQU   $00002000
MAX_END   EQU   $000FFFFF

 
        * New Region (y/n) – formatted as follows:
          *o   Only y/Y or q/Q char followed by enter



            * STARTING LOCATION
            * ENDING LOCATION
                        * read a word in memory
                        * convert to binary
                        * isolate bit 12-15
                        * look up found bit pattern in opcode table
                        * find correct operation
                        * divide into proper binary sections
                        * get EA mode from table
                        * get EA register from table  
            * BLOCK MESSAGE
                        * address
                        *   
            * REPEAT MESSAGE
            
            **** EA MODE TABLE ****
* Data Register Direct
* Address Register Direct
* Address Register Indirect
            
* Immediate Addressing
            
* Address Register Indirect with Post incrementing
            
* Address Register Indirect with Pre decrementing
            
* Absolute Long Address
            
* Absolute Word Address




                    **** OPCODE TABLE ****
* MOVE  ===========================================================
    * |00 |size| dest.reg | dest. mode| src. mode | src. reg|
    * size -> 01 == byte, 11 == word, 10 == long
    * MOVE.B
B_MOVE  EQU         $103C
* Data Register Direct
        MOVE.B      #14,D0
        MOVE.B      #17,D0
        MOVE.B      #21,D0
        MOVE.B      #99,D0
* Address Register Direct
* Address Register Indirect
        MOVE.W      test,A0
        MOVE.B      (A0),D0
        
                
    * MOVE.W
W_MOVE  EQU         $303C
* Absolute Word Address
        MOVE.W      #15,D0
        MOVE.W      #25,D0
        MOVE.W      #45,D0
        MOVE.W      #5,D0
        
        MOVE.W      #14,A0  ;RETURN SAME CODE AS MOVEA
    * MOVE.L
L_MOVES EQU         $7
* Absolute Long Address
        MOVE.L      #16,D0
        MOVE.L      #6,D0
        MOVE.L      #20,D0
        MOVE.L      #32,D0
        MOVE.L      #64,D0
        MOVE.L      #99,D0
        MOVE.L      #116,D0
        MOVE.L      #127,D0
        
        MOVE.L      #14,A0  ;RETURNS SAME CODE AS MOVEA
L_MOVEB EQU         $203C
        MOVE.L      #128,D0
        MOVE.L      #216,D0
        MOVE.L      #255,D0
        MOVE.L      #256,D0
        MOVE.L      #1000000000,D0
* MOVEA  ===========================================================
*    |00|size|dest.reg|001|src.mode|src.reg|
*   size -> 11 == word, 10 == long
    *MOVEA.W
W_MOVEA EQU         $307C    
        MOVEA.W     #14,A0
        MOVEA.W     #17,A0
        MOVEA.W     #21,A0
        MOVEA.W     #99,A0
        MOVEA.W     #1280,A0
        
     *MOVEA.L
L_MOVEA EQU         $207C
        MOVEA.L     #5,A0
        MOVEA.L     #127,A0
        MOVEA.L     #128,A0
        MOVEA.L     #255,A0
        MOVEA.L     #4096,A0
* MOVEM	 ===========================================================
*   |01001|dr|001|size|ea.mode|ea.reg|
*   dr -> 0 == register to memory, 1 == memory to register
*   size -> 0 == word , 1 == long
* ADD ===========================================================
*   |1101|reg|opmode|ea.mode|ea.reg|
*   opmode -> <ea> + Dn -> Dn {000 == Byte, 001 == word, 010 == long}
*             Dn + <ea> -> <ea> {100 == Byte, 101 == word, 110 == long}
* ADDA  ===========================================================
*   |1101|reg|opmode|ea.mode|ea.reg|
*   opmode -> 011 == word, 111 == long
* ADDQ ===========================================================
*   |0101|data|0|size|ea.mode|ea.register|
*   size -> 00 == byte, 01 == word, 10 == long
* SUB ===========================================================
*   |1001|reg|opmode|ea.mode|ea.reg|
*   Dn - <ea> -> Dn {000 == byte, 001 == word, 010 == long}
*   <ea> - Dn -> <ea> {100 == byte, 101 == word, 110 == long}
* SUBA ===========================================================
*   |1001|reg|opmode|ea.mode|ea.reg|
*   opmode -> 011 == word, 111 == long
* SUBI ===========================================================
*   |00000100|size|ea.mode|ea.reg|
*   size -> 00 == byte, 01 == word, 10 == long
* MULS ===========================================================
*   |1100|reg|111|ea.mode|ea.reg|
* DIVS ===========================================================
*   |1000|reg|111|ea.mode|ea.reg|
* LEA ===========================================================
*   |0100|reg|111|ea.mode|ea.reg|
* AND ===========================================================
*   |1100|reg|opmode|ea.mode|ea.reg|
*   opmode -> <ea>/\Dn -> Dn {000 == byte, 001 == word, 010 == long}
*             Dn /\<ea> -> <ea> {100 == byte, 101 == word, 110 == long}
* ORI ===========================================================
*   |00000000|size|ea.mode|ea.reg|
*   size -> 00 == byte, 01 == word, 10 == long
* NEG ===========================================================
*   |01000100|size|ea.mode|ea.reg|
*   size -> 00 == byte, 01 == word, 10 == long
* EOR ===========================================================
*   |1011|reg|opmode|ea.mode|ea.reg|
*   opmode -> 100 == byte, 101 == word, 110 == long <ea> XOR Dn -> <ea>
* EORI ===========================================================
*   |00001010|size|ea.mode|ea.reg|
*   size -> 00 == byte, 01 == word, 10 == long
* NOT ===========================================================
*   |01000110|size|ea.mode|ea.reg|
*   size -> 00 == byte, 01 == word, 10 == long
* LSR ===========================================================
*   Register shifts
*   |1110|count/reg|dr|size|i\r|01|reg|
*   count/register -> if i/r = 1 data reg specified contains shift count
*   count/register -> if i/r = 0 field contains shift count
*   dr -> 0 == shift left, 1 == shift right
*   size -> 00 == byte, 01 == word, 10 == long
*   Memory Shifts
*   |1110001|dr|11|ea.mode|ea.reg|
*   dr  -> 0 == shift right, 1 == shift left
* LSL ===========================================================
*   Register shifts
*   |1110|count/reg|dr|size|i\r|01|reg|
*   count/register -> if i/r = 1 data reg specified contains shift count
*   count/register -> if i/r = 0 field contains shift count
*   dr -> 0 == shift left, 1 == shift right
*   size -> 00 == byte, 01 == word, 10 == long
*   Memory Shifts
*   |1110001|dr|11|ea.mode|ea.reg|
*   dr  -> 0 == shift right, 1 == shift left
* ASR ===========================================================
*   Register shifts
*   |1110|count/reg|dr|size|i\r|00|reg|
*   count/register -> if i/r = 1 data reg specified contains shift count
*   count/register -> if i/r = 0 field contains shift count
*   dr -> 0 == shift left, 1 == shift right
*   size -> 00 == byte, 01 == word, 10 == long
*   Memory Shifts
*   |11100000|dr|11|ea.mode|ea.reg|
*   dr  -> 0 == shift right, 1 == shift left
* ASL ===========================================================
*   Register shifts
*   |1110|count/reg|dr|size|i\r|00|reg|
*   count/register -> if i/r = 1 data reg specified contains shift count
*   count/register -> if i/r = 0 field contains shift count
*   dr -> 0 == shift left, 1 == shift right
*   size -> 00 == byte, 01 == word, 10 == long
*   Memory Shifts
*   |11100000|dr|11|ea.mode|ea.reg|
*   dr  -> 0 == shift right, 1 == shift left
* ROL ===========================================================
*   Register shifts
*   |1110|count/reg|dr|size|i\r|11|reg|
*   count/register -> if i/r = 1 data reg specified contains shift count
*   count/register -> if i/r = 0 field contains shift count
*   dr -> 0 == shift left, 1 == shift right
*   size -> 00 == byte, 01 == word, 10 == long
*   Memory Shifts
*   |11100011|dr|11|ea.mode|ea.reg|
*   dr  -> 0 == shift right, 1 == shift left
* ROR ===========================================================
*   Register shifts
*   |1110|count/reg|dr|size|i\r|00|reg|
*   count/register -> if i/r = 1 data reg specified contains shift count
*   count/register -> if i/r = 0 field contains shift count
*   dr -> 0 == shift left, 1 == shift right
*   size -> 00 == byte, 01 == word, 10 == long
*   Memory Shifts
*   |11100000|dr|11|ea.mode|ea.reg|
*   dr  -> 0 == shift right, 1 == shift left
* BTST ===========================================================
*   Bit number dynamic, specified in a register
*   |0000|reg|100|ea.mode|ea.reg|
*   Bit number static, specified as immediate data
*   |0000100000|ea.mode|ea.reg|
* CMP ===========================================================
*   |1011|reg|opmode|ea.mode|ea.reg|
*   opmode -> 000 == byte, 001 == word, 010 == long
* CMPI ===========================================================
*   |00001100|size|ea.mode|ea.reg|
*   size -> 00 == byte, 01 == word, 10 == long
* CMPA ===========================================================
*   |1011|reg|opmode|ea.mode|ea.reg|
*   opmode -> 011== word, 111 == long
* Bcc (BEQ, BNE, BLT, BHI)===========================================================
*   |0110|condition|8-bit displacement|
*   |16-bit displacement if 8-bit = $00|
*   |32-bit displacement if 8-bit = $FF|
* This involves twos complement, you must learn about it before you can complete
* BRA ===========================================================
*   |01100000|8-bit displacement|
*   |16-bit displacement if 8-bit = $00|
*   |32-bit displacement if 8-bit = $FF|
* This involves twos complement, you must learn about it before you can complete
* JSR ===========================================================
*   |0100111010|ea.mode|ea.reg|
* RTS ===========================================================
*   |0100111001110101|
INVALID     LEA     INV,A1
            MOVE.B  #14,D0
            TRAP    #15
            BRA     LOOP
            
DONE        MOVE.B  #9,D0
            TRAP    #15
    **** VARIABLES ****
CR          EQU     $0D
LF          EQU     $0A
INTRO       DC.B    'Welcome Message!',CR,LF,CR,LF,CR,LF,0
            DC.B    '****************************************',CR,LF,0
BEG_MSG     DC.B    'Please Enter a value: ',CR,LF,0
END_MSG     DC.B    'Please Enter a value: ',CR,LF,0
INV         DC.B    'Please enter a value between $00002000 and $000FFFFF',CR,LF,0


    END    START        ; last line of source



