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
#include "../../Common/Accel.h"
#include "../../Common/ShellQueue.h"
#include "Behaviors/RANDOMBehavior.h"
#include "RNET1.h"

static portTASK_FUNCTION(Main, pvParameters) {
	KEY_EnableInterrupts();
	EVNT_SetEvent(EVNT_INIT);
	ACCEL_LowLevelInit();
	RNET1_SetChannel(6);
	if(ACCEL_Enable()!=ERR_OK)
	{
		SQUEUE_SendString("Acc. Enabling failed!!!!");
	}
	int counter=0;
	for (;;) {
		EventHandler_HandleEvent();
		counter++;
		if(counter==10)
		{
			EVNT_SetEvent(EVNT_LED_HEARTBEAT);
			counter=0;
		}
		FRTOS1_vTaskDelay(50 / portTICK_RATE_MS);
	}
}

void mainController_run(void) {
	PL_Init();
	BPinit();

	//BehaviorT forward={FORWARDAction,FORWARDSupress,FORWARDTakeControl};
	BehaviorT whiteLine={WHITELINEInit,WHITELINEAction,WHITELINESupress,WHITELINETakeControl};
	BehaviorT search={SearchInit,SEARCHAction,SEARCHSupress,SEARCHTakeControl};
	BehaviorT attack={ATTACKInit,ATTACKAction,ATTACKSupress,ATTACKTakeControl};
	BehaviorT remote={REMOTEInit,REMOTEAction,REMOTESupress,REMOTETakeControl};
	BehaviorT emergencyStop={EMERGENCYInit,EMERGENCYSTOPAction,EMERGENCYSTOPSupress,EMERGENCYSTOPTakeControl};

	BehaviorT randomTurn={RANDOMInit,RANDOMAction,RANDOMSupress,RANDOMTakeControl};

	BehaviorT behaviors[]={search,attack,remote,whiteLine};

	BPsetBehaviors(behaviors,4);





	 if (FRTOS1_xTaskCreate(Main, (signed portCHAR *)"MAIN", configMINIMAL_STACK_SIZE, NULL, 1, NULL) != pdPASS) {
	    for(;;){} /* error */
	  }
	 RTOS_Run();

}

