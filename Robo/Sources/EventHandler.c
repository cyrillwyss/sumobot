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
#include "../../Common/Trigger.h"

void ProcessInitEvet(void);
void ProcessSW1Event(void);
void ProcessSW1EventLong(void);
void ProcessSW1EventReleased(void);
void ProcessLEDHeartbeatEcent(void);
void TurnOffHeartBeat(TRG_CallBackDataPtr data);

EventAllocation evtAlloc[] = { { EVNT_INIT, ProcessInitEvet }, {
		EVNT_SW1_PRESSED, ProcessSW1Event },{
				EVNT_SW1_LPRESSED, ProcessSW1EventLong },{
						EVNT_SW1_RELEASED, ProcessSW1EventReleased }, {
				EVNT_LED_HEARTBEAT, ProcessLEDHeartbeatEcent } }; /*!< Allocation between event type and handler function*/

void EventHandler_HandleEvent(void) {
	EVNT_HandleEvent(evtAlloc, sizeof(evtAlloc));
}

void ProcessInitEvet(void) {
	CLS1_SendStr("Hello from Fat Bastard\r\n",CLS1_GetStdio()->stdOut);
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
	LED2_On();
}
void ProcessSW1EventLong(void){
	CLS1_SendStr("S2 Long Pressed\r\n",CLS1_GetStdio()->stdOut);
	LED2_Off();
}
void ProcessSW1EventReleased(void){
	CLS1_SendStr("S2 Released\r\n",CLS1_GetStdio()->stdOut);

}
void ProcessLEDHeartbeatEcent(void) {
	LED1_On();
	TRG_SetTrigger(TRG_HEARTBEAT_OFF,100/ TRG_TICKS_MS,TurnOffHeartBeat,NULL);
}

void TurnOffHeartBeat(TRG_CallBackDataPtr data){
	LED1_Off();
}
