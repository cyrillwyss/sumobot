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
#include "../../Common/ShellQueue.h"
#include "RApp.h"
#include "../../Common/RNet_AppConfig.h"
#include "../../Common/RNet_App.h"
#include "RNWK.h"
#include "RPHY.h"
#include "AD1.h"


void ProcessInitEvet(void);
void ProcessSW1Event(void);
void ProcessSW2Event(void);
void ProcessSW3Event(void);
void ProcessSW4Event(void);
void ProcessSW5Event(void);
void ProcessSW6Event(void);
void ProcessSW7Event(void);
void ProcessSW1EventLong(void);
void ProcessSW2EventLong(void);
void ProcessSW3EventLong(void);
void ProcessSW4EventLong(void);
void ProcessSW5EventLong(void);
void ProcessSW6EventLong(void);
void ProcessSW7EventLong(void);
void ProcessSW1EventReleased(void);
void ProcessSW2EventReleased(void);
void ProcessSW3EventReleased(void);
void ProcessSW4EventReleased(void);
void ProcessSW5EventReleased(void);
void ProcessSW6EventReleased(void);
void ProcessSW7EventReleased(void);
void ProcessLEDHeartbeatEcent(void);
void SendStringToUSB(char* string);
void ProcessJoystick(void);
static uint8_t APP_GetXY(uint16_t *x, uint16_t *y, int8_t *x8, int8_t *y8);
static uint16_t midPointX, midPointY;

EventAllocation evtAlloc[] = { { EVNT_INIT, ProcessInitEvet }, {
		EVNT_SW1_PRESSED, ProcessSW1Event },
		{ EVNT_SW2_PRESSED, ProcessSW2Event }, { EVNT_SW3_PRESSED,
				ProcessSW3Event }, { EVNT_SW4_PRESSED, ProcessSW4Event }, {
				EVNT_SW5_PRESSED, ProcessSW5Event }, { EVNT_SW6_PRESSED,
				ProcessSW6Event }, { EVNT_SW7_PRESSED, ProcessSW7Event },

		{ EVNT_SW1_LPRESSED, ProcessSW1EventLong }, { EVNT_SW2_LPRESSED,
				ProcessSW2EventLong },
		{ EVNT_SW3_LPRESSED, ProcessSW3EventLong }, { EVNT_SW4_LPRESSED,
				ProcessSW4EventLong },
		{ EVNT_SW5_LPRESSED, ProcessSW5EventLong }, { EVNT_SW6_LPRESSED,
				ProcessSW6EventLong },
		{ EVNT_SW7_LPRESSED, ProcessSW7EventLong }, { EVNT_SW1_RELEASED,
				ProcessSW1EventReleased }, { EVNT_SW2_RELEASED,
				ProcessSW2EventReleased }, { EVNT_SW3_RELEASED,
				ProcessSW3EventReleased }, { EVNT_SW4_RELEASED,
				ProcessSW4EventReleased }, { EVNT_SW5_RELEASED,
				ProcessSW5EventReleased }, { EVNT_SW6_RELEASED,
				ProcessSW6EventReleased }, { EVNT_SW7_RELEASED,
				ProcessSW7EventReleased }, { EVNT_PROCESS_JOYSTICK,
				ProcessJoystick }, { EVNT_LED_HEARTBEAT,
				ProcessLEDHeartbeatEcent } }; /*!< Allocation between event type and handler function*/

void EventHandler_HandleEvent(void) {
	EVNT_HandleEvent(evtAlloc, sizeof(evtAlloc));
}

void SendStringToUSB(char* string) {
#if PL_HAS_SHELL_QUEUE
	SQUEUE_SendString(string);
#else
	CLS1_SendStr(string, CLS1_GetStdio()->stdOut);
#endif
}

static uint8_t enabled = 0;

void sendENabled() {
	uint8_t data[2];
	data[0]=COMM_MAGICNUMBER;
	data[1] = enabled;
	RAPP_SendPayloadDataBlock(data, sizeof(data), RAPP_MSG_TYPE_ONOFF, DEST_ADDR_ROBO,
	RPHY_PACKET_FLAGS_NONE);
}

void sendJoystickData(uint8_t x, uint8_t y) {

	uint8_t data[3];
	data[0]=COMM_MAGICNUMBER;
	data[1] = x;
	data[2] = y;

	RAPP_SendPayloadDataBlock(data, sizeof(data), RAPP_MSG_TYPE_JOYSTICK_XY, DEST_ADDR_ROBO,
	RPHY_PACKET_FLAGS_NONE);

}

