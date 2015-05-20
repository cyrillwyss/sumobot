/*
 * ATTACKBehavior.c
 *
 *  Created on: 04.05.2015
 *      Author: Cyrill
 */

#include "ATTACKBehavior.h"
#include "../../Common/Ultrasonic.h"
#include "../../Common/Drive.h"
#include "FRTOS1.h"
#include "../../Common/ShellQueue.h"

static volatile int supressed = 0;

int ATTACKTakeControl(void) {
	uint16_t distance = US_GetDistance();
	return distance <= 70;
}
void ATTACKSupress(void) {
	supressed = 1;
}

void ATTACKInit(void){

}

static void Finalize(void) {
	DRV_SetSpeed(0, 0);
}

void ATTACKAction(void) {
	supressed = 0;
	int counter = 0;
	int lostCounter = 150;
	SQUEUE_SendString("Attacking...\r\n");

	DRV_SetSpeed(0, 0);

	for (counter = 0; counter < 50; counter++) {
		if (supressed) {
			Finalize();
			return;
		}
		FRTOS1_vTaskDelay(1 / portTICK_RATE_MS);
	}

	DRV_SetSpeed(6000, 6000);

	while (!supressed && lostCounter > 0) {
		if (!ATTACKTakeControl()) {
			lostCounter--;
		} else {
			lostCounter = 90;
		}

		FRTOS1_vTaskDelay(1 / portTICK_RATE_MS);
	}
	Finalize();
}
