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
#include "FRTOS1.h"
#include "../../Common/RTOS.h"
#include "../../Common/Keys.h"
#include "BehaviorProgramming.h"
#include "Behaviors/FORWARDbehavior.h"
#include "Behaviors/WhiteLineBehavior.h"
#include "Behaviors/ATTACKBehavior.h"
#include "Behaviors/SEARCHBehavior.h"
#include "Behaviors/EMERGENCYSTOPBehavior.h"
#include "Behaviors/REMOTEBehavior.h"

static portTASK_FUNCTION(Main, pvParameters) {
	KEY_EnableInterrupts();

	EVNT_SetEvent(EVNT_INIT);
	for (;;) {
		EventHandler_HandleEvent();

		FRTOS1_vTaskDelay(50 / portTICK_RATE_MS);
	}
}

void mainController_run(void) {
	PL_Init();
	BPinit();

	//BehaviorT forward={FORWARDAction,FORWARDSupress,FORWARDTakeControl};
	BehaviorT whiteLine={WHITELINEAction,WHITELINESupress,WHITELINETakeControl};
	BehaviorT search={SEARCHAction,SEARCHSupress,SEARCHTakeControl};
	BehaviorT attack={ATTACKAction,ATTACKSupress,ATTACKTakeControl};
	BehaviorT remote={REMOTEAction,REMOTESupress,REMOTETakeControl};
	BehaviorT emergencyStop={EMERGENCYSTOPAction,EMERGENCYSTOPSupress,EMERGENCYSTOPTakeControl};

	BehaviorT behaviors[]={search,attack,whiteLine,emergencyStop,remote};

	BPsetBehaviors(behaviors,5);





	 if (FRTOS1_xTaskCreate(Main, (signed portCHAR *)"MAIN", configMINIMAL_STACK_SIZE, NULL, 1, NULL) != pdPASS) {
	    for(;;){} /* error */
	  }
	 RTOS_Run();

}

