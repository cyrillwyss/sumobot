/*
 * EventHandler.c
 *
 *  Created on: 10.03.2015
 *      Author: Cyrill
 */
#include "EventHandler.h"
#include "../../Common/Led.h"
#include "WAIT1.h"
#include "../../Common/Mealy.h"
#include "CLS1.h"

void ProcessInitEvet(void);
void ProcessSW1Event(void);
void ProcessSW2Event(void);
void ProcessSW3Event(void);
void ProcessSW4Event(void);
void ProcessSW5Event(void);
void ProcessSW6Event(void);
void ProcessSW7Event(void);
void ProcessLEDHeartbeatEcent(void);

EventAllocation evtAlloc[] = { { EVNT_INIT, ProcessInitEvet }, {
		EVNT_SW1_PRESSED, ProcessSW1Event },
		{ EVNT_SW2_PRESSED, ProcessSW2Event }, { EVNT_SW3_PRESSED,
				ProcessSW3Event }, { EVNT_SW4_PRESSED, ProcessSW4Event }, {
				EVNT_SW5_PRESSED, ProcessSW5Event }, { EVNT_SW6_PRESSED,
				ProcessSW6Event }, { EVNT_SW7_PRESSED, ProcessSW7Event }, {
				EVNT_LED_HEARTBEAT, ProcessLEDHeartbeatEcent } }; /*!< Allocation between event type and handler function*/

void EventHandler_HandleEvent(void) {
	EVNT_HandleEvent(evtAlloc, sizeof(evtAlloc));
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

	CLS1_SendStr("A Pressed\r\n", CLS1_GetStdio()->stdOut);
	LED1_On();

}
void ProcessSW2Event(void) {
	CLS1_SendStr("B Pressed\r\n", CLS1_GetStdio()->stdOut);
	LED1_Off();
}
void ProcessSW3Event(void) {
	CLS1_SendStr("C Pressed\r\n", CLS1_GetStdio()->stdOut);

}
void ProcessSW4Event(void) {
	CLS1_SendStr("D Pressed\r\n", CLS1_GetStdio()->stdOut);

}
void ProcessSW5Event(void) {
	CLS1_SendStr("E Pressed\r\n", CLS1_GetStdio()->stdOut);

}
void ProcessSW6Event(void) {
	CLS1_SendStr("F Pressed\r\n", CLS1_GetStdio()->stdOut);

}
void ProcessSW7Event(void) {
	CLS1_SendStr("Joystick Pressed\r\n", CLS1_GetStdio()->stdOut);

}
void ProcessLEDHeartbeatEcent(void) {

	LED2_On();
	WAIT1_Waitms(100);
	LED2_Off();

}
