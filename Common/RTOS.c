/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_HAS_RTOS
#include "RTOS.h"
#include "FRTOS1.h"
#include "LED.h"
#include "Event.h"

static portTASK_FUNCTION(T1, pvParameters) {
	for (;;) {
		LED1_On();
		FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
		LED1_Off();
		FRTOS1_vTaskDelay(900/portTICK_RATE_MS);
	}
}

void RTOS_Run(void) {
	FRTOS1_vTaskStartScheduler();
	/* does usually not return here */
}

void RTOS_Init(void) {
	/*! \todo Add tasks here */
/*	if (FRTOS1_xTaskCreate(T1, (signed portCHAR *)"T1",
			configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
		for (;;) {
		} /* error */
	//}
}

void RTOS_Deinit(void) {
}

#endif /* PL_HAS_RTOS */
