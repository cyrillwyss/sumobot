/*
 * Timer.c
 *
 *  Created on: 10.03.2015
 *      Author: Cyrill
 */
#include "Timer.h"

#if PL_HAS_HAS_TIMER
#include "Event.h"
#include "TI1.h"

#define TICKS_FOR_HEARTBEAT (1000/TMR_TICK_MS)

int tickCounter=0;

void TMR_OnInterrupt(void){
	tickCounter++;
	if(tickCounter%TICKS_FOR_HEARTBEAT==0){
		EVNT_SetEvent(EVNT_LED_HEARTBEAT);
	}
}


void TMR_Init(void){

	tickCounter=0;
}


void TMR_Deinit(void){

}


int TMR_GetTicks(void){
	return tickCounter;
}

int TMR_GetTimeMS(void){
	return tickCounter*TMR_TICK_MS;
}
#endif
