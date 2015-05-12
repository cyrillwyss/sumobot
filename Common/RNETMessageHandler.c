/*
 * RNETMessageHandler.c
 *
 *  Created on: 05.05.2015
 *      Author: Cyrill
 */

#include "RNETMessageHandler.h"
#include "RNet_App.h"

static volatile int enabled = 0;
static volatile int speed = 0;
static volatile int steering = 0;

uint8_t RNETMH_HandleMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data,
		RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet) {

	uint8_t val;

	(void) size;
	(void) packet;
	if (size < 1 || data[0] != COMM_MAGICNUMBER) {
		return ERR_OK;
	}
	switch (type) {
	case RAPP_MSG_TYPE_ONOFF: /* generic data message */
		*handled = TRUE;
		if (size == 2) {
			enabled = data[1];
			if (!enabled) {
				speed = 0;
				steering = 0;
			}
		}
		return ERR_OK;
	case RAPP_MSG_TYPE_JOYSTICK_XY:
		*handled = TRUE;
		if (size == 3) {
			speed = (int8_t)data[1];
			steering = -(int8_t)data[2];
		}
		break;
	default: /*! \todo Handle your own messages here */
		break;
	} /* switch */
	return ERR_OK;
}

int RNETMH_getEnabled(void) {
	return enabled;
}

int RNETMH_getSPeedVal(void) {
	return speed;
}

int RNETMH_getSteeringVal(void) {
	return steering;
}
