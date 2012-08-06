/* 
 * File:   flashlib.c
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
 * Created on July 26, 2012, 2:06 PM
 */

#include "app_help.h"

#include <htc.h>           /* Global Header File */
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <stdlib.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

#include "flashlib.h"

//Unlock sequence to execute an operation with the flash memory controller
void flashlib_do()
{
    WREN=1;
    PMCON2=0x55;
    PMCON2=0xaa;
    WR=1;
    asm("nop");
    asm("nop");
    WREN=0;
}

//write between 1 and the row size, bytes to memory
void flashlib_row_write(unsigned int address, const char * data, char length)
{
    bool gie_enable=GIE;
    GIE=0; //Disable interrupts
    FREE=0; //Select write operation
    CFGS=0; //Select program as opposed to configuration memory

    //When the LWLO bit of the PMCON1 register is 1, the write sequence will
    //only load the write latches and will not initiate the write to Flash
    //program memory.
    LWLO=1;

    while(length > 1)
    {
        //Load the PMADRH:PMADRL register pair with the address of the location to be written
        PMADRH=address>>8;
        PMADRL=(char)address;
        //Load the PMDATH:PMDATL register pair with the program memory data to be written.
        PMDATH=0;//Upper 6 bits are wasted
        PMDATL=(char)*data;
        //Execute the unlock sequence. The write latch is now loaded.
        flashlib_do();

        length--;
        data++;
        address++;
    }

    //Clearing LWLO means that a write to PMDATH:PMDATL will execute a write operation
    //into flash
    LWLO=0;
    //Load the PMADRH:PMADRL register pair with the address of the location to be written
    PMADRH=address>>8;
    PMADRL=(char)address;
    //Load the PMDATH:PMDATL register pair with the program memory data to be written.
    PMDATH=0;//Upper 6 bits are wasted
    PMDATL=(char)*data;
    flashlib_do();

    GIE=gie_enable;
}

//erase a row
void flashlib_row_erase(unsigned int address)
{
    PMADRH=address>>8;
    PMADRL=(char)address;
    CFGS=0;
    FREE=1;

    flashlib_do();
}

//read a word
unsigned int flashlib_read_word(unsigned int address)
{
    PMADRH=address>>8;
    PMADRL=address;
    CFGS=0;
    RD=1;
    asm("nop");
    asm("nop");

    return (PMDATH<<8)+PMDATL;
}
