/*
 * Platform.c
 *
 *  Created on: 02.03.2015
 *      Author: tastyger
 */

#include "Platform.h"
#include "LED.h"

void PL_Init(void) {
#if PL_HAS_LED
  LED_Init();
#endif
}

void PL_Deinit(void) {
#if PL_HAS_LED
  LED_Deinit();
#endif
}
