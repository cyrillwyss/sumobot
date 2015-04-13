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
#include "CLS1.h"
#include "FRTOS1.h"
#include "../../Common/RTOS.h"
#include "../../Common/Sem.h"



static portTASK_FUNCTION(Main, pvParameters) {
	KEY_EnableInterrupts();

	EVNT_SetEvent(EVNT_INIT);
	for (;;) {
		KEY_Scan();
		EventHandler_HandleEvent();

		FRTOS1_vTaskDelay(50 / portTICK_RATE_MS);
	}
}

void mainController_run(void) {

	PL_Init();

	 if (FRTOS1_xTaskCreate(Main, (signed portCHAR *)"MAIN", configMINIMAL_STACK_SIZE, NULL, 1, NULL) != pdPASS) {
	    for(;;){} /* error */
	  }
	 SEM_Init();
	 RTOS_Run();

}

