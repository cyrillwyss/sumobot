/*
 * Timer.c
 *
 *  Created on: 10.03.2015
 *      Author: Cyrill
 */
#include "Timer.h"

#if PL_HAS_HAS_TIMER
#include "Event.h"
#include "Trigger.h"

#define TICKS_FOR_HEARTBEAT (1000/TMR_TICK_MS)


void TMR_OnInterrupt(void){
	TRG_IncTick();

}


void TMR_Init(void){

}


void TMR_Deinit(void){

}


#endif
