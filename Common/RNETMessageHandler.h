/*
 * RNETMessageHandler.h
 *
 *  Created on: 05.05.2015
 *      Author: Cyrill
 */

#ifndef RNETMESSAGEHANDLER_H_
#define RNETMESSAGEHANDLER_H_
#include "Platform.h"
#include "RNet_AppConfig.h"
#include "RPHY.h"
#include "RNWK.h"

uint8_t RNETMH_HandleMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet);

int RNETMH_getEnabled(void);

int RNETMH_getSPeedVal(void);

int RNETMH_getSteeringVal(void);

int RNETMH_getWhiteLineVal(void);


#endif /* RNETMESSAGEHANDLER_H_ */
