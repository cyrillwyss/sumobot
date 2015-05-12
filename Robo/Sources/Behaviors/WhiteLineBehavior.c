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
	return REF_HadLine();
}
void WHITELINESupress(void) {
	supressed = 1;

}

void WHITELINEInit(void){
	REF_resetHadLine();
}

static void Finalize(void) {
	DRV_SetSpeed(0, 0);
	REF_resetHadLine();
}

void WHITELINEAction(void) {
	supressed = 0;
	int counter = 0;
	SQUEUE_SendString("White line detected...\r\n");

	DRV_SetSpeed(-500, -500);
	for (counter = 0; counter < 50; counter++) {
		if (supressed) {
			Finalize();
			return;
		}
		FRTOS1_vTaskDelay(1 / portTICK_RATE_MS);
	}

	while (!supressed && WHITELINETakeControl()) {

		int sensorVal = REF_GetLineValue();
		int rotation = (2500 - sensorVal) / 5;

		DRV_SetSpeed(-4000, -4000);

		for (counter = 0; counter < 125; counter++) {
			if (supressed) {
				Finalize();
				return;
			}
			FRTOS1_vTaskDelay(1 / portTICK_RATE_MS);
		}

		DRV_SetSpeed(4000, -4000);

		for (counter = 0; counter < 300; counter++) {
			if (supressed) {
				Finalize();
				return;
			}
			FRTOS1_vTaskDelay(1 / portTICK_RATE_MS);
		}
		Finalize();
	}
}
