/*
 * EMERGENCYSTOPBehavior.c
 *
 *  Created on: 05.05.2015
 *      Author: Cyrill
 */

#include "EMERGENCYSTOPBehavior.h"

static volatile int supressed = 0;

int EMERGENCYSTOPTakeControl(void) {
	return false;
}
void EMERGENCYSTOPSupress(void) {
	supressed = 1;

}

static void Finalize(void) {
	DRV_SetSpeed(0, 0);
}

void EMERGENCYSTOPAction(void) {
	supressed = 0;

	SQUEUE_SendString("Emergency Stop!");
	DRV_SetSpeed(0, 0);
	while (!supressed && EMERGENCYSTOPTakeControl()) {
			FRTOS1_vTaskDelay(1 / portTICK_RATE_MS);
	}
	Finalize();
}
