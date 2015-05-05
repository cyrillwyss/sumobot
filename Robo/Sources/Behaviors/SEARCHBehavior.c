/*
 * SEARCHBehavior.c
 *
 *  Created on: 04.05.2015
 *      Author: Cyrill
 */
#include "SEARCHBehavior.h"
#include "FRTOS1.h"
#include "../../Common/Drive.h"
#include "../../Common/ShellQueue.h"

static volatile int supressed = 0;

int SEARCHTakeControl(void) {
	return 1;
}
void SEARCHSupress(void) {
	supressed = 1;
}
static void Finalize(void) {
	DRV_SetSpeed(0, 0);
}
void SEARCHAction(void) {

	supressed = 0;
	int counter = 0;
	SQUEUE_SendString("Searching...");
	DRV_SetSpeed(3000, -3000);
	while (!supressed) {
		FRTOS1_vTaskDelay(1 / portTICK_RATE_MS);
	}
	Finalize();
}
