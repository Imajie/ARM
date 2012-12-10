/*
 * File:        common.h
 * Purpose:     File to be included by all project files
 *
 * Notes:
 */

#ifndef _COMMON_H_
#define _COMMON_H_

/********************************************************************/

/*
 * Debug prints ON (#define) or OFF (#undef)
 */

#define DEBUG
#define DEBUG_PRINT

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


/********************************************************************/

#endif /* _COMMON_H_ */
