/*
 * Platform.c
 *
 *  Created on: 02.03.2015
 *      Author: tastyger
 */

#include "Platform.h"
#include "LED.h"
#include "Mealy.h"
#include "Keys.h"

void PL_Init(void) {
#if PL_HAS_MEALY
	MEALY_Init();
#endif
#if PL_HAS_LED
	LED_Init();
#endif

#if PL_HAS_EVENTS
	EVNT_Init();
#endif

#if PL_HAS_KEYS
	KEY_Init();
#endif
}

void PL_Deinit(void) {

#if PL_HAS_MEALY
	MEALY_Deinit();
#endif
#if PL_HAS_LED
	LED_Deinit();
#endif

#if PL_HAS_EVENTS
	EVNT_Deinit();
#endif

#if PL_HAS_KEYS
	KEY_Deinit();
#endif
}
