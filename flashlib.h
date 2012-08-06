/* 
 * File:   flashlib.h
 * Author: Jason White <Jason@JSWhite.net>
 * License: Modified BSD License
 *
 *  Version: 1.0
 *  Release Date: 08/06/2012
 *  Copyright 2012 (C) Jason White <Jason@JSWhite.net> 
 *  White Waters Software
 *
 *  http://www.github.com/python50/flashlib
 *
 * Created on July 26, 2012, 2:05 PM
 */

#ifndef FLASHLIB_H
#define	FLASHLIB_H


//example addresses, PIC16F1518
#define FLASHLIB_TOP (0x4000) //The highest flash address, in this case its 0x4000 for the PIC16F1518

/*
 Data can only be erased one row at a time, since you must erase before you
 write to memory most memory operations you do are based around a entire row as
 opposed to just a single memory location. 

 In the PIC16F1518 a row is 32, 14bit wide words of data. Here we define the
 addresses of the rows we will be reading and writing to in our application
*/

#define FLASHLIB_DATA_ROW_0 (FLASHLIB_TOP-(32*1))
#define FLASHLIB_DATA_ROW_1 (FLASHLIB_TOP-(32*2))
#define FLASHLIB_DATA_ROW_2 (FLASHLIB_TOP-(32*2))
//and etc.


//This is the unlock sequence for the memory controller
//it is called by the write and erase functions to execute a change to memory
//Warning: Do Not Call This Form Outside Code, You Could Potentially Corrupt Some Memory
void         flashlib_do();

//This takes a pointer to a array with a length of X and writes it to memory
//Make sure to erase the memory before you write to it !
void         flashlib_row_write(unsigned int address, const char * data, char length);

//This erases a row of memory, given its address. Note the address does not have
//to be aligned with the beginning of the row, any address within the row will
//do
void         flashlib_row_erase(unsigned int address);

//This reads one 14 bit word from flash memory
unsigned int flashlib_read_word(unsigned int address);



#endif	/* FLASHLIB_H */

