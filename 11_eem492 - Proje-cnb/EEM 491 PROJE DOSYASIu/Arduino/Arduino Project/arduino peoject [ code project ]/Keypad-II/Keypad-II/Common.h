
#ifndef _MYLIB_COMMON_H_
#define _MYLIB_COMMON_H_ 1

/****************************************************************************
 Module:	Common.h 	
 Author:    Mike Hankey http://www.JaxCoder.com
 Hardware 	AVR ATmega1280
 Software:	gcc 4.3.3 AVR Studio 4.18 Build 700

 DESCRIPTION: Common stuff I use all the time
						  
 License: This software is provided on as "AS IS" basis and the author assumes
 	no responsibility for its usage.  This software may be freely distributed
	provided this header is kept in place and the author (me) is given due
	credit for it.  
*****************************************************************************/

#ifndef _BOOL_
#define _BOOL_
enum { null = 0, false = 0, true };
typedef unsigned char bool;
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef unsigned char byte;
typedef unsigned short word;

typedef union ushort
{                       
    uint16_t Short;                          
    uint8_t Byte[2];
} ushort;

typedef union ulong
{
	uint32_t Long;
	uint16_t Word[2];
} ulong;
#endif //_MYLIB_COMMON_H_
