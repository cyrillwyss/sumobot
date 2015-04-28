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
#if PL_HAS_MOTOR_TACHO
#include "Tacho.h"
#endif

#define PID_SAMPLE_TIME_MS 10

static int cnt=0;


void TMR_OnInterrupt(void){
	TRG_IncTick();

#if PL_HAS_MOTOR_TACHO
	TACHO_Sample();
#endif

}


void TMR_Init(void){

}


void TMR_Deinit(void){

}


#endif
