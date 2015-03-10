/*
 * mainController.c
 *
 *  Created on: 24.02.2015
 *      Author: Cyrill
 */

#include "mainController.h"
#include "WAIT1.h"
#include "../../Common/Led.h"
#include "../../Common/Event.h"
#include "../../Common/Timer.h"
#include "EventHandler.h"

void mainController_run(void) {
	LED_Init();
	EVNT_Init();
	TMR_Init();

	EVNT_SetEvent(EVNT_INIT);

	while(1)
	{
		EventHandler_HandleEvent();
	}

}

