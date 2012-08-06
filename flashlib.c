#include "app_help.h"

#include <htc.h>           /* Global Header File */
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <stdlib.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

#include "flashlib.h"

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

void flashlib_row_write(unsigned int address, const char * data, char length)
{
    bool gie_enable=GIE;
    GIE=0;
    FREE=0;
    //Set the WREN bit of the PMCON1 register.
    WREN=1;
    //Clear the CFGS bit of the PMCON1 register.
    CFGS=0;
    //Set the LWLO bit of the PMCON1 register.
    //When the LWLO bit of the PMCON1 register is ?1?, the write sequence will
    //only load the write latches and will not initiate the write to Flash
    //program memory.
    LWLO=1;

    while(length > 1)
    {
        WREN=1;
        //Load the PMADRH:PMADRL register pair with the address of the location to be written
        PMADRH=address>>8;
        PMADRL=(char)address;
        //Load the PMDATH:PMDATL register pair with the program memory data to be written.
        PMDATH=0;
        PMDATL=(char)*data;
        //Execute the unlock sequence. The write latch is now loaded.
        flashlib_do();
        length--;
        data++;
        address++;
    }

    /*Increment the PMADRH:PMADRL register pair to point to the next location.
    Repeat steps 5 through 7 until all but the last write latch has been loaded.*/
    LWLO=0;//Will write latches
    PMADRH=address>>8;
    PMADRL=(char)address;
    PMDATH=0;
    PMDATL=(char)*data;
    flashlib_do();

     GIE=gie_enable;
}

void flashlib_row_erase(unsigned int address)
{
    PMADRH=address>>8;
    PMADRL=(char)address;
    CFGS=0;
    FREE=1;

    flashlib_do();
}

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