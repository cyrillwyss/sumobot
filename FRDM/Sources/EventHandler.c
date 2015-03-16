/*
 * EventHandler.c
 *
 *  Created on: 10.03.2015
 *      Author: Cyrill
 */
#include "EventHandler.h"
#include "../../Common/Led.h"
#include "WAIT1.h"



void ProcessInitEvet(void);
void ProcessSW1Event(void);
void ProcessSW2Event(void);
void ProcessSW3Event(void);
void ProcessSW4Event(void);
void ProcessLEDHeartbeatEcent(void);

EventAllocation evtAlloc[] = { { EVNT_INIT, ProcessInitEvet }, {
		EVNT_SW1_PRESSED, ProcessSW1Event },
		{ EVNT_SW2_PRESSED, ProcessSW2Event }, { EVNT_SW3_PRESSED,
				ProcessSW3Event }, { EVNT_SW4_PRESSED, ProcessSW4Event }, {
				EVNT_LED_HEARTBEAT, ProcessLEDHeartbeatEcent } }; /*!< Allocation between event type and handler function*/

void EventHandler_HandleEvent(void) {
	EVNT_HandleEvent(evtAlloc,sizeof(evtAlloc));
}

void ProcessInitEvet(void) {
	for (int i = 0; i < 3; i++) {
		LED2_On();
		WAIT1_Waitms(100);
		LED2_Off();
		WAIT1_Waitms(100);
	}
}
void ProcessSW1Event(void) {

	LED1_On();

}
void ProcessSW2Event(void) {
LED1_Off();
}
void ProcessSW3Event(void) {

}
void ProcessSW4Event(void) {

}
void ProcessLEDHeartbeatEcent(void) {

	LED2_On();
	WAIT1_Waitms(100);
	LED2_Off();

}
