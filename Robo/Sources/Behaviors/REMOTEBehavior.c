/*
 * REMOTEBehavior.c
 *
 *  Created on: 05.05.2015
 *      Author: Cyrill
 */

#include "REMOTEBehavior.h"

static volatile int supressed = 0;

int REMOTETakeControl(void) {
	return false;
}
void REMOTESupress(void) {
	supressed = 1;

}

static void Finalize(void) {
	DRV_SetSpeed(0, 0);
}

void REMOTEAction(void) {
	supressed = 0;

	SQUEUE_SendString("Remote Control Enabled...");
	while (!supressed && REMOTETakeControl()) {
			FRTOS1_vTaskDelay(1 / portTICK_RATE_MS);
	}
	Finalize();
}

