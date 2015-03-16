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
#include "EventHandler.h"
#include "../../Common/Timer.h"
#include "Cpu.h"
#include "../../Common/Mealy.h"
#include "../../Common/Platform.h"
#include "../../Common/Keys.h"


void mainController_run(void) {

	PL_Init();

	TMR_Init();
	KEY_EnableInterrupts();

	EVNT_SetEvent(EVNT_INIT);

	while(1)
	{

	//	KEY_Scan();

		MEALY_Step();

		//EventHandler_HandleEvent();

		WAIT1_Waitms(20);
	}


}

