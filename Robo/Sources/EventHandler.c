/*
 * EventHandler.c
 *
 *  Created on: 10.03.2015
 *      Author: Cyrill
 */
#include "EventHandler.h"
#include "../../Common/Led.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "../../Common/Buzzer.h"

void ProcessInitEvet(void);
void ProcessSW1Event(void);
void ProcessLEDHeartbeatEcent(void);

EventAllocation evtAlloc[] = { { EVNT_INIT, ProcessInitEvet }, {
		EVNT_SW1_PRESSED, ProcessSW1Event }, {
				EVNT_LED_HEARTBEAT, ProcessLEDHeartbeatEcent } }; /*!< Allocation between event type and handler function*/

void EventHandler_HandleEvent(void) {
	EVNT_HandleEvent(evtAlloc, sizeof(evtAlloc));
}

void ProcessInitEvet(void) {
	BUZ_Beep(250,600);
	for (int i = 0; i < 3; i++) {
		LED2_On();
		WAIT1_Waitms(100);
		LED2_Off();
		WAIT1_Waitms(100);
	}
}
void ProcessSW1Event(void) {
	CLS1_SendStr("S2 Pressed\r\n",CLS1_GetStdio()->stdOut);
}

void ProcessLEDHeartbeatEcent(void) {

	LED1_On();
	WAIT1_Waitms(100);
	LED1_Off();

}
