/*
 * RANDOMBehavior.c
 *
 *  Created on: 18.05.2015
 *      Author: Cyrill
 */

#include "RANDOMBehavior.h"
#include "FRTOS1.h"
#include "../../Common/ShellQueue.h"
#include "../../Common/Drive.h"

#define RANDOM_INTEVAL_MS 2500

static volatile int supressed = 0;
static volatile TickType_t lastExecutionTime = 0;

int RANDOMTakeControl() {
	return lastExecutionTime + RANDOM_INTEVAL_MS <  xTaskGetTickCount();
}
void RANDOMSupress() {
	supressed = 1;
}

void Finalize(void) {
	lastExecutionTime = xTaskGetTickCount();
	DRV_SetSpeed(0, 0);
}

void RANDOMAction() {
	supressed = 0;

	int counter = 0;
	SQUEUE_SendString("Random Turn...\r\n");
	DRV_SetSpeed(3000, -3000);
	for (counter = 0; counter < 250; counter++) {
		if (supressed) {
			Finalize();
			return;
		}
		FRTOS1_vTaskDelay(1 / portTICK_RATE_MS);
	}
	Finalize();
}

void RANDOMInit(void) {
	lastExecutionTime = xTaskGetTickCount();
}
