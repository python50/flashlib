/* 
 * File:   examples.c
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
 */
#include "flashlib.h"

void main()
{
    //Write A-Z plus a few others into flash
    char items[32]={0};
    for(char i=0;i!=32;i++)
	items='A'+i;

    flashlib_row_erase(FLASHLIB_DATA_ROW_0); //erase before writing
    flashlib_row_write(FLASHLIB_DATA_ROW_0,items,32); //write 32 letters into flash


    //Read them back
    char read_items[32]={0};

    for(char i=0;i!=32;i++)
        read_items[i]=flashlib_read_word(FLASHLIB_DATA_ROW_0+i);
}

