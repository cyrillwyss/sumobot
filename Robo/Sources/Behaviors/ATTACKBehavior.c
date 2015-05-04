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
	uint16_t distance=US_GetDistance();
	return distance>0&&distance<120;
}
void ATTACKSupress(void) {
	supressed = 1;
}

static void Finalize(void){
	DRV_SetSpeed(0, 0);
}

void ATTACKAction(void) {
	supressed = 0;
	int counter = 0;
	SQUEUE_SendString("Attacking...");
	while (!supressed&&ATTACKTakeControl()) {
		DRV_SetSpeed(2000, 2000);

		FRTOS1_vTaskDelay(1 / portTICK_RATE_MS);
	}
	Finalize();
}
