/* 
 * File:   flashlib.h
 * Author: jason
 *
 * Created on July 26, 2012, 2:05 PM
 */

#ifndef FLASHLIB_H
#define	FLASHLIB_H

#define FLASHLIB_TOP (0x4000)
#define FLASHLIB_COUNTER_DATA_0 (FLASHLIB_TOP-(32*1))
#define FLASHLIB_COUNTER_DATA_1 (FLASHLIB_TOP-(32*2))

//Short 16char messages, Total 16 messages, 8 flash rows
#define FLASHLIB_SM_TOP (FLASHLIB_TOP-(32*3))
#define FLASHLIB_LM_TOP (FLASHLIB_TOP-(32*11))

void         flashlib_do();

void         flashlib_row_write(unsigned int address, const char * data, char length);
void         flashlib_row_erase(unsigned int address);

unsigned int flashlib_read_word(unsigned int address);



#endif	/* FLASHLIB_H */

