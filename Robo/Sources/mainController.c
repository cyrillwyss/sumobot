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
#include "../../Common/Platform.h"
#include "EventHandler.h"
#include "CLS1.h"


void mainController_run(void) {
	PL_Init();

	TMR_Init();

	EVNT_SetEvent(EVNT_INIT);

	CLS1_SendStr("Hello from Robot\r\n",CLS1_GetStdio()->stdOut);


	while(1)
	{
		EventHandler_HandleEvent();
	}

}