void ProcessInitEvet(void) {

	APP_GetXY(&midPointX, &midPointY, NULL, NULL);
	SendStringToUSB("Hello from FRDM\r\n");
	for (int i = 0; i < 3; i++) {
		LED2_On();
		WAIT1_Waitms(100);
		LED2_Off();
		WAIT1_Waitms(100);
	}
}
void ProcessSW1Event(void) {

	SendStringToUSB("A Pressed\r\n");
	enabled = 1;
	sendENabled();
	LED2_On();

}
void ProcessSW2Event(void) {
	SendStringToUSB("B Pressed\r\n");
	enabled = 0;
	sendENabled();
	LED2_Off();
}
void ProcessSW3Event(void) {
	SendStringToUSB("C Pressed\r\n");

}
void ProcessSW4Event(void) {
	SendStringToUSB("D Pressed\r\n");

}
void ProcessSW5Event(void) {
	SendStringToUSB("E Pressed\r\n");

}
void ProcessSW6Event(void) {
	SendStringToUSB("F Pressed\r\n");

}
void ProcessSW7Event(void) {
	SendStringToUSB("Joystick Pressed\r\n");

}
void ProcessSW1EventLong(void) {
	SendStringToUSB("A Long Pressed\r\n");
}
void ProcessSW2EventLong(void) {
	SendStringToUSB("B Long Pressed\r\n");
}
void ProcessSW3EventLong(void) {
	SendStringToUSB("C Long Pressed\r\n");
}
void ProcessSW4EventLong(void) {
	SendStringToUSB("D Long Pressed\r\n");
}
void ProcessSW5EventLong(void) {
	SendStringToUSB("E Long Pressed\r\n");
}
void ProcessSW6EventLong(void) {
	SendStringToUSB("F Long Pressed\r\n");
}
void ProcessSW7EventLong(void) {
	SendStringToUSB("Joystick Long Pressed\r\n");
}
void ProcessSW1EventReleased(void) {
	SendStringToUSB("A Released\r\n");
}
void ProcessSW2EventReleased(void) {
	SendStringToUSB("B Released\r\n");
}
void ProcessSW3EventReleased(void) {
	SendStringToUSB("C Released\r\n");
}
void ProcessSW4EventReleased(void) {
	SendStringToUSB("D Released\r\n");
}
void ProcessSW5EventReleased(void) {
	SendStringToUSB("E Released\r\n");
}
void ProcessSW6EventReleased(void) {
	SendStringToUSB("F Released\r\n");
}
void ProcessSW7EventReleased(void) {
	SendStringToUSB("Joystick Released\r\n");
}

void ProcessJoystick(void) {
	if (enabled) {

		int16_t x, y;
		int8_t x8, y8;

		APP_GetXY(&x, &y, &x8, &y8);

		sendJoystickData(x8, y8);
	}
}

void ProcessLEDHeartbeatEcent(void) {
	LED1_Neg();
}

static int8_t ToSigned8Bit(uint16_t val, bool isX) {
	int32_t tmp;

	if (isX) {
		tmp = (int32_t) val - midPointX;
	} else {
		tmp = (int32_t) val - midPointY;
	}
	if (tmp > 0) {
		tmp = (tmp * 128) / 0x7fff;
	} else {
		tmp = (-tmp * 128) / 0x7fff;
		tmp = -tmp;
	}
	if (tmp < -128) {
		tmp = -128;
	} else if (tmp > 127) {
		tmp = 127;
	}
	return (int8_t) tmp;
}

static uint8_t APP_GetXY(uint16_t *x, uint16_t *y, int8_t *x8, int8_t *y8) {
	uint8_t res;
	uint16_t values[2];

	res = AD1_Measure(TRUE);
	if (res != ERR_OK) {
		return res;
	}
	res = AD1_GetValue16(&values[0]);
	if (res != ERR_OK) {
		return res;
	}
	if (x != NULL) {
		*x = values[0];
	}
	if (y != NULL) {
		*y = values[1];
	}
	/* transform into -128...127 with zero as mid position */
	if (x8 != NULL) {
		*x8 = ToSigned8Bit(values[0], TRUE);
	}
	if (y8 != NULL) {
		*y8 = ToSigned8Bit(values[1], FALSE);
	}
	return ERR_OK;
}
