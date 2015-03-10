/*
 * Platform.h
 *
 *  Created on: 02.03.2015
 *      Author: tastyger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h" /* for common Processor Expert types used throughout the project, e.g. 'bool' */
#include "PE_Error.h" /* global error constants */

/* List of supported platforms. The PL_BOARD_IS_xxx is defined in the compiler command line settings.  */
#define PL_IS_FRDM   (defined(PL_BOARD_IS_FRDM))
#define PL_IS_ROBO  (defined(PL_BOARD_IS_ROBO))



#define PL_HAS_LED      (1)

#if PL_IS_FRDM
  #define PL_NOF_LEDS       (3)
	#define PL_HAS_EVENTS	1
#elif PL_IS_ROBO
  #define PL_NOF_LEDS       (2)
	#define PL_HAS_EVENTS	1
#else
  #error "unknown configuration?"
#endif


void PL_Init(void);
void PL_Deinit(void);

#endif /* PLATFORM_H_ */
