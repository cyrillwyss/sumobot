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
#include "../../Common/ShellQueue.h"
#include "../../Common/Reflectance.h"

void ProcessInitEvet(void);
void ProcessSW1Event(void);
void ProcessSW1EventLong(void);
void ProcessSW1EventReleased(void);
void ProcessLEDHeartbeatEcent(void);
void TurnOffHeartBeat(TRG_CallBackDataPtr data);
void SendStringToUSB(char* string);

EventAllocation evtAlloc[] = { { EVNT_INIT, ProcessInitEvet }, {
		EVNT_SW1_PRESSED, ProcessSW1Event },{
				EVNT_SW1_LPRESSED, ProcessSW1EventLong },{
						EVNT_SW1_RELEASED, ProcessSW1EventReleased },{
				EVNT_LED_HEARTBEAT, ProcessLEDHeartbeatEcent } }; /*!< Allocation between event type and handler function*/

void EventHandler_HandleEvent(void) {
	EVNT_HandleEvent(evtAlloc, sizeof(evtAlloc));
}

void SendStringToUSB(char* string){
#if PL_HAS_SHELL_QUEUE
	SQUEUE_SendString(string);
#else
	CLS1_SendStr(string, CLS1_GetStdio()->stdOut);
#endif
}

void ProcessInitEvet(void) {
	SendStringToUSB("Hello from Fat Bastard\r\n" );
	BUZ_Beep(250,600);
	for (int i = 0; i < 3; i++) {
		LED2_On();
		WAIT1_Waitms(100);
		LED2_Off();
		WAIT1_Waitms(100);
	}
}
void ProcessSW1Event(void) {
	SendStringToUSB("S2 Pressed\r\n" );
	LED2_On();
}
void ProcessSW1EventLong(void){
	SendStringToUSB("S2 Long Pressed\r\n" );
	REF_StartStopCallibration();
	LED2_Off();
}
void ProcessSW1EventReleased(void){
	SendStringToUSB("S2 Released\r\n" );

}
void ProcessLEDHeartbeatEcent(void) {
	LED1_On();
	TRG_SetTrigger(TRG_HEARTBEAT_OFF,100/ TRG_TICKS_MS,TurnOffHeartBeat,NULL);
}

void TurnOffHeartBeat(TRG_CallBackDataPtr data){
	LED1_Off();
}

