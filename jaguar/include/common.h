/*
 * File:        common.h
 * Purpose:     File to be included by all project files
 *
 * Notes:
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#define F_CPU	(47000000)
/********************************************************************/
/* 
 * Include the generic CPU header file 
 */
#include "arm_cm0.h"

/* 
 * Include the platform specific header file 
 */
#include "freedom.h"

/* 
 * Include the cpu specific header file 
*/
//#include "MKL25Z128LK4.h"
#include "MKL25Z4.h"

#define NVIC_IntEnable(x)	(NVIC_ISER |= 1<<((x)-16))

#define __enable_interrupts()	\
	do{	\
		asm("CPSIE i");	\
	}while(0)

#define __disable_interrupts()	\
	do{	\
		asm("CPSID i");	\
	}while(0)

/********************************************************************/

#endif /* _COMMON_H_ */
