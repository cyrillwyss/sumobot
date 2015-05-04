/*
 * WhiteLineBehavior.c
 *
 *  Created on: 21.04.2015
 *      Author: Cyrill
 */

#include "WhiteLineBehavior.h"
#include "../../Common/Reflectance.h"
#include "../../Common/Drive.h"
#include "FRTOS1.h"
#include "../../Common/ShellQueue.h"

static volatile int supressed = 0;

int WHITELINETakeControl(void) {
	return REF_GetLineValue() > 0;
}
void WHITELINESupress(void) {
	supressed = 1;

}

static void Finalize(void) {
	DRV_SetSpeed(0, 0);

}

void WHITELINEAction(void) {
	supressed = 0;
	int counter = 0;

	SQUEUE_SendString("White line detected...");
	while (!supressed && WHITELINETakeControl()) {
		DRV_SetSpeed(-2000, -2000);

		for (counter = 0; counter < 500; counter++) {
			if (supressed) {
				Finalize();
				return;
			}
			FRTOS1_vTaskDelay(1 / portTICK_RATE_MS);
		}

		DRV_SetSpeed(2000, -2000);

		for (counter = 0; counter < 500; counter++) {
			if (supressed) {
				Finalize();
				return;
			}
			FRTOS1_vTaskDelay(1 / portTICK_RATE_MS);
		}
		Finalize();
	}
}
